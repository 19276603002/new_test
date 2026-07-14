#include "global.h"

// 初始化空图
void initGraph(TourGraph *g) {
	g->spot_count = 0;
	for (int i = 0; i < MAX_SCENIC; i++) {
		for (int j = 0; j < MAX_SCENIC; j++) {
			g->distance[i][j] = (i == j) ? 0 : INF;
		}
	}
	void floyd(TourGraph *g);
}

// 从文件加载数据(ai)
int loadFromFile(TourGraph *g, const char *filename) {
	FILE *fp = fopen(filename, "rb");
	if (!fp) return 0;
	fread(&g->spot_count, sizeof(int), 1, fp);
	fread(g->spots, sizeof(ScenicSpot), g->spot_count, fp);
	for (int i = 0; i < g->spot_count; i++) {
		fread(g->distance[i], sizeof(int), g->spot_count, fp);
	}
	fclose(fp);
	return 1;
}

// 加载预设景点与路径（北京经典景点）
void initDefaultData(TourGraph *g) {
	g->spot_count = 6;

	// 预设6个景点
	strcpy(g->spots[0].name, "天安门广场");
	strcpy(g->spots[0].desc, "北京中心地标，世界最大城市广场");
	g->spots[0].rating = 4.8;
	g->spots[0].ticket_price = 0;
	g->spots[0].visit_time = 90;

	strcpy(g->spots[1].name, "故宫博物院");
	strcpy(g->spots[1].desc, "明清皇家宫殿，世界文化遗产");
	g->spots[1].rating = 4.9;
	g->spots[1].ticket_price = 60;
	g->spots[1].visit_time = 180;

	strcpy(g->spots[2].name, "颐和园");
	strcpy(g->spots[2].desc, "清代皇家园林，中国四大名园之一");
	g->spots[2].rating = 4.7;
	g->spots[2].ticket_price = 30;
	g->spots[2].visit_time = 150;

	strcpy(g->spots[3].name, "天坛公园");
	strcpy(g->spots[3].desc, "明清皇帝祭天场所，古建筑瑰宝");
	g->spots[3].rating = 4.6;
	g->spots[3].ticket_price = 15;
	g->spots[3].visit_time = 120;

	strcpy(g->spots[4].name, "八达岭长城");
	strcpy(g->spots[4].desc, "万里长城精华段，世界文化遗产");
	g->spots[4].rating = 4.8;
	g->spots[4].ticket_price = 40;
	g->spots[4].visit_time = 240;

	strcpy(g->spots[5].name, "南锣鼓巷");
	strcpy(g->spots[5].desc, "北京老胡同文化特色街区");
	g->spots[5].rating = 4.3;
	g->spots[5].ticket_price = 0;
	g->spots[5].visit_time = 60;

	// 初始化距离矩阵
	for (int i = 0; i < g->spot_count; i++) {
		for (int j = 0; j < g->spot_count; j++) {
			g->distance[i][j] = INF;
		}
		g->distance[i][i] = 0;
	}

	// 设置景点间路径（双向，单位：米）
	g->distance[0][1] = 1000;
	g->distance[1][0] = 1000;   // 天安门-故宫
	g->distance[0][2] = 12000;
	g->distance[2][0] = 12000;  // 天安门-颐和园
	g->distance[0][3] = 3000;
	g->distance[3][0] = 3000;   // 天安门-天坛
	g->distance[0][5] = 2500;
	g->distance[5][0] = 2500;   // 天安门-南锣鼓巷
	g->distance[1][2] = 15000;
	g->distance[2][1] = 15000;  // 故宫-颐和园
	g->distance[1][5] = 2000;
	g->distance[5][1] = 2000;   // 故宫-南锣鼓巷
	g->distance[2][4] = 50000;
	g->distance[4][2] = 50000;  // 颐和园-八达岭
	g->distance[3][5] = 4000;
	g->distance[5][3] = 4000;   // 天坛-南锣鼓巷
	
	void floyd(TourGraph *g);
}

// 显示所有景点
void showAllSpots(TourGraph *g) {
	if (g->spot_count == 0) {
		printf("暂无景点信息！\n");
		return;
	}
	printf("\n===== 景点列表 =====\n");
	printf("编号\t名称\t\t评分\t票价\t游览时间\n");
	printf("----------------------------------------\n");
	for (int i = 0; i < g->spot_count; i++) {
		printf("%d\t%-10s\t%.1f\t%d元\t%d分钟\n",
		       i+1, g->spots[i].name, g->spots[i].rating,
		       g->spots[i].ticket_price, g->spots[i].visit_time);
	}
}

