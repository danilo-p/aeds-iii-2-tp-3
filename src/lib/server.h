#include "graph.h"

#ifndef SERVER_H
#define SERVER_H

typedef struct server Server;

int Server_getRound(Server *server);

Graph * Network_buildGraph(int *n, int *m);

void Network_destroyGraph(Graph *graph);

void Network_allocateUpdateRounds(Graph *graph);

void Network_saveRoundsAndAllocation(Graph *graph);

#endif