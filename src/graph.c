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
    g->v = malloc(v_size*sizeof(Vertex));

    for(i=0; i< g->v_size; i++){
        g->v[i].prob_0 = 0.0;
        g->v[i].prob_1 = 0.0;
        g->v[i].outDegree = 0;
        g->v[i].inDegree = 0;
        g->v[i].to_Id = malloc(sizeof(int));
        g->v[i].from_Id = malloc(sizeof(int));
    }

    return g;
}


int graph_numEdges(Graph *g){
    int i;

    if GRAPH_ISEMPTY(g) {
        printf("Error: Graph Empty \n");
        return _ERROR;
    }

    if (g->e_size == 0){
        for(i=0; i<g->v_size; i++)
            g->e_size += g->v[i].outDegree;
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


int graph_outDegree(Graph *g, int from_vId){
    if (g != NULL)
        return g->v[from_vId].outDegree;
    else {
        printf("Error: Not Allocated Graph \n");
        return _ERROR;
    }
}


int graph_inDegree(Graph *g, int from_vId){
    if (g != NULL)
        return g->v[from_vId].inDegree;
    else {
        printf("Error: Not Allocated Graph \n");
        return _ERROR;
    }
}


int graph_addEdge(Graph *g, int from_vId, int to_vId){
    int size;

    /* Update source vertex */
    g->v[from_vId -1].outDegree ++;
    size = g->v[from_vId-1].outDegree;

    g->v[from_vId-1].to_Id = (int*)realloc(g->v[from_vId-1].to_Id, size*sizeof(int));
    g->v[from_vId-1].to_Id[size-1]=to_vId;

    /* Update Destination vertex */

    g->v[to_vId-1].inDegree++; 
    size = g->v[to_vId-1].inDegree;

    g->v[to_vId-1].from_Id = (int*)realloc(g->v[to_vId-1].from_Id, size*sizeof(int));
    g->v[to_vId-1].from_Id[size -1] = from_vId;

    return _SUCCESS;
}


void graph_removeAll(Graph *g){
    int i;

    /* Remove the outgoing vertex of every vertex */
    for (i=0; i<g->v_size; i++){
        free(g->v[i].to_Id);
        free(g->v[i].from_Id);
    }

    free(g->v);
    free(g);
}


void graph_setVertexProb(Graph *g, int vId, double prob,
        int flag){

    if (flag ==1)
        g->v[vId].prob_0 = prob;
    else
        g->v[vId].prob_1 = prob;
}


double graph_getVertexProb(Graph *g, int vId){

    return g->v[vId].prob_0;
}


void graph_updateVertexProb(Graph *g, int vId){

    g->v[vId].prob_0 = g->v[vId].prob_1;
}


int graph_getVertexNeighborId(Graph *g,
        int vId, int index, int flag){

    if (flag == 0)
        return g->v[vId].from_Id[index];
    else
        return g->v[vId].to_Id[index];
}

void graph_printToFile(Graph *g, char *fileName){
    int numVertex;
    int outDegree;
    int inDegree;
    int i, j;
    FILE *file;

    file = fopen(fileName, "w+");
    if (file == NULL){
        printf("Error: Input Dataset File does not exist");
    }

    fprintf(file, "\n===================\n");
    fprintf(file, "\nGraph Printing ....\n");
    fprintf(file, "\n===================\n");

    numVertex = g->v_size;
    for (i=0; i<numVertex; i++){
        fprintf(file, "\n=================\n");
        fprintf(file, "\nVertex ID : %d\n", i+1);
        
        outDegree = g->v[i].outDegree;
        fprintf(file, "OutDegree : ");
        for(j=0; j<outDegree; j++){
            fprintf(file, "%d ", g->v[i].to_Id[j]);
        }

        fprintf(file, "\n");

        inDegree = g->v[i].inDegree;
        fprintf(file, "InDegree : ");
        for(j=0; j<inDegree; j++){
            fprintf(file, "%d ", g->v[i].from_Id[j]);
        }

        fprintf(file, "\n Probapilty : %f\n", g->v[i].prob_0);

        fprintf(file, "\n=================\n");
    }
}


    