// 添加景点
void addSpot(TourGraph *g) {
	if (g->spot_count >= MAX_SCENIC) {
		printf("景点数量已达上限！\n");
		return;
	}
	ScenicSpot *s = &g->spots[g->spot_count];
	printf("请输入景点名称：");
	scanf(" %[^\n]", s->name);
	printf("请输入景点描述：");
	scanf(" %[^\n]", s->desc);
	printf("请输入景点评分(0-5)：");
	scanf("%f", &s->rating);
	printf("请输入门票价格(元)：");
	scanf("%d", &s->ticket_price);
	printf("请输入建议游览时间(分钟)：");
	scanf("%d", &s->visit_time);

	for (int i = 0; i <= g->spot_count; i++) {
		g->distance[g->spot_count][i] = INF;
		g->distance[i][g->spot_count] = INF;
	}
	g->distance[g->spot_count][g->spot_count] = 0;
	g->spot_count++;
	printf("景点添加成功！\n");
	
	void floyd(TourGraph *g);
}

// 添加路径
void addPath(TourGraph *g) {
	int a, b, dist;
	showAllSpots(g);
	printf("请输入两个景点编号：");
	scanf("%d%d", &a, &b);
	if (a < 1 || a > g->spot_count || b < 1 || b > g->spot_count) {
		printf("景点编号无效！\n");
		return;
	}
	printf("请输入两点距离(米)：");
	scanf("%d", &dist);
	a--;
	b--;
	g->distance[a][b] = dist;
	g->distance[b][a] = dist;
	printf("路径添加成功！\n");
	
	void floyd(TourGraph *g);
}

// Dijkstra核心算法
//static void dijkstra(TourGraph *g, int start, int end) {
//	int dist[MAX_SCENIC];
//	int visited[MAX_SCENIC] = {0};
//	int path[MAX_SCENIC];
//
//	for (int i = 0; i < g->spot_count; i++) {
//		dist[i] = g->distance[start][i];
//		path[i] = (dist[i] < INF) ? start : -1;
//	}
//	visited[start] = 1;
//
//	for (int i = 0; i < g->spot_count - 1; i++) {
//		int min = INF, u = -1;
//		for (int j = 0; j < g->spot_count; j++) {
//			if (!visited[j] && dist[j] < min) {
//				min = dist[j];
//				u = j;
//			}
//		}
//		if (u == -1) break;
//		visited[u] = 1;
//
//		for (int v = 0; v < g->spot_count; v++) {
//			if (!visited[v] && g->distance[u][v] < INF) {
//				if (dist[v] > dist[u] + g->distance[u][v]) {
//					dist[v] = dist[u] + g->distance[u][v];
//					path[v] = u;
//				}
//			}
//		}
//	}
//
//	if (dist[end] >= INF) {
//		printf("两景点之间无可达路径！\n");
//		return;
//	}
//
//	printf("\n最短路径距离：%d 米 (%.2f 公里)\n", dist[end], dist[end]/1000.0);
//
//	int stack[MAX_SCENIC], top = 0;
//	int cur = end;
//	while (cur != -1) {
//		stack[top++] = cur;
//		if (cur == start) break;
//		cur = path[cur];
//	}
//
//	printf("路线：");
//	for (int i = top - 1; i >= 0; i--) {
//		printf("%s", g->spots[stack[i]].name);
//		if (i > 0) printf(" → ");
//	}
//	printf("\n");
//}

// 两点路径规划入口
//void planRoute(TourGraph *g) {
//	int start, end;
//	showAllSpots(g);
//	printf("请输入起点编号：");
//	scanf("%d", &start);
//	printf("请输入终点编号：");
//	scanf("%d", &end);
//	if (start < 1 || start > g->spot_count || end < 1 || end > g->spot_count) {
//		printf("编号无效！\n");
//		return;
//	}
//	dijkstra(g, start-1, end-1);
//}

