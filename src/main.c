#include <stdio.h>
#include "graph.h"
#include <time.h>
#include <math.h>
#include <mpi.h>

void main(int argc, char **argv){
    int rank, size;
    char *filename; /* Graph input datase file name */
    int numVertex; /* Number of vertex */



    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    /*Check Input arguments */
    if (argc < 5) {
        printf("Error : Input Arguments : <graph filename numVertex");
        exit(0);
    }

    strcpy(filename, argv[1]);
    numVertex = atoi(argv[2]);

    

}
