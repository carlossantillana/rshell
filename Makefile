CC=g++
CC_FLAGS=-ansi -pedantic -W -Wall -Werror
EXEC= rshell
SOURCES=$(wildcard src/*.cc)
OBJECTS=$(SOURCES:.cc=.o)

$(EXEC): $(OBJECTS)
		$(CC) $(CC_FLAGS) $(OBJECTS) -o rshell && mkdir ./bin && mv rshell bin

%.o: %.cc
		$(CC) -c $(CC_FLAGS) $< -o $@

clean:
		rm -rf $(EXEC) $(OBJECTS) ./bin
		#rm -rf *~ *.o ./bin


#g++ -c -ansi -pedantic -W -Wall -Werror main.cc -o main.o
#g++ -c -ansi -pedantic -W -Wall -Werror execution.cc -o execution.o
#g++ -c -ansi -pedantic -W -Wall -Werror read.cc -o read.o
#g++ main.o execution.o read.o -o rshell
