#include <stdio.h>
#include "graph.h"
#include <time.h>
#include <math.h>
#include "mpi.h"


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

        fclose(file)
    }
}

/*
 * Initialize vertex with prob=1
 * Sum PR(u)/L(u)
 *
 */

pageRank_init(Graph *g){

}


void main(int argc, char **argv){
    int rank, size;
    char *filename; /* Graph input datase file name */
    int numVertex;  /* Number of vertex */
    double d=0.85;   /* Dambing factor */
    int i, j, k;
    double sum;
    Graph *g;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    /*Check Input arguments */
    if (argc < 3) {
        printf("Error : Input Arguments : <graph filename> <numVertex> \n");
        exit(0);
    }

    strcpy(filename, argv[1]);
    numVertex = atoi(argv[2]);
    
    /*
     * Create and initialize a graph instance 
     * 
     */
    
    g = graph_new(numVertex);
   
    readInputdataset(filename, g);




    

}
