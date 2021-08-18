/*
 * MSTPrim'sNaiveAlgorithm.c
 *
 *  Created on: 1 Jul 2020
 *      Author: Grant
 */

#include <stdio.h>
#include <stdlib.h>

#define N 6

struct Graph {
	struct Node* head[N];
};

struct Node {
	int dest, weight;
	int explored;
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

		newNode = (struct Node*)malloc(sizeof(struct Node));
		newNode->dest = src;
		newNode->weight = weight;

		newNode->next = graph->head[dest];

		graph->head[dest] = newNode;
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

void NaivePrim(struct Graph* graph, int starting_vertex, int n)
{
	for (int i = 0; i < n; i++)
	{
		graph->head[i]->explored = 0;
	}

	graph->head[starting_vertex]->explored = 1;

	int vertices_processed = 0;

	int min_distance;
	int min_origin;
	int min_destination;

	while(vertices_processed < n - 1)
	{
		min_distance = 100;
		min_origin = 100;
		min_destination = 100;

		for (int i = 0; i < n; i++)
		{
			if (graph->head[i]->explored == 1)
			{
				struct Node* temp = graph->head[i];

				while (temp != NULL)
				{
					if (graph->head[temp->dest]->explored == 0)
					{
						if (temp->weight < min_distance)
						{
							min_distance = temp->weight;
							min_origin = i;
							min_destination = temp->dest;
						}
					}

					temp = temp->next;
				}
			}
		}

		if (min_distance < 100)
		{
			graph->head[min_destination]->explored = 1;
			printf("%d -> %d (%d)\n", min_origin, min_destination, min_distance);
			vertices_processed++;
		}
	}
}

int main(void)
{
	struct Edge edges[] =
	{
		{ 0, 1, 1 }, { 0, 2, 3 }, { 0, 3, 4 },
		{ 1, 2, 2 },
		{ 2, 3, 5 }
	};

	int n = sizeof(edges)/sizeof(edges[0]);

	struct Graph *graph = createGraph(edges, n);

	NaivePrim(graph, 0, 4);

	return 0;
}
