IDIR=include/
CC=gcc

GNUBLD=GNU_x86_64_0-0-1.out
WINBLD=WIN_x86_64_0-0-1.exe
MACBLD=MAC_x86_64_0-0-1.app

GNUFLG=-D GNU=1
WINFLG=-D WIN=1
MACFLG=-D MAC=1

all:
	$(CC) $(GNUFLG) -o bin/$(GNUBLD)  src/main.c
	$(CC) $(WINFLG) -o bin/$(WINBLD)  src/main.c
	$(CC) $(MACFLG) -o bin/$(MACBLD)  src/main.c

gnu:
	$(CC) $(GNUFLG) -o bin/$(GNUBLD)  src/main.c
win:
	$(CC) $(WINFLG) -o bin/$(WINBLD)  src/main.c
mac:
	$(CC) $(MACFLG) -o bin/$(MACBLD)  src/main.c