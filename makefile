CC=gcc
CFLAGS= -g -Wall -ansi -pedantic
all: goose
goose: game.o command.o game_loop.o graphic_engine.o screen.o space.o game_reader.o player.o object.o set.o die.o
	$(CC) $(CFLAGS) game.o command.o game_loop.o graphic_engine.o screen.o space.o game_reader.o player.o object.o set.o die.o -o goose

#Objetos
game.o: game.c game.h game_reader.h player.h object.h space.h set.h die.h
	$(CC) $(CFLAGS) -c game.c
command.o: command.c command.h
	$(CC) $(CFLAGS) -c command.c
game_loop.o: game_loop.c graphic_engine.h
	$(CC) $(CFLAGS) -c game_loop.c
graphic_engine.o: graphic_engine.c graphic_engine.h screen.h
	$(CC) $(CFLAGS) -c graphic_engine.c
screen.o: screen.c screen.h
	$(CC) $(CFLAGS) -c screen.c
space.o: space.c types.h space.h set.h
	$(CC) $(CFLAGS) -c space.c
game_reader.o: game_reader.c game_reader.h game.h command.h space.h set.h
	$(CC) $(CFLAGS) -c game_reader.c
player.o: player.c player.h object.h space.h types.h
	$(CC) $(CFLAGS) -c player.c
object.o: object.c object.h space.h types.h
	$(CC) $(CFLAGS) -c object.c
set.o: set.c set.h types.h
	$(CC) $(CFLAGS) -c set.c
die.o: die.c die.h types.h
	$(CC) $(CFLAGS) -c die.c


#Borrar objetos
clean:
	rm -f *.o
tar:
	tar -czvf goose.tar.gz *.c *.h data.dat
