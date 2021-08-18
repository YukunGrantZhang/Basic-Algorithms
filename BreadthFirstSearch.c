/*
 * BreadthFirstSearch.c
 *
 *  Created on: 20 Jun 2020
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

typedef struct queue
{
    int *items;
    int maxsize;
    int front;
    int rear;
    int size;
}queue;

queue* newQueue(int volume)
{
    queue *q = malloc(sizeof(struct queue));

    q->items = malloc(volume * sizeof(int));
    q->maxsize = volume;
    q->front = 0;
    q->rear = -1;
    q->size = 0;

    return q;
}

int queue_size(queue *q)
{
    return q->size;
}

int queue_isEmpty(queue *q)
{
    return !queue_size(q);
}

int queue_front(queue *q)
{
    return q->items[q->front];
}

void insert_queue(queue *q, int x)
{
    q->rear = (q->rear + 1) % q->maxsize;
    q->items[q->rear] = x;
    q->size++;
}

void pop_queue(queue *q)
{
    q->front = (q->front + 1) % q->maxsize;
    q->size--;
}

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

void BreadthFirstSearch(struct Graph* graph, int starting_vertex, int n)
{
	for (int i = 0; i < n; i++)
	{
		graph->head[i]->explored = 0;
	}

	graph->head[starting_vertex]->explored = 1;

	struct queue *Q = newQueue(graph->nV);

	insert_queue(Q, starting_vertex);

	int pop_vertex;

	while (!queue_isEmpty(Q))
	{
		pop_vertex = queue_front(Q);
		pop_queue(Q);

		printf("%d ", pop_vertex);

		struct Node* temp = graph->head[pop_vertex];

		while (temp != NULL)
		{
			if (graph->head[temp->dest]->explored == 0)
			{
				graph->head[temp->dest]->explored = 1;
				insert_queue(Q, temp->dest);
			}

			temp = temp->next;
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
		{ 2, 3 }, { 2, 4 },
		{ 3, 4 }, { 3, 5 },
		{ 4, 5 }
	};

	int n = sizeof(edges)/sizeof(edges[0]); //number of edges

	struct Graph *graph = createGraph(edges, n);

	graph->nV = 6;

	printGraph(graph);

	BreadthFirstSearch(graph, 0, graph->nV);

	return 0;
}
