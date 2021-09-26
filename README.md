![img](logo.png)

## Starter guide
**SERV** is a winsock2 wrapper that can be used to build API's and host websites so lets take a look at how to do that.

We will be making the **API** as a website is just an **API** that returns **HTML**.

Basic template
```c
#include "SERV.c" // We must include the library to use it

int main()
{
	CONFIG server = SERV_Setup("127.0.0.1", 80); // First we must setup the server by providing an IP and PORT

	atexit(SERV_Shutdown); // Then we make shure that the program closes cleanly and doesnt leave any mess behind

	HOST host = SERV_StartServer(server); // Then we start the server

	CLIENT client; // We ofcourse need a place to store the clients info

	while (1) // We dont want our server to only serve one user so we put it in an infinite loop
	{
		client = SERV_Connect(host); // We wait for a client to connect to our server

		if (SERV_MatchPath(client, "/")) // If the root address is requested
		{
			SERV_SendText(client, "Hello World!"); // Send "Hello World!" to the client
		}
		else // If they asked for a page we dont have
		{
			SERV_SendPageNotFound(client); // Send a 404 page not found to the client
		}

		client = SERV_CloseConnection(client); // We close the connection once we are done
	}

	return 0;
}
```

## Documentation