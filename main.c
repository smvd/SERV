#include "SERV.c"

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