#include "math.h"
#include "Shapes.h"
#include <string>
#include <sstream>

double twoPointsLength(const Point x, Point y){
    return sqrt((y.x-x.x)*(y.x-x.x)+(y.y-x.y)*(y.y-x.y));
}

double Rectangle::area() const{
    return l*w;
}
double Rectangle::perimeter() const{
    return 2*(l+w);
}
std::string Rectangle::description() const{
    std::stringstream ss;
    ss << "r(" << p.x << " " << p.y << " " << l << " " << w << ") ";
    return ss.str();
}

double Circle::area() const{
    return 3*r*r;
}
double Circle::perimeter() const{
    return 2*3*r;
}
std::string Circle::description() const{
    std::stringstream ss;
    ss << "c(" << p.x << " " << p.y << " " << r << ") ";
    return ss.str();
}

double Triangle::area() const{
    double a = twoPointsLength(fP, sP);
    double b = twoPointsLength(fP, tP);
    double c = twoPointsLength(sP, tP);
    double s = (a+b+c)/2;
    return sqrt(s*(s-a)*(s-b)*(s-c));
}
double Triangle::perimeter() const{
    double a = twoPointsLength(fP, sP);
    double b = twoPointsLength(fP, tP);
    double c = twoPointsLength(sP, tP);
    return a+b+c;
}
std::string Triangle::description() const{
    std::stringstream ss;
    ss << "t(" << fP.x << " " << fP.y << " " << sP.x << " " << sP.y << " " << tP.x << " " << tP.y << ") ";
    return ss.str();
}
