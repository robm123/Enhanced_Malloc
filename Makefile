

all: pa3

pa3: main.o myMalloc.o
	gcc main.o myMalloc.o -o pa3

main.o:	main.c
	gcc -c main.c

myMalloc.o: myMalloc.c
	gcc -c myMalloc.c

clean:
	rm -rf *o hello









#all: pa3


#linkList.o: myMalloc.c myMalloc.h
#	gcc -c myMalloc.c
 
#main.o: main.c myMalloc.h
#	gcc -c main.c
 
#pa3: main.o 
#	gcc -o pa3 main.o 


#clean:
#	rm -f sl
#	rm -f *.o
#	rm -f *.a
