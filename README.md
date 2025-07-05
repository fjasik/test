# Test

## 0. General cyber security

If you were part of a red team tasked with breaking into some small company that has zero interest in cyber security, how would you approach the subject?

## 1. JS/TS 

This looks pretty vanilla. Are there any problems with this code? If there are, propose a refactor / fix / change.

## 2. C++ Scope Exit

The `EstablishWebsocketConnection` function was taken from a larger `AsyncWebsocket` class, from a side project. It is a fairly correct partial implementation of the WinHttp websocket. The flow is dictated by Microsoft, we have to create a session, open a connection and make a request, all of which create resources that we have to manually manage. Early returns from the function mean we have to repeat code. What improvement could you suggest?
