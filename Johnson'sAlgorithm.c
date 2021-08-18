/*
 * Johnson'sAlgorithm.c
 *
 *  Created on: 13 Jul 2020
 *      Author: Grant
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_HEAP_SIZE 50

int heap[MAX_HEAP_SIZE];
int last_heap_element;

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define N 7

int dist[N];

struct Graph {
	struct Node* head[N];
	int nV;
};

struct Node {
	int dest, weight, explored, distance;
	int vertex_weight;
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
    //int size;
    //int *keys;
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
	}

	for (i = 0; i < n; i++)
	{
		int src = edges[i].src;
		int dest = edges[i].dest;
		int weight = edges[i].weight;

		if (graph->head[dest] == NULL)
		{
			struct Node* temp_node = graph->head[src];

			while (temp_node != NULL)
			{
				temp_node = temp_node->next;
			}

			temp_node = graph->head[dest];

			struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

			newNode->dest = 100;

			newNode->weight = 0;

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

void BinaryHeapDijkstra(struct Graph* graph, int starting_vertex, int n)
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

	MinHeap* heaps = createMinHeap(50);

	last_heap_element = 0;

	for (int i = 0; i < 50; i++)
	{
		heaps->nodes[i] = NULL;
	}

	for (int i = 0; i < 9; i++)
	{
		MinHeapNode* new_node = newMinHeapNode(i, 100);
		InsertHeap(heaps, new_node);
	}

	for (int i = 0; i < n; i++)
	{
		dist[i] = 100;
	}

	int vertices_processed = 0;

	while(vertices_processed < n - 1)
	{
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
						ReduceKey(heaps, temp->dest, dist[temp->dest]);

						struct Node* new_temp = graph->head[temp->dest];
						while (new_temp != NULL)
						{
							new_temp->distance = dist[temp->dest];
							new_temp = new_temp->next;
						}
					}

					temp = temp->next;
				}
			}
		}

		int extracted_vertex = ExtractMin(heaps);
		graph->head[extracted_vertex]->explored = 1;
		vertices_processed++;
	}
}

void JohnsonsAlgorithm(struct Graph* graph, struct Graph* original_graph, int starting_vertex, int n)
{
	int A[n][n];

	for (int a = 0; a < n; a++)
	{
		if (a == starting_vertex)
		{
			A[0][a] = 0;
		}
		else
		{
			A[0][a] = 100;
		}
	}

	int w[n];
	int e[n];
	int total[n];

	int count = 0;

	for (int i = 1; i < n; i++)
	{
		for (int v = 0; v < n; v++)
		{
			count = 0;

			int case_1 = A[i - 1][v];

			int x;
			for (x = 0; x < N; x++)
			{
				struct Node* ptr = graph->head[x];
				while (ptr != NULL)
				{
					//printf("%d -> %d (%d)\t", x, ptr->dest, ptr->weight);

					if (ptr->dest == v)
					{
						w[count] = x;
						e[count] = ptr->weight;
						count++;
					}

					ptr = ptr->next;
				}

				//printf("\n");
			}

			if (count > 0)
			{
				for (int y = 0; y < count; y++)
				{
					total[y] = A[i - 1][w[y]] + e[y];
				}

				int temp = total[0];
				for (int e = 0; e < count; e++)
				{
					if (total[e] < temp)
					{
						temp = total[e];
					}
				}

				int case_2 = temp;

				if (case_1 < case_2)
				{
					A[i][v] = case_1;
				}
				else
				{
					A[i][v] = case_2;
				}

			}
			else
			{
				A[i][v] = case_1;
			}
			//A[i][v] = case_1;
		}
	}

	for (int j = 0; j < n; j++)
	{
		for (int k = 0; k < n; k++)
		{
			printf("%d ", A[j][k]);
		}
		printf("\n");
	}

	for (int l = 0; l < n - 1; l++)
	{
		original_graph->head[l]->vertex_weight = A[n - 1][l];
		printf("%d ", original_graph->head[l]->vertex_weight);
	}
	printf("\n");

	int y;
	for (y = 0; y < N; y++)
	{
		struct Node* ptr = original_graph->head[y];

		if (ptr != NULL && ptr->dest > N)
		{
			continue;
		}

		int new_weight;

		while (ptr != NULL)
		{
			new_weight = ptr->weight + original_graph->head[y]->vertex_weight - original_graph->head[ptr->dest]->vertex_weight;
			ptr->weight = new_weight;
			//printf("%d -> %d (%d)\t", y, ptr->dest, ptr->weight);
			ptr = ptr->next;
		}

		//printf("\n");
	}

	printGraph(original_graph);
}

int main(void)
{
	struct Edge edges[] =
	{
		{ 0, 1, -2 },
		{ 1, 2, -1 },
		{ 2, 0, 4 }, { 2, 3, 2 }, { 2, 4, -3 },
		{ 5, 3, 1 }, { 5, 4, -4 },
		{ 6, 0, 0 }, { 6, 1, 0 }, { 6, 2, 0 }, { 6, 3, 0 }, { 6, 4, 0 }, { 6, 5, 0 }
	};

	int n = sizeof(edges)/sizeof(edges[0]);

	struct Graph *graph = createGraph(edges, n);

	printGraph(graph);

	struct Edge original_edges[] =
	{
		{ 0, 1, -2 },
		{ 1, 2, -1 },
		{ 2, 0, 4 }, { 2, 3, 2 }, { 2, 4, -3 },
		{ 5, 3, 1 }, { 5, 4, -4 }
	};

	int n_original = sizeof(original_edges)/sizeof(original_edges[0]);

	struct Graph *original_graph = createGraph(original_edges, n_original);

	printGraph(original_graph);

	JohnsonsAlgorithm(graph, original_graph, 6, 7);

	original_graph->nV = 6;

	BinaryHeapDijkstra(original_graph, 1, original_graph->nV);

	for (int i = 0; i < original_graph->nV; i++)
	{
		printf("%d ", original_graph->head[i]->distance);
	}

	return 0;
}
