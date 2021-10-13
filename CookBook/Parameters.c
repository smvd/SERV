#include "../SERV/SERV.h"

int main()
{
	SERVER server = SERV_StartServer("127.0.0.1", 80, 1);
	atexit(SERV_ShutdownServer);

	// A simple buffer
	char buffer[1000];

	while(1)
	{
		CLIENT client = SERV_Connect(server);

		if (client.headerLength > 0)
		{
			client = SERV_ParseArguments(client);

			if (SERV_MatchPath(client, "/"))
			{
                if (strcasecmp(client.method, "GET")) // If the clients request method is GET
                {
                    int index = SERV_GetParameter(client, "ID"); // Get the index of the ID parameter

                    if (index != -1) // If we found a valid index for ID
                    {
                        // client.parameters[index][0] holds the parameter name 'ID'
                        // client.parameters[index][1] holds the value for ID
                        int id = atoi(client.parameters[index][1]); // Convert the string into a int

                        if (id > 0 && id < 4) // If the id is outside of the allowed range
                        {
                            sprintf(buffer, "{ID: %d}", id); // Build the respons

                            SERV_SendData(client, TYPE_JSON, buffer, NOT_FILE);
                        }
                        else
                        {
                            SERV_SendStatus(client, 416); // Range not satisfiable
                        }
                    }
                    else
                    {
                        SERV_SendStatus(client, 400); // 400 Bad Reqeust
                    }
                }
                else
                {
                    SERV_SendStatus(client, 501); // 501 Not Implemented
                }
			}
			else
			{
                SERV_SendStatus(client, 404); // 404 Not Found
			}
		}

		client = SERV_CloseConnection(client);
	}
}