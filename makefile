all: patricia findbit
	gcc  obj/patricia.o obj/findbit.o
patricia: src/patricia.c include/libpat.h
	gcc -c  -I/home/csemtech/mt2010/j.ananya/IR/include src/patricia.c  -o obj/patricia.o
findbit:
	gcc -c  src/findbit.c  -o obj/findbit.o
