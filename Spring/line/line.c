#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

typedef struct {
    double x;
    double y;
} point;

double dist(point p1, point p2) {
    double xdiff = p1.x - p2.x;
    double ydiff = p1.y - p2.y;
    return sqrt(xdiff*xdiff + ydiff*ydiff);
}

typedef struct {
    point p1;
    point p2;
} line;

double length(line l) {
    return dist(l.p1, l.p2);
}

double slope(line l) {
    return (l.p2.y - l.p1.y)/(l.p2.x - l.p1.x);
}

bool point_on_line(line l, point p) {
    double m = slope(l);
    double y_intercept = l.p1.y - m*l.p1.x;
    return fabs(p.y - (m*p.x + y_intercept)) < 1e-6;
}

int main(int argc, char *argv[]) {
    line l1 = {
        .p1 = {0, 0},
        .p2 = {1, 2}
    };
    line l2 = {
        .p1 = {-3, 1},
        .p2 = {0, 1}
    };
    point p1 = {-3, -6};
    point p2 = {5, 1};
    point p3 = {2, -1};

    printf("Should be %f: %f\n", sqrt(64 + 49), dist(p1, p2));
    printf("Should be %f: %f\n", 3.0, length(l2));
    printf("Should be %f: %f\n", 2.0, slope(l1));

    printf("Should be 1: %i\n", point_on_line(l1, p1));
    printf("Should be 1: %i\n", point_on_line(l2, p2));
    printf("Should be 0: %i\n", point_on_line(l1, p3));
    printf("Should be 0: %i\n", point_on_line(l2, p3));
    printf("Should be 0: %i\n", point_on_line(l1, p2));
    printf("Should be 0: %i\n", point_on_line(l2, p1));
    return 0;
}
