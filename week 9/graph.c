#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

void add_edge(Graph* self, int from, int to, int w) {
	// make a new node
	EdgeNodePtr newNode = malloc(sizeof(struct edgeNode));
	if (newNode == NULL) return;

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

double* calculate_pagerank(Graph* G, int iterations, double d) {
	int V = G->V;

	// make array for pagerank
	double* PR = malloc(sizeof(double) * V);

	// make temp array for new pagerank
	double* newPR = malloc(sizeof(double) * V);

	// make array for outdegrees
	int* outdegree = malloc(sizeof(int) * V);

	// start all pageranks with 1
	for (int i = 0; i < V; i++) {
		PR[i] = 1.0;
	}

	// start all outdegrees with 0
	for (int i = 0; i < V; i++) {
		outdegree[i] = 0;
	}

	// calculate outdegrees
	for (int v = 0; v < V; v++) {
		EdgeNodePtr current = G->edges[v].head;

		while (current != NULL) {
			outdegree[v]++;
			current = current->next;
		}
	}

	// run pagerank iterations
	for (int it = 0; it < iterations; it++) {

		// set all new pageranks first
		for (int i = 0; i < V; i++) {
			newPR[i] = 1.0 - d;
		}

		// go through all edges
		for (int v = 0; v < V; v++) {
			EdgeNodePtr current = G->edges[v].head;

			while (current != NULL) {
				int to = current->edge.to_vertex;

				if (outdegree[v] > 0) {
					newPR[to] = newPR[to] + d * (PR[v] / outdegree[v]);
				}

				current = current->next;
			}
		}

		// copy new pageranks into old pageranks
		for (int i = 0; i < V; i++) {
			PR[i] = newPR[i];
		}
	}

	free(newPR);
	free(outdegree);

	return PR;
}