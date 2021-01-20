#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double x;
    double y;
} point;

const char *suffix(int n) {
    if (n % 100 == 11 || n % 100 == 12 || n % 100 == 13) {
        return "th";
    } else if (n % 10 == 1) {
        return "st";
    } else if (n % 10 == 2) {
        return "nd";
    } else if (n % 10 == 3) {
        return "rd";
    } else {
        return "th";
    }
}

point *read_points(int *count) {
    printf("How many points are on your polygon?\n>");
    scanf("%i", count);
    point *array = calloc(*count, sizeof(point));
    printf("\nSeparate the x and y coordinates with a space.\n");
    for (int i = 0; i < *count; i++) {
        printf("Enter the %i%s point>", i + 1, suffix(i + 1));
        scanf("%lf %lf", &array[i].x, &array[i].y);
    }
    return array;
}

double dist(const point point1, const point point2) {
    double xdiff = point1.x - point2.x;
    double ydiff = point1.y - point2.y;
    return sqrt(xdiff*xdiff + ydiff*ydiff);
}

double get_perimeter(const point *points, size_t count) {
    double perimeter = 0;
    for (size_t i = 0; i < count; i++) {
        perimeter += dist(points[i], points[(i + 1) % count]);
    }
    return perimeter;
}

double get_area(const point *points, size_t count) {
    point cur, next;
    double area = 0;
    for (size_t i = 0; i < count; i++) {
        cur = points[i]; 
        next = points[(i + 1) % count]; 
        area += (next.x + cur.x)*(next.y - cur.y);
    }
    return fabs(area)/2;
}

int main(int argc, char *argv[]) {
    printf("Welcome to the POLYGON PALACE!\n");
    int count;
    point *points = read_points(&count);
    if (points == NULL) {
        return 1;
    }
    double perimeter = get_perimeter(points, count);
    double area = get_area(points, count);
    printf("\nPerimeter: %lf\nArea: %lf\n", perimeter, area);
    
    free(points);
    return 0;
}
