#include "global.h"

// 显示菜单
void showMenu() {
    printf("\n");
    printf("==================================\n");
    printf("    旅游景点规划系统 V1.0\n");
    printf("==================================\n");
    printf("1. 查看所有景点\n");
    printf("2. 添加新景点\n");
    printf("3. 添加景点间路径\n");
    printf("4. 两点间最短路径规划\n");
    printf("5. 多景点游览路线规划\n");
    printf("6. 按评分推荐景点\n");
    printf("7. 按预算筛选景点\n");
	printf("8. 删除景点\n");
    printf("9. 重新加载预设数据\n");
    printf("10. 查看各个路径是否连通及距离\n");
    printf("0. 退出系统\n");
    printf("==================================\n");
    printf("请选择功能：");
}

int main() {
    TourGraph graph;
    initGraph(&graph);
    int choice;

    // 启动优先加载本地文件，无文件则加载预设景点
    if (loadFromFile(&graph, "tour_data.dat")) {
        printf("已加载历史数据，当前景点数：%d\n", graph.spot_count);
    } else {
        initDefaultData(&graph);
        printf("已加载预设北京经典景点，共%d个\n", graph.spot_count);
    }

    while (1) {
        showMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1: showAllSpots(&graph); break;
            case 2: addSpot(&graph); break;
            case 3: addPath(&graph); break;
//            case 4: planRoute(&graph); break;
			case 4:planRouteByFloyd(&graph); break;
            case 5: planMultiSpot(&graph); break;
            case 6: recommendByRating(&graph); break;
            case 7: filterByBudget(&graph); break;
			case 8: deleteSpot(&graph); break;
            case 9:
                initDefaultData(&graph);
                printf("已重置为预设景点数据\n");
                break;
            case 10:printf_distance(&graph);break;
            case 0:
                printf("感谢使用，再见！\n");
                return 0;
            default:
                printf("输入无效，请重新选择！\n");
        }
    }
}
