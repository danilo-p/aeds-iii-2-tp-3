#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "graph.h"
#include "network.h"

const char *MIN_ROUNDS_OUTPUT_FILE_NAME = "rodada.txt";
const char *ALLOCATION_OUTPUT_FILE_NAME = "alocacao.txt";

/**
 * @brief Server structure. Just stores it's update round.
 */
struct server {
    int round;
};

/**
 * @brief Creates a new server with no round allocation.
 * 
 * Time complexity: O(1).
 * Space complexity: O(1).
 * 
 * @return Server* A pointer to the created server.
 */
static Server * Server_create() {
    Server *server = (Server *) malloc(sizeof(Server));
    server->round = 0;
    return server;
}

/**
 * @brief Getter for the server round.
 * 
 * Time complexity: O(1).
 * 
 * @param server The server.
 * @return int The server round.
 */
int Server_getRound(const Server *server) {
    return server->round;
}

/**
 * @brief Setter for the server round.
 * 
 * Time complexity: O(1).
 * 
 * @param server The server.
 */
void Server_setRound(Server *server, int round) {
    server->round = round;
}


/**
 * @brief Destroys the given server.
 * 
 * Time complexity: O(1).
 * 
 * @param server The server to be destroyed.
 */
void Server_destroy(Server *server) {
    free(server);
}

/**
 * @brief Builds a new network with the data read from the stdin.
 * 
 * It creates a graph structure for the network. The servers are stored on a
 * fixed size array, and a server can be recovered by it's ID using the array's
 * index ID - 1.
 * 
 * Time complexity: O(serversNumber + connectionsNumber).
 * Space complexity: O(serversNumber + connectionsNumber).
 * 
 * @param serversNumber The number of servers on the network.
 * @param connectionsNumber The number of connections between servers.
 * @return Graph* The new network graph.
 */
Graph * Network_build(int *serversNumber, int *connectionsNumber) {
    scanf("%d", serversNumber);
    scanf("%d", connectionsNumber);
    int i;
    Graph *graph = Graph_create(*serversNumber);

    for (i = 0; i < *serversNumber; i += 1) {
        Server *server = Server_create();
        Vertex *vertex = Vertex_create(server);
        Graph_insertVertex(graph, vertex, i);
    }

    int v1, v2;
    for (i = 0; i < *connectionsNumber; i += 1) {
        scanf("%d %d", &v1, &v2);
        Vertex_setEdge(
            Graph_getVertices(graph)[v1 - 1],
            Graph_getVertices(graph)[v2 - 1],
            0
        );
    }

    return graph;
}

/**
 * @brief Destroys the given network graph.
 * 
 * Time complexity: O(serversNumber + connectionsNumber).
 * 
 * @param graph The network graph to be destroyed.
 */
void Network_destroy(Graph *graph) {
    for (int i = 0; i < Graph_getVerticesNumber(graph); i += 1) {
        Vertex *vertex = Graph_getVertices(graph)[i];
        Server_destroy(Vertex_getData(vertex));
        Vertex_destroy(vertex);
    }
    Graph_destroy(graph);
}

/**
 * @brief Check the server neighbours to say if the server round is valid.
 * 
 * let D the server vertex's degree.
 * Time complexity: O(D).
 * 
 * @param serverVertex The vertex of the server on the network graph.
 * @return int 1 for valid. 0 for invalid.
 */
int Server_isRoundValid(const Vertex* serverVertex) {
    Server *server = (Server *) Vertex_getData(serverVertex);
    List *connections = Vertex_getEdges(serverVertex);
    for (int i = 0; i < List_getSize(connections); i += 1) {
        Vertex *connectedVertex = (Vertex *) List_getItem(connections, i);
        Server *connectedServer = (Server *) Vertex_getData(connectedVertex);
        if (Server_getRound(server) == Server_getRound(connectedServer)) {
            return 0;
        }
    }
    return 1;
}

/**
 * @brief Set the minimum update round according to the server neighbourhood.
 * 
 * let D the server vertex's degree.
 * Time complexity (Worst case): O(D²).
 * 
 * @param serverVertex The server vertex to set.
 * @return int The minimum update round required for the server.
 */
int Server_setMinimumUpdateRound(const Vertex* serverVertex) {
    Server *server = Vertex_getData(serverVertex);

    int minRound = 0;
    do {
        minRound += 1;
        server->round = minRound;
    } while (!Server_isRoundValid(serverVertex));

    return minRound;
}

/**
 * @brief Save allocation results on the output files.
 * 
 * Time complexity: O(V).
 * 
 * @param graph The network graph.
 * @param minRounds The mininum number of rounds to perform the update.
 */
void Network_saveRoundsAndAllocation(const Graph *graph, const int minRounds) {
    FILE *file;

    file = fopen(MIN_ROUNDS_OUTPUT_FILE_NAME, "w");
    fprintf(file, "%d\n", minRounds);
    printf("%d\n", minRounds);
    fclose(file);

    file = fopen(ALLOCATION_OUTPUT_FILE_NAME, "w");
    Vertex **vertices = Graph_getVertices(graph);
    int verticesNumber = Graph_getVerticesNumber(graph);
    Server *server;
    for (int i = 0; i < verticesNumber; i += 1) {
        server = (Server *) Vertex_getData(vertices[i]);
        fprintf(file, "%d %d\n", i + 1, server->round);
        printf("%d %d\n", i + 1, server->round);
    }
    fclose(file);
}