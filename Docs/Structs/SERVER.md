# Structs/SERVER
`SERVER` is defined in `SERV_Struct.c` and is meant to hold the basic server settings. It wraps the  `sockaddr_in` struct from winsock, it also includes a `SOCKET` type named listener.

```c
typedef struct
{
	struct sockaddr_in config;
	SOCKET listener;
}SERVER;
```