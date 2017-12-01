#include "graph.h"
#include <stdlib.h>
#include <stdio.h>

#define _SUCCESS 1 
#define _ERROR -1
#define GRAPH_ISEMPTY(g) ((g== NULL)? (1) : (0))

Graph* graph_new(int v_size){
    Graph *g = malloc(sizeof(Graph));
    int i;

    g->v_size = v_size;
    g->e_size = 0;
    g->v = malloc(sizeof(Vertex));

    for(i=0; i< g->v_size; i++){
        g->v[i].con_size = 0;
        g->v[i].to_Id = malloc(sizeof(int));
    }

    return g;
}

int graph_addVertex(Graph *g, int from_vId, int to_vId){
    int size;

    g->v[from_vId].con_size ++;
    size = g->v[from_vId].con_size;

    g->v[from_vId].to_Id = (int*)realloc(g->v[from_vId].to_Id, size*sizeof(int));
    g->v[from_vId].to_Id[size-1]=to_vId;

    g->v[from_vId].p_t0 = 0;
    g->v[from_vId].p_t1 = 0;
    return _SUCCESS;
}

int graph_remove(Graph *g){
    int i;

    /* Remove the outgoing vertex of every vertex */
    for (i=0; i<g->v_size; i++){
        free(g->v[i].to_Id);
    }

    free(g->v);
    free(g);

    return _SUCCESS;
}

int graph_numEdges(Graph *g){
    int i;

    if (g->e_size == 0){
        for(i=0; i<g->v_size; i++)
            g->e_size += g->v[i].con_size;
    }

    return g->e_size;
}

int graph_numVertices(Graph *g){

    if GRAPH_ISEMPTY(g) {
        printf("Error: Graph Empty \n");
        return _ERROR;
    }

    return g->v_size;
}

int graph_outEdgesCount(Graph *g, int from_vId){
    if (g != NULL)
        return g->v[from_vId].con_size;
    else {
        printf("Error: Not Allocated Graph \n");
        return _ERROR;
    }
}

int graph_initProb(Graph *g, int from_id, double prob){

    if GRAPH_ISEMPTY(g) {
        printf("Error: Graph Empty \n");
        return _ERROR;
    }

    
    g->v[from_id].p_t0 = 0;
    g->v[from_id].p_t1 = prob;

    return _SUCCESS;
}


























































