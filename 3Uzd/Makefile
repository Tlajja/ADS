bankSim.exe: main.c bank.o queue.o BigInt.o
	gcc -std=c99 -o bankSim.exe main.c bank.o queue.o BigInt.o

bank.o: bank.c bank.h
	gcc -c -std=c99 bank.c

queue.o: queue.c queue.h
	gcc -c -std=c99 queue.c

BigInt.o: BigInt.c BigInt.h
	gcc -c -std=c99 BigInt.c






