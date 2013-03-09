stringsub: main.o stringsubber.o
	g++ -Wall -g -o stringsub main.o stringsubber.o

stringsubber.o: stringsubber.cpp 
	g++ -Wall -g -c stringsubber.cpp 

clean:
	rm -f stamping main.o *~