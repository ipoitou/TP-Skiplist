all : skiplist

skiplist: main.o skiplist.o element.o
	g++ -g main.o skiplist.o element.o -o skiplist

main.o: main.cpp skiplist.h element.h
	g++ -g -Wall -c main.cpp

skiplist.o: skiplist.h skiplist.cpp element.h
	g++ -g -Wall -c skiplist.cpp

element.o: element.h element.cpp
	g++ -g -Wall -c element.cpp


clean:
	rm *.o

veryclean: clean
	rm *.out
