# SERV_StartServer
`SERV_StartServer()` is defined in `SERV_Core.c` and is used to setup the server.
It returns a configured server.

| name | type | use |
|------|------|-----|
| ip | char [] | Holds the IP for the server to be hosted on |
| port | int | Holds the PORT for the server to listen to |
| maxBacklog | int | Holds the maximum ammount of clients that can connect |

```c
SERVER SERV_StartServer(char ip[], int port, int maxBacklog);
```