#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main() {
	Graph G;   // our graph variable

	// open the file
	FILE* file = fopen("graph.txt", "r");

	// check if file opened or not
	if (file == NULL) {
		printf("Error opening file!\n");
		return 1;
	}

	// read number of vertices
	fscanf(file, "%d", &G.V);

	// make array of edge lists
	G.edges = malloc(sizeof(EdgeList) * G.V);

	// make every list empty first
	for (int v = 0; v < G.V; v++) {
		G.edges[v].head = NULL;
	}

	int from, to, weight;

	// read all edges from file
	while (fscanf(file, "%d,%d,%d", &from, &to, &weight) == 3) {
		add_edge(&G, from, to, weight);   // add edge into graph
	}

	// close the file
	fclose(file);

	// make array for indegrees
	int* indegree = malloc(sizeof(int) * G.V);

	// start all indegrees with 0
	for (int i = 0; i < G.V; i++) {
		indegree[i] = 0;
	}

	// go through all vertex lists
	for (int v = 0; v < G.V; v++) {
		EdgeNodePtr current = G.edges[v].head;

		// go through one linked list
		while (current != NULL) {
			// increase indegree of destination vertex
			indegree[current->edge.to_vertex]++;
			current = current->next;
		}
	}

	// print result
	printf("In-degrees:\n");
	for (int i = 0; i < G.V; i++) {
		printf("%d: %d\n", i, indegree[i]);
	}

	// free extra memory
	free(indegree);
	free_graph(&G);

	return 0;
}