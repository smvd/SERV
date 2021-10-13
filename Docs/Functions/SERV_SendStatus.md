# SERV_SendStatus
`SERV_SendStatus()` is declared in `SERV_Sending.c` and is used for sending a basic header to the client.
It logs the clients IP and PORT and will exit when it fails.

| name | type | use |
|------|------|-----|
| client | CLIENT | Holds a reference to the clients connection |
| code | int | Holds the http status code for the header |

| code | text |
|------|------|
| 100 | Continue |
| 101 | Switching Protocols |
| 102 | Processing |
| 103 | Early Hints |
| 200 | Ok |
| 201 | Created |
| 202 | Accepted |
| 203 | Non-Authoritative Information |
| 204 | No Content |
| 205 | Reset Content |
| 206 | Partial Content |
| 207 | Multi-Status |
| 208 | Already Reported |
| 226 | IM Used |
| 300 | Multiple Choices |
| 301 | Moved Permanently |
| 302 | Found |
| 303 | See Other |
| 304 | Not Modified |
| 305 | Use Proxy |
| 306 | Switch Proxy |
| 307 | Temporary Redirect |
| 308 | Permanent Redirect |
| 400 | Bad Request |
| 401 | Unauthorized |
| 402 | Payment Required |
| 403 | Forbidden |
| 404 | Not Found |
| 405 | Method Not Allowed |
| 406 | Not Acceptable | 
| 407 | Proxy Authentication Required |
| 408 | Request Time Out |
| 409 | Conflict |
| 410 | Gone |
| 411 | Length Required |
| 412 | Precondition Failed |
| 413 | Payload Too Large |
| 414 | Uri Too Long |
| 415 | Unsupported Media Type |
| 416 | Range not Satisfiable |
| 417 | Exception Failed |
| 421 | Misdirected Request |
| 422 | Unprocessable Entity |
| 423 | Locked |
| 424 | Failed Dependency |
| 425 | Too Early |
| 426 | Upgrade Required |
| 428 | Precondition Required |
| 429 | Too Many Requests |
| 431 | Request Header Field Too Large |
| 451 | Unavaillable For Legal Reasons |
| 500 | Internal Server Error |
| 501 | Not Implemented |
| 502 | Bad Gateway |
| 503 | Service Unavailable |
| 504 | Gateway Timeout |
| 505 | HTTP Version Not Supported |
| 506 | Variant Also Negotiates |
| 507 | Insufficient Storage |
| 508 | Loop detected |
| 510 | Not Extended |
| 511 | Network Authentication Required |

```c
void SERV_SendStatus(CLIENT client, int code);
```