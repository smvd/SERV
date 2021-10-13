# SERV_SendData
`SERV_SendData()` is declared in `SERV_Sending.c` and is used for sending data to the client.
It logs the clients IP and PORT and will exit upon failing.

| name | type | use |
|------|------|-----|
| client | CLIENT | Holds a reference to the clients connection |
| type | int | Holds the type of data to be sent
| data | char [] | Holds the raw bytes meant to get sent to the client |
| isFile | int | Flag for weather data holds a path |

| type |
|------|
| TYPE_TEXT |
| TYPE_PHP |
| TYPE_JAVASCRIPT |
| TYPE_CSS |
| TYPE_BIN |
| TYPE_HTML |
| TYPE_RTF |
| TYPE_PDF |
| TYPE_ODT |
| TYPE_DOC |
| TYPE_XLS |
| TYPE_ODS |
| TYPE_CSV |
| TYPE_OTF |
| TYPE_TTF |
| TYPE_JSON |
| TYPE_XML |
| TYPE_ZIP |
| TYPE_7ZIP |
| TYPE_TAR |
| TYPE_RAR |
| TYPE_GZIP |
| TYPE_BZIP |
| TYPE_BZIP2 |
| TYPE_WEBP |
| TYPE_TIFF |
| TYPE_SVG |
| TYPE_PNG |
| TYPE_JPEG |
| TYPE_ICON |
| TYPE_GIF |
| TYPE_BMP |
| TYPE_WEBM |
| TYPE_MPEG |
| TYPE_MP4 |
| TYPE_WEBA |
| TYPE_WAV |
| TYPE_OPUS |
| TYPE_MP3 |
| TYPE_MIDI |

```c
void SERV_SendData(CLIENT client, int type, char data[], int isFile)
```