#include "graph.h"

#ifndef NETWORK_H
#define NETWORK_H

typedef struct server Server;

int Server_getRound(const Server *server);

void Server_setRound(Server *server, int round);

int Server_setMinimumUpdateRound(const Vertex* serverVertex);

Graph * Network_build(int *n, int *m);

void Network_destroy(Graph *graph);

void Network_saveRoundsAndAllocation(const Graph *graph, const int minRounds);

int Network_checkAllocation(const Graph *graph);

#endif