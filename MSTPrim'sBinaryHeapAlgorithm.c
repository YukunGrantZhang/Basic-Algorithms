/*
 * MSTPrim'sBinaryHeapAlgorithm.c
 *
 *  Created on: 1 Jul 2020
 *      Author: Grant
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_HEAP_SIZE 50

int heap[MAX_HEAP_SIZE];
int last_heap_element;

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define N 6

int dist[N];
int origin[N];

struct Graph {
	struct Node* head[N];
};

struct Node {
	int dest, weight;
	int smallest_dest;
	int explored;
	struct Node* next;
};

struct Edge {
	int src, dest, weight;
};

typedef struct MinHeapNode
{
    int vertex;
    int weight;
}MinHeapNode;

typedef struct MinHeap
{
    MinHeapNode **nodes;
}MinHeap;

MinHeapNode* newMinHeapNode(int v, int w)
{
    MinHeapNode* minHeapNode = malloc(sizeof(struct MinHeapNode));
    minHeapNode->vertex = v;
    minHeapNode->weight = w;
    return minHeapNode;
}

MinHeap* createMinHeap(int capacity)
{
    MinHeap* minHeap = malloc(sizeof(struct MinHeap));
    minHeap->nodes = malloc(capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

void BubbleUp(MinHeap* heaps, int current_index)
{
	int parent_index = (int)(floor((current_index + 1) / 2)) - 1;
	MinHeapNode* temp;

	if (parent_index < 0)
	{
		parent_index = 0;
	}

	while (heaps->nodes[current_index]->weight < heaps->nodes[parent_index]->weight)
	{
		temp = heaps->nodes[current_index];
		heaps->nodes[current_index] = heaps->nodes[parent_index];
		heaps->nodes[parent_index] = temp;

		current_index = parent_index;
		parent_index = (int)(floor((current_index + 1) / 2)) - 1;

		if (parent_index < 0)
		{
			break;
		}
	}

}

void BubbleDown(MinHeap* heaps, int starting_index)
{
	int current_index = starting_index;
	int left_child_index = (current_index + 1) * 2 - 1;
	int right_child_index = (current_index + 1) * 2;

	int selection_index;

	if (heaps->nodes[left_child_index] == NULL || heaps->nodes[right_child_index] == NULL)
	{
		if (heaps->nodes[left_child_index] != NULL && heaps->nodes[current_index]->weight > heaps->nodes[left_child_index]->weight)
		{
			MinHeapNode* temp = heaps->nodes[current_index];
			heaps->nodes[current_index] = heaps->nodes[left_child_index];
			heaps->nodes[left_child_index] = temp;
		}

		return;
	}

	while (heaps->nodes[current_index]->weight > heaps->nodes[left_child_index]->weight || heaps->nodes[current_index]->weight > heaps->nodes[right_child_index]->weight)
	{
		if (heaps->nodes[left_child_index]->weight < heaps->nodes[right_child_index]->weight)
		{
			selection_index = left_child_index;
		}
		else
		{
			selection_index = right_child_index;
		}

		MinHeapNode* temp2 = heaps->nodes[current_index];
		heaps->nodes[current_index] = heaps->nodes[selection_index];
		heaps->nodes[selection_index] = temp2;

		current_index = selection_index;
		left_child_index = (current_index + 1) * 2 - 1;
		right_child_index = (current_index + 1) * 2;

		if (heaps->nodes[left_child_index] == NULL || heaps->nodes[right_child_index] == NULL)
		{
			if (heaps->nodes[left_child_index] != NULL && heaps->nodes[current_index]->weight > heaps->nodes[left_child_index]->weight)
			{
				MinHeapNode* temp3 = heaps->nodes[current_index];
				heaps->nodes[current_index] = heaps->nodes[left_child_index];
				heaps->nodes[left_child_index] = temp3;
			}

			break;
		}
	}
}

void InsertHeap(MinHeap* heaps, MinHeapNode* temp_node)
{
	heaps->nodes[last_heap_element] = temp_node;
	int current_element_index = last_heap_element;
	last_heap_element++;

	BubbleUp(heaps, current_element_index);
}

int ExtractMin(MinHeap* heaps)
{
	int last_index = last_heap_element - 1;
	int min = heaps->nodes[0]->vertex;

	heaps->nodes[0] = heaps->nodes[last_index];
	heaps->nodes[last_index] = NULL;
	last_heap_element--;

	BubbleDown(heaps, 0);

	return min;
}

void DeleteKey(MinHeap* heaps, int vertex)
{
	int location = 50;

	for (int i = 0; i < last_heap_element; i++)
	{
		if (heaps->nodes[i]->vertex == vertex)
		{
			location = i;
		}
	}

	if (location == 50)
	{
		return;
	}

	int last_index = last_heap_element - 1;

	heaps->nodes[location] = heaps->nodes[last_index];
	heaps->nodes[last_index] = NULL;
	last_heap_element--;

	BubbleDown(heaps, location);
}

void ReduceKey(MinHeap* heaps, int vertex, int new_reduction_weight)
{
	int location = 50;

	for (int i = 0; i < last_heap_element; i++)
	{
		if (heaps->nodes[i]->vertex == vertex)
		{
			location = i;
		}
	}

	if (location == 50)
	{
		return;
	}

	heaps->nodes[location]->weight = new_reduction_weight;

	BubbleUp(heaps, location);
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

void BinaryPrim(struct Graph* graph, int starting_vertex, int n)
{
	for (int i = 0; i < n; i++)
	{
		graph->head[i]->explored = 0;
	}

	graph->head[starting_vertex]->explored = 1;

	MinHeap* heaps = createMinHeap(50);

	last_heap_element = 0;

	for (int i = 0; i < 50; i++)
	{
		heaps->nodes[i] = NULL;
	}

	for (int i = 0; i < n; i++)
	{
		MinHeapNode* new_node = newMinHeapNode(i, 100);
		InsertHeap(heaps, new_node);
	}

	for (int i = 0; i < n; i++)
	{
		dist[i] = 100;
	}

	for (int i = 0; i < n; i++)
	{
		origin[i] = 100;
	}

	int vertices_processed = 0;

	while(vertices_processed < n - 1)
	{
		for (int i = 0; i < n; i++)
		{
			if (graph->head[i]->explored == 1)
			{
				struct Node* temp = graph->head[i];

				while (temp != NULL)
				{
					if (graph->head[temp->dest]->explored == 0)
					{
						if (temp->weight < dist[temp->dest])
						{
							dist[temp->dest] = temp->weight;
							origin[temp->dest] = i;
							ReduceKey(heaps, temp->dest, dist[temp->dest]);
						}
					}

					temp = temp->next;
				}
			}
		}

		int extracted_vertex = ExtractMin(heaps);
		graph->head[extracted_vertex]->explored = 1;
		printf("%d -> %d (%d)\n", origin[extracted_vertex], extracted_vertex, dist[extracted_vertex]);
		vertices_processed++;

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

	BinaryPrim(graph, 0, 4);

	return 0;
}
