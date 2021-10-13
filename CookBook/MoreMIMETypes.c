#include "../SERV/SERV.h"

// For a list of all supported MIME types see SERV.h

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

            if (SERV_MatchPath(client, "/"))
            {
                SERV_SendData(client, TYPE_HTML, "data/home.html", IS_FILE);
            }
            else if (SERV_MatchPath(client, "/image"))
            {
                SERV_SendData(client, TYPE_PNG, "data/image.png", IS_FILE);
            }
            else if (SERV_MatchPath(client, "/video"))
            {
                SERV_SendData(client, TYPE_MP4, "data/video.mp4", IS_FILE);
            }
            else if (SERV_MatchPath(client, "/audio"))
            {
                SERV_SendData(client, TYPE_MP3, "data/audio.mp3", IS_FILE);
            }
            else if (SERV_MatchPath(client, "/text"))
            {
                SERV_SendData(client, TYPE_TEXT, "This is text", NOT_FILE);
            }
            else
            {
                SERV_SendStatus(client, 404);
            }
		}
		else
		{
			SERV_SendStatus(client, 408);
		}

		client = SERV_CloseConnection(client);
	}
}