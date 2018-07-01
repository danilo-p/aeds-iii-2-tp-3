#include <stdio.h>
#include "lib/server.h"
#include "lib/graph.h"
#include "lib/list.h"

int allocateUpdateWithMaxRounds(Vertex *serverVertex, int maxRounds) {
    Server *server = (Server *) Vertex_getData(serverVertex);
    printf("allocateUpdateWithMaxRounds %d - Starting\n", Server_getId(server));
    Server_setMinimumUpdateRound(serverVertex);

    printf("allocateUpdateWithMaxRounds %d - min possible round = %d\n", Server_getId(server), Server_getRound(server));
    if (Server_getRound(server) > maxRounds) {
        printf("allocateUpdateWithMaxRounds %d - overflows max round\n", Server_getId(server));
        return 0;
    }

    printf("allocateUpdateWithMaxRounds %d - max round limit is ok. Going down...\n", Server_getId(server));
    List *connections = Vertex_getEdges(serverVertex);
    for (int i = 0; i < List_getSize(connections); i += 1) {
        Vertex *connectedVertex = (Vertex *) List_getItem(connections, i);
        Server *connectedServer = (Server *) Vertex_getData(connectedVertex);
        if (
            !Server_getRound(connectedServer) &&
            !allocateUpdateWithMaxRounds(connectedVertex, maxRounds)
        ) {
            printf("allocateUpdateWithMaxRounds %d - connections checked and it is impossible. Going up...\n", Server_getId(server));
            return 0;
        }
    }

    printf("allocateUpdateWithMaxRounds %d - Possible solution found. Going up...\n", Server_getId(server));
    return 1;
}

int allocateUpdateRounds(Graph *graph) {
    int minRounds = 0;
    do {
        minRounds += 1;
    } while (!allocateUpdateWithMaxRounds(
        Graph_getVertices(graph)[0],
        minRounds
    ));
    return minRounds;
}

int main() {
    int n, m;
    Graph *graph = Network_buildGraph(&n, &m);
    Network_saveRoundsAndAllocation(graph, allocateUpdateRounds(graph));
    Network_destroyGraph(graph);
    return 0;
}