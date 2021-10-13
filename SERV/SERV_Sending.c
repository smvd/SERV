void SERV_SendRaw(CLIENT client, char data[])
{
	char buffer[MAX_BUFFER_SIZE * 2];
    
	sprintf(buffer, "Sending to %s:%d", client.ip, client.port);
	SERV_Log(buffer, LOGGING_SENDING);

	if (send(client.socket, data, strlen(data), NO_SWITCHES) == SOCKET_ERROR) // Send the client the raw bytes
	{
		exit(1);
	}
}

void SERV_BuildHeader(char * buffer, int code, char text[])
{
    sprintf(buffer, "http/1.1 %d %s\nConnection: close\nContent-Length: %d\n\n%s\r\n\r\n", code, text, (int)strlen(text), text);
}

void SERV_SendStatus(CLIENT client, int code)
{
    char buffer[MAX_BUFFER_SIZE];

    switch (code)
    {
        case 100:
            SERV_BuildHeader(buffer, code, "Continue");
            break;
        case 101:
            SERV_BuildHeader(buffer, code, "Switching Protocols");
            break;
        case 102:
            SERV_BuildHeader(buffer, code, "Processing");
            break;
        case 103:
            SERV_BuildHeader(buffer, code, "Early Hints");
            break;

        case 200:
            SERV_BuildHeader(buffer, code, "Ok");
            break;
        case 201:
            SERV_BuildHeader(buffer, code, "Created");
            break;
        case 202:
            SERV_BuildHeader(buffer, code, "Accepted");
            break;
        case 203:
            SERV_BuildHeader(buffer, code, "Non-Authoritative Information");
            break;
        case 204:
            SERV_BuildHeader(buffer, code, "No Content");
            break;
        case 205:
            SERV_BuildHeader(buffer, code, "Reset Content");
            break;
        case 206:
            SERV_BuildHeader(buffer, code, "Partial Content");
            break;
        case 207:
            SERV_BuildHeader(buffer, code, "Multi-Status");
            break;
        case 208:
            SERV_BuildHeader(buffer, code, "Already Reported");
            break;
        case 226:
            SERV_BuildHeader(buffer, code, "IM Used");
            break;

        case 300:
            SERV_BuildHeader(buffer, code, "Multiple Choices");
            break;
        case 301:
            SERV_BuildHeader(buffer, code, "Moved Permanently");
            break;
        case 302:
            SERV_BuildHeader(buffer, code, "Found");
            break;
        case 303:
            SERV_BuildHeader(buffer, code, "See Other");
            break;
        case 304:
            SERV_BuildHeader(buffer, code, "Not Modified");
            break;
        case 305:
            SERV_BuildHeader(buffer, code, "Use Proxy");
            break;
        case 306:
            SERV_BuildHeader(buffer, code, "Switch Proxy");
            break;
        case 307:
            SERV_BuildHeader(buffer, code, "Temporary Redirect");
            break;
        case 308:
            SERV_BuildHeader(buffer, code, "Permanent Redirect");
            break;

        case 400:
            SERV_BuildHeader(buffer, code, "Bad Request");
            break;
        case 401:
            SERV_BuildHeader(buffer, code, "Unauthorized");
            break;
        case 402:
            SERV_BuildHeader(buffer, code, "Payment Required");
            break;
        case 403:
            SERV_BuildHeader(buffer, code, "Forbidden");
            break;
        case 404:
            SERV_BuildHeader(buffer, code, "Not Found");
            break;
        case 405:
            SERV_BuildHeader(buffer, code, "Method Not Allowed");
            break;
        case 406:
            SERV_BuildHeader(buffer, code, "Not Acceptable");
            break;
        case 407:
            SERV_BuildHeader(buffer, code, "Proxy Authentication Required");
            break;
        case 408:
            SERV_BuildHeader(buffer, code, "Request Timeout");
            break;
        case 409:
            SERV_BuildHeader(buffer, code, "Conflict");
            break;
        case 410:
            SERV_BuildHeader(buffer, code, "Gone");
            break;
        case 411:
            SERV_BuildHeader(buffer, code, "Length Required");
            break;
        case 412:
            SERV_BuildHeader(buffer, code, "Precondition Failed");
            break;
        case 413:
            SERV_BuildHeader(buffer, code, "Payload Too Large");
            break;
        case 414:
            SERV_BuildHeader(buffer, code, "Uri Too Long");
            break;
        case 415:
            SERV_BuildHeader(buffer, code, "Unsupported Media Type");
            break;
        case 416:
            SERV_BuildHeader(buffer, code, "Range Not Satisfiable");
            break;
        case 417:
            SERV_BuildHeader(buffer, code, "Exception Failed");
            break;
        case 421:
            SERV_BuildHeader(buffer, code, "Misdirected Request");
            break;
        case 422:
            SERV_BuildHeader(buffer, code, "Unprocessable Entity");
            break;
        case 423:
            SERV_BuildHeader(buffer, code, "Locked");
            break;
        case 424:
            SERV_BuildHeader(buffer, code, "Failed Dependency");
            break;
        case 425:
            SERV_BuildHeader(buffer, code, "Too Early");
            break;
        case 426:
            SERV_BuildHeader(buffer, code, "Upgrade Required");
            break;
        case 428:
            SERV_BuildHeader(buffer, code, "Precondition Required");
            break;
        case 429:
            SERV_BuildHeader(buffer, code, "Too Many Requests");
            break;
        case 431:
            SERV_BuildHeader(buffer, code, "Request Header Field Too Large");
            break;
        case 451:
            SERV_BuildHeader(buffer, code, "Unavailable For Legal Reasons");
            break;

        case 500:
            SERV_BuildHeader(buffer, code, "Internal Server Error");
            break;
        case 501:
            SERV_BuildHeader(buffer, code, "Not Implemented");
            break;
        case 502:
            SERV_BuildHeader(buffer, code, "Bad Gateway");
            break;
        case 503:
            SERV_BuildHeader(buffer, code, "Service Unavailable");
            break;
        case 504:
            SERV_BuildHeader(buffer, code, "Gateway Timeout");
            break;
        case 505:
            SERV_BuildHeader(buffer, code, "HTTP Version Not Supported");
            break;
        case 506:
            SERV_BuildHeader(buffer, code, "Variant Also Negotiates");
            break;
        case 507:
            SERV_BuildHeader(buffer, code, "Insufficient Storage");
            break;
        case 508:
            SERV_BuildHeader(buffer, code, "Loop Detected");
            break;
        case 510:
            SERV_BuildHeader(buffer, code, "Not Extended");
            break; 
        case 511:
            SERV_BuildHeader(buffer, code, "Network Authentication Required");
            break;
    }

    SERV_SendRaw(client, buffer);
}

