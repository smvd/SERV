# Project SERV
SERV is a winsock2 wrapper meant to make building API's with C very easy. It removes all the boiler plate that comes with the windows headers and replaces it with a few simple functions. If your are new follow the Installation guide down below, also you should look at some of the examples in the CookBook. If you have any questions the Docs should get them anwsered otherwise i suggest opening an issue.

## Installation
To use SERV you will need to get the source code from the github release page and copy it to the folder your code is stored in. After that its fairly simple just add `-lWS2_32` to your compilation command and add `#include "SERV/SERV.h"` to the top of your program.

Installing SERV is very simple.
1. [Download](https://github.com/smvd/SERV/releases/latest) 
2. Extract the ZIP
3. Add the SERV folder to your project
4. Link `WS2_32`
5. Put `#include "SERV/SERV.h"` at the top of your source file