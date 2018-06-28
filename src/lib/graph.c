#include <stdlib.h>
#include "graph.h"
#include "list.h"

/**
 * @brief Vertex structure.
 */
struct vertex {
    /** Data stored on the vertex. */
    void *data;
    /** List with reference for the vertices that this one is related to. */
    List *edges;
};

/**
 * @brief Creates a new vertex with the given data.
 * 
 * Complexity: O(1).
 * 
 * @param data An generic pointer to the data the will be stored on the vertex.
 * @return Vertex* A pointer to the new vertex.
 */
Vertex * Vertex_create(void *data) {
    Vertex *vertex = (Vertex *) malloc(sizeof(Vertex));
    vertex->data = data;
    vertex->edges = List_create();
    return vertex;
}

/**
 * @brief Getter for the vertex data.
 * 
 * Complexity: O(1).
 * 
 * @param vertex The vertex.
 * @return void* The vertex data.
 */
void * Vertex_getData(Vertex *vertex) {
    return vertex->data;
}

/**
 * @brief Setter for the vertex data.
 * 
 * Complexity: O(1).
 * 
 * @param vertex The vertex.
 * @param data The data.
 * @return void* The vertex data.
 */
void Vertex_setData(Vertex *vertex, void *data) {
    vertex->data = data;
}

/**
 * @brief Getter for the vertex edges.
 * 
 * Complexity: O(1).
 * 
 * @param vertex The vertex.
 * @return List* The vertex edges.
 */
List * Vertex_getEdges(Vertex *vertex) {
    return vertex->edges;
}

/**
 * @brief Destroys the given vertex.
 * 
 * It will empty the edges list without destroying the related vertices. After,
 * it will destroy the list.
 * 
 * n: The number of edges of the vertex.
 * Complexty: O(n).
 * 
 * @param vertex The vertex to be destroyed.
 */
void Vertex_destroy(Vertex *vertex) {
    List *edges = Vertex_getEdges(vertex);
    while (List_getSize(edges) > 0) {
        List_removeItem(edges, -1);
    }
    List_destroy(edges);
    free(vertex);
}

/**
 * @brief Sets an edge between the given vertices.
 * 
 * Complexity: O(1).
 * 
 * @param vertex1 The origin vertex.
 * @param vertex2 The target vertex.
 * @param oriented If 1, it will also add an edge between vertex2 and vertex1.
 */
void Vertex_setEdge(Vertex *vertex1, Vertex *vertex2, int oriented) {
    List_insertItem(Vertex_getEdges(vertex1), vertex2, -1);

    if (!oriented) {
        List_insertItem(Vertex_getEdges(vertex2), vertex1, -1);
    }
}

/**
 * @brief DinamicGraph structure for graphs that dont have an already defined
 * number of vertices. Slower than the fixed graph.
 */
struct dinamic_graph {
    /** List used to store the graph's vertices. */
    List *vertices;
};

/**
 * @brief Creates a new graph
 * 
 * Complexity: O(1).
 * 
 * @return DinamicGraph* A pointer to the created graph.
 */
DinamicGraph * DinamicGraph_create() {
    DinamicGraph *graph = (DinamicGraph *) malloc(sizeof(DinamicGraph));
    graph->vertices = List_create();
    return graph;
}

/**
 * @brief Getter for the graph vertices.
 * 
 * Complexity: O(1).
 * 
 * @param graph The graph.
 * @return List* The graph vertices.
 */
List * DinamicGraph_getVertices(DinamicGraph *graph) {
    return graph->vertices;
}

/**
 * @brief Destroy the given graph.
 * 
 * It will destroy only the list that was created. It will assume that the
 * inserted vertices and it's contents will be removed and destroyed by who
 * created them.
 * 
 * Complexity: O(1).
 * 
 * @param graph The graph to be destroyied.
 */
void DinamicGraph_destroy(DinamicGraph *graph) {
    List_destroy(DinamicGraph_getVertices(graph));
    free(graph);
}

/**
 * @brief Inserts a new vertex on the graph.
 * 
 * Complexity: O(1).
 * 
 * @param graph The graph.
 * @param vertex The vertex to be inserted.
 */
void DinamicGraph_insertVertex(DinamicGraph *graph, Vertex *vertex) {
    List_insertItem(DinamicGraph_getVertices(graph), vertex, -1);
}

/**
 * @brief Graph structure for graphs that has an already defined number of
 * vertices. Faster than the dinamic graph.
 */
struct graph {
    /** Array used to store the graph's vertices pointers. */
    Vertex **vertices;
    int verticesNumber;
};

/**
 * @brief Creates a new graph
 * 
 * Complexity: O(1).
 *
 * @param verticesNumber The amount of vertices.
 * @return Graph* A pointer to the created graph.
 */
Graph * Graph_create(int verticesNumber) {
    Graph *graph = (Graph *) malloc(sizeof(Graph));
    graph->vertices = (Vertex **) malloc(verticesNumber * sizeof(Vertex *));
    graph->verticesNumber = verticesNumber;
    return graph;
}

/**
 * @brief Getter for the graph vertices.
 * 
 * Complexity: O(1).
 * 
 * @param graph The graph.
 * @return Vertex** The graph vertices.
 */
Vertex ** Graph_getVertices(Graph *graph) {
    return graph->vertices;
}

/**
 * @brief Getter for the graph vertices.
 * 
 * Complexity: O(1).
 * 
 * @param graph The graph.
 * @return The graph vertices number defined on the creation.
 */
int Graph_getVerticesNumber(Graph *graph) {
    return graph->verticesNumber;
}

/**
 * @brief Destroy the given graph.
 * 
 * It will destroy the allocated array for the vertices. It assumes that the
 * creator already destroyied each vertex data.
 * 
 * Complexity: O(1).
 * 
 * @param graph The graph to be destroyied.
 */
void Graph_destroy(Graph *graph) {
    free(graph->vertices);
    free(graph);
}

/**
 * @brief Inserts a new vertex on the graph.
 * 
 * Complexity: O(1).
 * 
 * @param graph The graph.
 * @param vertex The vertex to be inserted.
 */
void Graph_insertVertex(Graph *graph, Vertex *vertex, int position) {
    Vertex **vertices = Graph_getVertices(graph);
    vertices[position] = vertex;
}