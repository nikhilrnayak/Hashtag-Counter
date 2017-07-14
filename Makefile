all:
	g++ -g -o fibonacciHeap.o -c fibonacciHeap.cpp
	g++ -g -o hashtagcounter readLine.cpp fibonacciHeap.o -std=c++11

fibonacciHeap:	fibonacciHeap.cpp
		g++ -g -o $@.o -c $^

hashtagcounter:	readLine.cpp	
			g++ -g -o $@ $^ fibonacciHeap.o -std=c++11

clean:
	rm fibonacciHeap.o hashtagcounter *output*.txt
