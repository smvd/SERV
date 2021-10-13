# SERV_BuildHeader
`SERV_BuildHeader()` is declared in `SERV_Sending.c` and is used for building a return header.
It will output a basic http/1.1 header, this function is not meant to be used by the client but is intended for `SERV_SendStatus()` to simplify the code.

| name | type | use |
|------|------|-----|
| buffer | char * | Holds a pointer to the buffer where the header needs to be stored |
| code | int | Holds the value for the http code to be put in the header |
| text | char [] | Holds the text that should be placed in the header |

```c
void SERV_BuildHeader(char * buffer, int code, char text[]);
```