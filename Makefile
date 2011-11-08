GCC = gcc
OPS = -g
LINK_OPS = -lglut -lGL -lGLU -lX11  -lm -L/usr/X11R6/lib
OBJS = main.o Parser.o
TEST_OBJS = 

all: $(OBJS) Makefile
	$(GCC) $(OPS) $(LINK_OPS) $(OBJS) -o tron

main.o : main.c
	$(GCC) $(OPS) -c main.c

Parser.o : Parser.c
	$(GCC) $(OPS) -c Parser.c

clean:
	rm -rf tron .\#* \#* *.o .*~ *~ *.gch semantic.cache
