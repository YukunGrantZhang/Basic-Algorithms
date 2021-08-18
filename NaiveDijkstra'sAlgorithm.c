/*
 * NaiveDijkstra'sAlgorithm.c
 *
 *  Created on: 24 Jun 2020
 *      Author: Grant
 */

#include <stdio.h>
#include <stdlib.h>

#define N 6

int dist[N];

struct Graph {
	struct Node* head[N];
	int nV;
};

struct Node {
	int dest, weight, explored, distance;
	struct Node* next;
};

struct Edge {
	int src, dest, weight;
};

struct Graph* createGraph(struct Edge edges[], int n)
{
	unsigned i;

	struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));

	for (i = 0; i < N; i++)
		graph->head[i] = NULL;

	for (i = 0; i < n; i++)
	{
		int src = edges[i].src;
		int dest = edges[i].dest;
		int weight = edges[i].weight;

		struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
		newNode->dest = dest;
		newNode->weight = weight;

		newNode->next = graph->head[src];

		graph->head[src] = newNode;

		if (i == n - 1)
		{
			graph->head[src]->next = graph->head[dest];

			struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

			newNode->dest = 100;

			newNode->next = NULL;

			graph->head[dest] = newNode;
		}
	}

	return graph;
}

void printGraph(struct Graph* graph)
{
	int i;
	for (i = 0; i < N; i++)
	{
		struct Node* ptr = graph->head[i];
		while (ptr != NULL)
		{
			printf("%d -> %d (%d)\t", i, ptr->dest, ptr->weight);
			ptr = ptr->next;
		}

		printf("\n");
	}
}

void NaiveDijkstra(struct Graph* graph, int starting_vertex, int n)
{
	for (int i = 0; i < n; i++)
	{
		graph->head[i]->explored = 0;
	}

	graph->head[starting_vertex]->explored = 1;

	for (int i = 0; i < n; i++)
	{
		graph->head[i]->distance = 0;
	}

	for (int i = 0; i < n; i++)
	{
		dist[i] = 100;
	}

	int vertices_processed = 0;

	int min_distance;
	int min_vertex;

	while(vertices_processed < n - 1)
	{
		min_distance = 100;
		min_vertex = 100;

		for (int i = 0; i < n; i++)
		{
			if (graph->head[i]->explored == 1)
			{
				struct Node* temp = graph->head[i];

				if (temp->dest > n - 1)
				{
					break;
				}

				while (temp != NULL)
				{
					if (graph->head[temp->dest]->explored == 1)
					{
						temp = temp->next;
						continue;
					}

					if (temp->distance + temp->weight < dist[temp->dest])
					{
						dist[temp->dest] = temp->distance + temp->weight;

						struct Node* new_temp = graph->head[temp->dest];
						while (new_temp != NULL)
						{
							new_temp->distance = dist[temp->dest];
							new_temp = new_temp->next;
						}
					}

					if (graph->head[temp->dest]->distance < min_distance)
					{
						min_distance = graph->head[temp->dest]->distance;
						min_vertex = temp->dest;
					}

					temp = temp->next;
				}
			}
		}

		if (min_distance < 100)
		{
			graph->head[min_vertex]->explored = 1;
			vertices_processed++;
		}
	}
}

int main(void)
{
	struct Edge edges[] =
	{
		{ 0, 1, 1 }, { 0, 2, 4 },
		{ 1, 2, 2 }, { 1, 3, 6 },
		{ 2, 3, 3 }
	};

	int n = sizeof(edges)/sizeof(edges[0]);

	struct Graph *graph = createGraph(edges, n);

	graph->nV = 4;

	printGraph(graph);

	NaiveDijkstra(graph, 0, graph->nV);

	for (int i = 0; i < graph->nV; i++)
	{
		printf("%d ", graph->head[i]->distance);
	}

	return 0;
}
