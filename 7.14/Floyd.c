#include "global.h"

//Floyd 全源最短路径核心算法
void floyd(TourGraph *g) {
    int n = g->spot_count;

    // 初始化
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            g->floyd_dist[i][j] = g->distance[i][j];
            // 有直连路径则前驱为起点i，无路径则前驱为-1
            if (i != j && g->distance[i][j] < INF)
                g->floyd_path[i][j] = i;
            else
                g->floyd_path[i][j] = -1;
        }
    }
    //o(n)爆了 
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (g->floyd_dist[i][k] < INF && g->floyd_dist[k][j] < INF) {
                    if (g->floyd_dist[i][j] > g->floyd_dist[i][k] + g->floyd_dist[k][j]) {
                        g->floyd_dist[i][j] = g->floyd_dist[i][k] + g->floyd_dist[k][j];
                        g->floyd_path[i][j] = g->floyd_path[k][j];
                    }
                }
            }
        }
    }
}

//内部工具：递归回溯打印完整路径
static void printFloydPath(TourGraph *g, int start, int end) {
    if (start == end) {
        printf("%s", g->spots[start].name);
        return;
    }
    if (g->floyd_path[start][end] == -1) {
        printf("无可达路径");
        return;
    }
    printFloydPath(g, start, g->floyd_path[start][end]);
    printf(" → %s", g->spots[end].name);
}

//对外接口：两点最短路径查询
void planRouteByFloyd(TourGraph *g) {
    int start, end;
    showAllSpots(g);
    printf_distance(g); 
    
    printf("请输入起点编号：");
    scanf("%d", &start);
    printf("请输入终点编号：");
    scanf("%d", &end);

    // 编号合法性校验
    if (start < 1 || start > g->spot_count || end < 1 || end > g->spot_count) {
        printf("景点编号无效！\n");
        return;
    }
    start--; end--;

    // 不可达判断
    if (g->floyd_dist[start][end] >= INF) {
        printf("两景点之间无可达路径！\n");
        return;
    }

    // 输出结果
    printf("\n===== 最短路径规划结果 =====\n");
    printf("总距离：%d 米 (%.2f 公里)\n", 
           g->floyd_dist[start][end], 
           g->floyd_dist[start][end] / 1000.0);
    printf("途经路线：");
    printFloydPath(g, start, end);
    printf("\n");
}
