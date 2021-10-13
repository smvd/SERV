# SERV_CloseConnection
`SERV_CloseConnection()` is defined in `SERV_Connection.c` and is used to close the connection with the client.
It returns a reset version of the client.

| name | type | use |
|------|------|-----|
| client | CLIENT | Holds a reference to the client |

```c
CLIENT SERV_CloseConnection(CLIENT client);
```