all: build run

build:
	gcc main.c -o SERV.exe -W -Wall -Werror -lWS2_32

run:
	./SERV.exe