/*
 * DFSTopologicalSort.c
 *
 *  Created on: 21 Jun 2020
 *      Author: Grant
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 50

int current_label;

struct Graph {
	struct Node* head[N];
	int nV;
};

struct Node {
	int dest;
	int explored;
	int topological_order;
	struct Node* next;
};

struct Edge {
	int src, dest;
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

		struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
		newNode->dest = dest;

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
			printf("(%d -> %d)\t", i, ptr->dest);
			ptr = ptr->next;
		}

		printf("\n");
	}
}

void DepthFirstSearch(struct Graph* graph, int vertex)
{
	graph->head[vertex]->explored = 1;

	struct Node* temp = graph->head[vertex];

	while (temp != NULL)
	{
		if (temp->dest != 100)
		{
			if (graph->head[temp->dest]->explored == 0)
			{
				DepthFirstSearch(graph, temp->dest);
			}
		}

		temp = temp->next;
	}

	graph->head[vertex]->topological_order = current_label;
	current_label--;
}

void DFSLoop(struct Graph* graph)
{
	for (int i = 0; i < graph->nV; i++)
	{
		graph->head[i]->explored = 0;
	}

	current_label = graph->nV;

	for (int j = 0; j < graph->nV; j++)
	{
		if (graph->head[j]->explored == 0)
		{
			DepthFirstSearch(graph, j);
		}
	}
}

int main(void)
{
	srand ( time(NULL) );

	struct Edge edges[] =
	{
		{ 0, 1 }, { 0, 2 },
		{ 1, 3 },
		{ 2, 3 }
	};

	int n = sizeof(edges)/sizeof(edges[0]); //number of edges

	struct Graph *graph = createGraph(edges, n);

	graph->nV = 4;

	printGraph(graph);

	DFSLoop(graph);

	for (int i = 0; i < graph->nV; i++)
	{
		printf("%d ", graph->head[i]->topological_order);
	}

	return 0;
}
