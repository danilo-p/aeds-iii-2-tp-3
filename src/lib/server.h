#include "graph.h"

#ifndef SERVER_H
#define SERVER_H

typedef struct server Server;

int Server_getRound(Server *server);

Graph * Grid_buildGraph(int *n, int *m);

void Grid_destroyGraph(Graph *graph);

int Grid_getMinUpdateRounds(Graph *graph);

#endif