#include <math.h>
#include <iostream>

#ifndef _POINT_H
#define _POINT_H

class Point
{
private:
    /* data */
public:
    Point(/* args */);
    ~Point();

    double x;
    double y;
    double getDistance(Point &p);
    Point(double _x, double _y);
};

Point::Point(/* args */)
{
    x = 0;
    y = 0;
}
Point::Point(double _x, double _y)
{
    x = _x;
    y = _y;
}

double Point::getDistance(Point &p)
{
    double dx = x - p.x;
    double dy = y - p.y;
    return sqrt(dx * dx + dy * dy);
}

Point::~Point()
{
}

#endif

int main()
{
    Point a;
    Point b;
    printf("输入a点的坐标:\n");
    scanf("%lf,%lf", &a.x, &a.y);
    printf("输入b点的坐标:\n");
    scanf("%lf,%lf", &b.x, &b.y);

    double distance = a.getDistance(b);

    printf("a-b两点的距离是：%f\n", distance);

    return 0;
}