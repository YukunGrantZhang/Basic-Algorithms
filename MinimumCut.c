/*
 * MinimumCut.c
 *
 *  Created on: 16 Jun 2020
 *      Author: Grant
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 50

struct Graph {
	struct Node* head[N];
};

struct Node {
	int dest;
	struct Node* next;
};

struct Edge {
	int src, dest;
};

struct Cut {
	int src, dest, edges;
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

struct Cut* Contraction(struct Graph* graph, struct Edge edges[], int n)
{
	int i;
	int number_of_vertices = 0;

	for (i = 0; i < N; i++)
	{
		struct Node* ptr = graph->head[i];

		if (ptr != NULL)
		{
			number_of_vertices++;
		}
	}

	//printf("%d\n", number_of_vertices);

	int original_number_of_vertices = number_of_vertices;

	while (number_of_vertices > 2)
	{
		int upper = n - 1;
		int lower = 0;
		int num;

		int edges_found = 0;
		while (edges_found == 0) //picks random edge
		{
			num = (rand() % (upper - lower + 1)) + lower;

			if (edges[num].src != 100 && edges[num].dest != 100)
			{
				edges_found = 1;
				//printf("%d ", num);
			}

		}

		int chosen_src = edges[num].src;
		int chosen_dest = edges[num].dest;

		for (int b = 0; b < n; b++)
		{
			if (edges[b].src == chosen_src && edges[b].dest != chosen_dest)
			{
				edges[b].src = chosen_src;
			}

			if (edges[b].dest == chosen_dest && edges[b].src != chosen_src)
			{
				edges[b].dest = chosen_src;
			}
		}

		edges[num].src = 100;
		edges[num].dest = 100;

		if (graph->head[chosen_dest] == NULL)
			continue;

		struct Node* dest_ptr = graph->head[chosen_dest];
		//dest_ptr = dest_ptr->next;

		struct Node* src_ptr = graph->head[chosen_src];


		while (src_ptr != NULL)
		{

			if (src_ptr->dest == chosen_dest)
			{
				struct Node* change = src_ptr;

				if (change->next != NULL)
				{
					if (change->next->next != NULL)
					{
						change->next = change->next->next;
					}
					else
					{
						change->next = NULL;
					}
				}
			}


			src_ptr = src_ptr->next;
		}

		while (dest_ptr != NULL)
		{
			if (dest_ptr->dest == chosen_src)
			{
				struct Node* change = dest_ptr;

				if (change->next != NULL)
				{
					if (change->next->next != NULL)
					{
						change->next = change->next->next;
					}
					else
					{
						change->next = NULL;
					}
				}

			}

			dest_ptr = dest_ptr->next;
		}

		struct Node* original_dest_ptr = graph->head[chosen_dest];

		src_ptr = original_dest_ptr->next;

		graph->head[chosen_dest] = NULL;

		number_of_vertices--;
	}

	int j = 0;

	struct Cut* newCut = (struct Cut*)malloc(sizeof(struct Cut));
	newCut->src = 100;
	newCut->dest = 100;

	while (j < original_number_of_vertices)
	{
		if (graph->head[j] != NULL)
		{
			if (newCut->src == 100)
			{
				newCut->src = j;

				int e = 1;

				struct Node* temp = graph->head[j];
				while (temp->next != NULL)
				{
					e++;
					temp = temp->next;
				}

				newCut->edges = e;
			}
			else
			{
				newCut->dest = j;
			}
			//printf("J: %d", j);
		}

		j++;
	}

	printf("Minimum Number of Cuts: %d", newCut->edges);

	return newCut;
}

int main(void)
{
	srand ( time(NULL) );

	struct Edge edges[] =
	{
		{ 0, 1 }, { 0, 5 }, { 0, 4 },
		{ 1, 4 }, { 1, 5 }, { 1, 2 },
		{ 2, 6 }, { 2, 7 }, { 2, 3 },
		{ 3, 6 }, { 3, 7 },
		{ 4, 5 },
		{ 5, 6 },
		{ 6, 7 }
	};

	int n = sizeof(edges)/sizeof(edges[0]); //number of edges

	struct Graph *graph = createGraph(edges, n);

	printGraph(graph);

	struct Cut* temp_cut = Contraction(graph, edges, n);

	return 0;
}


