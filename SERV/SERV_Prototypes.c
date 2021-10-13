void SERV_SendRaw(CLIENT client, char data[]);
void SERV_BuildHeader(char * buffer, int code, char text[]);
void SERV_SendStatus(CLIENT client, int code);
void SERV_SendData(CLIENT client, int type, char data[], int isFile);

SERVER SERV_StartServer(char ip[], int port, int maxBacklog);
void SERV_ShutdownServer();

CLIENT SERV_ParseArguments(CLIENT client);
int SERV_GetParameter(CLIENT client, char key[]);
int SERV_MatchPath(CLIENT client, char path[]);

void SERV_Log(char * message, int type);

CLIENT SERV_Connect(SERVER server);
CLIENT SERV_CloseConnection(CLIENT client);
