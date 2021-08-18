/*
 * clustering.c
 *
 *  Created on: 3 Jul 2020
 *      Author: Grant
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#define N 50

#define MAX_HEAP_SIZE 50

int heap[MAX_HEAP_SIZE];
int last_heap_element;

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

typedef struct MinHeapNode
{
    int start;
    int end;
    int weight;
}MinHeapNode;

typedef struct MinHeap
{
    MinHeapNode **nodes;
}MinHeap;

MinHeapNode* newMinHeapNode(int s, int e, int w)
{
    MinHeapNode* minHeapNode = malloc(sizeof(struct MinHeapNode));
    minHeapNode->start = s;
    minHeapNode->end = e;
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

MinHeapNode* ExtractMin(MinHeap* heaps)
{
	int last_index = last_heap_element - 1;
	MinHeapNode* min = heaps->nodes[0];

	heaps->nodes[0] = heaps->nodes[last_index];
	heaps->nodes[last_index] = NULL;
	last_heap_element--;

	BubbleDown(heaps, 0);

	return min;
}

struct Edge {
	int src, dest, weight;
};

void Clustering(struct Edge edges[], int n, int starting_clusters, int ending_clusters)
{
	MinHeap* heaps = createMinHeap(50);

	for (int i = 0; i < n; i++)
	{
		MinHeapNode* new_node = newMinHeapNode(edges[i].src, edges[i].dest, edges[i].weight);
		InsertHeap(heaps, new_node);
	}

	int beginning_clusters = starting_clusters;
	int clusters[starting_clusters];
	int grouping = 0;

	for (int a = 0; a < starting_clusters; a++)
	{
		clusters[a] = grouping;
		a++;
	}
	grouping++;

	int count = 0;
	struct Edge arranged_edges[n];
	int heap_count = 0;

	MinHeapNode* temp_node = ExtractMin(heaps);
	heap_count++;

	arranged_edges[count].src = temp_node->start;
	arranged_edges[count].dest = temp_node->end;
	arranged_edges[count].weight = temp_node->weight;
	count++;

	clusters[temp_node->start] = grouping;
	clusters[temp_node->end] = grouping;
	starting_clusters--;

	while (ending_clusters < starting_clusters)
	{
		MinHeapNode* temp_node = ExtractMin(heaps);
		heap_count++;
		int joint_nodes = 0;

		for (int a = 0; a < count; a++)
		{
			if (temp_node->start == arranged_edges[a].src || temp_node->start == arranged_edges[a].dest)
			{
				joint_nodes = 1;
				int skip = 0;

				for (int b = 0; b < count; b++)
				{
					if (temp_node->end == arranged_edges[b].src || temp_node->end == arranged_edges[b].dest)
					{
						skip = 1;
						break;
					}
				}

				if (skip == 1)
				{
					break;
				}

				arranged_edges[count].src = temp_node->start;
				arranged_edges[count].dest = temp_node->end;
				arranged_edges[count].weight = temp_node->weight;
				count++;

				int temp_grouping = clusters[temp_node->start];
				clusters[temp_node->start] = temp_grouping;
				clusters[temp_node->end] = temp_grouping;
				starting_clusters--;

				break;
			}

			if (temp_node->end == arranged_edges[a].src || temp_node->end == arranged_edges[a].dest)
			{
				joint_nodes = 1;
				int skip = 0;

				for (int b = 0; b < count; b++)
				{
					if (temp_node->start == arranged_edges[b].src || temp_node->start == arranged_edges[b].dest)
					{
						skip = 1;
						break;
					}
				}

				if (skip == 1)
				{
					break;
				}

				arranged_edges[count].src = temp_node->start;
				arranged_edges[count].dest = temp_node->end;
				arranged_edges[count].weight = temp_node->weight;
				count++;

				int temp_grouping = clusters[temp_node->end];
				clusters[temp_node->start] = temp_grouping;
				clusters[temp_node->end] = temp_grouping;
				starting_clusters--;

				break;
			}
		}

		if (joint_nodes == 0)
		{
			arranged_edges[count].src = temp_node->start;
			arranged_edges[count].dest = temp_node->end;
			arranged_edges[count].weight = temp_node->weight;
			count++;

			grouping++;
			clusters[temp_node->start] = grouping;
			clusters[temp_node->end] = grouping;
			starting_clusters--;
		}
	}

	for (int m = 1; m <= grouping; m++)
	{
		for (int n = 0; n < beginning_clusters; n++)
		{
			if (clusters[n] == m)
			{
				printf("%d ", n);
			}
		}
		printf("\n");
	}

	for (int w = 0; w < beginning_clusters; w++)
	{
		if (clusters[w] == 0)
		{
			printf("%d\n", w);
		}
	}
}

int main(void)
{
	srand ( time(NULL) );

	struct Edge edges[] =
	{
		{ 0, 1, 1 }, { 0, 2, 5 }, { 0, 3, 4 }, { 0, 4, 2 },
		{ 1, 2, 7 },
		{ 2, 4, 6 },
		{ 3, 4, 3 }
	};

	int n = sizeof(edges)/sizeof(edges[0]); //number of edges

	Clustering(edges, n, 5, 3);

	return 0;
}
