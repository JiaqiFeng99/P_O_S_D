#ifndef UTSHAPES_H_INCLUDED
#define UTSHAPES_H_INCLUDED

#include "..\cppunitlite\TestHarness.h"
#include "Shapes.h"
#include <vector>

const double epsilon = 0.000001;
// added this line
TEST (first, Rectangle) {
    Rectangle rect(0,0,4,2);
    DOUBLES_EQUAL(8,rect.area(),epsilon);
    DOUBLES_EQUAL(12,rect.perimeter(),epsilon);
}

TEST(sencond,Circle)
{
    Circle circ(0,0,10);
    DOUBLES_EQUAL(300,circ.area(),epsilon);
    DOUBLES_EQUAL(60,circ.perimeter(),epsilon);
}

TEST (third, sumOfArea) {
    Rectangle r1(0,0,4,2);
    Rectangle r2(0,0,3,3);
    std::vector<Rectangle> rects;
    rects.push_back(r1);
    rects.push_back(r2);
    DOUBLES_EQUAL(17, sumOfArea(rects),epsilon);
}

TEST (fourth, sumOfArea) {
    std::vector<Rectangle> rects;
    DOUBLES_EQUAL(0, sumOfArea(rects),epsilon);
}

TEST (fifth, sumOfArea) {
    Rectangle r1(0,0,4,2);
    Circle c1(0,0,10);
    std::vector<Shape *> ss;
    ss.push_back(&r1);
    ss.push_back(&c1);
    DOUBLES_EQUAL(308,sumOfArea(ss),epsilon);
}
TEST(sixth,Triangle)
{
    Triangle tri(0,0,3,4,6,0);
    DOUBLES_EQUAL(12,tri.area(),epsilon);
    DOUBLES_EQUAL(16,tri.perimeter(),epsilon);
}
TEST(seventh,sumOfPerimeter)
{
    Rectangle r1(0,0,4,2);
    Circle c1(0,0,10);
    Triangle t1(0,0,3,4,6,0);
    vector<Shape *> ss;
    ss.push_back(&r1);
    ss.push_back(&c1);
    ss.push_back(&t1);
    DOUBLES_EQUAL(88,sumOfPerimeter(ss),epsilon);
}




//test maxAera function
TEST(eighth,maxAreaOfShapes)
{
    Rectangle r1(0,0,4,2);
    Circle c1(0,0,10);
    Triangle t1(0,0,3,4,6,0);
    vector<Shape *> ss;
    ss.push_back(&r1);
    ss.push_back(&c1);
    ss.push_back(&t1);
    DOUBLES_EQUAL(300,maxArea(ss),epsilon);
}
//test sortByDecreasingPerimeter function
TEST(ninth,sortShapes)
{
    Rectangle r1(0,0,4,2);
    Circle c1(0,0,10);
    Triangle t1(0,0,3,4,6,0);
    vector<Shape *> ss;
    ss.push_back(&r1);
    ss.push_back(&c1);
    ss.push_back(&t1);
    sortByDecreasingPerimeter(ss);
    //by decreasing sort c1(60)>t1(16)>r1(12)
    DOUBLES_EQUAL(60,ss[0]->perimeter(),epsilon);
    DOUBLES_EQUAL(16,ss[1]->perimeter(),epsilon);
    DOUBLES_EQUAL(12,ss[2]->perimeter(),epsilon);
}
TEST(comboShape,combo)
{
    Rectangle rTall(0,0,4,2);
    Circle cSmall(0,0,10);
    vector<Shape *>ss={&rTall,&cSmall};
    comboShape shapes(ss);
    DOUBLES_EQUAL(308,shapes.area(),epsilon);
    DOUBLES_EQUAL(72,shapes.perimeter(),epsilon);
}
TEST(comboShapeAdd,combo)
{
    Rectangle rTall(0,0,4,2);
    Circle cSmall(0,0,10);
    vector<Shape *>ss={&rTall};
    comboShape shapes(ss);
    shapes.add(&cSmall);
    DOUBLES_EQUAL(308,shapes.area(),epsilon);
    DOUBLES_EQUAL(72,shapes.perimeter(),epsilon);
}
TEST(multiComboShape,combo)
{
    Rectangle rTall(0,0,4,2);
    Circle cSmall(0,0,10);
    vector<Shape *>s1{&rTall,&cSmall};
    vector<Shape *>s2{&cSmall};
    comboShape shapes1(s1);
    comboShape shapes2(s2);
    shapes2.add(&shapes1);
    DOUBLES_EQUAL(608,shapes2.area(),epsilon);
    DOUBLES_EQUAL(132,shapes2.perimeter(),epsilon);
}
#endif // UTSHAPES_H_INCLUDED
