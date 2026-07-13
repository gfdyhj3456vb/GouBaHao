#define _CRT_SECURE_NO_WARNINGS
#include "../include/adjacency_matrix.h"
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
typedef struct {
	int* data;
	int front;
	int rear;
	int capacity;
}Queue;
Queue* createQueue(int capacity) {
	Queue* q = (Queue*)malloc(sizeof(Queue));
	if (q == NULL) {
		printf("队列内存分配失败！\n");
		return NULL;
	}
	q->data = (int*)malloc(capacity * sizeof(int));
	if (q->data == NULL) {
		printf("队列数据区内存分配失败!\n");
		free(q);
		return NULL;
	}
	q->front = 0;
	q->rear = 0;
	q->capacity = capacity;
	return q;
}
void destroyQueue(Queue* q) {
	if (q != NULL) {
		if (q->data != NULL) {
			free(q->data);
		}
		free(q);
	}
}
int isEmpty(Queue* q) {
	return (q->front == q->rear);
}
int isFull(Queue* q) {
	return((q->rear + 1) % q->capacity == q->front);
}
void enqueue(Queue* q, int value) {
	if (isFull(q)) {
		printf("队列已满，无法入队！\n");
		return;
	}
	q->data[q->rear] = value;
	q->rear = (q->rear + 1) % q->capacity;
}
int dequeue(Queue* q) {
	if (isEmpty(q)) {
		printf("队列为空，无法出队！\n");
		return -1;
	}
	int value = q->data[q->front];
	q->front = (q->front + 1) % q->capacity;
	return value;
}
int peek(Queue* q) {
	if (isEmpty(q)) {
		printf("队列为空！\n");
		return -1;
	}
	return q->data[q->front];
}
int getQueueSize(Queue* q) {
	return(q->rear - q->front + q->capacity) % q->capacity;
}
int getIndex(Graph* g, char ch) {
	for (int i = 0; i < g->vertexCount; i++) {
		if (ch == g->data[i]) {
			return i;
		}
	}
	return -1;
}
void FirstGraph(Graph* g) {
	printf("请输入图的顶点数和边数:\n");
	int a, b;
	scanf("%d %d", &a, &b);
	if (a > MAX) {
		printf("输入的顶点数大于MAX\n");
		return;
	}
	g->vertexCount = a;
	g->edgeCount = b;
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			g->edge[i][j] = 0;
		}
	}
	for (int i = 0; i < g->vertexCount; i++) {
		printf("请输入第%d个顶点：", i + 1);
		scanf(" %c", &(g->data[i]));
		printf("\n");
	}
	int i = 0;
	while (i < g->edgeCount) {
		printf("请输入第%d条边的起始点，终点和权值：", i + 1);
		char r, l;
		int p;
		scanf(" %c %c %d", &r, &l, &p);
		int q = getIndex(g, r);
		int w = getIndex(g, l);
		if (q == -1 || w == -1) {
			printf("输入的起始点和终点有问题，请重新输入\n");
			continue;
		}
		g->edge[q][w] = p;
		g->edge[w][q] = p;
		i++;
	}
}
void printGraph(Graph g) {
	printf("\n====邻接矩阵====\n");
	printf("    ");
	for (int i = 0; i < g.vertexCount; i++) {
		printf("%c  ", g.data[i]);
	}
	printf("\n");
	for (int i = 0; i < g.vertexCount; i++) {
		printf("%c  ", g.data[i]);
		for (int j = 0; j < g.vertexCount; j++) {
			printf("%d  ", g.edge[i][j]);
		}
		printf("\n");
	}
	printf("============\n");
}
int AddVertex(Graph* g, char vertex) {
	if (g->vertexCount >= MAX) {
		printf("景点数量已经达上限(%d)!\n", MAX);
		return -1;
	}
	if (getIndex(g, vertex) != -1) {
		printf("景点'%c'已存在！\n", vertex);
		return -1;
	}
	g->data[g->vertexCount] = vertex;
	for (int i = 0; i <= g->vertexCount; i++) {
		g->edge[i][g->vertexCount] = 0;
		g->edge[g->vertexCount][i] = 0;
	}
	g->vertexCount++;
	printf("景点'%c'添加成功！当前景点数：%d\n", vertex, g->vertexCount);
	return 0;
}
int AddEdge(Graph* g, char from, char to, int weight) {
	int i = getIndex(g, from);
	int j = getIndex(g, to);
	if (i == -1 || j == -1) {
		printf("输入景点不存在，请先添加景点！\n");
		return -1;
	}
	if (i == j) {
		printf("不能添加起点和终点相同的边！\n");
		return -1;
	}
	if (g->edge[i][j] != 0) {
		printf("路径%c->%c存在，权值由%d改为%d\n", from, to, g->edge[i][j], weight);
	}
	else {
		g->edgeCount++;
	}
	g->edge[i][j] = weight;
	g->edge[j][i] = weight;
	printf("路径%c->%c添加成功！权值：%d\n", from, to, weight);
	return 0;
}
void DisplayVertices(Graph g) {
	printf("\n====景点列表====\n");
	if (g.vertexCount == 0) {
		printf("当前没有景点！\n");
		return;
	}
	printf("编号\t景点\n");
	for (int i = 0; i < g.vertexCount; i++) {
		printf("%d\t%c\n", i + 1, g.data[i]);
	}
	printf("总景点数：%d\n", g.vertexCount);
	printf("==========\n");
}
void ShowMenu() {
	printf("\n--- 景区路径规划系统 ---\n");
	printf("1. 添加景点\n");
	printf("2. 添加路径\n");
	printf("3. 显示景区图（邻接矩阵）\n");
	printf("4. 显示景点列表\n");
	printf("5. 深度优先遍历（DFS）\n");
	printf("6. 广度优先遍历（BFS）\n");
	printf("7. 切换图类型\n");
	printf("0. 退出\n");
	printf("请选择操作：");
}
static void dfsRecursive(Graph* g, int vertex, int* visited, char* path, int* index) {
	visited[vertex] = 1;
	path[*index] = g->data[vertex];
	(*index)++;
	for (int i = 0; i < g->vertexCount; i++) {
		if (g->edge[vertex][i] > 0 && !visited[i]) {
			dfsRecursive(g, i, visited, path, index);
		}
	}
}
char* DFS(Graph* g, char start, int* returnSize) {
	if (g == NULL) {
		*returnSize = 0;
		return NULL;
	}
	int statrIndex = -1;
	for (int i = 0; i < g->vertexCount; i++) {
		if (g->data[i] == start) {
			statrIndex = i;
			break;
		}
	}
	if (statrIndex == -1) {
		printf("顶点 '%c' 不存在！\n", start);
		*returnSize = 0;
		return NULL;
	}
	int* visited = (int*)calloc(g->vertexCount, sizeof(int));
	if (visited == NULL) {
		printf("内存分配失败(visited)\n");
		*returnSize;
		return NULL;
	}
	char* path = (char*)malloc(g->vertexCount * sizeof(char));
	if (path == NULL) {
		printf("内存分配失败(path)\n");
		free(visited);
		*returnSize = 0;
		return NULL;
	}
	int index = 0;
	dfsRecursive(g, statrIndex, visited, path, &index);
	free(visited);
	*returnSize = index;
	return path;
}
char* BFS(Graph* g, char start, int* returnSize) {
	if (g == NULL) {
		*returnSize = 0;
		return NULL;
	}
	int startIndex = -1;
	for (int i = 0; i < g->vertexCount; i++) {
		if (g->data[i] == start) {
			startIndex = i;
			break;
		}
	}
	if (startIndex == -1) {
		printf("顶点 '%c' 不存在！\n", start);
		*returnSize = 0;
		return NULL;
	}
	int* visited = (int*)calloc(g->vertexCount, sizeof(int));
	if (visited == NULL) {
		printf("内存分配失败(visited)\n");
		*returnSize = 0;
		return NULL;
	}
	char* path = (char*)malloc(g->vertexCount * sizeof(char));
	if (path == NULL) {
		printf("内存分配失败(path)\n");
		free(visited);
		*returnSize = 0;
		return NULL;
	}
	Queue* queue = createQueue(g->vertexCount);
	if (queue == NULL) {
		printf("队列创建失败！\n");
		free(visited);
		free(path);
		*returnSize = 0;
		return NULL;
	}
	int pathIndex = 0;
	visited[startIndex] = 1;
	path[pathIndex++] = g->data[startIndex];
	enqueue(queue, startIndex);
	while (!isEmpty(queue)) {
		int current = dequeue(queue);
		for (int i = 0; i < g->vertexCount; i++) {
			if (g->edge[current][i] > 0 && !visited[i]) {
				visited[i] = 1;
				path[pathIndex++] = g->data[i];
				enqueue(queue, i);
			}
		}
	}
	for (int i = 0; i < g->vertexCount; i++) {
		if (visited[i])continue;
		visited[i] = 1;
		path[pathIndex++] = g->data[i];
		enqueue(queue, i);
		while (!isEmpty(queue)) {
			int current = dequeue(queue);
			for (int j = 0; j < g->vertexCount; j++) {
				if (g->edge[current][j] > 0 && !visited[j]) {
					visited[j] = 1;
					path[pathIndex++] = g->data[j];
					enqueue(queue, j);
				}
			}
		}
	}
	free(visited);
	destroyQueue(queue);
	*returnSize = pathIndex;
	return path;
}