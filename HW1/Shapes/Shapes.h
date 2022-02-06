#ifndef SHAPES_H_INCLUDED
#define SHAPES_H_INCLUDED

#include <vector>
#include <cmath>
#include <iostream>
using namespace std;

class Shape {
public:
    virtual double area() const = 0;
    virtual double perimeter() const=0;
    virtual ~Shape(){}
};
class Rectangle : public Shape {
public:
    Rectangle(double ulcx, double ulcy, double length, double width):
        x(ulcx),y(ulcy),l(length),w(width){}
    double area() const {return l*w;}
    double perimeter()const {return (l+w)*2;}
private:
    double x,y,l,w;
};

class Circle : public Shape{
public:
    Circle(double centerX,double centerY,double radius):
        cx(centerX),cy(centerY),r(radius){}
    double area()const {return 3*r*r;}
    double perimeter()const {return 2*3*r;}
private:
    double cx,cy,r;
};

//find a line between two points
double LengthOfTriangle(double x1,double x2,double y1,double y2)
{
    return sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
}
//determine whether the three points constitute a triangle
bool isTriangle(double a,double b,double c)
{
    if(((a+b)<=c)||((a+c)<=b)||((b+c)<a))
        return false;
    else
        return true;
}
class Triangle:public Shape{
public:
    Triangle(double tx1,double ty1,double tx2,double ty2,double tx3,double ty3):
        x1(tx1),x2(tx2),x3(tx3),y1(ty1),y2(ty2),y3(ty3){}
    double area()const {
        //find three line of triangle
        double a=LengthOfTriangle(x1,x2,y1,y2);
        double b=LengthOfTriangle(x1,x3,y1,y3);
        double c=LengthOfTriangle(x2,x3,y2,y3);
        //determine whether the triangle
        if(isTriangle(a,b,c))
        {
            //using Helen formula
            double s=(a+b+c)/2;//1/2of triangle perimeter
            return(sqrt(s*(s-a)*(s-b)*(s-c)));
        }
        //not a triangle
        else
        {
            return 0;
        }
    }
    double perimeter()const {
        //find three line of triangle
        double a=LengthOfTriangle(x1,x2,y1,y2);
        double b=LengthOfTriangle(x1,x3,y1,y3);
        double c=LengthOfTriangle(x2,x3,y2,y3);
        //determine whether the triangle
        if(isTriangle(a,b,c))
        {
            return (a+b+c);
        }
        //not a triangle
        else
        {
            return 0;
        }
    }
private:
    double x1,x2,x3,y1,y2,y3;
};

double sumOfArea(std::vector<Rectangle> rects) {
    double total =0;
    for (Rectangle r: rects)
        total += r.area();
    return total;
}

double sumOfArea(std::vector<Shape *> rects) {
    double total =0;
    for (Shape *r: rects)
        total += r->area();
    return total;
}
double sumOfPerimeter(vector<Shape *>shapes)
{
    double total=0;
    for(Shape *p:shapes)
        total+=p->perimeter();
    return total;
}
#endif // SHAPES_H_INCLUDED
