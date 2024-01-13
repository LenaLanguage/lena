
# Compiler

CC=gcc

CFLAGS=-Wall -std=c17 -Isrc -m64 -municode -O3 -s -flto -fdata-sections -ffunction-sections -Wl,--gc-sections

OUT=lena/win64/lena.exe

OBJ=src/lena.o src/ldelay/ldelay.o

all: $(OUT)

$(OUT): $(OBJ)
	$(CC) $(CFLAGS) -o $(OUT) $(OBJ)

lena.o: src/lena.c
	$(CC) $(CFLAGS) -c src/lena.c -o src/lena.o

ldelay.o: src/ldelay/ldelay.c
	$(CC) $(CFLAGS) -c src/ldelay/ldelay.c -o src/ldelay/ldelay.o

clean:
	rm -f $(OUT)