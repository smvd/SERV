#ifndef SERV_LOADED
#define SERV_LOADED

#include <Winsock.h>
#include <Stdlib.h>
#include <Stdio.h>

#define PAGE_NOT_FOUND "HTTP/1.1 404 Not Found\nConnection: close\r\n\r\n"
#define NO_SWITCHES 0
#define MAX_BUFFER_SIZE 1024

typedef struct sockaddr_in CONFIG;
typedef SOCKET HOST;

typedef struct
{
	int headerLength;
	char header[MAX_BUFFER_SIZE];
	SOCKET socket;
}CLIENT;


CONFIG SERV_Setup(char ip[], int port)
{
	// Setup winsock
	CONFIG server;

	WSADATA wsaData;
	WSAStartup(MAKEWORD(2,2), &wsaData);

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(ip);
	server.sin_port = htons(port);

	return server;
}

void SERV_Shutdown()
{
	// Cleanup winsock
    WSACleanup();
}

HOST SERV_StartServer(CONFIG server)
{
	HOST host;

	host = socket(AF_INET, SOCK_STREAM, NO_SWITCHES);
	bind(host, (struct sockaddr *)&server, sizeof(server));
	listen(host, 1);

	return host;
}

CLIENT SERV_Connect(HOST host)
{
	// Wait for a client
	CLIENT client;
	int socketSize = sizeof(struct sockaddr_in);

	client.socket = accept(host, NULL, &socketSize);

	client.headerLength = recv(client.socket, client.header, MAX_BUFFER_SIZE, NO_SWITCHES);

	return client;
}

CLIENT SERV_CloseConnection(CLIENT client)
{
    shutdown(client.socket, SB_BOTH);
    closesocket(client.socket);

    return client;
}

int SERV_MatchPath(CLIENT client, char path[])
{
	// Match path with request

	char * request;

	request = strtok(client.header, " ");
	request = strtok(NULL, " ");

	if (strcasecmp(request, path) == 0)
	{
		return 1;
	}
	
	return 0;
}

void SERV_SendText(CLIENT client, char text[])
{
	// Send text to client
	char buffer[MAX_BUFFER_SIZE];

	sprintf(buffer, "HTTP/1.1 200 OK\nConnection: close\nContent-Type: text\nContent-Length: %d\n\n%s\r\n\r\n", (int)strlen(text), text);

	send(client.socket, buffer, strlen(buffer), NO_SWITCHES);
}

void SERV_SendJson(CLIENT client, char json[])
{
	// Send json to client
	char buffer[MAX_BUFFER_SIZE];

	sprintf(buffer, "HTTP/1.1 200 OK\nConnection: close\nContent-Type: text/json\nContent-Length: %d\n\n%s\r\n\r\n", (int)strlen(json), json);

	send(client.socket, buffer, strlen(buffer), NO_SWITCHES);
}

void SERV_SendHTML(CLIENT client, char html[])
{
	// Send html to client
	char buffer[MAX_BUFFER_SIZE];

	sprintf(buffer, "HTTP/1.1 200 OK\nConnection: close\nContent-Type: text/html\nContent-Length: %d\n\n%s\r\n\r\n", (int)strlen(html), html);

	send(client.socket, buffer, strlen(buffer), NO_SWITCHES);
}

void SERV_SendPageNotFound(CLIENT client)
{
	send(client.socket, PAGE_NOT_FOUND, strlen(PAGE_NOT_FOUND), NO_SWITCHES);
}

#endif