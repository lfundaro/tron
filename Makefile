GCC = g++
OPS = -g
LINK_OPS = -lglut -lGL -lGLU -lX11 -lxml2 -lm -L/usr/X11R6/lib
OBJS = main.o Parser.o tinystr.o tinyxml.o tinyxmlerror.o tinyxmlparser.o
TEST_OBJS = 

all: $(OBJS) Makefile
	$(GCC) $(OPS) $(LINK_OPS) $(OBJS) -o tron

main.o : main.cpp
	$(GCC) $(OPS) -c main.cpp

Parser.o : Parser.cpp
	$(GCC) $(OPS) -c Parser.cpp

tinystr.o : tinystr.cpp
	$(GCC) $(OPS) -c tinystr.cpp

tinyxml.o: tinyxml.cpp
	$(GCC) $(OPS) -c tinyxml.cpp

tinyxmlerror.o: tinyxmlerror.cpp
	$(GCC) $(OPS) -c tinyxmlerror.cpp

tinyxmlparser.o: tinyxmlparser.cpp
	$(GCC) $(OPS) -c tinyxmlparser.cpp

clean:
	rm -rf tron test .\#* \#* *.o .*~ *~ *.gch semantic.cache
