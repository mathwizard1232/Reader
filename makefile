all: print.o reader.cpp main.cpp utility.cpp
	g++ print.o main.cpp -o main -lncurses

print.o: print.h print.cpp utility.o
	g++ -c utility.o print.cpp -lncurses

utility.o: utility.cpp
	g++ -c utility.cpp

clean:
	rm *~