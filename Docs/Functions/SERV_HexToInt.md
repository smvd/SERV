# SERV_HexToInt
`SERV_HexToInt()` is defined in `SERV_Parameters.c` and is used to convert a hexadecimal char to an int.
It will return -1 if it cant conver the character and is case insensative.

| name | type | use |
|------|------|-----|
| c | char | Holds the character to be converted |

```c
int SERV_HexToInt(char c);
```