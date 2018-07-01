#include <stdio.h>
#include "lib/server.h"
#include "lib/graph.h"
#include "lib/list.h"

int allocateUpdateRounds(Graph *graph) {
    int i, minRounds = 0;
    int verticesNumber = Graph_getVerticesNumber(graph);
    Vertex **vertices = Graph_getVertices(graph);
    for (i = 0; i < verticesNumber; i += 1) {
        Vertex *serverVertex = vertices[i];
        Server *server = (Server *) Vertex_getData(serverVertex);
        Server_setMinimumUpdateRound(serverVertex);
        if (Server_getRound(server) > minRounds) {
            minRounds = Server_getRound(server);
        }
    }
    return minRounds;
}

int main() {
    int n, m;
    Graph *graph = Network_buildGraph(&n, &m);
    Network_saveRoundsAndAllocation(graph, allocateUpdateRounds(graph));
    Network_destroyGraph(graph);
    return 0;
}