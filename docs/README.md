# Project SERV

## Installation
To use SERV you will need to get the source code from the github release page and copy it to the folder your code is stored in. After that its fairly simple just add `-lWS2_32` to your compilation command and add `#include "SERV.c"` to the top of your program.

## Cookbook

## Documentation
```c
SERVER SERV_Setup(char ip[], int port); // Configure the server and start winsock2
void SERV_Shutdown(); // Shuts down winsock2 and exits
CLIENT SERV_ParseArguments(CLIENT client); // Split the method, path and arguments from the client header
HOST SERV_StartServer(SERVER server, int maxBacklog); // Setup the listener for the server
CLIENT SERV_Connect(HOST host); // Wait for a client connection and recieve its header
CLIENT SERV_CloseConnection(CLIENT client); // Stop the client from sending data and clear the socket
int SERV_MatchPath(CLIENT client, char path[]); // Match the clients request and the given path
int SERV_GetParameter(CLIENT client, char key[]); // Check if the client has a parameter matching the key; returns the index
```

```c
void SERV_SendImage(CLIENT client, char type[], char path[]); // Read an image from disk and send it to the client
void SERV_SendMP4(CLIENT client, char path[]); // Read an mp4 file from disk and send it to the client
void SERV_SendRaw(CLIENT client, char data[]); // Send the raw data to the client
void SERV_SendText(CLIENT client, char text[]); // Build the http header for the text and send it to the client
void SERV_SendJson(CLIENT client, char json[]); // Build the http header for the json and send it to the client
void SERV_SendHTML(CLIENT client, char html[]); // Build the http header for the html and send it to the client
void SERV_SendPageNotFound(CLIENT client); // Build a 404 page not found header and send it to the client
void SERV_SendInvalidArguments(CLIENT client); // Build a 400 invalid arguments header and send it to the client
void SERV_SendBadRequest(CLIENT client); // Build a 400 bad request header and send it to the client
void SERV_SendForbidden(CLIENT client); // Build a 403 forbidden header and send it to the client
void SERV_SendUnauthorized(CLIENT client); // Build a 401 unauthorized header and send it to the client
void SERV_SendImATeapot(CLIENT client); // Build a 418 I'm a tea pot header and send it to the client
```