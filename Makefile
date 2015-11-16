project: library.o
	cc library.o -o project
library.o: library.c
	cc -Wall -c library.c
