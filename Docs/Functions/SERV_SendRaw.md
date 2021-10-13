# SERV_SendRaw
`SERV_SendRaw()` is declared in `SERV_Sending.c` and is used for sending data to the client.
It logs the clients IP and PORT and will exit upon failing.

| name | type | use |
|------|------|-----|
| client | CLIENT | Holds a reference to the clients connection |
| data | char [] | Holds the raw bytes meant to get sent to the client |

```c
void SERV_SendRaw(CLIENT client, char data[]);
```