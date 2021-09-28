#include "SERV.c"

/*
int main()
{
	CONFIG server = SERV_Setup("127.0.0.1", 80);

	atexit(SERV_Shutdown);

	HOST host = SERV_StartServer(server, 1);

	CLIENT client;

	while (1)
	{
		client = SERV_Connect(host);

		if (SERV_MatchPath(client, "/"))
		{
			SERV_SendText(client, "This is made with the SERV project");
		}
		else if (SERV_MatchPath(client, "/hello"))
		{
			SERV_SendText(client, "Hello World!");
		}
		else if (SERV_MatchPath(client, "/json"))
		{
			SERV_SendJson(client, "{text:\"It even supports json\"}");
		}
		else if (SERV_MatchPath(client, "/html"))
		{
			SERV_SendHTML(client, "<h1>HTML isnt an issue either</h1>");
		}
		else
		{
			SERV_SendPageNotFound(client);
		}

		client = SERV_CloseConnection(client);
	}

	SERV_Shutdown();

	return 0;
}
*/

#define GLOBAL_API_KEY "9tUEsbj2"

int main()
{
	CONFIG server = SERV_Setup("127.0.0.1", 80);

	atexit(SERV_Shutdown);

	HOST host = SERV_StartServer(server, 1);
	CLIENT client;

	char buffer[5000];

	while (1)
	{
		client = SERV_Connect(host);

		if (client.headerLength > 0)
		{
			client = SERV_ParseArguments(client);

			if 	(
					SERV_MatchPath(client, "/ID") && 					// localhost/ID
					client.parameterCount == 2 && 						// 2 arguments
					strcasecmp(client.parameters[0][0], "ID") == 0 && 	// First argument is ID
					strcasecmp(client.parameters[1][0], "KEY") == 0		// Second argument is key
				)
			{
				if (strcmp(client.parameters[1][1], GLOBAL_API_KEY) == 0)	// If the key matches the global one (dont do this, add a DB with a list of keys so you can revoke acces)
				{
					sprintf(buffer, "{ID: %s, PATH: %s}", client.parameters[0][1], client.path);

					SERV_SendJson(client, buffer);
				}
				else
				{
					SERV_SendAccesForbidden(client);
				}
			}
			else
			{
				SERV_SendPageNotFound(client);
			}
		}
		else
		{
			SERV_SendPageNotFound(client);
		}


		SERV_CloseConnection(client);
	}

	return 0;
}