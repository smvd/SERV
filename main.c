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
			// printf("%s : %s\n", client.method, client.path);

			// for (int i = 0; i < client.parameterCount; i++)
			// {
			// 	printf("%s : %s\n", client.parameters[i][0], client.parameters[i][1]);
			// }

			if (SERV_MatchPath(client, "/ID") && client.parameterCount == 2)
			{
				if (strcasecmp(client.parameters[0][0], "ID") == 0 && strcasecmp(client.parameters[1][0], "KEY") == 0)
				{
					if (strcmp(client.parameters[1][1], GLOBAL_API_KEY) == 0)
					{
						// Return

						sprintf(buffer, "{ID: %s, PATH: %s}", client.parameters[0][0], client.path);

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
		}
		else
		{
			SERV_SendPageNotFound(client);
		}


		SERV_CloseConnection(client);
	}

	return 0;
}