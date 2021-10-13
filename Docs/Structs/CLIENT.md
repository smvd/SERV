# Structs/CLIENT
`CLIENT` is defined in `SERV_Struct.c` and is meant to hold the info related to the client.

| member name | data type | use purpose |
|-------------|-----------|-------------|
|parameterCount | int | Holds the total ammount of supplied parameters |
| parameters | char [] [] [] | Holds the key value pairs for the parameters |
| headerLength | int | Holds the byte size of the recieved header |
| header | char [] | Holds the client provided header |
| method | char [] | Holds the method the client used |
| path | char [] | Holds the path the client requested |
| ip | char [] | Holds the clients IP |
| port | int | Holds the port the client is listening to |
| socket | SOCKET | Holds the reference to the connection with the client |

```c
typedef struct
{
	int parameterCount;
	char parameters[MAX_PARAMETER_COUNT][2][MAX_BUFFER_SIZE];

	int headerLength;
	char header[MAX_BUFFER_SIZE];
	char method[MAX_METHOD_SIZE];
	char path[MAX_BUFFER_SIZE];

	char ip[MAX_IP_LENGTH];
	int port;

	SOCKET socket;
}CLIENT;
```