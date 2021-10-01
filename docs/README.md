# Project SERV

**SERV** is a winsock 2 wrapper meant for making REST API's.

[Documentation](#Documentation)

[Installation](#Installation)

[Cookbook](#Cookbook)

# Installation
To install SERV simply go to the release page and download the latest version. Then just move it into the folder your source is stored in. The only added compiler flag you will need is `-lWS2_32 ` and you will need to `#include "SERV.c"`. To add the flag you should look up a guide for (the compiler you are using as there are just too many IDE's to go over.

# Cookbook


# Documentation
## Functions 
[SERV_Setup()](##SERV_Setup())

[SERV_Shutdown()](#SERV_Shutdown())

[SERV_ParseArguments()](#SERV_ParseArguments())

[SERV_GetParameter()](#SERV_GetParameter())

[SERV_StartServer()](#SERV_StartServer())

[SERV_Connect()](#SERV_Connect())

[SERV_CloseConnection()](#SERV_CloseConnection())

[SERV_MatchPath()](#SERV_MatchPath())

[SERV_SendRaw()](#SERV_SendRaw())

[SERV_SendText()](#SERV_SendText())

[SERV_SendJson()](#SERV_SendJson())

[SERV_SendHTML()](#SERV_SendHTML())

[SERV_SendPageNotFound()](#SERV_SendPageNotFound())

[SERV_SendInvalidArguments()](#SERV_SendInvalidArguments())

[SERV_SendBadRequest()](#SERV_SendBadRequest())

[SERV_SendForbidden()](#SERV_SendForbidden())

[SERV_SendUnauthorized()](#SERV_SendUnauthorized())

[SERV_SendImATeapot()](#SERV_SendImATeapot())

[SERV_SendImage()](#SERV_SendImage())

[SERV_SendMP4()](#SERV_SendMP4())

## Structs
[CLIENT](#CLIENT)
[SERVER](#SERVER)
[HOST](#HOST)

## SERV_Setup()
