#ifndef SHAPES_H_INCLUDED
#define SHAPES_H_INCLUDED

#include <string>
#include "Point.h"

class Shape
{
public:
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual std::string description() const {return std::string("");}
};

class Rectangle:public Shape
{
public:
    Rectangle(Point point, double length, double width):p(point),l(length),w(width){}
    double area() const;
    double perimeter() const;
    std::string description() const;

private:
    Point p;
    double l,w;
};

class Circle:public Shape
{
public:
    Circle(Point point,double radius):p(point), r(radius){}
    double area() const;
    double perimeter() const;
    std::string description() const;
private:
    Point p;
    double r;
};

class Triangle:public Shape{
public:
    Triangle(Point firstPoint, Point secondPoint, Point thirdPoint):fP(firstPoint), sP(secondPoint), tP(thirdPoint){}
    double area() const;
    double perimeter() const;
    std::string description() const;
private:
    Point fP, sP, tP;
};

#endif // SHAPES_H_INCLUDED
