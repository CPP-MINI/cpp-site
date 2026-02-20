#include "point.hpp"

int factor = 2;

int dist(Point p, Point q) {
    int dx = p.x - q.x;
    int dy = p.y - q.y;
    return factor * (dx * dx + dy * dy);
}
