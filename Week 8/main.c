#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main() {
	Graph G;   // our graph variable

	// open the file
	FILE* file = fopen("musae_git_edges.csv", "r");

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

	int from, to;
	int edgeCount = 0;

	while (!feof(file)) {
		if (fscanf(file, "%d,%d", &from, &to) == 2) {
			add_edge(&G, from, to, 0);
			edgeCount++;
		}
	}

	printf("Edges loaded = %d\n", edgeCount);

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
			indegree[current->edge.to_vertex]++;
			current = current->next;
		}
	}

	// print ALL results
	printf("In-degrees:\n");
	for (int i = 0; i < G.V; i++) {
		printf("%d: %d\n", i, indegree[i]);
	}

	// free memory
	free(indegree);
	free_graph(&G);

	return 0;
}