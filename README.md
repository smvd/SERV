![img](https://github.com/smvd/SERV/blob/master/Logo.png)

## Starter guide
**SERV** is a winsock2 wrapper that can be used to build API's and host websites so lets take a look at how to do that.

We will be making the **API** as a website is just an **API** that returns **HTML**.

Basic template
```c
#include "SERV.c" // We must include the library to use it

int main()
{
	CONFIG server = SERV_Setup("127.0.0.1", 80); // We configure the server with an IP and PORT

	atexit(SERV_Shutdown); // Make shure we clean up before closing the program

	HOST host = SERV_StartServer(server); // Then we start the server

	CLIENT client; // We ofcourse need a place to store the clients info

	while (1) // We dont want our server to only serve one user so we put it in an infinite loop
	{
		client = SERV_Connect(host); // We wait for a client to connect to our server

		if (SERV_MatchPath(client, "/")) // If the root address is requested
		{
			SERV_SendText(client, "Hello World!"); // Send "Hello World!" to the client
		}
		else if (SERV_MatchPath(client, "/json")) // We can ofcourse add more pages
		{
			SERV_SendJson(client, "{text:\"It even supports JSON\"}"); // Json can also be sent
		}
		else if (SERV_MatchPath(client, "/html"))
		{
			SERV_SendHTML(client, "<h1>Even HTML</h1>"); // HTML isnt an issue for SERV
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

Now there are a few ways to acces our pages.
If you have a terminal you can use the CURL command to request the pages.
```
curl localhost
curl localhost/json
curl localhost/html
```
Another way to acces the pages is to simply go to your browser and visit localhost. However our page is not public on the internet yet. That wouuld require port forwarding and requesting a static IP wich is a bit outside of the scope of this basic guide.