#--------------------------------------
#
# Author : Jack Kolokasis
# email  : kolokasis@csd.uoc.gr
#
#--------------------------------------

CC=gcc
CFLAGS= -Wall -pedantic
LIBS = -lpthread
NUMA =

all: pagerank_exe

pagerank_exe: main.o pagerank.o graph.o
	$(CC) $(CFLAGS) main.o pagerank.o graph.o -o pagerank_exe $(LIBS)

main.o: main.c pagerank.h graph.h
	$(CC) $(CFLAGS) -c main.c -o main.o

pagerank.o: pagerank.c pagerank.h graph.h
	$(CC) $(CFLAGS) $(NUMA) -c pagerank.c -o pagerank.o $(LIBS)

graph.o: graph.c graph.h
	$(CC) $(CFLAGS) -c graph.c -o graph.o

clean:
	rm -rf *.o pagerank_exe

cleanOut:
	rm -rf results.csv

removeAll: clean cleanOut 

