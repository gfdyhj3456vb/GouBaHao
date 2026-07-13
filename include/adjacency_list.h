#define _CRT_SECURE_NO_WARNINGS
#pragma once
#ifndef ADJACENCY_LIST_H
#define ADJACENCY_LIST_H
#include <stdbool.h>
#define MAX_VERTEX_NUM 100
typedef struct EdgeNode {
	int adjVertex;
	int weight;
	struct EdgeNode* next;
}EdgeNode;
typedef struct {
	char data;
	EdgeNode* firstEdge;
}VertexNode;
typedef struct {
	VertexNode vertices[MAX_VERTEX_NUM];
	int vertexCount;
	int edgeCount;
}AdjList;
AdjList* al_create(void);
void al_destory(AdjList* graph);
int al_addVertex(AdjList* graph, char data);
int al_addEdge(AdjList* graph, char from, char to, int weight);
void al_print(AdjList* graph);
void al_dfs(AdjList* graph, char start);
void al_bfs(AdjList* graph, char start);
#endif

