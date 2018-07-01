#include <stdio.h>
#include "lib/network.h"
#include "lib/graph.h"
#include "lib/list.h"

/**
 * @brief Check if the network update rounds allocation is valid.
 * 
 * Time complexity: O(V + E).
 * 
 * @param network The network graph.
 * @return int 1 for valid. 0 for invalid.
 */
int Network_isAllocationValid(const Graph *network) {
    Vertex **connections = Graph_getVertices(network);
    Vertex *serverVertex;
    int validAllocation = 1;
    for (int i = 0; i < Graph_getVerticesNumber(network); i += 1) {
        serverVertex = connections[i];
        if (!Server_isRoundValid(serverVertex)) {
            validAllocation = 0;
        }
    }
    return validAllocation;
}

/**
 * @brief Check if is possible to perform an update with the specified maximum
 * number of rounds with backtracking.
 * 
 * Time complexity: O(maxRounds^(V + 1))
 * 
 * @param network The network graph.
 * @param currentVertexIndex The current vertex index.
 * @param maxRounds The maximum number of rounds.
 * @return int 1 if possible. 0 if impossible.
 */
int Network_isAllocationPossible(const Graph *network,
                                 const int currentVertexIndex,
                                 const int maxRounds) {
    int serversNumber = Graph_getVerticesNumber(network);
    if (currentVertexIndex == serversNumber) {
        return Network_isAllocationValid(network);
    }

    Vertex *currentVertex = Graph_getVertices(network)[currentVertexIndex];
    Server *currentServer = (Server *) Vertex_getData(currentVertex);
    for (int round = 1; round <= maxRounds; round += 1) {
        Server_setRound(currentServer, round);
        if (
            Server_isRoundValid(currentVertex) &&
            Network_isAllocationPossible(network,
                                    currentVertexIndex + 1,
                                    maxRounds)
        ) {
            return 1;
        }
    }

    return 0;
}

/**
 * @brief Allocate the servers on update rounds.
 * 
 * Time complexity: O(minRounds^(V + 1))
 * 
 * @param network The network graph.
 * @return int The minimum number of rounds required for the update.
 */
int Network_allocateUpdateRounds(const Graph *network) {
    int minRounds = 0;

    do {
        minRounds += 1;
    } while (!Network_isAllocationPossible(
        network,
        0,
        minRounds
    ));

    return minRounds;
}

/**
 * @brief The main function.
 * 
 * Time complexity: O(minRounds^(V + 1))
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