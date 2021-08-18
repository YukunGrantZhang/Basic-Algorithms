/*
 * MSTKruskal'sUnionByRankAlgorithm.c
 *
 *  Created on: 4 Jul 2020
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

struct Graph {
	struct Node* head[N];
};

struct Node {
	int dest, weight;
	int smallest_dest;
	int explored;
	int index;
	int rank;
	struct Node* next;
	struct Node* leader;
	struct Node* child;
};

struct Edge {
	int src, dest, weight;
};

void DepthFirstSearch(struct Graph* graph, int vertex, int leader)
{
	graph->head[vertex]->explored = 1;

	graph->head[vertex]->leader = graph->head[leader];

	graph->head[leader]->child = graph->head[vertex];

	struct Node* temp = graph->head[vertex];

	while (temp != NULL)
	{
		if (graph->head[temp->dest]->explored == 0)
		{
			DepthFirstSearch(graph, temp->dest, leader);
		}

		temp = temp->next;
	}
}

struct Node* FindLeader(struct Node* input_node)
{
	struct Node* parent_node = input_node;

	while(parent_node->leader != parent_node)
	{
		parent_node = parent_node->leader;
	}

	return parent_node;
}

void UpdateRank(struct Node* input_node)
{
	input_node->rank = 0;

	while(input_node->child != NULL)
	{
		if (input_node->child != input_node)
		{
			break;
		}

		input_node->rank++;
	}
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
		newNode->index = src;
		newNode->leader = NULL;
		newNode->explored = 0;
		newNode->child = NULL;

		newNode->next = graph->head[src];

		graph->head[src] = newNode;

		newNode = (struct Node*)malloc(sizeof(struct Node));
		newNode->dest = src;
		newNode->weight = weight;
		newNode->index = dest;
		newNode->leader = NULL;
		newNode->explored = 0;
		newNode->child = NULL;

		newNode->next = graph->head[dest];

		graph->head[dest] = newNode;
	}

	for (i = 0; i < N; i++)
	{
		if (graph->head[i] != NULL)
		{
			if (graph->head[i]->explored == 0)
			{
				DepthFirstSearch(graph, i, i);
			}
		}
	}

	return graph;
}

void InsertEdge(struct Graph* graph, struct Edge edge)
{
	struct Node* leader_Node;

	if (graph->head[edge.src] != NULL && graph->head[edge.dest] != NULL)
	{
		if (graph->head[edge.src]->rank >= graph->head[edge.dest]->rank)
		{
			leader_Node = graph->head[edge.src]->leader;
			graph->head[edge.dest]->leader->leader = leader_Node;
			graph->head[edge.src]->leader->child = graph->head[edge.dest]->leader;
		}
		else
		{
			leader_Node = graph->head[edge.dest]->leader;
			graph->head[edge.src]->leader->leader = leader_Node;
			graph->head[edge.dest]->leader->child = graph->head[edge.src]->leader;
		}
	}
	else if (graph->head[edge.src] != NULL && graph->head[edge.dest] == NULL)
	{
		leader_Node = graph->head[edge.src]->leader;
	}
	else if (graph->head[edge.dest] != NULL && graph->head[edge.src] == NULL)
	{
		leader_Node = graph->head[edge.dest]->leader;
	}
	else
	{
		leader_Node = NULL;
	}

	int src = edge.src;
	int dest = edge.dest;
	int weight = edge.weight;

	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->dest = dest;
	newNode->weight = weight;
	newNode->index = src;
	newNode->leader = leader_Node;

	if (leader_Node != NULL)
	{
		leader_Node->child = newNode;
	}

	newNode->explored = 0;
	newNode->child = NULL;

	newNode->next = graph->head[src];

	graph->head[src] = newNode;

	if (leader_Node == NULL)
	{
		graph->head[src]->leader = graph->head[src];
		graph->head[src]->child = graph->head[src];
	}

	newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->dest = src;
	newNode->weight = weight;
	newNode->index = dest;
	newNode->leader = leader_Node;

	if (leader_Node != NULL)
	{
		leader_Node->child = newNode;
	}

	newNode->explored = 0;
	newNode->child = NULL;

	newNode->next = graph->head[dest];

	graph->head[dest] = newNode;

	if (leader_Node == NULL)
	{
		graph->head[dest]->leader = graph->head[src];
		graph->head[src]->child = graph->head[dest];
	}
}

void printGraph(struct Graph* graph)
{
	int i;
	for (i = 0; i < N; i++)
	{
		struct Node* ptr = graph->head[i];
		while (ptr != NULL)
		{
			printf("%d -> %d (%d)\t", ptr->index, ptr->dest, ptr->weight);
			ptr = ptr->next;
		}

		printf("\n");
	}
}

void KruskalNaiveAlgorithm(struct Edge edges[], int n)
{
	MinHeap* heaps = createMinHeap(50);

	for (int i = 0; i < n; i++)
	{
		MinHeapNode* new_node = newMinHeapNode(edges[i].src, edges[i].dest, edges[i].weight);
		InsertHeap(heaps, new_node);
	}

	int count = 0;
	struct Edge arranged_edges[n];
	int heap_count = 0;

	MinHeapNode* temp_node = ExtractMin(heaps);
	heap_count++;
	printf("%d, %d, %d\n", temp_node->start, temp_node->end, temp_node->weight);

	arranged_edges[count].src = temp_node->start;
	arranged_edges[count].dest = temp_node->end;
	arranged_edges[count].weight = temp_node->weight;
	count++;

	struct Graph* graph = createGraph(arranged_edges, count);

	while (heap_count < n)
	{
		MinHeapNode* temp_node = ExtractMin(heaps);
		heap_count++;
		int joint_nodes = 0;

		if (graph->head[temp_node->start] != NULL && graph->head[temp_node->end] != NULL)
		{
			if (FindLeader(graph->head[temp_node->start]) == FindLeader(graph->head[temp_node->end]))
			{
				continue;
			}
		}

		printf("%d, %d, %d\n", temp_node->start, temp_node->end, temp_node->weight);
		struct Edge new_edge;
		new_edge.src = temp_node->start;
		new_edge.dest = temp_node->end;
		new_edge.weight = temp_node->weight;

		InsertEdge(graph, new_edge);

		for (int b = 0; b < N; b++)
		{
			if (graph->head[b] != NULL)
			{
				UpdateRank(graph->head[b]);
			}
		}
	}
}

int main(void)
{
	srand ( time(NULL) );

	struct Edge edges1[] =
	{
		{ 0, 1, 1 }, { 0, 2, 5 }, { 0, 3, 4 }, { 0, 4, 2 },
		{ 1, 2, 7 },
		{ 2, 4, 6 },
		{ 3, 4, 3 }
	};

	struct Edge edges2[] =
	{
		{ 0, 1, 1 }, { 0, 2, 5 }, { 0, 3, 4 }, { 0, 4, 6 },
		{ 1, 2, 7 },
		{ 2, 4, 2 },
		{ 3, 4, 3 }
	};

	int n = sizeof(edges1)/sizeof(edges1[0]); //number of edges

	KruskalNaiveAlgorithm(edges2, n);

	return 0;
}
