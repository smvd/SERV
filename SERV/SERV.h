#ifndef SERV_LOADED
#define SERV_LOADED

    #include <Winsock.h>
    #include <Stdlib.h>
    #include <Stdio.h>
    #include <Time.h>

    #define BUG printf("BUGBUG\n");

    #include "SERV_Definitions.c"
    #include "SERV_Struct.c"
    #include "SERV_Prototypes.c"
    
    #include "SERV_Core.c"
    #include "SERV_Connection.c"
    #include "SERV_Parameters.c"
    #include "SERV_Sending.c"
    #include "SERV_Logging.c"

#endif