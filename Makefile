IDIR=include/
CC=gcc

GNUBLD=GNU_x86_64_0-0-1.out
WINBLD=WIN_x86_64_0-0-1.exe
MACBLD=MAC_x86_64_0-0-1.app

all:
	$(CC) -D GNU=1 -o bin/$(GNUBLD)  src/main.c
	$(CC) -D WIN=1 -o bin/$(WINBLD)  src/main.c
	$(CC) -D MAC=1 -o bin/$(MACBLD)  src/main.c

gnu:
	$(CC) -D GNU=1 -o bin/$(GNUBLD)  src/main.c
win:
	$(CC) -D WIN=1 -o bin/$(WINBLD)  src/main.c
mac:
	$(CC) -D MAC=1 -o bin/$(MACBLD)  src/main.c