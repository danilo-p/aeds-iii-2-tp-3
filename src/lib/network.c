#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "graph.h"
#include "network.h"

const char *MIN_ROUNDS_OUTPUT_FILE_NAME = "rodada.txt";
const char *ALLOCATION_OUTPUT_FILE_NAME = "alocacao.txt";

struct server {
    int round;
};

static Server * Server_create() {
    Server *server = (Server *) malloc(sizeof(Server));
    server->round = 0;
    return server;
}

int Server_getRound(const Server *server) {
    return server->round;
}

void Server_setRound(Server *server, int round) {
    server->round = round;
}

void Server_destroy(Server *server) {
    free(server);
}

Graph * Network_build(int *n, int *m) {
    scanf("%d", n);
    scanf("%d", m);
    int i;
    Graph *graph = Graph_create(*n);

    for (i = 0; i < *n; i += 1) {
        Server *server = Server_create(i + 1);
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

void Network_destroy(Graph *graph) {
    int i;
    for (i = 0; i < Graph_getVerticesNumber(graph); i += 1) {
        Vertex *vertex = Graph_getVertices(graph)[i];
        Server_destroy(Vertex_getData(vertex));
        Vertex_destroy(vertex);
    }
    Graph_destroy(graph);
}

static int Server_checkConnections(const Vertex* serverVertex) {
    Server *server = (Server *) Vertex_getData(serverVertex);
    List *connections = Vertex_getEdges(serverVertex);
    for (int i = 0; i < List_getSize(connections); i += 1) {
        Vertex *connectedVertex = (Vertex *) List_getItem(connections, i);
        Server *connectedServer = (Server *) Vertex_getData(connectedVertex);
        if (Server_getRound(server) == Server_getRound(connectedServer)) {
            return 0;
        }
    }
    return 1;
}

int Server_setMinimumUpdateRound(const Vertex* serverVertex) {
    Server *server = Vertex_getData(serverVertex);

    int minRound = 0;
    do {
        minRound += 1;
        Server_setRound(server, minRound);
    } while (!Server_checkConnections(serverVertex));

    return minRound;
}

int Network_checkAllocation(const Graph *graph) {
    Vertex **vertices = Graph_getVertices(graph);
    int verticesNumber = Graph_getVerticesNumber(graph);
    Vertex *serverVertex;
    int validAllocation = 1;
    for (int i = 0; i < verticesNumber; i += 1) {
        serverVertex = vertices[i];
        if (!Server_checkConnections(serverVertex)) {
            validAllocation = 0;
        }
    }
    printf("Servers allocation is%s valid!\n", validAllocation ? "" : " NOT");
    return validAllocation;
}

void Network_saveRoundsAndAllocation(const Graph *graph, const int minRounds) {
    FILE *file;

    file = fopen(MIN_ROUNDS_OUTPUT_FILE_NAME, "w");
    fprintf(file, "%d\n", minRounds);
    printf("%d\n", minRounds);
    fclose(file);

    file = fopen(ALLOCATION_OUTPUT_FILE_NAME, "w");
    Vertex **vertices = Graph_getVertices(graph);
    int verticesNumber = Graph_getVerticesNumber(graph);
    Server *server;
    for (int i = 0; i < verticesNumber; i += 1) {
        server = (Server *) Vertex_getData(vertices[i]);
        fprintf(file, "%d %d\n", i + 1, server->round);
        printf("%d %d\n", i + 1, server->round);
    }
    fclose(file);
}