#ifndef __PAGERANK_H
#define __PAGERANK_H
#include "graph.h"

Graph* _Graph;

extern void pageRank_setGraph(Graph *g);

extern Graph* pageRank_getGraph();

extern void pageRank_init();

extern void* pageRank_run(void *arguments);


#endif
