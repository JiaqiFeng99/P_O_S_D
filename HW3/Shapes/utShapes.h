#ifndef UTSHAPES_H_INCLUDED
#define UTSHAPES_H_INCLUDED

#include "..\cppunitlite\TestHarness.h"
#include "Shapes.h"
#include "ShapeMedia.h"
//#include "MediaVisitor.h"
#include <vector>
#include <cmath>

const double epsilon = 0.0001;
// added this line
TEST (first, Rectangle)
{
    Rectangle rect(0,0,4,2);
    DOUBLES_EQUAL(8,rect.area(),epsilon);
}

TEST(sencond,Circle)
{
    Circle circ(0,0,10);
    DOUBLES_EQUAL(300,circ.area(),epsilon);
}

TEST (fifth, sumOfArea)
{
    Rectangle r1(0,0,4,2);
    Circle c1(0,0,10);
    std::vector<Shape *> ss;
    ss.push_back(&r1);
    ss.push_back(&c1);
    DOUBLES_EQUAL(308,sumOfArea(ss),epsilon);
}

TEST ( seven, media ) {
    Rectangle r1(0,0,4,2);
    ShapeMedia sR1( &r1 ) ;
    DOUBLES_EQUAL(8,sR1.area(),epsilon);
}

TEST ( eight, comboMedia ) {
    Rectangle r1(0,0,4,2);
    Rectangle r2(0,0,4,3);
    ShapeMedia sR1( &r1 ) ;
    ShapeMedia sR2( &r2 ) ;
    std::vector<Media *> ss{&sR1,&sR2};
    ComboMedia cm(ss);
    DOUBLES_EQUAL(20,cm.area(),epsilon) ;
}



//------------------------HW3--------------------------
TEST(regularHexagon,ComboMedia)
{
    Rectangle r1(0,0,2*sqrt(3),2);
    Triangle t1(0,0,-1,sqrt(3),0,2*sqrt(3));
    Triangle t2(2,0,3,sqrt(3),2,2*sqrt(3));

    ShapeMedia sR1(&r1);
    ShapeMedia sT1(&t1);
    ShapeMedia sT2(&t2);
    vector<Media *>ss{&sR1};
    ComboMedia cm(ss);
    cm.add(&sT1);
    cm.add(&sT2);

    DOUBLES_EQUAL(10.3923,cm.area(),epsilon);
    DOUBLES_EQUAL(25.8564,cm.perimeter(),epsilon);
}
TEST(visit,MediaVisitor)
{
    Rectangle r1(0,0,4,2);//area:8 perimeter:12
    Triangle t1(0,0,0,3,4,0);//area:6 perimeter:12
    Triangle t2(0,0,0,3,4,0);//area:6 perimeter:12

    ShapeMedia sR1(&r1);
    ShapeMedia sT1(&t1);
    ShapeMedia sT2(&t2);
    vector<Media *>ss1{&sR1,&sT1};
    vector<Media *>ss2{&sT2};
    ComboMedia cm1(ss1);
    ComboMedia cm2(ss2);
    cm1.add(&cm2);
    AreaVisitor av;
    PerimeterVisitor pv;
    cm1.accept(&av);
    cm1.accept(&pv);

    DOUBLES_EQUAL(20,av.getArea(),epsilon);
    DOUBLES_EQUAL(36,pv.getPerimeter(),epsilon);
}
#endif // UTSHAPES_H_INCLUDED
