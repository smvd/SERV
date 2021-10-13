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
			SERV_SendData(client, TYPE_TEXT, "Hello World!", NOT_FILE); // Send the client "Hello World!"
		}
		else // If the client request was empty
		{
			SERV_SendStatus(client, 408); // Return Request Timeout
		}

		client = SERV_CloseConnection(client);
	}
}