#include <stdio.h>
#include "lib/server.h"
#include "lib/graph.h"

int main() {
    int n, m;
    Graph *graph = Network_buildGraph(&n, &m);
    Network_allocateUpdateRounds(graph);
    Network_saveRoundsAndAllocation(graph);
    Network_destroyGraph(graph);
    return 0;
}