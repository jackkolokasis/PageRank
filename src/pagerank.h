#ifndef __PAGERANK_H
#define __PAGERANK_H
#include "graph.h"

/*
 * PageRank Initialization
 *
 * @param threads Total number of threads
 * @param g Graph
 *
 */
extern void pageRank_init(Graph *g, int threads);

/*
 * PageRank start algorithm with initialized probs
 *
 */
extern void pageRank_start();

/*
 * Pagerank run algorithm function
 *
 * @param arguments The thread Id
 *
 */
extern void* pageRank_run(void *arguments);

/*
 * Pagerank update all vertices prob at each end of superStep.
 *
 * @param arguments The thread Id
 *
 */
extern void* pageRank_update(void *arguments);

/*
 * Get the Grapha with the probapilities of each vertex
 *
 */
extern Graph* pageRank_getGraph();

#endif
