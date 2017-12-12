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

Graph * readInputDataset(char *filename, Graph *g) {
    FILE *file;
    int fromId, toId;

    #ifdef DEBUG_T
    printf("\n============================\n");
    printf("\n Read Input File : START !!!\n");
    printf("\n============================\n");
    #endif
    
    file = fopen(filename, "r");
    if (file == NULL){
        printf("Error: Input Dataset File does not exist");
    }

    while (!feof(file)){
        if (fscanf(file, "%d %d", &fromId, &toId) == 2){
            if (graph_addEdge(g, fromId, toId) == 0){
                printf("Error: Vertex not added to the graph succesfully");
            }
        }
    }

    fclose(file);

    #ifdef DEBUG_T
    printf("\n============================\n");
    printf("\n Read Input File : DONE !!! \n");
    printf("\n============================\n");
    #endif
    
    return g;
}

/* 
 * Check Input Argumnents
 */
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

/*
 * Print the vertex pageRank in a file
 */
void printToFile(Graph *g, char *filename){
    FILE *file;
    int i;
    int vertices = graph_numVertices(g);

    file = fopen(filename, "w+");
    if (file == NULL){
        printf("Error: Input Dataset File does not exist");
    }

    fprintf(file, "Vertex Id \t Rank \n");

    for (i=0; i<vertices; i++){
        fprintf(file, " %d \t %f \n", i+1, graph_getVertexProb(g, i));
    }

    fclose(file);
}

int main(int argc, char **argv){
    char *filename = NULL;              /* Graph input datase file name */
    int numVertex;               /* Number of vertex */
    int numIter;                 /* Number of iterations */
    int i;                       /* Counter */
    int threadId;                /* Thread Counter */
    Graph *g;                    /* Graph object */
    pthread_t thread_handle[1024];    /* Maximum number of threads */
    clock_t start, end;          /* Start and End time variables */
    double elapsed;              /* Elapsed Time */
    char *outFileName = NULL;           /* Output File Name */

    /* Check Input arguments */
    if (argc < 6) {
        printf("Error : Input Arguments : <numOfThreads> <graph filename> <numVertex> <numIter> <outFileName>\n");
        exit(0);
    }

    numThreads = atoi(argv[1]);
    filename = argv[2];
    numVertex = atoi(argv[3]);
    numIter = atoi(argv[4]);
    outFileName = argv[5];

    if (checkInputArgs(numThreads, numVertex, numIter) == 1){
        exit(0);
    }

    g = graph_new(numVertex);       /* Create and initialize a graph instance */
    g = readInputDataset(filename, g);  /* Read Iput Dataset of Graph. */
    
    pageRank_init(g, numThreads);   /* PageRank Class Initialization */

    start = clock();

    for(i=0; i<numIter; i++) {
       for (threadId=0; threadId < numThreads; threadId++) {
           
           /* Run pagerank here */
           pthread_create(&thread_handle[threadId], NULL, pageRank_run, (void *)threadId);
       } 

       for (threadId = 0; threadId < numThreads; threadId++) {
           pthread_join(thread_handle[threadId], NULL);
       }

       pageRank_update();
    }

    end = clock();

    elapsed = (double) (end - start) / (CLOCKS_PER_SEC/1000);

    printf("%d\t%f\n", numThreads, elapsed);

    g = pageRank_getGraph();

    printToFile(g,outFileName);

    // graph_printToFile(g, outFileName);

    graph_removeAll(g);

    return 0;
}
