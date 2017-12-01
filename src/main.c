#include <stdio.h>
#include "graph.h"
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "pagerank.h"

#define MAX 1024
#define _ERROR 1
#define _SUCCESS 0 

int numThreads;     /* Number of threads */

/*
 * Read Input File.
 * 
 * Input dataset is an Edge List File of format: 
 *  <srcId> <dstId>
 *
 * Store all this file in the Graph Object.
 */

void readInputDataset(char *filename, Graph *g) {
    FILE *file;
    int fromId, toId;
    int tmp_size;

    file = fopen(filename, "r");
    if (file == NULL){
        printf("Error: Input Dataset File does not exist");
    }

    while (!feof(file)){
        if (fscanf(file, "%d\t%d\n", &fromId, &toId)){
            if (graph_addVertex(g, fromId, toId) == 0){
                printf("Error: Vertex not added to the graph succesfully");
            }
        }

        fclose(file);
    }
}

int checkInputArgs(int num_threads, int numVertex, int numIter){
    if (num_threads < 1) {
        printf("Error: Number of threads must be equall or greater of 1\n");
        return _ERROR;
    }

    if (numVertex < 1) {
        printf("Error: Number of vertex is not valid \n");
        return _ERROR;
    }

    if (numIter <= 0){
        printf("Error: Number of itteration must be greater of 1 \n");
        return _ERROR;
    }

    return _SUCCESS;
}

void main(int argc, char **argv){
    int rank, size;
    char *filename;              /* Graph input datase file name */
    int numVertex;               /* Number of vertex */
    double d=0.85;               /* Dambing factor */
    int numIter;                 /* Number of iterations */
    int i;                       /* Counter */
    int threadId;                /* Thread Counter */
    double sum;
    Graph *g;                    /* Graph object */
    pthread_t *thread_handle;    /* Maximum number of threads */
    clock_t start, end;          /* Start and End time variables */
    double elapsed;              /* Elapsed Time */

    /* Check Input arguments */
    if (argc < 5) {
        printf("Error : Input Arguments : <numOfThreads> <graph filename> <numVertex> <numIter> \n");
        exit(0);
    }

    numThreads = atoi(argv[1]);
    strcpy(filename, argv[2]);
    numVertex = atoi(argv[3]);
    numIter = atoi(argv[4]);

    if (checkInputArgs(numThreads, numVertex, numIter) == 1){
        exit(0);
    }

    g = graph_new(numVertex);       /* Create and initialize a graph instance */
    readInputDataset(filename, g);  /* Read Iput Dataset of Graph. */
    
    pageRank_setGraph(g);           /* Pass the graph inside the Pagerank class */          

    pageRank_init();

    start = clock();

    for(i=0; i< numIter; i++) {
        for (threadId=0; threadId < numThreads; threadId ++) {
            
            /* Run pagerank here */
            pthread_create(&thread_handle[threadId], NULL, pageRank_run, &threadId);
        }

        for (threadId = 0; threadId < numThreads; threadId++) {
            pthread_join(thread_handle[threadId], NULL);
        }
    }

    end = clock();

    elapsed = (double) (end - start) / CLOCKS_PER_SEC;

    printf("\nTotal Time Program Running = %f \n", elapsed);

    /*
     * Print all the propabilities of the graph 
     * Put here the code of printing.
     * print will be a function inside the graph.
     *
     */
}
