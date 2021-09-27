#ifndef SERV_LOADED
#define SERV_LOADED

#include <Winsock.h>
#include <Stdlib.h>
#include <Stdio.h>

#define PAGE_NOT_FOUND "HTTP/1.1 404 Not Found\nConnection: close\r\n\r\n"
#define NO_SWITCHES 0
#define MAX_BUFFER_SIZE 1024
#define MAX_IP_LENGTH 16
#define MAX_PARAMETER_COUNT 5

typedef struct sockaddr_in CONFIG;
typedef SOCKET HOST;

typedef struct
{
	int headerLength;
	int parameterCount;
	char path[MAX_BUFFER_SIZE];
	char parameters[MAX_PARAMETER_COUNT][2][MAX_BUFFER_SIZE];
	char header[MAX_BUFFER_SIZE];
	char ip[MAX_IP_LENGTH];
	int port;
	SOCKET socket;
}CLIENT;

CONFIG SERV_Setup(char ip[], int port)
{
	// Setup winsock
	CONFIG server;
	WSADATA wsaData;

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(ip);
	server.sin_port = htons(port);
	
	printf("Starting winsock...");
	if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
	{
		printf("Failed\n");
		exit(1);
	}
	printf("Succes\n");

	return server;
}

void SERV_Shutdown()
{
	// Cleanup winsock
	printf("Shuttingdown winsock...");
    if (WSACleanup() == SOCKET_ERROR)
    {
    	printf("Failed\n");
    	exit(1);
    }
    printf("Succes\n");
}

CLIENT SERV_ParseArguments(CLIENT client)
{
	// Split path and arguments ; Split arguments
	char headerCopy[MAX_BUFFER_SIZE];

	strcpy(headerCopy, client.header);

	char * path = strtok(headerCopy, " ");
	path = strtok(NULL, " ");

	int pathLenght = strlen(path);

	for (int i = 0; i < pathLenght; i++)
	{
		if (path[i] == '?')
		{
			path[i] = '\0';
			pathLenght = i;
			break;
		}
	}

	if (pathLenght > 1 && path[pathLenght -1] == '/')
	{
		path[pathLenght -1] = '\0';
	}

	strcpy(client.path, path);

	strcpy(headerCopy, client.header);

	// Find the first ? and split at the first ' ' after it
	char * parametersStart = strchr(headerCopy, '?');
	client.parameterCount = 0;

	if (parametersStart != NULL && parametersStart[1] != '0') // Check if its way out in the header
	{
		parametersStart++;
		parametersStart = strtok(parametersStart, " ");

		// Split at every &
		char * parameters = strtok(parametersStart, "&");

		int i = 0;

		while (parameters != NULL)
		{
			strcpy(client.parameters[i][0], parameters);
			parameters = strtok(NULL, "&");
			i++;
		}

		client.parameterCount = i;

		for (int i = 0; i < client.parameterCount; i++)
		{
			parameters = strtok(client.parameters[i][0], "=");
			strcpy(client.parameters[i][0], parameters);
			parameters = strtok(NULL, "=");
			strcpy(client.parameters[i][1], parameters);
		}
	}

	return client;
}

HOST SERV_StartServer(CONFIG server, int maxBacklog)
{
	HOST host;

	printf("Making host socket...");
	host = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (host == INVALID_SOCKET)
	{
		printf("Failed\n");
		exit(1);
	}
	printf("Succes\n");

	printf("Binding host socket...");
	if (bind(host, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
	{
		printf("Failed\n");
	}
	printf("Succes\n");

	printf("Setting up listener...");
	if (listen(host, maxBacklog) == SOCKET_ERROR)
	{
		printf("Failed\n");
		exit(1);
	}
	printf("Succes\n");

	return host;
}

CLIENT SERV_Connect(HOST host)
{
	// Wait for a client
	CLIENT client;
	int socketSize = sizeof(struct sockaddr_in);
	struct sockaddr_in clientInfo;

	printf("\nWaiting for connection...");
	client.socket = accept(host, (struct sockaddr *)&clientInfo, &socketSize);
	if (client.socket == INVALID_SOCKET)
	{
		printf("Failed\n");
		exit(1);
	}
	printf("Succes\n");


	printf("Recieving request...");
	client.headerLength = recv(client.socket, client.header, MAX_BUFFER_SIZE, NO_SWITCHES);
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

	strcpy(client.ip, inet_ntoa(clientInfo.sin_addr));
	client.port = ntohs(clientInfo.sin_port);

	return client;
}

CLIENT SERV_CloseConnection(CLIENT client)
{
	printf("Shuttingdown sending...");
    if (shutdown(client.socket, 1) == SOCKET_ERROR)
    {
    	printf("Failed\n");
    	exit(1);
    }
    printf("Succes\n");

    printf("Closing socket...");
    if (closesocket(client.socket) == SOCKET_ERROR)
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
	if (strcasecmp(client.path, path) == 0)
	{
		return 1;
	}
	
	return 0;
}

void SERV_SendRaw(CLIENT client, char data[])
{
	printf("Sending data...");
	if (send(client.socket, data, strlen(data), NO_SWITCHES) == SOCKET_ERROR)
	{
		printf("Failed\n");
		exit(1);
	}
	printf("Succes\n");
}

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
	SERV_SendRaw(client, PAGE_NOT_FOUND);
}

#endif