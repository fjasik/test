# Test

## 0. General cyber security

If you were part of a red team tasked with breaking into some small company that has zero interest in cyber security, how would you approach the subject?

## 1. JS/TS 

Look at the file `test.ts` in `./js/`.

This looks pretty vanilla. Are there any problems with this code? If there are, propose a refactor / fix / change. Any improvements?

## 2. C++ Scope Exit

Now look at the file `test.cpp` in `./Test/`.

The `EstablishWebsocketConnection` function was taken from a larger `AsyncWebsocket` class, from a side project. It is a fairly correct partial implementation of the WinHttp websocket. The flow is dictated by Microsoft, we have to create a session, open a connection and make a request, all of which create resources that we have to manually manage. Because of early returns, the function ends up repeating the code responsible for closing the handles we’ve opened. What improvement could you suggest? Anything else?

## 3. Classic

What's a buffer overflow?
