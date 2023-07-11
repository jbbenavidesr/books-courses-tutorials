timber: timber.o
	g++ -o timber timber.o -lsfml-graphics -lsfml-window -lsfml-system

timber.o: main.cpp
	g++ -c -o timber.o main.cpp

clean:
	rm timber timber.o