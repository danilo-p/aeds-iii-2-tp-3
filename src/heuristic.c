#include <stdio.h>
#include "lib/server.h"
#include "lib/graph.h"

int main() {
    int n, m;
    Graph *graph = Grid_buildGraph(&n, &m);
    printf("%d\n", Grid_getMinUpdateRounds(graph));
    Grid_destroyGraph(graph);
    return 0;
}