all: main mouseActions cursorpos click
CXXFLAGS=-Wall -g
CXX=g++
main: main.o
	$(CXX) -o $@ $^
click: click.o
	$(CXX) -o $@ $^
cursorpos: cursorpos.o
	$(CXX) -o $@ $^
clean:
	rm -f *.o *.exe