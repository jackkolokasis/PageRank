#ifndef __GRAPH_H_
#define __GRAPH_H_

/* 
 * May change the structure of the graph
 *
 * from id to 
 *
 */

typedef struct _vertex{
    double prob_0;
    double prob_1;
    int outDegree;
    int inDegree;
    int *to_Id;
    int *from_Id;
}Vertex;

typedef struct _graph {
    int v_size;
    int e_size;
    Vertex *v;
}Graph;

/*
 * Create Graph Object
 *
 * @param v_size Total Number of Vertex
 * @ret   g Graph object
 *
 */
extern Graph *graph_new(int v_size);

/*
 * Count the total number of edges in the graph.
 *
 * @param g Graph
 * @ret   e_size The total number of edges
 *
 */
extern int graph_numEdge(Graph *g);

/*
 * Count the total number of vertices.
 *
 * @param g Graph
 * @ret   v_size Total number of vertices.
 *
 */
extern int graph_numVertices(Graph *g);

/*
 * Out Degree edges number of a current vertex
 *
 * @param g Graph
 * @parm  vId Vertex Id
 * @ret   outDegree Number of outdegrees of the vId vertex
 *
 */
extern int graph_outDegree(Graph *g, int vId);

/*
 * In Degree edges number of a current vertex.
 *
 * @param g Graph
 * @param vId Vertex Id
 * @ret   inDegree Number of outdegrees edged of vId vertex
 *
 */
extern int graph_inDegree(Graph *g, int vId);

/*
 * Add the edge from the vertx from_vId to the vertex to_vId, if its not there.
 *
 * @param g Graph
 * @param from_vId Source vertex
 * @param to_Id Destination Vertex
 * @ret   OK if its success, ERROR if is not
 *
 */
extern int graph_addEdge(Graph *g, int from_vId, int to_vId);

/*
 * Remove the whole graph.
 *
 * param g Graph
 */

extern void graph_removeAll(Graph *g);

/*
 * Set Propability to the Vertex.
 *
 * @param g Graph
 * @param vId Vertex Id
 * @param prob Propability of the vertex
 *
 */
extern void graph_setVertexProb(Graph *g, int vId, 
        double prob, int flag);

/*
 * Get Vertex Probability.
 *
 * @param g Graph
 * @param vId Vertex Id
 * @ret   prob The propability of the vertex
 *
 */
extern double graph_getVertexProb(Graph *g, int vId);

/*
 * Update Vertex Probability before each superStep.
 *
 * @param g Graph
 * @param vId Vertex Id
 * 
 */
extern void graph_updateVertexProb(Graph *g, int vId);

/*
 * Vertex Neighbors Ids.
 *
 * @param g Graph
 * @param vId Vertex Id
 * @param index Index of the Neigbor Id.
 * @param flag 0 for in-Neighbors and 1 for out-Neighbors
 *
 * @ret neighborId The neighborId.
 *
 */
extern int graph_getVertexNeighborId(Graph *g,
        int vId, int index, int flag);

/*
 * Print the Graph in an output file.
 *
 * @param g Graph
 * @param fileName Output file name.
 *
 */
extern void graph_printToFile(Graph *g, char *fileName);

#endif
