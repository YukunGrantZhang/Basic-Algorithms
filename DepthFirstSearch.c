/*
 * DepthFirstSearch.c
 *
 *  Created on: 21 Jun 2020
 *      Author: Grant
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 50

struct Graph {
	struct Node* head[N];
	int nV;
};

struct Node {
	int dest;
	int explored;
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

		newNode = (struct Node*)malloc(sizeof(struct Node));
		newNode->dest = src;

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
			printf("(%d -> %d)\t", i, ptr->dest);
			ptr = ptr->next;
		}

		printf("\n");
	}
}

void DepthFirstSearch(struct Graph* graph, int vertex)
{
	graph->head[vertex]->explored = 1;

	printf("%d ", vertex);

	struct Node* temp = graph->head[vertex];

	while (temp != NULL)
	{
		if (graph->head[temp->dest]->explored == 0)
		{
			DepthFirstSearch(graph, temp->dest);
		}

		temp = temp->next;
	}
}

int main(void)
{
	srand ( time(NULL) );

	struct Edge edges[] =
	{
		{ 0, 1 }, { 0, 2 },
		{ 1, 3 },
		{ 2, 3 }, { 2, 4 },
		{ 3, 4 }, { 3, 5 },
		{ 4, 5 }
	};

	int n = sizeof(edges)/sizeof(edges[0]); //number of edges

	struct Graph *graph = createGraph(edges, n);

	graph->nV = 6;

	printGraph(graph);

	for (int i = 0; i < graph->nV; i++)
	{
		graph->head[i]->explored = 0;
	}

	DepthFirstSearch(graph, 0);

	return 0;
}
