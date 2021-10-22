#include "../SERV/SERV.h"
#include <stdio.h>

int main()
{
	SERVER server = SERV_StartServer("127.0.0.1", 80, 1);

	atexit(SERV_ShutdownServer);

	while(1)
	{
		CLIENT client = SERV_Connect(server);

		if (client.headerLength > 0)
		{
			client = SERV_ParseArguments(client);

            if (strcasecmp(client.method, "GET") == 0)
            {
                if (SERV_MatchPath(client, "/"))
                {
                    SERV_SendData(client, TYPE_TEXT, "You can upload a message by calling to /upload.\nYou can also get the most recent message by calling to /message.\n", NOT_FILE);
                }
                else if (SERV_MatchPath(client, "/upload"))
                {
                    int index = SERV_GetParameter(client, "MSG");

                    if (index != -1)
                    {
                        FILE * fp = fopen("MessengerStorage.txt", "w");
                        if (fp == NULL)
                        {
                            SERV_SendStatus(client, 500); // Serverside error
                        }
                        else
                        {
                            fputs(client.parameters[index][1], fp);

                            fclose(fp);

                            SERV_SendStatus(client, 201); // Created
                        }
                    }
                    else
                    {
                        SERV_SendStatus(client, 400); // Bad request
                    }
                }
                else if (SERV_MatchPath(client, "/message"))
                {
                    SERV_SendData(client, TYPE_TEXT, "MessengerStorage.txt", IS_FILE);
                }
                else
                {
                    SERV_SendStatus(client, 404); // Not found
                }
            }
            else
            {
                SERV_SendStatus(client, 405); // Method not allowed
            }
		}
		else
		{
			SERV_SendStatus(client, 408); // Connection time out
		}

		client = SERV_CloseConnection(client);
	}
}