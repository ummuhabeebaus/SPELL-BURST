CC=gcc
CFLAGS=-IC:/sdl2/i686-w64-mingw32/include -Wall
LDFLAGS=-LC:/sdl2/i686-w64-mingw32/lib -lSDL2 -lSDL2_image -lSDL2_mixer -lmingw32 -lSDL2main

SRC=src/main.c src/bubble_shooting.c src/word_forming.c src/utils.c
OBJ=$(SRC:.c=.o)
EXEC=spell_burst

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	del *.o
	del $(EXEC)






