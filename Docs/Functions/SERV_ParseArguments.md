# SERV_ParseArguments
`SERV_ParseArguments()` is defined in `SERV_Parameters.c` and is used to parse the clients request.
It returns a client with the parsed fields filled in.

| name | type | use |
|------|------|-----|
| client | CLIENT | Holds a reference to the client |

```c
CLIENT SERV_ParseArguments(CLIENT client);
```