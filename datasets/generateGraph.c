#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printToFile(char *fileName, int **matrix, int numVertices){
    FILE *file;
    int i, j;

    file = fopen(fileName, "w+");

    for(i=0; i<numVertices; i++){
        for (j=0; j<numVertices; j++){
            if(matrix[i][j] == 1){
                fprintf(file, "%d\t%d\n",i+1, j+1);
            }
        }
    }

    fclose(file);
}

void main(int argc, char* argv[]){
    int **matrix;
    int numVertices;
    int numEdges;
    int i, j, counter;
    char *filename;

    numVertices = atoi(argv[1]);
    numEdges = atoi(argv[2]);
    filename = argv[3];

    matrix = (int **) calloc(numVertices, sizeof(int *)); 
    for(i=0; i<numVertices; i++){
        matrix[i] = (int *)calloc(numVertices, sizeof(int));
    }

    /*
     * 10000 * 10000
     * edges : 1000 000
     *
     */

    counter = 0;
    srand(time(NULL));
    while(counter < numEdges){
        i = rand()%numVertices;
        j = rand()%numVertices;

        if (i == j){
            continue;
        }
        else if (matrix[i][j] == 1){
            continue;
        }
        else{
            matrix[i][j] = 1;
            counter ++;
        }
    }

    printToFile(filename, matrix, numVertices);

}


