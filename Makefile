all: main
CXXFLAGS=-Wall -g
CXX=g++
main: main.o display.o screen.o mouse.o cputimer.o menu.o program.o
	$(CXX) -o $@ $^
clean:
	rm -f *.o *.exe