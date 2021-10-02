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