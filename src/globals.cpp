#include <headers/globals.hpp>

int calculate_distance(int x1, int y1, int x2, int y2) {
    return round(sqrt(pow(x1-x2, 2) + pow((y1-y2), 2)));
};