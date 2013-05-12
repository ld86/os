CC=g++
CXXFLAGS=-std=c++11
LDFLAGS=-pthread
main: main.o runner.o life_server.o life.o
runner.o: runner.h
life_server.o: life_server.h
life.o: life.h
clean:
	rm -f *.o main
