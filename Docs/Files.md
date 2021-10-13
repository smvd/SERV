# Files
Currently SERV is spread out over 9 files.

## SERV_Connections.c
`SERV_Connections.c` holds all the functions related to connecting with the client.

```c
CLIENT SERV_Connect(SERVER server);
CLIENT SERV_CloseConnection(CLIENT client);
```

## SERV_Core.c
`SERV_Core.c` holds all the functions related to managing the server.

```c
SERVER SERV_StartServer(char ip[], int port, int MaxBacklog);
void SERV_ShutdownServer();
```

## SERV_Definitions.c
`SERV_Definitions.c` holds all the constant values used by SERV. This is also the place to look for setting configuration values.

## SERV_Logging.c
`SERV_Logging.c` holds all the functions related to loging the actions taken by SERV.

```c
void SERV_Log(char * message, int type);
```

## SERV_Parameters.c
`SERV_Parameters.c` holds all the functions related to handeling the header arguments.

```c
CLIENT SERV_ParseArguments(CLIENT client);
int SERV_GetParameter(CLIENT client, char key[]);
int SERV_MatchPath(CLIENT client, char path[]);
```

## SERV_Prototypes.c
`SERV_Prototypes.c` holds all the prototypes for the functions inside SERV.

## SERV_Sending.c
`SERV_Sending.c` holds all the functions related to sending data to the client.

```c
void SERV_SendRaw(CLIENT client, char data[]);
void SERV_BuildHeader(char * buffer, int code, char text[]);
void SERV_SendStatus(CLIENT client, int code);
void SERV_SendData(CLIENT client, int type, char data[], int isFile);
```

## SERV_Structs.c
`SERV_Structs.c` holds all the structure definitions for SERV.

```c
typedef struct SERVER;
typedef struct CLIENT;
```

## SERV.h
`SERV.h` holds the include statements for the rest of Project SERV.