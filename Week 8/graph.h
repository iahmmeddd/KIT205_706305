#ifndef GRAPH_H
#define GRAPH_H

// this stores one edge
typedef struct edge {
	int to_vertex;
	int weight;
} Edge;

// this is one node in the linked list
typedef struct edgeNode {
	Edge edge;
	struct edgeNode* next;
} *EdgeNodePtr;

// this is the list wrapper
typedef struct edgeList {
	EdgeNodePtr head;
} EdgeList;

// this is the graph
typedef struct graph {
	int V;            // number of vertices
	EdgeList* edges;  // array of edge lists
} Graph;

// add one edge into graph
void add_edge(Graph* self, int from, int to, int w);

// free all memory of graph
void free_graph(Graph* self);

#endif