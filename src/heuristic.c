#include <stdio.h>
#include "lib/network.h"
#include "lib/graph.h"
#include "lib/list.h"

/**
 * @brief Allocate the servers on update rounds.
 * 
 * Time complexity (Worst case): O(V + m*E).
 * 
 * @param network The network graph.
 * @return int The minimum number of rounds required for the update.
 */
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

/**
 * @brief The main function.
 * 
 * Time complexity (Worst case): O(V + m*E).
 * 
 * @return int Program's exit status code.
 */
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