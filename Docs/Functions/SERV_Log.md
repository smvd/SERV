# SERV_Log
`SERV_Log()` is defined in `SERV_Logging.c` and is used to log the SERVs actions.
It will log a message with the given type and generate a timestamp along it.
This function is however meant to only be used internaly, for debugging you should use the `BUG` macro instead.

| name | type | use |
|------|------|-----|
| message | char * | Holds the message to be logged |
| type | int | Holds the type to be logged |

```c
void SERV_Log(char * message, int type);
```