#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "server.h"
#include "graph.h"

const char *MIN_ROUNDS_OUTPUT_FILE_NAME = "rodada.txt";
const char *ALLOCATION_OUTPUT_FILE_NAME = "alocacao.txt";

struct server {
    int id;
    int round;
};

Server * Server_create(int id) {
    Server *server = (Server *) malloc(sizeof(Server));
    server->id = id;
    server->round = 0;
    return server;
}

int Server_getId(Server *server) {
    return server->id;
}

int Server_getRound(Server *server) {
    return server->round;
}

void Server_setRound(Server *server, int round) {
    server->round = round;
}

void Server_destroy(Server *server) {
    free(server);
}

Graph * Network_buildGraph(int *n, int *m) {
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

void Network_destroyGraph(Graph *graph) {
    int i;
    for (i = 0; i < Graph_getVerticesNumber(graph); i += 1) {
        Vertex *vertex = Graph_getVertices(graph)[i];
        Server_destroy(Vertex_getData(vertex));
        Vertex_destroy(vertex);
    }
    Graph_destroy(graph);
}

int Server_checkConnections(Vertex* serverVertex) {
    Server *server = (Server *) Vertex_getData(serverVertex);
    printf("Server_checkConnections - %d %d\n", Server_getId(server), Server_getRound(server));
    List *connections = Vertex_getEdges(serverVertex);
    for (int i = 0; i < List_getSize(connections); i += 1) {
        Vertex *connectedVertex = (Vertex *) List_getItem(connections, i);
        Server *connectedServer = (Server *) Vertex_getData(connectedVertex);
        printf("Server_checkConnections - checking %d %d\n", Server_getId(connectedServer), Server_getRound(connectedServer));
        if (Server_getRound(server) == Server_getRound(connectedServer)) {
            printf("Server_checkConnections - failed!\n");
            return 0;
        }
    }
    printf("Server_checkConnections - ok!\n");
    return 1;
}

void Server_setMinimumUpdateRound(Vertex* serverVertex) {
    Server *server = Vertex_getData(serverVertex);
    printf("Server_setMinimumUpdateRound - %d\n", Server_getId(server));
    int minimum = 0;
    do {
        minimum += 1;
        Server_setRound(server, minimum);
        printf("Server_setMinimumUpdateRound - trying with %d\n", minimum);
    } while (!Server_checkConnections(serverVertex));
    printf("Server_setMinimumUpdateRound - found %d!\n", minimum);
}

int compareServers(const void *a, const void *b) {
    Vertex *vertexA = (*((Vertex **) a));
    Vertex *vertexB = (*((Vertex **) b));
    Server *serverA = Vertex_getData(vertexA);
    Server *serverB = Vertex_getData(vertexB);
    return serverA->round > serverB->round;
}

void Network_saveRoundsAndAllocation(Graph *graph, int minRounds) {
    Vertex **vertices = Graph_getVertices(graph);
    int verticesNumber = Graph_getVerticesNumber(graph);
    FILE *file;
    Server *server;

    file = fopen(MIN_ROUNDS_OUTPUT_FILE_NAME, "w");
    fprintf(file, "%d\n", minRounds);
    printf("%d\n", minRounds);
    fclose(file);

    file = fopen(ALLOCATION_OUTPUT_FILE_NAME, "w");
    for (int i = 0; i < verticesNumber; i += 1) {
        server = (Server *) Vertex_getData(vertices[i]);
        fprintf(file, "%d %d\n", server->id, server->round);
        printf("%d %d\n", server->id, server->round);
    }
    fclose(file);
}