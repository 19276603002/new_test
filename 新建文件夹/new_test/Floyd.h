#ifndef TOUR_H
#define TOUR_H

#include "global.h"

void floyd(TourGraph *g);                // 执行Floyd算法，计算所有景点两两最短路径
void planRouteByFloyd(TourGraph *g);     // 菜单入口：查询两点间最短路径

#endif
