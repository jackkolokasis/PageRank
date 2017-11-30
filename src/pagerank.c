#include "pagerank.h"
#include "graph.h"

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

void* pageRank_run(void * args){
 /* To DO
  * 
  * This function is responsible for the
  * algorithm. Create that
  *
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

