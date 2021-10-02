SERVER SERV_StartServer(char ip[], int port, int maxBacklog)
{
	// Setup winsock
	SERVER server;
	WSADATA wsaData;

	server.config.sin_family = AF_INET; 					// Its a web socket
	server.config.sin_addr.s_addr = inet_addr(ip); 		// Byte order bullshit [big vs little endian]
	server.config.sin_port = htons(port); 					// More of that byte order bullshit
	
	printf("Starting winsock...");
	if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) 	// Makeword sets the version to 2.2 (the newest)
	{
		printf("Failed\n");
		exit(1);
	}
	printf("Succes\n");

	server.listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); // Make a bi-directional, TCP protocol, web socket
	printf("Making host socket...");
	if (server.listener == INVALID_SOCKET)
	{
		printf("Failed\n");
		exit(1);
	}
	printf("Succes\n");

	printf("Binding host socket...");
	if (bind(server.listener, (struct sockaddr *)&server.config, sizeof(server.config)) == SOCKET_ERROR) // Link the socket to the given IP and PORT
	{
		printf("Failed\n");
		exit(1);
	}
	printf("Succes\n");

	printf("Setting up listener...");
	if (listen(server.listener, maxBacklog) == SOCKET_ERROR) // Set the socket up to recieve connections
	{
		printf("Failed\n");
		exit(1);
	}
	printf("Succes\n");


	return server;
}

void SERV_ShutdownServer()
{
	// Cleanup winsock
	printf("Shuttingdown winsock...");
    if (WSACleanup() == SOCKET_ERROR)
    {
    	printf("Failed\n");
		if (WSAGetLastError() == 10091)
		{
			printf("This is a knows issue but there is no fix available yet\n");
		}
    	exit(1);
    }
    printf("Succes\n");
}