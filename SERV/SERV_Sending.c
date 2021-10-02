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