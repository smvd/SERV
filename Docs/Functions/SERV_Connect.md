# SERV_Connect
`SERV_Connect()` is defined in `SERV_Connection.c` and is used to accept the clients request.
It returns a client with the SOCKET field filled in.

| name | type | use |
|------|------|-----|
| server | SERVER | Holds the settings for the server |

```c
CLIENT SERV_Connect(SERVER server);
```