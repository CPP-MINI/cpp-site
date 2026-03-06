struct Point {
    int x;
    int y;
    int z;
};

int dist(Point p, Point q) {
    int dx = p.x - q.x;
    int dy = p.y - q.y;
    int dz = p.z - q.z;
    return dx * dx + dy * dy + dz * dz;
}
