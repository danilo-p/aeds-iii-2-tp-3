#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "server.h"
#include "graph.h"

struct server {
    int round;
};

Server * Server_create() {
    Server *server = (Server *) malloc(sizeof(Server));
    server->round = -1;
    return server;
}

int Server_getRound(Server *server) {
    return server->round;
}

void Server_destroy(Server *server) {
    free(server);
}

Graph * Grid_buildGraph(int *n, int *m) {
    scanf("%d", n);
    scanf("%d", m);
    int i;
    Graph *graph = Graph_create(*n);

    for (i = 0; i < *n; i += 1) {
        Server *server = Server_create();
        Vertex *vertex = Vertex_create(server);
        Graph_insertVertex(graph, vertex, i);
    }

    int v1, v2;
    for (i = 0; i < *m; i += 1) {
        scanf("%d %d", &v1, &v2);
        Vertex_setEdge(
            Graph_getVertices(graph)[v1 - 1],
            Graph_getVertices(graph)[v2 - 1],
            0
        );
    }

    return graph;
}

void Grid_destroyGraph(Graph *graph) {
    int i;
    for (i = 0; i < Graph_getVerticesNumber(graph); i += 1) {
        Vertex *vertex = Graph_getVertices(graph)[i];
        Server_destroy(Vertex_getData(vertex));
        Vertex_destroy(vertex);
    }
    Graph_destroy(graph);
}

int Grid_getMinUpdateRounds(Graph *graph) {
    int i, j;
    int rounds = -1;

    int verticesNumber = Graph_getVerticesNumber(graph);
    Vertex **vertices = Graph_getVertices(graph);
    for (i = 0; i < verticesNumber; i += 1) {
        Vertex *serverVertex = vertices[i];
        List *serverEdges = Vertex_getEdges(serverVertex);
        int minRound = -1;
        for (j = 0; j < List_getSize(serverEdges); j += 1) {
            Vertex *connectedVertex = (Vertex *) List_getItem(serverEdges, j);
            Server *connectedServer = (Server *) Vertex_getData(connectedVertex);
            if (
                (j == 0 && connectedServer->round > 0) ||
                (minRound > 0 && minRound < connectedServer->round)
            ) {
                minRound = connectedServer->round;
            }
        }
        Server *server = (Server *) Vertex_getData(serverVertex);
        server->round = minRound > 0 ? minRound - 1 : ++rounds;
    }

    return rounds;
}