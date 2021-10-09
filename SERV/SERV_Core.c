SERVER SERV_StartServer(char ip[], int port, int maxBacklog)
{
	// Setup winsock
	SERVER server;
	WSADATA wsaData;

	server.config.sin_family = AF_INET;					// Its a web socket
	server.config.sin_addr.s_addr = inet_addr(ip); 		// Byte order bullshit [big vs little endian]
	server.config.sin_port = htons(port);				// More of that byte order bullshit
	
	SERV_Log("Starting winsock", LOGGING_SETUP);
	if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) 	// Makeword sets the version to 2.2 (the newest)
	{
		exit(1);
	}

	server.listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); // Make a bi-directional, TCP protocol, web socket
	SERV_Log("Making host socket", LOGGING_SETUP);
	if (server.listener == INVALID_SOCKET)
	{
		exit(1);
	}

	SERV_Log("Binding host socket", LOGGING_SETUP);
	if (bind(server.listener, (struct sockaddr *)&server.config, sizeof(server.config)) == SOCKET_ERROR) // Link the socket to the given IP and PORT
	{
		exit(1);
	}

	SERV_Log("Setting up listener", LOGGING_SETUP);
	if (listen(server.listener, maxBacklog) == SOCKET_ERROR) // Set the socket up to recieve connections
	{
		exit(1);
	}

	return server;
}

void SERV_ShutdownServer()
{
	// Cleanup winsock
	SERV_Log("Shuttingdown winsock", LOGGING_SETUP);
    if (WSACleanup() == SOCKET_ERROR)
    {
		if (WSAGetLastError() == 10091)
		{
			SERV_Log("A known error has occured", LOGGING_ERROR);
		}
    	exit(1);
    }
}