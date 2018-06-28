#include <stdio.h>
#include "lib/server.h"
#include "lib/graph.h"

int main() {
    int n, m;
    Graph *graph = Grid_buildGraph(&n, &m);
    Grid_allocateUpdateRounds(graph);
    Grid_saveRoundsAndAllocation(graph);
    Grid_destroyGraph(graph);
    return 0;
}