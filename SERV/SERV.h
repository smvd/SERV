#ifndef SERV_LOADED
#define SERV_LOADED

    #include <Winsock.h>
    #include <Stdlib.h>
    #include <Stdio.h>

    #define NO_SWITCHES 0
    #define MAX_BUFFER_SIZE 1024
    #define MAX_IP_LENGTH 16
    #define MAX_PARAMETER_COUNT 5
    #define MAX_METHOD_SIZE 10
    #define RECIEVE_TIMEOUT 100

    #define BUG printf("BUGBUG\n");

    #include "SERV_Struct.c"

    #include "SERV_Core.c"
    #include "SERV_Connection.c"
    #include "SERV_Parameters.c"
    #include "SERV_Sending.c"
    #include "SERV_Error.c"

#endif