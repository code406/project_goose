CC=gcc
CFLAGS= -g -Wall -ansi -pedantic
all: goose
goose: game.o command.o game_loop.o graphic_engine.o screen.o space.o game_reader.o player.o object.o
	$(CC) $(CFLAGS) game.o command.o game_loop.o graphic_engine.o screen.o space.o game_reader.o player.o object.o -o goose

#Objetos
game.o: game.c
	$(CC) $(CFLAGS) -c game.c
command.o: command.c
	$(CC) $(CFLAGS) -c command.c
game_loop.o: game_loop.c
	$(CC) $(CFLAGS) -c game_loop.c
graphic_engine.o: graphic_engine.c
	$(CC) $(CFLAGS) -c graphic_engine.c
screen.o: screen.c
	$(CC) $(CFLAGS) -c screen.c
space.o: space.c
	$(CC) $(CFLAGS) -c space.c
game_reader.o: game_reader.c
	$(CC) $(CFLAGS) -c game_reader.c
player.o: player.c
	$(CC) $(CFLAGS) -c player.c
object.o: object.c
	$(CC) $(CFLAGS) -c object.c

#Borrar objetos
clean:
	rm -f *.o
