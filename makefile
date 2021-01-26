# makefile
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)
CFLAGS= -Wall -g2 -fPIC # -DDEBUG
LDFLAGS= -ldl -lSDL2
EXE=splash

	
players:
	cd pl && $(MAKE)

all: players $(OBJS)
	gcc  $(OBJS) $(LDFLAGS) -o $(EXE)


tp5: $(OBJS)
	gcc  $(OBJS) -ldl -lSDL2 -lsplash -o $(EXE)

liba: $(OBJS)
	ar crs libsplash.a actions.o player.o world.o render.o bomb.o

libso: $(OBJS)
	gcc -shared -o libsplash.so actions.o main.o player.o world.o

clean: 
	rm -f core
	rm -f *.a
	rm -f *.so
	rm -f $(OBJS)
	rm -f $(EXE)

clean_all: clean 
	cd pl && $(MAKE) clean

github:all
	git add .
	git commit -m update
	git push -u save --all 


