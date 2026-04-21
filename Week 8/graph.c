#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

void add_edge(Graph* self, int from, int to, int w) {
	// make a new node
	EdgeNodePtr newNode = malloc(sizeof(struct edgeNode));

	// put edge info inside node
	newNode->edge.to_vertex = to;
	newNode->edge.weight = w;

	// insert at front of the list
	newNode->next = self->edges[from].head;
	self->edges[from].head = newNode;
}

void free_graph(Graph* self) {
	// go through every vertex list
	for (int v = 0; v < self->V; v++) {
		EdgeNodePtr current = self->edges[v].head;

		// free all nodes in that list
		while (current != NULL) {
			EdgeNodePtr temp = current;
			current = current->next;
			free(temp);
		}
	}

	// free the array of lists
	free(self->edges);
}