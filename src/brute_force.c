#include <stdio.h>
#include "lib/network.h"
#include "lib/graph.h"
#include "lib/list.h"

int Network_isAllocationPossible(const Vertex *serverVertex,
                                 const int maxRounds) {
    if (Server_setMinimumUpdateRound(serverVertex) > maxRounds) {
        return 0;
    }

    List *serverConnections = Vertex_getEdges(serverVertex);
    for (int i = 0; i < List_getSize(serverConnections); i += 1) {
        Vertex *connectedVertex = (Vertex *) List_getItem(serverConnections, i);
        Server *connectedServer = (Server *) Vertex_getData(connectedVertex);
        if (
            !Server_getRound(connectedServer) &&
            !Network_isAllocationPossible(connectedVertex, maxRounds)
        ) {
            return 0;
        }
    }

    return 1;
}

int Network_allocateUpdateRounds(const Graph *network) {
    int minRounds = 0;

    do {
        minRounds += 1;
    } while (!Network_isAllocationPossible(
        Graph_getVertices(network)[0],
        minRounds
    ));

    return minRounds;
}

int main() {
    int n, m;
    Graph *network = Network_build(&n, &m);
    Network_saveRoundsAndAllocation(
        network,
        Network_allocateUpdateRounds(network)
    );
    Network_destroy(network);
    return 0;
}