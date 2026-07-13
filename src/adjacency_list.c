#define _CRT_SECURE_NO_WARNINGS
#include "../include/adjacency_list.h"
#include <stdio.h>
#include<stdlib.h>
static int findVertexIndex(AdjList* graph, char data) {
	for (int i = 0; i < graph->vertexCount; i++) {
		if (data == graph->vertices[i].data) {
			return i;
		}
	}
	return -1;
}
AdjList* al_create(void) {
	AdjList* graph = (AdjList*)malloc(sizeof(AdjList));
	if (graph == NULL) {
		printf("邻接表内存分配失败！\n");
		return NULL;
	}
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		graph->vertices[i].data = '\0';
		graph->vertices[i].firstEdge = NULL;
	}
	graph->vertexCount = 0;
	graph->edgeCount = 0;
	return graph;
}
void al_destory(AdjList* graph) {
	if (graph == NULL)return;
	for (int i = 0; i < graph->vertexCount; i++) {
		EdgeNode* edge = graph->vertices[i].firstEdge;
		while (edge != NULL) {
			EdgeNode* temp = edge;
			edge = edge->next;
			free(temp);
		}
		graph->vertices[i].firstEdge = NULL;
	}
	free(graph);
}
int al_addVertex(AdjList* graph, char data) {
	if (graph == NULL) {
		printf("图为空！\n");
		return -1;
	}
	if (graph->vertexCount >= MAX_VERTEX_NUM) {
		printf("顶点数已达上限%d！", MAX_VERTEX_NUM);
		return -1;
	}
	if (findVertexIndex(graph, data) != -1) {
		printf("顶点'%c'已存在!\n", data);
		return -1;
	}
	graph->vertices[graph->vertexCount].data = data;
	graph->vertices[graph->vertexCount].firstEdge = NULL;
	graph->vertexCount++;
	printf("顶点'%c'添加成功!当前顶点数为：%d\n", data, graph->vertexCount);
	return graph->vertexCount - 1;
}
int al_addEdge(AdjList* graph, char from, char to, int weight) {
	if (graph == NULL) {
		printf("图指针为空！\n");
		return -1;
	}
	int fromIdx = findVertexIndex(graph, from);
	int toIdx = findVertexIndex(graph, to);
	if (fromIdx == -1) {
		printf("错误：起点顶点 '%c' 不存在！请先添加景点。\n", from);
		return -1;
	}
	if (toIdx == -1) {
		printf("错误：终点顶点 '%c' 不存在！请先添加景点。\n", to);
		return -1;
	}
	if (fromIdx == toIdx) {
		printf("错误：不能添加起点和终点相同的边！\n");
		return -1;
	}
	EdgeNode* current = graph->vertices[fromIdx].firstEdge;
	while (current != NULL) {
		if (current->adjVertex == toIdx) {
			printf("边已存在，权值由%d更新为%d\n", current->weight, weight);
			current->weight = weight;
			EdgeNode* rev = graph->vertices[toIdx].firstEdge;
			while (rev != NULL) {
				if (rev->adjVertex == fromIdx) {
					rev->weight = weight;
					break;
				}
				rev = rev->next;
			}
			return 0;
		}
		current = current->next;
	}
	EdgeNode* newEdge = (EdgeNode*)malloc(sizeof(EdgeNode));
	if (newEdge == NULL) {
		printf("边节点内存分配失败！\n");
		return -1;
	}
	newEdge->adjVertex = toIdx;
	newEdge->weight = weight;
	newEdge->next = graph->vertices[fromIdx].firstEdge;
	graph->vertices[fromIdx].firstEdge = newEdge;
	EdgeNode* reverseEdge = (EdgeNode*)malloc(sizeof(EdgeNode));
	if (reverseEdge == NULL) {
		printf("反节点内存分配失败！\n");
		return -1;
	}
	reverseEdge->adjVertex = fromIdx;
	reverseEdge->weight = weight;
	reverseEdge->next = graph->vertices[toIdx].firstEdge;
	graph->vertices[toIdx].firstEdge = reverseEdge;
	graph->edgeCount++;
	printf("边%c-%c添加成功！权值为：%d\n", from, to, weight);
	return 0;
}
void al_print(AdjList* graph) {
	if (graph == NULL) {
		printf("图指针为空！\n");
		return;
	}
	printf("\n========== 邻接表（无向图） ==========\n");
	printf("顶点数：%d，边数：%d\n", graph->vertexCount, graph->edgeCount);
	for (int i = 0; i < graph->vertexCount; i++) {
		printf("%c->", graph->vertices[i].data);
		EdgeNode* edge = graph->vertices[i].firstEdge;
		if (edge == NULL) {
			printf("NULL\n");
			continue;
		}
		while (edge != NULL) {
			printf("[%c,%d]", graph->vertices[edge->adjVertex].data, edge->weight);
			edge = edge->next;
		}
		printf("NULL\n");
	}
	printf("=========================================\n");
}
static void dfsRecursive(AdjList* graph, int vertex, int* visited) {
	visited[vertex] = 1;
	printf("%c ", graph->vertices[vertex].data);
	EdgeNode* edge = graph->vertices[vertex].firstEdge;
	while (edge != NULL) {
		int neighbor = edge->adjVertex;
		if (!visited[neighbor]) {
			dfsRecursive(graph, neighbor, visited);
		}
		edge = edge->next;
	}
}
void al_dfs(AdjList* graph, char start) {
	if (graph == NULL) {
		printf("图指针为空！\n");
		return;
	}
	int startIdx = findVertexIndex(graph, start);
	if (startIdx == -1) {
		printf("起始顶点'%c'不存在！\n", start);
		return;
	}
	int visited[MAX_VERTEX_NUM] = { 0 };
	printf("DFS遍历顺序：");
	dfsRecursive(graph, startIdx, visited);
	for (int i = 0; i < graph->vertexCount; i++) {
		if (!visited[i]) {
			printf("\n（不连通分量）");
			dfsRecursive(graph, i, visited);
		}
	}
	printf("\n");
}
typedef struct {
	int* data;
	int front;
	int rear;
	int capacity;
}BfsQueue;
static BfsQueue* createBfsQueue(int capacity) {
	BfsQueue* q = (BfsQueue*)malloc(sizeof(BfsQueue));
	if (q == NULL) {
		printf("队列内存分配失败！\n");
		return NULL;
	}
	q->data = (int*)malloc(capacity * sizeof(int));
	if (q->data == NULL) {
		printf("队列数据区内存分配失败！\n");
		free(q);
		return NULL;
	}
	q->front = 0;
	q->rear = 0;
	q->capacity = capacity;
	return q;
}
static void destroyBfsQueue(BfsQueue* q) {
	if (q != NULL) {
		if (q->data != NULL) {
			free(q->data);
		}
		free(q);
	}
}
static int isBfsQueueEmpty(BfsQueue* q) {
	return q->front == q->rear;
}
static int isBfsQueueFull(BfsQueue* q) {
	return (q->rear + 1) % q->capacity == q->front;
}
static void enqueueBfs(BfsQueue* q, int value) {
	if (isBfsQueueFull(q)) {
		printf("队列已满，无法入队！\n");
		return;
	}
	q->data[q->rear] = value;
	q->rear = (q->rear + 1) % q->capacity;
}
static int dequeueBfs(BfsQueue* q) {
	if (isBfsQueueEmpty(q)) {
		printf("队列为空，无法出队！\n");
		return -1;
	}
	int value = q->data[q->front];
	q->front = (q->front + 1) % q->capacity;
	return value;
}
void al_bfs(AdjList* graph, char start) {
	if (graph == NULL) {
		printf("图指针为空！\n");
		return;
	}
	int startIdx = findVertexIndex(graph, start);
	if (startIdx == -1) {
		printf("起始顶点%c不存在！\n", start);
		return;
	}
	int visited[MAX_VERTEX_NUM] = { 0 };
	BfsQueue* queue = createBfsQueue(graph->vertexCount);
	if (queue == NULL) {
		printf("队列创建失败！\n");
		return;
	}
	printf("BFS遍历顺序：");
	visited[startIdx] = 1;
	printf("%c ", graph->vertices[startIdx].data);
	enqueueBfs(queue, startIdx);
	while (!isBfsQueueEmpty(queue)) {
		int current = dequeueBfs(queue);
		EdgeNode* edge = graph->vertices[current].firstEdge;
		while (edge != NULL) {
			int neighbor = edge->adjVertex;
			if (!visited[neighbor]) {
				visited[neighbor] = 1;
				printf("%c ", graph->vertices[neighbor].data);
				enqueueBfs(queue, neighbor);
			}
			edge = edge->next;
		}
	}
	for (int i = 0; i < graph->vertexCount; i++) {
		if (visited[i])continue;
		visited[i] = 1;
		printf("\n（不连通分量）%c", graph->vertices[i].data);
		enqueueBfs(queue, i);
		while (!isBfsQueueEmpty(queue)) {
			int current = dequeueBfs(queue);
			EdgeNode* edge = graph->vertices[current].firstEdge;
			while (edge != NULL) {
				int neighbor = edge->adjVertex;
				if (!visited[neighbor]) {
					visited[neighbor] = 1;
					printf("%c ", graph->vertices[neighbor].data);
					enqueueBfs(queue, neighbor);
				}
				edge = edge->next;
			}
		}
	}
	printf("\n");
	destroyBfsQueue(queue);
}
