# SERV_GetParameter
`SERV_GetParameter()` is defined in `SERV_Parameters.c` and is used to retrieve the value of a parameter.
It returns the index where the value is stored.
To acces the stored value acces `client.parameters[index][1]`.

| name | type | use |
|------|------|-----|
| client | CLIENT | Holds a reference to the client |
| key | char [] | Holds the name of the key value pair |

```c
int SERV_GetParameter(CLIENT client, char key[])
```