// The comments might include strong language (i mean its still socket programming)

#ifndef SERV_LOADED	// Stop SERV from being loaded multiple times [header guard]
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

CLIENT SERV_ParseArguments(CLIENT client)
{
	char buffer[MAX_BUFFER_SIZE];

	strcpy(buffer, client.header);	// Make a copy of the header to preserve the original

	char * path = strtok(buffer, " ");	// Split it at the first space

	strcpy(client.method, path);

	path = strtok(NULL, " "); // Split it at the second space

	int IncludesParameters = 0;
	
	// Take everything before the first ? (if it exists)
	for (int i = 0; i < (int)strlen(path); i++)
	{
		if (path[i] == '?')
		{
			path[i] = '\0';
			IncludesParameters = 1;
			break;
		}
	}
	
	strcpy(client.path, path);

	if (IncludesParameters) // If we found a '?' in the path we have to parse the arguments
	{
		strcpy(buffer, client.header); // Reset the copy of the header as strtok will have messed it up
		path = strtok(buffer, " ");
		path = strtok(NULL, " ");

		path = strchr(path, '?'); // Read from the first '?'
		++path; // Shift one character over so we dont include the '?'

		strcpy(buffer, path);

		path = strtok(buffer, "&"); // Split the buffer at '&' (the parameter seperator)

		int i = 0;

		while (path != NULL) // Loop until we have parsed every parameter
		{
			strcpy(client.parameters[i][0], path);
			path = strtok(NULL, "&");
			i++;
		}

		client.parameterCount = i;

		// Loop over all the parameters and cut them at '=' to create the key value pairs
		for (int i = 0; i < client.parameterCount; i++)
		{
			strcpy(buffer, client.parameters[i][0]);

			path = strtok(buffer, "=");
			strcpy(client.parameters[i][0], path);

			path = strtok(NULL, "=");
			strcpy(client.parameters[i][1], path);
		}
	}

	return client;
}

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

int SERV_MatchPath(CLIENT client, char path[])
{
	// Match path with request
	if (strcasecmp(client.path, path) == 0) // Yes it returs 0 when succesfull i swear they where drunk while making the function
	{
		return 1;
	}
	
	return 0;
}

void SERV_SendRaw(CLIENT client, char data[])
{
	printf("Sending data...");
	if (send(client.socket, data, strlen(data), NO_SWITCHES) == SOCKET_ERROR) // Send the client the raw bytes
	{
		printf("Failed\n");
		exit(1);
	}
	printf("Succes\n");
}

// The next functions are just plain header building and then calling SERV_SendRaw(0) to throw it at the client
void SERV_SendText(CLIENT client, char text[])
{
	// Send text to client
	char buffer[MAX_BUFFER_SIZE];

	sprintf(buffer, "HTTP/1.1 200 OK\nConnection: close\nContent-Type: text\nContent-Length: %d\n\n%s\r\n\r\n", (int)strlen(text), text);

	SERV_SendRaw(client, buffer);
}

void SERV_SendJson(CLIENT client, char json[])
{
	// Send json to client
	char buffer[MAX_BUFFER_SIZE];

	sprintf(buffer, "HTTP/1.1 200 OK\nConnection: close\nContent-Type: text/json\nContent-Length: %d\n\n%s\r\n\r\n", (int)strlen(json), json);

	SERV_SendRaw(client, buffer);
}

void SERV_SendHTML(CLIENT client, char html[])
{
	// Send html to client
	char buffer[MAX_BUFFER_SIZE];

	sprintf(buffer, "HTTP/1.1 200 OK\nConnection: close\nContent-Type: text/html\nContent-Length: %d\n\n%s\r\n\r\n", (int)strlen(html), html);

	SERV_SendRaw(client, buffer);
}

void SERV_SendPageNotFound(CLIENT client)
{
	SERV_SendRaw(client, "HTTP/1.1 404 Not Found\nConnection: close\nContent-Length: 14\n\nPage Not Found\r\n\r\n");
}

void SERV_SendInvalidArguments(CLIENT client)
{
	SERV_SendRaw(client, "http/1.1 400 Invalid Arguments\nConnection: close\nContent-Length: 17\n\nInvalid Arguments\r\n\r\n");
}

void SERV_SendBadRequest(CLIENT client)
{
	SERV_SendRaw(client, "http/1.1 400 Bad Request\nConnection: close\r\n\r\n");
}

void SERV_SendForbidden(CLIENT client)
{
	SERV_SendRaw(client, "http/1.1 403 Forbidden\nConnection: close\nCentent-Length: 15\n\nForbidden\r\n\r\n");
}

void SERV_SendUnauthorized(CLIENT client)
{
	SERV_SendRaw(client, "http/1.1 401 Unauthorized\nConnection: close\nCentent-Length: 12\n\nUnauthorized\r\n\r\n");
}

void SERV_SendImATeapot(CLIENT client)
{
	SERV_SendRaw(client, "http/1.1 418 I'm A Tea Pot\nConnection: close\nContent-Lenght: 13\n\nI'm A Tea Pot\r\n\r\n");
}

int SERV_GetParameter(CLIENT client, char key[])
{
	// Loop over each parameter
	for (int i = 0; i < client.parameterCount; i++)
	{
		// If it includes the key
		if (strcasecmp(client.parameters[i][0], key) == 0)
		{
			return i;

			break;
		}
	}

	return -1;
}

void SERV_SendImage(CLIENT client, char type[], char path[])
{
	FILE * fp = fopen(path, "rb"); 	// Get a handle to the given file

	fseek(fp, 0, SEEK_END);			// Jump to the end of the file
	int size = ftell(fp);			// Check how many bytes me are from 0
	fseek(fp, 0, SEEK_SET);			// Jump to the start of the file

	char * buffer = (char *)malloc(size * sizeof(char)); // Make a buffer the size of the image

	sprintf(buffer, "http/1.1 200 Ok\nConnection: close\nContent-Type: image/%s\nContent-Length %d\r\n\r\n", type, size); // Build the header

	send(client.socket, buffer, strlen(buffer), NO_SWITCHES); // Send it to the client

	fread(buffer, size, 1, fp); // Read the image into the buffer
	fclose(fp); 				// Close the image file

	send(client.socket, buffer, size, NO_SWITCHES); // Send the image to the client
}

void SERV_SendMP4(CLIENT client, char path[])
{
	// Like in send image we open and find the size of the file
	FILE * fp = fopen(path, "rb");
	fseek(fp, 0, SEEK_END);
	int size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	char * buffer = (char *)malloc(size * sizeof(char)); // Claim space for the buffer to store the video

	sprintf(buffer, "http/1.1 200 Ok\nConnection: close\nContent-Type: video/mp4\nContent-Length %d\r\n\r\n", size); // Build the header

	send(client.socket, buffer, strlen(buffer), NO_SWITCHES); // Send the header to the client

	// Read the file into the buffer and close the file
	fread(buffer, size, 1, fp);
	fclose(fp);

	send(client.socket, buffer, size, NO_SWITCHES); // Send the video to the client
}

#endif