# SERV_MatchPath
`SERV_MatchPath()` is defined in `SERV_Parameters.c` and is used to check the path the client has requested.
It returns 1 if the client requested the path.

| name | type | use |
|------|------|-----|
| client | CLIENT | Holds a reference to the client |
| path | char [] | Holds the path to test against |

```c
int SERV_MatchPath(CLIENT client, char path[]);
```