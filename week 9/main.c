#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main() {
	Graph G;   // our graph variable

	// open the large file
	FILE* file = fopen("musae_git_edges.csv", "r");

	// check if file opened or not
	if (file == NULL) {
		printf("Error opening file!\n");
		return 1;
	}

	int from, to;
	int maxVertex = -1;
	char line[100];

	// first pass to find biggest vertex number
	while (fgets(line, sizeof(line), file) != NULL) {
		if (sscanf(line, "%d,%d", &from, &to) == 2) {
			if (from > maxVertex) {
				maxVertex = from;
			}

			if (to > maxVertex) {
				maxVertex = to;
			}
		}
	}

	// number of vertices
	G.V = maxVertex + 1;

	// reset file back to start
	rewind(file);

	// make array of edge lists
	G.edges = malloc(sizeof(EdgeList) * G.V);

	// make every list empty first
	for (int v = 0; v < G.V; v++) {
		G.edges[v].head = NULL;
	}

	// read all edges from file
	while (fgets(line, sizeof(line), file) != NULL) {
		if (sscanf(line, "%d,%d", &from, &to) == 2) {
			add_edge(&G, from, to, 1);
		}
	}

	// close the file
	fclose(file);

	printf("Graph loaded successfully\n");
	printf("Vertices: %d\n", G.V);

	// calculate pagerank
	double* pagerank = calculate_pagerank(&G, 20, 0.85);

	printf("PageRank calculated successfully\n");

	// print first 10 vertices
	printf("\nFirst 10 vertices:\n");
	for (int i = 0; i < 10 && i < G.V; i++) {
		printf("%d: %.6f\n", i, pagerank[i]);
	}

	// print top 10 pageranks
	printf("\nTop 10 PageRanks:\n");

	for (int count = 0; count < 10 && count < G.V; count++) {
		int bestIndex = -1;
		double bestValue = -1.0;

		for (int i = 0; i < G.V; i++) {
			if (pagerank[i] > bestValue) {
				int alreadyPrinted = 0;

				for (int j = 0; j < count; j++) {
					// this part is handled by making printed values negative below
				}

				bestValue = pagerank[i];
				bestIndex = i;
			}
		}

		printf("%d: %.6f\n", bestIndex, bestValue);

		// make it negative so it will not print again
		pagerank[bestIndex] = -1.0;
	}

	// free memory
	free(pagerank);
	free_graph(&G);

	return 0;
}