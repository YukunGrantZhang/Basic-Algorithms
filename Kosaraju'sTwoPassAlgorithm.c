/*
 * Kosaraju'sTwoPassAlgorithm.c
 *
 *  Created on: 22 Jun 2020
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
	int finishing_time;
	int leader;
	struct Node* next;
};

struct Edge {
	int src, dest;
};

int t;
int s[50];
int leader_tracker;

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

void FirstDepthFirstSearch(struct Graph* graph, int vertex)
{
	graph->head[vertex]->explored = 1;

	graph->head[vertex]->leader = s[leader_tracker];

	struct Node* temp = graph->head[vertex];

	while (temp != NULL)
	{
		if (graph->head[temp->dest]->explored == 0)
		{
			FirstDepthFirstSearch(graph, temp->dest);
		}

		temp = temp->next;
	}

	t++;
	graph->head[vertex]->finishing_time = t;
}

void FirstDFSLoop(struct Graph* graph)
{
	t = 0;

	leader_tracker = 0;

	for (int i = 0; i < graph->nV; i++)
	{
		graph->head[i]->explored = 0;
	}

	for (int j = graph->nV - 1; j >= 0; j--)
	{
		if (graph->head[j]->explored == 0)
		{
			s[leader_tracker] = j;

			FirstDepthFirstSearch(graph, j);

			printf("\n");

			leader_tracker++;
		}
	}
}

void SecondDepthFirstSearch(struct Graph* graph, int vertex)
{
	graph->head[vertex]->explored = 1;

	struct Node* temp = graph->head[vertex];

	printf("%d ", vertex);

	while (temp != NULL)
	{
		if (graph->head[temp->dest]->explored == 0)
		{
			SecondDepthFirstSearch(graph, temp->dest);
		}

		temp = temp->next;
	}
}

void SecondDFSLoop(struct Graph* graph)
{
	for (int i = 0; i < graph->nV; i++)
	{
		graph->head[i]->explored = 0;
	}

	for (int j = graph->nV; j >= 0; j--)
	{
		for (int i = 0; i < graph->nV; i++)
		{
			if ((graph->head[i]->explored == 0) && (graph->head[i]->finishing_time = j))
			{
				printf("Leader: %d\n", graph->head[i]->leader);

				SecondDepthFirstSearch(graph, graph->head[i]->leader);

				printf("\n");
			}
		}
	}
}

int main(void)
{
	srand ( time(NULL) );

	struct Edge edges[] =
	{
		{ 0, 3 },
		{ 1, 7 },
		{ 2, 5 },
		{ 3, 6 },
		{ 4, 1 },
		{ 5, 7 }, { 5, 8 },
		{ 6, 0 },
		{ 7, 4 },
		{ 8, 2 }, { 8, 6 }
	};

	int n = sizeof(edges)/sizeof(edges[0]); //number of edges

	struct Graph *graph = createGraph(edges, n);

	graph->nV = 9;

	printGraph(graph);

	struct Edge reverse_edges[n];

	for (int i = 0; i < n; i++)
	{
		reverse_edges[i].src = edges[i].dest;
		reverse_edges[i].dest = edges[i].src;
	}

	struct Graph *reverse_graph = createGraph(reverse_edges, n);

	reverse_graph->nV = 9;

	printGraph(reverse_graph);

	FirstDFSLoop(reverse_graph);

	for (int i = 0; i < reverse_graph->nV; i++)
	{
		graph->head[i]->finishing_time = reverse_graph->head[i]->finishing_time;
		graph->head[i]->leader = reverse_graph->head[i]->leader;
	}

	SecondDFSLoop(graph);


	return 0;
}
