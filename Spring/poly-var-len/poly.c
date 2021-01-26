#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double x;
    double y;
} point;

typedef struct {
    size_t len;
    point points[];
} polygon;

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

polygon *read_polygon() {
    printf("How many points are on your polygon?\n>");
    size_t len = 0;
    scanf("%zu", &len);
    polygon *poly = malloc(sizeof(polygon) + len * sizeof(point));
    poly->len = len;
    printf("\nSeparate the x and y coordinates with a space.\n");
    for (int i = 0; i < len; i++) {
        printf("Enter the %i%s point>", i + 1, suffix(i + 1));
        scanf("%lf %lf", &(poly->points[i].x), &(poly->points[i].y));
    }
    return poly;
}

double dist(const point point1, const point point2) {
    double xdiff = point1.x - point2.x;
    double ydiff = point1.y - point2.y;
    return sqrt(xdiff*xdiff + ydiff*ydiff);
}

double get_perimeter(const polygon *poly) {
    double perimeter = 0;
    for (size_t i = 0; i < poly->len; i++) {
        perimeter += dist(poly->points[i], poly->points[(i + 1) % poly->len]);
    }
    return perimeter;
}

double get_area(const polygon *poly) {
    point cur, next;
    double area = 0;
    for (size_t i = 0; i < poly->len; i++) {
        cur = poly->points[i]; 
        next = poly->points[(i + 1) % poly->len]; 
        area += (next.x + cur.x)*(next.y - cur.y);
    }
    return fabs(area)/2;
}

int main(int argc, char *argv[]) {
    printf("Welcome to the POLYGON PALACE!\n");

    polygon *poly = read_polygon();
    if (poly == NULL) {
        return 1;
    }
    double perimeter = get_perimeter(poly);
    double area = get_area(poly);
    printf("\nPerimeter: %lf\nArea: %lf\n", perimeter, area);
    
    free(poly);
    return 0;
}
