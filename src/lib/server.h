#include "graph.h"

#ifndef SERVER_H
#define SERVER_H

typedef struct server Server;

int Server_getId(Server *server);

int Server_getRound(Server *server);

void Server_setRound(Server *server, int round);

void Server_setMinimumUpdateRound(Vertex* serverVertex);

Graph * Network_buildGraph(int *n, int *m);

void Network_destroyGraph(Graph *graph);

void Network_allocateUpdateRounds(Graph *graph);

void Network_saveRoundsAndAllocation(Graph *graph, int minRounds);

#endif