#ifndef SERV_LOADED
#define SERV_LOADED

    #include <Winsock.h>
    #include <Stdlib.h>
    #include <Stdio.h>
    #include <Time.h>

    #define NO_SWITCHES 0
    #define MAX_BUFFER_SIZE 1024
    #define MAX_IP_LENGTH 16
    #define MAX_PARAMETER_COUNT 5
    #define MAX_METHOD_SIZE 10
    #define RECIEVE_TIMEOUT 100

    #define LOGGING_ERROR 1
    #define LOGGING_CONNECTION 2
    #define LOGGING_SETUP 3
    #define LOGGING_SENDING 4

    #define COLOR_WHITE "\e[37m"
    #define COLOR_RED "\e[31m"
    #define COLOR_BLUE "\e[34m"
    #define COLOR_GREEN "\e[32m"
    #define COLOR_YELLOW "\e[33m"
    #define COLOR_PURPLE "\e[35m"

    #define BUG printf("BUGBUG\n");

    #include "SERV_Struct.c"

    // Core functions
    void SERV_ShutdownServer(); // Shuts down winsock2 and exits
    SERVER SERV_StartServer(char ip[], int port, int maxBacklog); // Setup the listener for the server

    // Connection functions
    CLIENT SERV_Connect(SERVER host); // Wait for a client connection and recieve its header
    CLIENT SERV_CloseConnection(CLIENT client); // Stop the client from sending data and clear the socket

    // Argument functions
    CLIENT SERV_ParseArguments(CLIENT client); // Split the method, path and arguments from the client header
    int SERV_MatchPath(CLIENT client, char path[]); // Match the clients request and the given path
    int SERV_GetParameter(CLIENT client, char key[]); // Check if the client has a parameter matching the key; returns the index

    // Sending functions
    void SERV_SendImage(CLIENT client, char type[], char path[]); // Read an image from disk and send it to the client
    void SERV_SendMP4(CLIENT client, char path[]); // Read an mp4 file from disk and send it to the client
    void SERV_SendRaw(CLIENT client, char data[]); // Send the raw data to the client
    void SERV_SendText(CLIENT client, char text[]); // Build the http header for the text and send it to the client
    void SERV_SendJson(CLIENT client, char json[]); // Build the http header for the json and send it to the client
    void SERV_SendHTML(CLIENT client, char html[]); // Build the http header for the html and send it to the client
    void SERV_BuildHeader(char * buffer, int code, char text[]); // Build a http header from the given code and text
    void SERV_SendStatus(CLIENT client, int code); // Send a header with an error code of the given type
    // All official codes on https://en.wikipedia.org/wiki/List_of_HTTP_status_codes are supported

    // Logging functions
    void SERV_Log(char * message, int type); // Log a message of the given type

    #include "SERV_Core.c"
    #include "SERV_Connection.c"
    #include "SERV_Parameters.c"
    #include "SERV_Sending.c"
    #include "SERV_Logging.c"

#endif