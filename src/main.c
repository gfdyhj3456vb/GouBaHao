#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include "../include/adjacency_matrix.h"
#include "../include/adjacency_list.h"
typedef enum {
    GRAPH_MATRIX,
    GRAPH_LIST
}GraphType;
int main() {
    Graph g;
    FirstGraph(&g);
    AdjList* listGraph = al_create();
    if (listGraph == NULL) {
        printf("邻接表创建失败！程序退出。\n");
        return 1;
    }
    GraphType currentType = GRAPH_MATRIX;
    int choice;
    char from, to, vertex;
    int weight;
    while (1) {
        printf("\n当前图类型：%s\n", currentType == GRAPH_MATRIX ? "邻接矩阵" : "邻接表");
        ShowMenu();
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("请输入要添加的景点（单字符）：");
            scanf(" %c", &vertex);
            if (currentType == GRAPH_MATRIX) {
                AddVertex(&g, vertex);
            }
            else {
                al_addVertex(listGraph, vertex);
            }

            break;

        case 2:
            printf("请输入起点、终点和权值（如 A B 5）：");
            scanf(" %c %c %d", &from, &to, &weight);
            if (currentType == GRAPH_MATRIX) {
                AddEdge(&g, from, to, weight);
            }
            else {
                al_addEdge(listGraph, from, to, weight);
            }

            break;

        case 3:
            if (currentType == GRAPH_MATRIX) {
                printGraph(g);
            }
            else {
                al_print(listGraph);
            }
            break;

        case 4:
            if (currentType == GRAPH_MATRIX) {
                DisplayVertices(g);
            }
            else {
                printf("\n==== 景点列表 ====\n");
                if (listGraph->vertexCount == 0) {
                    printf("当前没有景点！\n");
                }
                else {
                    printf("编号\t景点\n");
                    for (int i = 0; i < listGraph->vertexCount; i++) {
                        printf("%d\t%c\n", i + 1, listGraph->vertices[i].data);
                    }
                    printf("总景点数：%d\n", listGraph->vertexCount);
                }
                printf("================\n");
            }
            break;
        case 5:
            printf("请输入起始顶点:");
            scanf(" %c", &vertex);
            if (currentType == GRAPH_MATRIX) {
                int pathSize1 = 0;
                char* path1 = DFS(&g, vertex, &pathSize1);
                if (path1 != NULL) {
                    printf("DFS 遍历顺序:");
                    for (int i = 0; i < pathSize1; i++) {
                        printf("%c", path1[i]);
                        if (i < pathSize1 - 1) printf("->");
                    }
                    printf("\n");
                    free(path1);
                }
                else {
                    printf("DFS 执行失败，请检查起始顶点是否存在。\n");
                }
            }
            else {
                al_dfs(listGraph, vertex);
            }
            break;
        case 6:
            printf("请输入起始顶点：");
            scanf(" %c", &vertex);
            if (currentType == GRAPH_MATRIX) {
                int pathSize2 = 0;
                char* path2 = BFS(&g, vertex, &pathSize2);
                if (path2 != NULL) {
                    printf("BFS遍历顺序:");
                    for (int i = 0; i < pathSize2; i++) {
                        printf("%c", path2[i]);
                        if (i < pathSize2 - 1)printf("->");
                    }
                    printf("\n");
                    free(path2);
                }
                else {
                    printf("BFS 执行失败，请检查起始顶点是否存在。\n");
                }
            }
            else {
                al_bfs(listGraph, vertex);
            }
            break;
        case 7:
            if (currentType == GRAPH_MATRIX) {
                currentType = GRAPH_LIST;
                printf("已切换到邻接表。");
                if (listGraph->vertexCount == 0) {
                    printf("（当前邻接表为空，请添加景点和路径）\n");
                }
                else {
                    printf("\n");
                }
            }
            else {
                currentType = GRAPH_MATRIX;
                printf("已切换到邻接矩阵。\n");
            }
            break;
        case 0:
            printf("感谢使用，再见！\n");
            return 0;

        default:
            printf("无效选择，请重新输入。\n");
        }
    }
    return 0;
}
