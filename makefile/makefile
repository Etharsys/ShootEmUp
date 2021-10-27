# Makefile Projet Shoot'em up

CC=gcc
CFLAGS=-Wall -ansi -g `pkg-config --cflags MLV`
LDFLAGS=-lMLV -lm `pkg-config --libs MLV`
DEFINERS=../include/Balancing.h ../include/Error.h ../include/Graphic_Values.h
OBJ=Game_loop.o Entity.o Graphic.o Collision.o Moove.o Star.o Shoot.o Spawn.o Parseur.o
OBJ_BIN=../bin/Game_loop.o ../bin/Entity.o ../bin/Graphic.o ../bin/Collision.o ../bin/Moove.o ../bin/Star.o ../bin/Shoot.o ../bin/Spawn.o ../bin/Parseur.o

# Exe
Shoot: $(OBJ)
	$(CC) -o ../bin/Shoot $(OBJ_BIN) $(CFLAGS) $(LDFLAGS)

# Object files
Game_loop.o: ../src/Game_loop.c ../include/Game_loop.h ../include/Entity.h ../include/Graphic.h ../include/Collision.h ../include/Moove.h  ../include/Star.h ../include/Shoot.h  ../include/Spawn.h ../include/Parseur.h $(DEFINERS)
	$(CC) -c $< $(CFLAGS) -o ../bin/Game_loop.o

Parseur.o: ../src/Parseur.c ../include/Parseur.h ../include/Entity.h $(DEFINERS)
	$(CC) -c $< $(CFLAGS) -o ../bin/Parseur.o

Star.o: ../src/Star.c ../include/Star.h $(DEFINERS)
	$(CC) -c $< $(CFLAGS) -o ../bin/Star.o

Collision.o: ../src/Collision.c ../include/Collision.h ../include/Entity.h $(DEFINERS)
	$(CC) -c $< $(CFLAGS) -o ../bin/Collision.o

Moove.o: ../src/Moove.c ../include/Moove.h ../include/Collision.h ../include/Entity.h $(DEFINERS)
	$(CC) -c $< $(CFLAGS) -o ../bin/Moove.o

Entity.o: ../src/Entity.c ../include/Entity.h $(DEFINERS)
	$(CC) -c $< $(CFLAGS) -o ../bin/Entity.o -lm

Graphic.o: ../src/Graphic.c ../include/Graphic.h ../include/Entity.h ../include/Star.h $(DEFINERS)
	$(CC) -c $< $(CFLAGS) -o ../bin/Graphic.o

Spawn.o: ../src/Spawn.c ../include/Spawn.h ../include/Entity.h $(DEFINERS)
	$(CC) -c $< $(CFLAGS) -o ../bin/Spawn.o

Shoot.o: ../src/Shoot.c ../include/Shoot.h ../include/Entity.h $(DEFINERS)
	$(CC) -c $< $(CFLAGS) -o ../bin/Shoot.o



# %.o: %.c
#	  $(CC) -c $< $(CFLAGS)


# clean rules
install: Shoot
	make clean

uninstall: clean
	rm -f ../bin/Shoot

clean:
	rm -f ../bin/*.o
