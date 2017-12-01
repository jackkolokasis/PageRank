#include "pagerank.h"
#include "graph.h"
#include <pthread.h>
#include <stdlib.h>

int totalThreads;

pthread_mutex_t lock;

/*
 * Adjency Matrix NxN
 *
 * -----------------
 *  0  | 0.5 | 0 | 0
 * -----------------
 * 0.3 |  0  | 0 | 0
 * -----------------
 * 0.3 |  0  | 1 | 0.5
 * -----------------
 * 0.3 | 0.5 | 0 | 0
 * -----------------
 */

void createMatrix(){
    int i;
    int j;
    int numVertex = _Graph->v_size;

    matrix = (double **)calloc(numVertex, sizeof(double *));
    
    for(i=0; i<numVertex; i++){
        matrix[i] = 
            (double *)calloc (numVertex, sizeof(double));
    }

    for (i=0; i<numVertex; i++){
        for (j=0; j<_Graph->v[i].con_size; j++) {
            int id_x = _Graph->v[i].to_Id[j];

            matrix[id_x][i] = 1/_Graph->v[i].con_size;
        }
    }

    /* Instead of matrix is better to have two parallel
     * arrays inside
     * one for from_Id and one for the weight
     */
}


/*
 * Pagerank Initialization Propabilities
 *
 * In this step pagerank initialize all the vertices
 * with a first value.
 *
 * PR(v) = 1/N where N is the total number of vertex.
 */

void pageRank_init(){

    int i;
    int numVertex = graph_numVertices(_Graph);
    int prob = 1/numVertex;

    for (i=0; i<numVertex; i++){
        graph_initProb(_Graph, i, prob);
    }

    createMatrix();
}

/*
 * Pagerank Running the algorithm.
 *
 * This algorithm is running by the created threads.
 * On every superstep calculates a new propability
 * for each vertex.
 *
 * PR(v) = ((1-d)/N ) +  SUM { PR(j)/L(j)}
 *                    (j)NinDeg(v)
 *
 */

void* pageRank_run(void *args){
    int tId = *(int *) args;    /* Thread Id */
    int l_bound;                /* Lower Bound */
    int u_bound;                /* Upper Bound */
    int numVertex = _Graph->v_size;

    l_bound = (numVertex/totalThreads) *tId;
    u_bound = l_bound + (numVertex/totalThreads);


    /* Divide the array according the threads ids
     * Use init probs multiply with.
     */
}

/*
 * Set the Graph to run the pageRank
 *
 */

void pageRank_setGraph(Graph *g){
   _Graph = g;
}

/*
 * Get the Graph with the new propabilities
 *
 */
Graph* pageRank_getGraph(){
    return _Graph;
}

void pageRank_stop(){
    graph_remove(_Graph);
    pthread_mutex_destroy(&lock);
}


void pageRank_start(int threads){
    totalThreads = threads;
}
