#ifndef __GRAPH_H_
#define __GRAPH_H_

typedef struct _vertex{
    double p_t0;
    double p_t1;
    int con_size;
    int *to_Id;
}Vertex;

typedef struct _graph {
    int v_size;
    int e_size;
    Vertex *v;
}Graph;

extern Graph *graph_new(int v_size);

extern int graph_numEdges(Graph *g);

extern int graph_numVertices(Graph *g);

extern int graph_addVertex(Graph *g, int from_vId, int to_vId);

extern int graph_remove(Graph *g);

extern int graph_outEdgesCount(Graph *g, int from_vId);

extern int graph_initProb(Graph *g, int from_id, double prob);

/* Have to complete the interface */ 

#endif
