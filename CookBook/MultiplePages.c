#include "../SERV/SERV.h" // Add the SERV library

int main()
{
	SERVER server = SERV_StartServer("127.0.0.1", 80, 1); // Setup the server at localhost

	atexit(SERV_ShutdownServer); // Add a safe shutdown

	while(1) // Loop forever
	{
		CLIENT client = SERV_Connect(server); // Wait for a client to connect

		if (client.headerLength > 0) // If the client sent a request
		{
			client = SERV_ParseArguments(client); // Parse the clients request

            if (SERV_MatchPath(client, "/")) // Check if they asked for the home page
            {
                SERV_SendData(client, TYPE_HTML, "data/home.html", IS_FILE); // Send the home page
            }
            else if (SERV_MatchPath(client, "/page2")) // Check if they asked for the second page
            {
                SERV_SendData(client, TYPE_HTML, "<h1>This is the second page</h1>", NOT_FILE); // Send the second page
            }
            else // If they asked for a page we dont have
            {
                SERV_SendStatus(client, 404); // Return 404 not found
            }
		}
		else // If the client request was empty
		{
			SERV_SendStatus(client, 408); // Return Request Timeout
		}

		client = SERV_CloseConnection(client);
	}
}