void SERV_SendData(CLIENT client, int type, char data[], int isFile)
{
    char buffer[MAX_BUFFER_SIZE] = "http/1.1 200 Ok\nConnection: Close\nContent-Type: ";

    switch (type)
    {
        case TYPE_TEXT:
            strcat(buffer, "text/plain");
            break;
        case TYPE_PHP:
            strcat(buffer, "application/x-httpd-php");
            break;
        case TYPE_JAVASCRIPT:
            strcat(buffer, "text/javascript");
            break;
        case TYPE_CSS:
            strcat(buffer, "text/css");
            break;
        case TYPE_BIN:
            strcat(buffer, "application/octet-stream");
            break;

        case TYPE_HTML:
            strcat(buffer, "text/html");
            break;
        case TYPE_RTF:
            strcat(buffer, "application/rtf");
            break;
        case TYPE_PDF:
            strcat(buffer, "application/pdf");
            break;
        case TYPE_ODT:
            strcat(buffer, "application/vnd.oasis.opendocument.text");
            break;
        case TYPE_DOC:
            strcat(buffer, "application/msword");
            break;

        case TYPE_XLS:
            strcat(buffer, "application/vnd.ms-excel");
            break;
        case TYPE_ODS:
            strcat(buffer, "application/vnd.oasis.opendocument.spreadsheet");
            break;
        case TYPE_CSV:
            strcat(buffer, "text/csv");
            break;

        case TYPE_OTF:
            strcat(buffer, "font/otf");
            break;
        case TYPE_TTF:
            strcat(buffer, "font/ttf");
            break;

        case TYPE_JSON:
            strcat(buffer, "application/json");
            break;
        case TYPE_XML:
            strcat(buffer, "application/xml");
            break;

        case TYPE_ZIP:
            strcat(buffer, "application/zip");
            break;
        case TYPE_7ZIP:
            strcat(buffer, "application/x-7z-compressed");
            break;
        case TYPE_TAR:
            strcat(buffer, "application/x-tar");
            break;
        case TYPE_RAR:
            strcat(buffer, "application/vnd.rar");
            break;
        case TYPE_GZIP:
            strcat(buffer, "application/gzip");
            break;
        case TYPE_BZIP:
            strcat(buffer, "application/x-bzip");
            break;
        case TYPE_BZIP2:
            strcat(buffer, "application/x-bzip2");
            break;
        
        case TYPE_WEBP:
            strcat(buffer, "image/webp");
            break;
        case TYPE_TIFF:
            strcat(buffer, "image/tiff");
            break;
        case TYPE_SVG:
            strcat(buffer, "image/svg+xml");
            break;
        case TYPE_PNG:
            strcat(buffer, "image/png");
            break;
        case TYPE_JPEG:
            strcat(buffer, "image/jpeg");
            break;
        case TYPE_ICON:
            strcat(buffer, "image/vnd.microsoft.icon");
            break;
        case TYPE_GIF:
            strcat(buffer, "image/gif");
            break;
        case TYPE_BMP:
            strcat(buffer, "image/bmp");
            break;

        case TYPE_WEBM:
            strcat(buffer, "video/webm");
            break;
        case TYPE_MPEG:
            strcat(buffer, "video/mpeg");
            break;
        case TYPE_MP4:
            strcat(buffer, "video/mp4");
            break;

        case TYPE_WEBA:
            strcat(buffer, "audio/webm");
            break;
        case TYPE_WAV:
            strcat(buffer, "audio/wav");
            break;
        case TYPE_OPUS:
            strcat(buffer, "audio/opus");
            break;
        case TYPE_MP3:
            strcat(buffer, "audio/mpeg");
            break;
        case TYPE_MIDI:
            strcat(buffer, "audio/midi");
            break;
    }

    int length;

    if (isFile) // Content length mismatch altho it looks good
    {
        FILE * fp = fopen(data, "rb");
        if (fp == NULL)
        {
            SERV_SendStatus(client, 500);
            return;
        }

        fseek(fp, 0, SEEK_END);
        length = ftell(fp);
        fseek(fp, 0, SEEK_SET);
	    fclose(fp);
    }
    else
    {
        length = strlen(data);
    }

    char temp[MAX_BUFFER_SIZE];
    sprintf(temp, "\nContent-Length: %d\n\n", length);
    strcat(buffer, temp);

    SERV_SendRaw(client, buffer);

    if (isFile)
    {
        int ret;
        FILE * fp = fopen(data, "rb");

        while (1)
        {
            ret = fread(buffer, 1, MAX_BUFFER_SIZE, fp);

            send(client.socket, buffer, ret, NO_SWITCHES);

            if (ret < MAX_BUFFER_SIZE)
            {
                break;
            }
        }
    }
    else
    {
        send(client.socket, data, length, NO_SWITCHES);
    }

    send(client.socket, "\r\n\r\n", 4, NO_SWITCHES);
}