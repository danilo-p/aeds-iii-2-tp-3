#include "list.h"

#ifndef GRAPH_H
#define GRAPH_H

typedef struct vertex Vertex;

Vertex * Vertex_create(void *data);

void * Vertex_getData(Vertex *vertex);

void Vertex_setData(Vertex *vertex, void *data);

List * Vertex_getEdges(Vertex *vertex);

void Vertex_destroy(Vertex *vertex);

void Vertex_setEdge(Vertex *vertex1, Vertex *vertex2, int oriented);


typedef struct dinamic_graph DinamicGraph;

DinamicGraph * DinamicGraph_create();

List * DinamicGraph_getVertices(DinamicGraph *graph);

void DinamicGraph_destroy(DinamicGraph *graph);

void DinamicGraph_insertVertex(DinamicGraph *graph, Vertex *vertex);


typedef struct graph Graph;

Graph * Graph_create(int verticesNumber);

Vertex ** Graph_getVertices(Graph *graph);

int Graph_getVerticesNumber(Graph *graph);

void Graph_destroy(Graph *graph);

void Graph_insertVertex(Graph *graph, Vertex *vertex, int position);

#endif