// 多景点游览规划（贪心近似TSP）
void planMultiSpot(TourGraph *g) {
	int n, spots[MAX_SCENIC];
	printf("请输入要游览的景点数量：");
	scanf("%d", &n);
	if (n <= 0 || n > g->spot_count) {
		printf("数量无效！\n");
		return;
	}

	showAllSpots(g);
	printf("请依次输入%d个景点编号：\n", n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &spots[i]);
		spots[i]--;
	}

	int visited[MAX_SCENIC] = {0};
	int order[MAX_SCENIC];
	int total_dist = 0;
	int cur = spots[0];
	visited[0] = 1;
	order[0] = spots[0];

	for (int i = 1; i < n; i++) {
		int min_dist = INF, next_idx = -1;
		for (int j = 0; j < n; j++) {
			if (!visited[j] && g->distance[cur][spots[j]] < min_dist) {
				min_dist = g->distance[cur][spots[j]];
				next_idx = j;
			}
		}
		if (next_idx == -1) {
			printf("存在不可达景点！\n");
			return;
		}
		visited[next_idx] = 1;
		order[i] = spots[next_idx];
		total_dist += min_dist;
		cur = spots[next_idx];
	}

	int total_time = 0, total_price = 0;
	printf("\n===== 推荐游览顺序 =====\n");
	for (int i = 0; i < n; i++) {
		printf("%d. %s\n", i+1, g->spots[order[i]].name);
		total_time += g->spots[order[i]].visit_time;
		total_price += g->spots[order[i]].ticket_price;
	}
	printf("\n总路程：%d 米 (%.2f 公里)\n", total_dist, total_dist/1000.0);
	printf("总游览时间：%d 分钟 (%.1f 小时)\n", total_time, total_time/60.0);
	printf("总门票费用：%d 元\n", total_price);
}

// 按评分排序推荐
void recommendByRating(TourGraph *g) {
	if (g->spot_count == 0) {
		printf("暂无景点！\n");
		return;
	}
	int idx[MAX_SCENIC];
	for (int i = 0; i < g->spot_count; i++) idx[i] = i;

	for (int i = 0; i < g->spot_count - 1; i++) {
		for (int j = 0; j < g->spot_count - i - 1; j++) {
			if (g->spots[idx[j]].rating < g->spots[idx[j+1]].rating) {
				int temp = idx[j];
				idx[j] = idx[j+1];
				idx[j+1] = temp;
			}
		}
	}

	printf("\n===== 评分推荐TOP5 =====\n");
	int count = g->spot_count < 5 ? g->spot_count : 5;
	for (int i = 0; i < count; i++) {
		int s = idx[i];
		printf("%d. %-10s 评分:%.1f 票价:%d元\n",
		       i+1, g->spots[s].name, g->spots[s].rating, g->spots[s].ticket_price);
	}
}

// 按预算筛选
void filterByBudget(TourGraph *g) {
	int budget;
	printf("请输入门票预算上限(元)：");
	scanf("%d", &budget);

	printf("\n符合预算的景点：\n");
	int found = 0;
	for (int i = 0; i < g->spot_count; i++) {
		if (g->spots[i].ticket_price <= budget) {
			printf("- %s (票价:%d元, 评分:%.1f)\n",
			       g->spots[i].name, g->spots[i].ticket_price, g->spots[i].rating);
			found = 1;
		}
	}
	if (!found) printf("无符合条件的景点\n");
}



// 删除指定景点
void deleteSpot(TourGraph *g) {
	if (g->spot_count == 0) {
		printf("当前无景点可删除！\n");
		return;
	}

	int num;
	showAllSpots(g);
	printf("请输入要删除的景点编号：");
	scanf("%d", &num);

	// 编号合法性校验
	if (num < 1 || num > g->spot_count) {
		printf("景点编号无效！\n");
		return;
	}

	int idx = num - 1;
	char confirm;
	printf("确认删除景点【%s】吗？(y/n): ", g->spots[idx].name);
	scanf(" %c", &confirm);
	if (confirm != 'y' && confirm != 'Y') {
		printf("已取消删除操作\n");
		return;
	}

	// 1. 前移景点数组，覆盖被删除的元素
	for (int i = idx; i < g->spot_count - 1; i++) {
		g->spots[i] = g->spots[i + 1];
	}

	// 2. 前移距离矩阵的行（删除第idx行）
	for (int i = idx; i < g->spot_count - 1; i++) {
		memcpy(g->distance[i], g->distance[i + 1], sizeof(g->distance[i]));
	}

	// 3. 左移距离矩阵的列（删除第idx列）
	for (int i = 0; i < g->spot_count - 1; i++) {
		for (int j = idx; j < g->spot_count - 1; j++) {
			g->distance[i][j] = g->distance[i][j + 1];
		}
	}

	// 4. 景点总数减1
	g->spot_count--;


	printf("景点删除成功，路径数据已同步更新！\n");
	
	void floyd(TourGraph *g);
}

void printf_distance(TourGraph *g){
	printf("%-16s", "");
	for(int k=0;k<g->spot_count;k++){
		printf("%-16s",g->spots[k].name);
	}
	printf("\n");
	for(int i=0;i<g->spot_count;i++){
		printf("%-16s",g->spots[i].name);
		for(int j=0;j<g->spot_count;j++){
			if (g->distance[i][j] >= INF) {
                printf("%-16s", "∞");
        	}else{printf("%-16d",g->distance[i][j]);}
		}
		printf("\n");
	}
}
















