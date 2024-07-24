#pragma once
#include <cmath>

#define SCREEN_WIDTH 1024// 640
#define SCREEN_HEIGHT 720// 580
#define DEBUGGING false

#define DT 1.0L/120.0L

extern int opacity;

int calculate_distance(int x1, int y1, int x2, int y2);

struct Vec2d {
    double x = 0;
    double y = 0;
};