#ifndef TOUR_H
#define TOUR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SCENIC 50       // 最大景点数量
#define NAME_LEN 30         // 景点名称最大长度
#define DESC_LEN 100        // 景点描述最大长度
#define INF 99999           // 表示无穷大（无直接路径）

// 景点结构体
typedef struct ScenicSpot{
    char name[NAME_LEN];    // 景点名称
    char desc[DESC_LEN]; 	// 景点描述
    float rating;           // 评分（0-5）
    int ticket_price;
    int visit_time;         // 建议游览时间
} ScenicSpot;


// 工作结构体
typedef struct TourGraph{
    ScenicSpot spots[MAX_SCENIC];   // 景点数组
    int distance[MAX_SCENIC][MAX_SCENIC];  // 距离矩阵（单位：米）
    int spot_count;                  // 当前景点数量
    //floyd
	int floyd_dist[MAX_SCENIC][MAX_SCENIC]; // 全源最短距离矩阵
    int floyd_path[MAX_SCENIC][MAX_SCENIC]; // 前驱节点矩阵，用于还原完整路径  
} TourGraph;


// 函数声明
void initGraph(TourGraph *g);                  // 初始化空图

void printf_distance(TourGraph *g);

void initDefaultData(TourGraph *g);            // 加载预设景点数据

void showAllSpots(TourGraph *g);               // 显示所有景点

void addSpot(TourGraph *g);                    // 添加景点

void addPath(TourGraph *g);                    // 添加路径

void planRoute(TourGraph *g);                  // 两点最短路径规划

void planMultiSpot(TourGraph *g);              // 多景点游览规划

void recommendByRating(TourGraph *g);          // 按评分推荐

void filterByBudget(TourGraph *g);             // 按预算筛选

//void saveToFile(TourGraph *g, const char *filename);  // 保存数据
int loadFromFile(TourGraph *g, const char *filename);  // 加载数据

void deleteSpot(TourGraph *g);    // 删除指定景点

void floyd(TourGraph *g);                // 执行Floyd算法，计算所有景点两两最短路径

void planRouteByFloyd(TourGraph *g);     // 菜单入口：查询两点间最短路径

#endif
