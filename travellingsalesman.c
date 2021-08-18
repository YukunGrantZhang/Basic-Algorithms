/*
 * travellingsalesman.c
 *
 *  Created on: 13 Jul 2020
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

int min = 100;

void bruteforcealgorithm(struct Graph* graph, int vertex, int sum, int count, int nodes_visited[4])
{
	if (count == 3)
	{
		if (sum < min)
		{
			min = sum;
		}

		for (int a = 0; a < 4; a++)
		{
			nodes_visited[a] = 100;
		}
		return;
	}

	struct Node* ptr = graph->head[vertex];
	sum += ptr->weight;
	nodes_visited[count] = vertex;
	count += 1;

	while (ptr != NULL)
	{
		int d = ptr->dest;

		int enter = 0;
		for (int a = 0; a < count; a++)
		{
			if (d == nodes_visited[a])
			{
				enter = 1;
				break;
			}
		}

		if (enter == 0)
		{
			bruteforcealgorithm(graph, ptr->dest, sum, count, nodes_visited);
		}

		ptr = ptr->next;
	}

}

int main(void)
{
	struct Edge edges[] =
	{
		{ 0, 1, 2 }, { 0, 2, 1 }, { 0, 3, 4 },
		{ 1, 2, 3 }, { 1, 3, 5 },
		{ 2, 3, 6 }
	};

	int n = sizeof(edges)/sizeof(edges[0]);

	struct Graph *graph = createGraph(edges, n);

	printGraph(graph);

	int e[4];

	bruteforcealgorithm(graph, 0, 0, 0, e);

	printf("%d", min);

	return 0;
}
