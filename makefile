all: race

race: main.o 
	g++ main.o  -o race

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm -rf *.o race