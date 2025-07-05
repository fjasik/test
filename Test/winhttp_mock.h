#pragma once

#ifdef __APPLE__

    #include <cstddef>
    #include <cstdint>
    #include <cwchar>

//
// Basic Windows type aliases
//
typedef void* HANDLE;
typedef void* HINTERNET;
typedef unsigned long DWORD;
typedef uintptr_t DWORD_PTR;
typedef wchar_t WCHAR;
typedef WCHAR* LPWSTR;
typedef const WCHAR* LPCWSTR;
typedef unsigned short INTERNET_PORT;
typedef int BOOL;

    #define NULL 0
    #define FALSE 0
    #define TRUE 1

    //
    // Constants used
    //
    #define WINHTTP_ACCESS_TYPE_DEFAULT_PROXY 0
    #define WINHTTP_NO_PROXY_NAME nullptr
    #define WINHTTP_NO_PROXY_BYPASS nullptr
    #define WINHTTP_FLAG_ASYNC 0x10000000
    #define WINHTTP_OPTION_UPGRADE_TO_WEB_SOCKET 114
    #define WINHTTP_CALLBACK_FLAG_ALL_COMPLETIONS 0xFFFFFFFF
    #define WINHTTP_INVALID_STATUS_CALLBACK ((void*)-1)
    #define WINHTTP_NO_ADDITIONAL_HEADERS nullptr
    #define WINHTTP_NO_REQUEST_DATA nullptr

    #define WAIT_OBJECT_0 0x00000000L
    #define WAIT_TIMEOUT 0x00000102L

//
// Stub function declarations
//
inline HINTERNET WinHttpOpen(LPCWSTR, DWORD, LPCWSTR, LPCWSTR, DWORD) {
    return nullptr;
}

inline HINTERNET WinHttpConnect(HINTERNET, LPCWSTR, INTERNET_PORT, DWORD) {
    return nullptr;
}

inline HINTERNET WinHttpOpenRequest(
    HINTERNET, LPCWSTR, LPCWSTR, LPCWSTR, LPCWSTR, LPCWSTR*, DWORD) {
    return nullptr;
}

inline BOOL WinHttpSetOption(HINTERNET, DWORD, void*, DWORD) {
    return TRUE;
}

inline void*
WinHttpSetStatusCallback(HINTERNET,
                         void (*)(HINTERNET, DWORD_PTR, DWORD, void*, DWORD),
                         DWORD,
                         DWORD_PTR) {
    return nullptr;
}

inline BOOL
WinHttpSendRequest(HINTERNET, LPCWSTR, DWORD, void*, DWORD, DWORD, DWORD_PTR) {
    return TRUE;
}

inline BOOL WinHttpCloseHandle(HINTERNET) {
    return TRUE;
}

inline DWORD GetLastError() {
    return 0;
} // dummy error code

inline DWORD WaitForMultipleObjects(DWORD, const HANDLE*, BOOL, DWORD) {
    return WAIT_TIMEOUT;
}

#endif // __APPLE__
