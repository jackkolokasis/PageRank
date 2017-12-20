#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* 
 * Print the generated Graph in an output file
 *
 * @param fileName  : Name of the output file
 * @param matrix    : Matrix containing the graph.
 * @param numVertices: Total number of vertex of the graph
 */
void printToFile(char *fileName, int **matrix, int numVertices){
    FILE *file;     /* File descriptor  */
    int i, j;

    /* Open the file to append the graph */
    file = fopen(fileName, "w+");

    for(i=0; i<numVertices; i++){
        for (j=0; j<numVertices; j++){
            if(matrix[i][j] == 1){
                fprintf(file, "%d\t%d\n",i+1, j+1);
            }
        }
    }

    /* Close the file */
    fclose(file);
}

int main(int argc, char* argv[]){
    int **matrix;           /* Matrix to save the generated graph */
    int numVertices;        /* Total number of vertices           */
    int numEdges;           /* Total number of edges              */
    int i, j, counter;      
    char *filename;         /* Output filename                    */

    numVertices = atoi(argv[1]);
    numEdges = atoi(argv[2]);
    filename = argv[3];
    
    /* Allocate memmory for the matrix */
    matrix = (int **) calloc(numVertices, sizeof(int *)); 
    for(i=0; i<numVertices; i++){
        matrix[i] = (int *)calloc(numVertices, sizeof(int));
    }

    /* Generate the new graph */
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

    /* Save us file */
    printToFile(filename, matrix, numVertices);

    return 0;

}


