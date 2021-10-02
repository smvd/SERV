CLIENT SERV_Connect(SERVER server)
{
	CLIENT client;
	int socketSize = sizeof(struct sockaddr_in); // accept wants a pointer to the int size of the sockaddr_in struct (its another one of the realy fucking bone headed design choises that somehow got into the final product eventhough its such a big fucking pain even some of the docs complain about it)
	struct sockaddr_in clientInfo;

	printf("\nWaiting for connection...");
	client.socket = accept(server.listener, (struct sockaddr *)&clientInfo, &socketSize); // It will hang until a client attempts to connect to the server
	if (client.socket == INVALID_SOCKET)
	{
		printf("Failed\n");
		exit(1);
	}
	printf("Succes\n");

	printf("Recieving request...");
	setsockopt(client.socket, SOL_SOCKET, SO_RCVTIMEO, (char*)RECIEVE_TIMEOUT, sizeof((char*)RECIEVE_TIMEOUT));
	client.headerLength = recv(client.socket, client.header, MAX_BUFFER_SIZE, NO_SWITCHES); // Get the header from the client
	if (client.headerLength == SOCKET_ERROR)
	{
		printf("Failed\n");
		exit(1);
	}
	else if (client.headerLength == 0)
	{
		printf("Connection closed\n");
	}
	else
	{
		printf("Succes\n");
	}

	strcpy(client.ip, inet_ntoa(clientInfo.sin_addr)); 	// Convert back from that byte order bullshit
	client.port = ntohs(clientInfo.sin_port);			// The port needs to be unfucked too

	return client;
}

CLIENT SERV_CloseConnection(CLIENT client)
{
	printf("Shuttingdown sending...");
    if (shutdown(client.socket, 1) == SOCKET_ERROR)	// Tell the client to shut up
    {
    	printf("Failed\n");
    	exit(1);
    }
    printf("Succes\n");

    printf("Closing socket...");
    if (closesocket(client.socket) == SOCKET_ERROR) // Just hang up on them
    {
    	printf("Failed\n");
    	exit(1);
    }
    printf("Succes\n");

    return client;
}