#include <stdio.h>
#include "lib/network.h"
#include "lib/graph.h"
#include "lib/list.h"

int Network_allocateUpdateRounds(const Graph *network) {
    int minRounds = 0;

    Vertex **servers = Graph_getVertices(network);
    for (int i = 0; i < Graph_getVerticesNumber(network); i += 1) {
        Vertex *serverVertex = servers[i];
        Server *server = (Server *) Vertex_getData(serverVertex);
        if (Server_setMinimumUpdateRound(serverVertex) > minRounds) {
            minRounds = Server_getRound(server);
        }
    }

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