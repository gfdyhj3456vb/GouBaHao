#define _CRT_SECURE_NO_WARNINGS
#pragma once
#ifndef ADJACENCY_MATRIX_H
#define ADJACENCY_MATRIX_H
#include<stdbool.h>
#define MAX 100
typedef struct adjacency {
	char data[MAX];
	int edge[MAX][MAX];
	int vertexCount, edgeCount;
}Graph;
void FirstGraph(Graph* g);
void printGraph(Graph g);
int AddVertex(Graph* g, char vertex);
int AddEdge(Graph* g, char from, char to, int weight);
void DisplayVertices(Graph g);
void ShowMenu();
char* DFS(Graph* g, char start, int* returnSize);
char* BFS(Graph* g, char start, int* returnSize);
#endif 