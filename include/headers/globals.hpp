#pragma once
#include <cmath>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGH 720
#define DEBUGGING false

#define DT 1.0L/120.0L



int calculate_distance(int x1, int y1, int x2, int y2);

struct Vec2d {
    double x = 0;
    double y = 0;
};