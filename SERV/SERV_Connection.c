CLIENT SERV_Connect(SERVER server)
{
	CLIENT client;
	int socketSize = sizeof(struct sockaddr_in); // accept wants a pointer to the int size of the sockaddr_in struct (its another one of the realy fucking bone headed design choises that somehow got into the final product eventhough its such a big fucking pain even some of the docs complain about it)
	struct sockaddr_in clientInfo;

	SERV_Log("Waiting for client", LOGGING_CONNECTION);
	client.socket = accept(server.listener, (struct sockaddr *)&clientInfo, &socketSize); // It will hang until a client attempts to connect to the server
	if (client.socket == INVALID_SOCKET)
	{
		exit(1);
	}

	SERV_Log("Recieved connection", LOGGING_CONNECTION);
	setsockopt(client.socket, SOL_SOCKET, SO_RCVTIMEO, (char*)RECIEVE_TIMEOUT, sizeof((char*)RECIEVE_TIMEOUT));
	client.headerLength = recv(client.socket, client.header, MAX_BUFFER_SIZE, NO_SWITCHES); // Get the header from the client
	if (client.headerLength == SOCKET_ERROR)
	{
		exit(1);
	}
	else if (client.headerLength == 0)
	{
		printf(COLOR_ERROR "                         Connection closed\n" COLOR_RESET);
	}

	strcpy(client.ip, inet_ntoa(clientInfo.sin_addr)); 	// Convert back from that byte order bullshit
	client.port = ntohs(clientInfo.sin_port);			// The port needs to be unfucked too

	return client;
}

CLIENT SERV_CloseConnection(CLIENT client)
{
	SERV_Log("Closing connection", LOGGING_CONNECTION);
    if (shutdown(client.socket, 1) == SOCKET_ERROR)	// Tell the client to shut up
    {
    	exit(1);
    }

	SERV_Log("Closing socket", LOGGING_CONNECTION);
    if (closesocket(client.socket) == SOCKET_ERROR) // Just hang up on them
    {
    	exit(1);
    }

	printf("=================================================================\n\n");

    return client;
}