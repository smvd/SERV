void SERV_SendRaw(CLIENT client, char data[])
{
	char buffer[MAX_BUFFER_SIZE * 2];
	sprintf(buffer, "Sending %s to %s:%d", client.path, client.ip, client.port);
	SERV_Log(buffer, LOGGING_SENDING);
	if (send(client.socket, data, strlen(data), NO_SWITCHES) == SOCKET_ERROR) // Send the client the raw bytes
	{
		exit(1);
	}
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

void SERV_SendImage(CLIENT client, char type[], char path[])
{
	FILE * fp = fopen(path, "rb"); 	// Get a handle to the given file

	if (fp == NULL)
	{
		SERV_SendError(client, 500);
		return;
	}

	fseek(fp, 0, SEEK_END);			// Jump to the end of the file
	int size = ftell(fp);			// Check how many bytes me are from 0
	fseek(fp, 0, SEEK_SET);			// Jump to the start of the file

	char * buffer = (char *)malloc(size * sizeof(char)); // Make a buffer the size of the image

	sprintf(buffer, "http/1.1 200 Ok\nConnection: close\nContent-Type: image/%s\nContent-Length %d\r\n\r\n", type, size); // Build the header

	SERV_SendRaw(client, buffer); 	// Send it to the client

	fread(buffer, size, 1, fp); // Read the image into the buffer
	fclose(fp); 				// Close the image file

	send(client.socket, buffer, size, NO_SWITCHES); // Send the image to the client
}

void SERV_SendMP4(CLIENT client, char path[])
{
	// Like in send image we open and find the size of the file
	FILE * fp = fopen(path, "rb");

	if (fp == NULL)
	{
		SERV_SendError(client, 500);
		return;
	}

	fseek(fp, 0, SEEK_END);
	int size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	char * buffer = (char *)malloc(size * sizeof(char)); // Claim space for the buffer to store the video

	sprintf(buffer, "http/1.1 200 Ok\nConnection: close\nContent-Type: video/mp4\nContent-Length %d\r\n\r\n", size); // Build the header

	SERV_SendRaw(client, buffer);	// Send the header to the client

	// Read the file into the buffer and close the file
	fread(buffer, size, 1, fp);
	fclose(fp);

	SERV_SendRaw(client, buffer);	// Send the video to the client
}

void SERV_BuildHeader(char * buffer, int code, char text[])
{
    sprintf(buffer, "http/1.1 %d %s\nConnection: close\nContent-Length: %d\n\n%s\r\n\r\n", code, text, (int)strlen(text), text);
}

void SERV_SendError(CLIENT client, int type)
{
    char buffer[MAX_BUFFER_SIZE];

    switch (type)
    {
        case 100:
            SERV_BuildHeader(buffer, type, "Continue");
            break;
        case 101:
            SERV_BuildHeader(buffer, type, "Switching Protocols");
            break;
        case 102:
            SERV_BuildHeader(buffer, type, "Processing");
            break;
        case 103:
            SERV_BuildHeader(buffer, type, "Early Hints");
            break;

        case 200:
            SERV_BuildHeader(buffer, type, "Ok");
            break;
        case 201:
            SERV_BuildHeader(buffer, type, "Created");
            break;
        case 202:
            SERV_BuildHeader(buffer, type, "Accepted");
            break;
        case 203:
            SERV_BuildHeader(buffer, type, "Non-Authoritative Information");
            break;
        case 204:
            SERV_BuildHeader(buffer, type, "No Content");
            break;
        case 205:
            SERV_BuildHeader(buffer, type, "Reset Content");
            break;
        case 206:
            SERV_BuildHeader(buffer, type, "Partial Content");
            break;
        case 207:
            SERV_BuildHeader(buffer, type, "Multi-Status");
            break;
        case 208:
            SERV_BuildHeader(buffer, type, "Already Reported");
            break;
        case 226:
            SERV_BuildHeader(buffer, type, "IM Used");
            break;

        case 300:
            SERV_BuildHeader(buffer, type, "Multiple Choices");
            break;
        case 301:
            SERV_BuildHeader(buffer, type, "Moved Permanently");
            break;
        case 302:
            SERV_BuildHeader(buffer, type, "Found");
            break;
        case 303:
            SERV_BuildHeader(buffer, type, "See Other");
            break;
        case 304:
            SERV_BuildHeader(buffer, type, "Not Modified");
            break;
        case 305:
            SERV_BuildHeader(buffer, type, "Use Proxy");
            break;
        case 306:
            SERV_BuildHeader(buffer, type, "Switch Proxy");
            break;
        case 307:
            SERV_BuildHeader(buffer, type, "Temporary Redirect");
            break;
        case 308:
            SERV_BuildHeader(buffer, type, "Permanent Redirect");
            break;

        case 400:
            SERV_BuildHeader(buffer, type, "Bad Request");
            break;
        case 401:
            SERV_BuildHeader(buffer, type, "Unauthorized");
            break;
        case 402:
            SERV_BuildHeader(buffer, type, "Payment Required");
            break;
        case 403:
            SERV_BuildHeader(buffer, type, "Forbidden");
            break;
        case 404:
            SERV_BuildHeader(buffer, type, "Not Found");
            break;
        case 405:
            SERV_BuildHeader(buffer, type, "Method Not Allowed");
            break;
        case 406:
            SERV_BuildHeader(buffer, type, "Not Acceptable");
            break;
        case 407:
            SERV_BuildHeader(buffer, type, "Proxy Authentication Required");
            break;
        case 408:
            SERV_BuildHeader(buffer, type, "Request Timeout");
            break;
        case 409:
            SERV_BuildHeader(buffer, type, "Conflict");
            break;
        case 410:
            SERV_BuildHeader(buffer, type, "Gone");
            break;
        case 411:
            SERV_BuildHeader(buffer, type, "Length Required");
            break;
        case 412:
            SERV_BuildHeader(buffer, type, "Precondition Failed");
            break;
        case 413:
            SERV_BuildHeader(buffer, type, "Payload Too Large");
            break;
        case 414:
            SERV_BuildHeader(buffer, type, "Uri Too Long");
            break;
        case 415:
            SERV_BuildHeader(buffer, type, "Unsupported Media Type");
            break;
        case 416:
            SERV_BuildHeader(buffer, type, "Range Not Satisfiable");
            break;
        case 417:
            SERV_BuildHeader(buffer, type, "Exception Failed");
            break;
        case 421:
            SERV_BuildHeader(buffer, type, "Misdirected Request");
            break;
        case 422:
            SERV_BuildHeader(buffer, type, "Unprocessable Entity");
            break;
        case 423:
            SERV_BuildHeader(buffer, type, "Locked");
            break;
        case 424:
            SERV_BuildHeader(buffer, type, "Failed Dependency");
            break;
        case 425:
            SERV_BuildHeader(buffer, type, "Too Early");
            break;
        case 426:
            SERV_BuildHeader(buffer, type, "Upgrade Required");
            break;
        case 428:
            SERV_BuildHeader(buffer, type, "Precondition Required");
            break;
        case 429:
            SERV_BuildHeader(buffer, type, "Too Many Requests");
            break;
        case 431:
            SERV_BuildHeader(buffer, type, "Request Header Field Too Large");
            break;
        case 451:
            SERV_BuildHeader(buffer, type, "Unavailable For Legal Reasons");
            break;

        case 500:
            SERV_BuildHeader(buffer, type, "Internal Server Error");
            break;
        case 501:
            SERV_BuildHeader(buffer, type, "Not Implemented");
            break;
        case 502:
            SERV_BuildHeader(buffer, type, "Bad Gateway");
            break;
        case 503:
            SERV_BuildHeader(buffer, type, "Service Unavailable");
            break;
        case 504:
            SERV_BuildHeader(buffer, type, "Gateway Timeout");
            break;
        case 505:
            SERV_BuildHeader(buffer, type, "HTTP Version Not Supported");
            break;
        case 506:
            SERV_BuildHeader(buffer, type, "Variant Also Negotiates");
            break;
        case 507:
            SERV_BuildHeader(buffer, type, "Insufficient Storage");
            break;
        case 508:
            SERV_BuildHeader(buffer, type, "Loop Detected");
            break;
        case 510:
            SERV_BuildHeader(buffer, type, "Not Extended");
            break; 
        case 511:
            SERV_BuildHeader(buffer, type, "Network Authentication Required");
            break;
    }

    SERV_SendRaw(client, buffer);
}