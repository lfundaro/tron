GCC = gcc
OPS = -g
LINK_OPS = -lglut -lGL -lGLU -lX11  -lm -L/usr/X11R6/lib
OBJS = main.o Parser.o Elementos.o
TEST_OBJS = 

all: $(OBJS) Makefile
	$(GCC) $(OPS) $(LINK_OPS) $(OBJS) -o tron

main.o : main.cpp
	$(GCC) $(OPS) -c main.cpp

Parser.o : Parser.c
	$(GCC) $(OPS) -c Parser.c

Elementos.o: Elementos.cpp
	$(GCC) $(OPS) -c Elementos.cpp

clean:
	rm -rf tron .\#* \#* *.o .*~ *~ *.gch semantic.cache
