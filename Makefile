all: build run

build:
	gcc src/main.c -o bin/SERV.exe -W -Wall -Werror -lWS2_32 

run:
	cd bin; ./SERV.exe