#define _GNU_SOURCE
#include "pagerank.h"
#include "graph.h"
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

Graph* _Graph;
int totalThreads;

/*
 * Pagerank Initialization Propabilities
 *
 * In this step pagerank initialize all the vertices
 * with a first value.
 *
 * PR(v) = 1/N where N is the total number of vertex.
 */

void pageRank_init(Graph *g, int threads){

    #ifdef DEBUG_T
    printf("\n================================\n");
    printf("\nPagerank INIT\n");
    printf("\n================================\n");
    #endif
   
    _Graph = g;
    totalThreads = threads;

    #ifdef DEBUG_T
    printf("\n================================\n");
    printf("\nPagerank INIT DONE !!!\n");
    printf("\n================================\n");
    #endif

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

void* pageRank_run(void *arguments){
    int tId = (int) arguments;                   /* Thread Id      */
    int l_bound;                                 /* Lower Bound    */
    int u_bound;                                 /* Upper Bound    */
    int numVertex = graph_numVertices(_Graph);   /* Total Vertex   */
    int i, j;
    double constProb;                            /* Dumby Prob     */
    double sum, prob;
    int inDegree, tmpvId;
    cpu_set_t cpuset;                            /* Set CPU to Run */
    pthread_t thread;                            /* Thread         */
    
    #ifdef NUMA_SOCKARR
    int array[32] = {0,8,16,24,1,9,17,25,        /* Select according to thread Id on wich core to run */
                     2,10,18,26,3,11,19,27,
                     4,12,20,28,5,13,21,29,
                     6,14,22,30,7,15,23,31};
    CPU_ZERO(&cpuset);
    CPU_SET(array[tId], &cpuset);
    #endif
    
    #ifndef NUMA_SOCARR 
    if (tId >=0 && tId <8){
        CPU_SET(tId, &cpuset);
    }
    else if(tId >=8 && tId <16){
        CPU_SET(tId+8, &cpuset);
    }
    else if(tId >=16 && tId <24){
        CPU_SET(tId-8, &cpuset);
    }
    else{
        CPU_SET(tId+8, &cpuset);
    }
    #endif
    
    thread = pthread_self();
    pthread_setaffinity_np(thread, sizeof(cpu_set_t), &cpuset);
    
    l_bound = (numVertex/totalThreads) *(tId);
    u_bound = l_bound + (numVertex/totalThreads);
   
    #ifdef DEBUG_T
    printf("================================");
    printf("\nStart Running Thread ID = %d\n", tId);
    printf("================================");
    #endif

    if (tId == (totalThreads - 1)){
        u_bound = u_bound + numVertex%totalThreads;
    }

    constProb = 0.15/numVertex;                 /* (1-d)/N */
    
    for (i=l_bound; i<u_bound; i++){
        sum = 0.0;
        inDegree = graph_inDegree(_Graph, i);
        
        for (j=0; j<inDegree; j++){
            tmpvId = graph_getVertexNeighborId(_Graph, i, j, 0);
            if (graph_outDegree(_Graph, tmpvId) == 0){
                continue;
            }
            else{
                sum = sum + (graph_getVertexProb(_Graph, tmpvId) / graph_outDegree(_Graph, tmpvId));
            }
        }

        prob = constProb + (0.85 * sum);

        graph_setVertexProb(_Graph, i, prob, 0);
    }

    return NULL;
}

/*
 * Update all vertex Propabilities at the end of each superStep with the new
 * one.
 *
 */
void* pageRank_update(void *arguments){
    int tId = (int) arguments;                   /* Thread Id       */
    int l_bound;                                 /* Lower Bound     */
    int u_bound;                                 /* Upper Bound     */
    int numVertex = graph_numVertices(_Graph);   /* Total Vertex    */

    int i;

    cpu_set_t cpuset;                            /* Set CPU to Run  */
    pthread_t thread;                            /* Thread          */
    
    #ifdef NUMA_SOCKARR
    int array[32] = {0,8,16,24,1,9,17,25,        /* Select according to thread Id on wich core to run */
                     2,10,18,26,3,11,19,27,
                     4,12,20,28,5,13,21,29,
                     6,14,22,30,7,15,23,31};
    CPU_ZERO(&cpuset);
    CPU_SET(array[tId], &cpuset); 
    #endif

    #ifndef NUMA_SOCKARR
    CPU_ZERO(&cpuset);
    if (tId >=0 && tId <8){
        CPU_SET(tId, &cpuset);
    }
    else if(tId >=8 && tId <16){
        CPU_SET(tId+8, &cpuset);
    }
    else if(tId >=16 && tId <24){
        CPU_SET(tId-8, &cpuset);
    }
    else{
        CPU_SET(tId+8, &cpuset);
    }
    #endif
    
    thread = pthread_self();
    pthread_setaffinity_np(thread, sizeof(cpu_set_t), &cpuset);

    
    l_bound = (numVertex/totalThreads) *(tId);
    u_bound = l_bound + (numVertex/totalThreads);

    if (tId == (totalThreads - 1)){
        u_bound = u_bound + numVertex%totalThreads;
    }

    for(i=l_bound; i<u_bound; i++){
        graph_updateVertexProb(_Graph, i);
    }

    return NULL;
}

/*
 * Get the Graph with the new propabilities
 *
 */

Graph* pageRank_getGraph(){
    return _Graph;
}

