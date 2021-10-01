#include "SERV/SERV.c"

#define PASSWORD "Hello"
#define BUFFER_SIZE 256

int main()
{
	SERVER server = SERV_Setup("127.0.0.1", 80);

	atexit(SERV_Shutdown);

	HOST host = SERV_StartServer(server, 1);

	while(1)
	{
		CLIENT client = SERV_Connect(host);

		if (client.headerLength > 0)
		{
			client = SERV_ParseArguments(client);

			if (SERV_MatchPath(client, "/"))
			{
				SERV_SendText(client, "You can request an image based on its ID, but for video you will need a password");
			}
			else if (SERV_MatchPath(client, "/image"))
			{
				int index = SERV_GetParameter(client, "ID");

				if (index > -1)
				{
					int id = atoi(client.parameters[index][1]);

					if (id > 0 && id < 4)
					{
						char buffer[BUFFER_SIZE];

						sprintf(buffer, "%d.png", id);

						SERV_SendImage(client, "png", buffer);
					}
					else
					{
						SERV_SendInvalidArguments(client);
					}
				}
				else
				{
					SERV_SendInvalidArguments(client);
				}
			}
			else if (SERV_MatchPath(client, "/video"))
			{
				int index = SERV_GetParameter(client, "KEY");

				if (index != -1)
				{
					if (strcmp(client.parameters[index][1], PASSWORD) == 0)
					{
						SERV_SendMP4(client, "vid.mp4");
					}
					else
					{
						SERV_SendAccesForbidden(client);
					}
				}
				else
				{
					SERV_SendInvalidArguments(client);
				}
			}
			else
			{
				SERV_SendPageNotFound(client);
			}
		}
		else
		{
			SERV_SendBadRequest(client);
		}

		SERV_CloseConnection(client);
	}

	return 0;
}