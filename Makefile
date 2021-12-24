IDIR=include/
CC=gcc

all:
	$(CC) -D GNU=1 -o bin/GNU_x86_64_0.0.1  src/main.c
	$(CC) -D WIN=1 -o bin/WIN_x86_64_0.0.1.exe  src/main.c
	$(CC) -D MAC=1 -o bin/MAC_x86_64_0.0.1.app  src/main.c

gnu:
	$(CC) -D GNU=1 -o bin/GNU_x86_64_0.0.1  src/main.c
mac:
	$(CC) -D MAC=1 -o bin/MAC_x86_64_0.0.1.app  src/main.c
win:
	$(CC) -D WIN=1 -o bin/WIN_x86_64_0.0.1.exe  src/main.c