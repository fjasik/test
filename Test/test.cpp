#ifdef __APPLE__
    #include "winhttp_mock.h"
#else
    #include <WinSock2.h>
    #include <Windows.h>
    #include <winhttp.h>
#endif

#include <iostream>
#include <string>
#include <vector>

namespace Hydra::Labs::Test {
    namespace AsyncWebsocket {
        void ResetAllFlags();
        void ResetAllHandles();
        void StaticCallback(
            HINTERNET handle,
            DWORD_PTR context,
            DWORD code,
            void* info,
            DWORD length);

        HANDLE connectedEvent;

        HANDLE connectionFailedEvent;
    }

    namespace {
        static constexpr auto kDefaultWebsocketTimeoutMs = 5000;
    }

    static bool EstablishWebsocketConnection(
        const std::wstring& serverName,
        INTERNET_PORT serverPort,
        const std::wstring& path) {
        std::cout << "Attempting to establish connection..." << std::endl;

        AsyncWebsocket::ResetAllFlags();
        AsyncWebsocket::ResetAllHandles();

        HINTERNET session = WinHttpOpen(
            L"AsyncWebsocket/0.1.0",
            WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
            WINHTTP_NO_PROXY_NAME,
            WINHTTP_NO_PROXY_BYPASS,
            WINHTTP_FLAG_ASYNC);
        if (!session) {
            std::cout << "Failed to open WinHttp session: " << GetLastError()
                      << std::endl;
            return false;
        }

        std::wcout << L"Target: " << serverName << L":" << serverPort << path
                   << std::endl;

        HINTERNET connection =
            WinHttpConnect(session, serverName.c_str(), serverPort, NULL);
        if (!connection) {
            std::cout << "Failed to open WinHttp connection: " << GetLastError()
                      << std::endl;

            WinHttpCloseHandle(session);

            return false;
        }

        HINTERNET request = WinHttpOpenRequest(
            connection, L"GET", path.c_str(), NULL, NULL, NULL, 0);
        if (!request) {
            std::cout << "Failed to open WinHttp request: " << GetLastError()
                      << std::endl;

            WinHttpCloseHandle(session);
            WinHttpCloseHandle(connection);

            return false;
        }

#pragma prefast(                                                               \
    suppress : 6387,                                                           \
    "WINHTTP_OPTION_UPGRADE_TO_WEB_SOCKET does not take any arguments")
        auto success = WinHttpSetOption(
            request, WINHTTP_OPTION_UPGRADE_TO_WEB_SOCKET, NULL, 0);
        if (!success) {
            std::cout << "Failed to set websocket upgrade option: "
                      << GetLastError() << std::endl;

            WinHttpCloseHandle(session);
            WinHttpCloseHandle(connection);
            WinHttpCloseHandle(request);

            return false;
        }

        const auto callbackResult = WinHttpSetStatusCallback(
            request,
            AsyncWebsocket::StaticCallback,
            WINHTTP_CALLBACK_FLAG_ALL_COMPLETIONS,
            0);

        if (callbackResult == WINHTTP_INVALID_STATUS_CALLBACK) {
            std::cout << "Failed to set callback: " << GetLastError()
                      << std::endl;

            WinHttpCloseHandle(session);
            WinHttpCloseHandle(connection);
            WinHttpCloseHandle(request);

            return false;
        }

        success = WinHttpSendRequest(
            request,
            WINHTTP_NO_ADDITIONAL_HEADERS,
            0,
            WINHTTP_NO_REQUEST_DATA,
            0,
            0,
            NULL);
        if (!success) {
            std::cout << "Failed to send request: " << GetLastError()
                      << std::endl;

            WinHttpCloseHandle(session);
            WinHttpCloseHandle(connection);
            WinHttpCloseHandle(request);

            return false;
        }

        const std::vector<HANDLE> events = {
            AsyncWebsocket::connectedEvent,
            AsyncWebsocket::connectionFailedEvent,
        };

        enum EventOperation : DWORD {
            WebsocketConnected = WAIT_OBJECT_0,
            WebsocketConnectionFailed,
        };

        const auto result = WaitForMultipleObjects(
            static_cast<DWORD>(events.size()),
            events.data(),
            FALSE,
            kDefaultWebsocketTimeoutMs);

        switch (result) {
        case WebsocketConnected: {
            std::cout << "Websocket is connected" << std::endl;

            WinHttpCloseHandle(session);
            WinHttpCloseHandle(connection);
            WinHttpCloseHandle(request);

            return true;
        }
        case WebsocketConnectionFailed: {
            std::cout << "Websocket connection failed" << std::endl;
            break;
        }
        case WAIT_TIMEOUT: {
            std::cout << "Wait for connection timed out" << std::endl;
            break;
        }
        default: {
            std::cout << "Unexpected wait result when waiting for connection"
                      << std::endl;
            break;
        }
        }

        WinHttpCloseHandle(session);
        WinHttpCloseHandle(connection);
        WinHttpCloseHandle(request);

        return false;
    }

}
