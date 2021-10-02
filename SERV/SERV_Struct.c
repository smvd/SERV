typedef struct
{
	struct sockaddr_in config;
	SOCKET listener;
}SERVER;

typedef struct
{
	int parameterCount;
	char parameters[MAX_PARAMETER_COUNT][2][MAX_BUFFER_SIZE]; // Its a 3D array cuz there are multiple key value pairs

	int headerLength;
	char header[MAX_BUFFER_SIZE];
	char method[MAX_METHOD_SIZE];
	char path[MAX_BUFFER_SIZE];

	char ip[MAX_IP_LENGTH];
	int port;

	SOCKET socket;
}CLIENT;