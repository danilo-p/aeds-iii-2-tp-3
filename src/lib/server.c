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

int Server_getRound(Server *server) {
    return server->round;
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

void Network_allocateUpdateRounds(Graph *graph) {
    int i, j, rounds = 1;
    int verticesNumber = Graph_getVerticesNumber(graph);
    Vertex **vertices = Graph_getVertices(graph);
    for (i = 0; i < verticesNumber; i += 1) {
        Vertex *serverVertex = vertices[i];
        List *serverEdges = Vertex_getEdges(serverVertex);
        int available[rounds];
        for (j = 0; j < rounds; j += 1) { available[j] = 1; }
        for (j = 0; j < List_getSize(serverEdges); j += 1) {
            Vertex *connectedVertex = (Vertex *) List_getItem(serverEdges, j);
            Server *connectedServer = (Server *) Vertex_getData(connectedVertex);
            if (connectedServer->round > 0) {
                available[connectedServer->round - 1] = 0;
            }
        }
        Server *server = (Server *) Vertex_getData(serverVertex);
        for (j = 0; j < rounds; j += 1) {
            if (available[j]) {
                server->round = j + 1;
                break;
            }
        }
        if (!server->round) {
            server->round = ++rounds;
        }
    }
}

int compareServers(const void *a, const void *b) {
    Vertex *vertexA = (*((Vertex **) a));
    Vertex *vertexB = (*((Vertex **) b));
    Server *serverA = Vertex_getData(vertexA);
    Server *serverB = Vertex_getData(vertexB);
    return serverA->round > serverB->round;
}

void Network_saveRoundsAndAllocation(Graph *graph) {
    Vertex **vertices = Graph_getVertices(graph);
    int verticesNumber = Graph_getVerticesNumber(graph);
    FILE *file;
    Server *server;

    qsort(
        vertices,
        verticesNumber,
        sizeof(Vertex *),
        compareServers
    );

    file = fopen(MIN_ROUNDS_OUTPUT_FILE_NAME, "w");
    server = (Server *) Vertex_getData(vertices[verticesNumber - 1]);
    fprintf(file, "%d\n", server->round);
    printf("%d\n", server->round);
    fclose(file);

    file = fopen(ALLOCATION_OUTPUT_FILE_NAME, "w");
    for (int i = 0; i < verticesNumber; i += 1) {
        server = (Server *) Vertex_getData(vertices[i]);
        fprintf(file, "%d %d\n", server->id, server->round);
        printf("%d %d\n", server->id, server->round);
    }
    fclose(file);
}