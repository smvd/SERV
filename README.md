# Project SERV
SERV is a winsock2 wrapper meant to make building API's with C very easy. It removes all the boiler plate that comes with the windows headers and replaces it with a few simple functions. For new commers i recommend looking at [the installation guide](#Installation) and [the cookbook](#Cookbook). Ofcourse there is also some basic [Documentation](#Documentation) and a [Roadmap](#Roadmap)

## Installation
To use SERV you will need to get the source code from the github release page and copy it to the folder your code is stored in. After that its fairly simple just add `-lWS2_32` to your compilation command and add `#include "SERV/SERV.h"` to the top of your program.

Installing SERV is very simple.
1. [Download](http://github.com/smvd/SERV/releases/) 
2. Extract the ZIP
3. Add the SERV folder to your project
4. Link `WS2_32`
5. Put `#include "SERV/SERV.h"` at the top of your code

## Cookbook
### Basic setup:
```c
#include "SERV/SERV.h" // Add the SERV library

int main()
{
	// Host a server on the ip 127.0.0.1 (localhost)
	// Listen on port 80 (standard for webservers)
	// Allow 1 client to be waiting to be served
	SERVER server = SERV_StartServer("127.0.0.1", 80, 1);

	// When we close the program clean up
	atexit(SERV_ShutdownServer);

	// Loop forever
	while(1)
	{
		// Wait for a client to connect
		CLIENT client = SERV_Connect(server);

		// If the client sent us any data
		if (client.headerLength > 0)
		{
			// Parse the data so we know what page he asked for
			client = SERV_ParseArguments(client);

			// Check if the client asked for the root path
			if (SERV_MatchPath(client, "/"))
			{
				// Send some text to the client
				SERV_SendText(client, "Hello world!");
			}
			else // If the client asked for a page we dont have
			{
				// Return a 404 page not found
				SERV_SendPageNotFound(client);
			}
		}

		// Close the connection so we can serv (hehe) the next client
		client = SERV_CloseConnection(client);
	}

	// Exit without errors
	return 0;
}
```

### Multiple pages:
```c
int main()
{
	// Host a server on the ip 127.0.0.1 (localhost)
	// Listen on port 80 (standard for webservers)
	// Allow 1 client to be waiting to be served
	SERVER server = SERV_StartServer("127.0.0.1", 80, 1);

	// When we close the program clean up
	atexit(SERV_ShutdownServer);

	// Loop forever
	while(1)
	{
		// Wait for a client to connect
		CLIENT client = SERV_Connect(server);

		// If the client sent us any data
		if (client.headerLength > 0)
		{
			// Parse the data so we know what page he asked for
			client = SERV_ParseArguments(client);

			// Check if the client asked for the root path
			if (SERV_MatchPath(client, "/"))
			{
				// Send some text to the client
				SERV_SendText(client, "Hello world!");
			}
			else if (SERV_MatchPath(client, "/page2")) // If the client asked for the second page
			{
				// Send some text to the client
				SERV_SendText(client, "You are looking at the second page");
			}
			else // If the client asked for a page we dont have
			{
				// Return a 404 page not found
				SERV_SendPageNotFound(client);
			}
		}

		// Close the connection so we can serv (hehe) the next client
		client = SERV_CloseConnection(client);
	}

	// Exit without errors
	return 0;
}
```

### Different file types:
```c
#include "SERV/SERV.h" // Add the SERV library

int main()
{
	// Host a server on the ip 127.0.0.1 (localhost)
	// Listen on port 80 (standard for webservers)
	// Allow 1 client to be waiting to be served
	SERVER server = SERV_StartServer("127.0.0.1", 80, 1);

	// When we close the program clean up
	atexit(SERV_ShutdownServer);

	// Loop forever
	while(1)
	{
		// Wait for a client to connect
		CLIENT client = SERV_Connect(server);

		// If the client sent us any data
		if (client.headerLength > 0)
		{
			// Parse the data so we know what page he asked for
			client = SERV_ParseArguments(client);

			// Check if the client asked for the root path
			if (SERV_MatchPath(client, "/"))
			{
				SERV_SendText(client, "Hello world!");
			}
			else if (SERV_MatchPath(client, "/json"))
			{
				// Send json to the client
				SERV_SendJson(client, "{text: \"Hello world!\"}");
			}
			else if (SERV_MatchPath(client, "/html"))
			{
				// Send html to the client
				SERV_SendHTML(client, "<h1>Hello world!</h1>");
			}
			else if (SERV_MatchPath(client, "/image"))
			{
				// Send an image to the client (the second parameter desides the format)
				// If it cant find the image it will create a segmentation fault
				SERV_SendImage(client, "png", "Img.png");
			}
			else if (SERV_MatchPath(client, "/video"))
			{
				// Send an MP4 file to the client (if the server cant find the file you wil get a segmentation fault)
				SERV_SendMP4(client, "vid.mp4");
			}
			else // If the client asked for a page we dont have
			{
				// Return a 404 page not found
				SERV_SendPageNotFound(client);
			}
		}

		// Close the connection so we can serv (hehe) the next client
		client = SERV_CloseConnection(client);
	}

	// Exit without errors
	return 0;
}
```

### Using parameters:
```c
#include "SERV/SERV.h" // Add the SERV library

int main()
{
	// Host a server on the ip 127.0.0.1 (localhost)
	// Listen on port 80 (standard for webservers)
	// Allow 1 client to be waiting to be served
	SERVER server = SERV_StartServer("127.0.0.1", 80, 1);

	// When we close the program clean up
	atexit(SERV_ShutdownServer);

	// A simple buffer
	char buffer[1000];

	// Loop forever
	while(1)
	{
		// Wait for a client to connect
		CLIENT client = SERV_Connect(server);

		// If the client sent us any data
		if (client.headerLength > 0)
		{
			// Parse the data so we know what page he asked for
			client = SERV_ParseArguments(client);

			// Check if the client asked for the root path
			if (SERV_MatchPath(client, "/"))
			{
				// Get the index of the ID parameter
				int index = SERV_GetParameter(client, "ID");

				// If ID exists
				if (index != -1)
				{
					// Convert the string into a number (we request p[index][1] because p[index][0] holds the name 'ID' in this case)
					int id = atoi(client.parameters[index][1]);

					// If the ID falls within the available range or atoi couldnt convert it making id 0
					if (id > 0 && id < 4)
					{
						// Store the path to the image in the buffer
						sprintf(buffer, "%d.png", id);

						// Since we where carfull with the path we know that it will always find the image
						SERV_SendImage(client, "png", buffer);
					}
					else
					{
						SERV_SendPageNotFound(client);
					}
				}
				else
				{
					SERV_SendInvalidArguments(client);
				}
			}
			else // If the client asked for a page we dont have
			{
				// Return a 404 page not found
				SERV_SendPageNotFound(client);
			}
		}

		// Close the connection so we can serv (hehe) the next client
		client = SERV_CloseConnection(client);
	}

	// Exit without errors
	return 0;
}
```

## Documentation
```c
// Core functions
void SERV_ShutdownServer(); // Shuts down winsock2 and exits
HOST SERV_StartServer(char ip[], int port, int maxBacklog); // Setup the listener for the server

// Connection functions
CLIENT SERV_Connect(HOST host); // Wait for a client connection and recieve its header
CLIENT SERV_CloseConnection(CLIENT client); // Stop the client from sending data and clear the socket

// Argument functions
CLIENT SERV_ParseArguments(CLIENT client); // Split the method, path and arguments from the client header
int SERV_MatchPath(CLIENT client, char path[]); // Match the clients request and the given path
int SERV_GetParameter(CLIENT client, char key[]); // Check if the client has a parameter matching the key; returns the index

// Sending functions
void SERV_SendImage(CLIENT client, char type[], char path[]); // Read an image from disk and send it to the client
void SERV_SendMP4(CLIENT client, char path[]); // Read an mp4 file from disk and send it to the client
void SERV_SendRaw(CLIENT client, char data[]); // Send the raw data to the client
void SERV_SendText(CLIENT client, char text[]); // Build the http header for the text and send it to the client
void SERV_SendJson(CLIENT client, char json[]); // Build the http header for the json and send it to the client
void SERV_SendHTML(CLIENT client, char html[]); // Build the http header for the html and send it to the client

// Error functions
void SERV_SendPageNotFound(CLIENT client); // Build a 404 page not found header and send it to the client
void SERV_SendInvalidArguments(CLIENT client); // Build a 400 invalid arguments header and send it to the client
void SERV_SendBadRequest(CLIENT client); // Build a 400 bad request header and send it to the client
void SERV_SendForbidden(CLIENT client); // Build a 403 forbidden header and send it to the client
void SERV_SendUnauthorized(CLIENT client); // Build a 401 unauthorized header and send it to the client
void SERV_SendImATeapot(CLIENT client); // Build a 418 I'm a tea pot header and send it to the client
```

## Roadmap
For SERV 2.0:
- Patch out all known bugs
- Add support for more MIDI types
- Validate all input to functions
- Write a custom better version of atoi
- Replace all dangerous functions with safe ones
- Remake the logging system
