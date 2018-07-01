#include "list.h"

#ifndef GRAPH_H
#define GRAPH_H

typedef struct vertex Vertex;

Vertex * Vertex_create(void *data);

void * Vertex_getData(const Vertex *vertex);

void Vertex_setData(Vertex *vertex, void *data);

List * Vertex_getEdges(const Vertex *vertex);

void Vertex_destroy(Vertex *vertex);

void Vertex_setEdge(Vertex *vertex1, Vertex *vertex2, const int oriented);


typedef struct dinamic_graph DinamicGraph;

DinamicGraph * DinamicGraph_create();

List * DinamicGraph_getVertices(const DinamicGraph *graph);

void DinamicGraph_destroy(DinamicGraph *graph);

void DinamicGraph_insertVertex(DinamicGraph *graph, Vertex *vertex);


typedef struct graph Graph;

Graph * Graph_create(const int verticesNumber);

Vertex ** Graph_getVertices(const Graph *graph);

int Graph_getVerticesNumber(const Graph *graph);

void Graph_destroy(Graph *graph);

void Graph_insertVertex(const Graph *graph, Vertex *vertex, const int position);

#endif
