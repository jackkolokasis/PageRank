#--------------------------------------
#
# Author : Jack Kolokasis
# email  : kolokasis@csd.uoc.gr
#
#--------------------------------------

CC=gcc
CFLAGS= -Wall -pedantic
LIBS = -lpthread

all: graphGen_exe

graphGen_exe: generateGraph.o	
	$(CC) $(CFLAGS) generateGraph.o -o graphGen_exe $(LIBS)

generateGraph.o: generateGraph.c
	$(CC) $(CFLAGS) -c generateGraph.c -o generateGraph.o

generate: 
	./graphGen_exe 10000 10000000 graph_10000_10000000.txt
	./graphGen_exe 10000 1000000 graph_10000_1000000.txt
	./graphGen_exe 100000 20000000 graph_100k_20m.txt

clean:
	rm -rf *.o graphGen_exe

removeAll:
	rm -rf *o graphGen_exe graph_*

