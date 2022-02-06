#ifndef UT_H_INCLUDED
#define UT_H_INCLUDED


#include "cppunitlite\TestHarness.h"
#include <vector>
#include <iostream>
#include "Shapes.h"
#include "Point.h"
#include "Media.h"
#include "Visitor.h"
#include "Builder.h"
#include "Text.h"
#include "Document.h"
#include "Director.h"

const double epsilon = 0.000001;

// added this line
TEST (first, Rectangle)
{
    Rectangle rect(Point(0,0),4,2);
    DOUBLES_EQUAL(8,rect.area(),epsilon);
}
TEST(sencond,Circle)
{
    Circle circ(Point(0,0),10);
    DOUBLES_EQUAL(300,circ.area(),epsilon);
}
TEST(third,Circle)
{
    Triangle tri(Point(0,0),Point(0,3),Point(4,3));
    DOUBLES_EQUAL(6,tri.area(),epsilon);
}

TEST ( seven, media ) {
    Rectangle r1(Point(0,0),4,2);
    ShapeMedia sR1(&r1) ;
    DOUBLES_EQUAL(8,sR1.area(),epsilon);
}
TEST ( eight, comboMedia ) {
    Rectangle r1(Point(0,0),4,2);
    Rectangle r2(Point(0,0),4,3);
    ShapeMedia sR1(&r1) ;
    ShapeMedia sR2(&r2) ;
    std::vector<Media *> ss{&sR1,&sR2};
    ComboMedia cm(ss);
    DOUBLES_EQUAL(20,cm.area(),epsilon) ;
}

TEST (ComboMedia, DescriptionVisitor) {
    Rectangle r1(Point(0,0),4,2);
    Circle r2(Point(0,0),10);
    ShapeMedia sR1(&r1) ;
    ShapeMedia sR2(&r2) ;
    std::vector<Media *> ss{&sR1,&sR2};
    ComboMedia cm(ss);
    DescriptionVisitor dv;
    cm.accept(&dv);
    CHECK(std::string("combo(r(0 0 4 2) c(0 0 10) )") == dv.getDescription());
}
TEST (ComboMedia, AreaVisitor) {
    Rectangle r1(Point(0,0),4,2);
    Circle r2(Point(0,0),10);
    ShapeMedia sR1(&r1) ;
    ShapeMedia sR2(&r2) ;
    std::vector<Media *> ss{&sR1,&sR2};
    ComboMedia cm(ss);
    AreaVisitor av;
    cm.accept(&av);
    DOUBLES_EQUAL(308, av.getArea(), epsilon);
}
TEST (ComboMedia, PerimeterVisitor){
    Rectangle r1(Point(0,0),4,2);
    Circle r2(Point(0,0),10);
    ShapeMedia sR1(&r1) ;
    ShapeMedia sR2(&r2) ;
    std::vector<Media *> ss{&sR1,&sR2};
    ComboMedia cm(ss);
    PerimeterVisitor pv;
    cm.accept(&pv);
    DOUBLES_EQUAL(72, pv.getPerimeter(), epsilon);
}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
TEST(HW4_1, ShapeMediaBuilder){
    Circle c(Point(0,0), 5);
    ShapeMediaBuilder smb;
    smb.buildShapeMedia(&c);
    DescriptionVisitor dv;
    smb.getMedia()->accept(&dv);
    CHECK(std::string("c(0 0 5) ") == dv.getDescription());
    DOUBLES_EQUAL(75, smb.getMedia()->area(), epsilon);
}
TEST(HW4_2, ShapeMediaBuilder){
    Rectangle r1(Point(10, 0), 15, 5);
    Rectangle r2(Point(0, 0), 25, 20);
    Circle c1(Point(12, 5), 2);
    Triangle t1(Point(0, 20), Point(16, 32), Point(25, 20));
    ComboMediaBuilder cmb1, cmb2, cmb3;
    cmb1.buildComboMedia();
    cmb2.buildComboMedia();
    cmb3.buildComboMedia();
    cmb1.buildShapeMedia(&r1);
    cmb1.buildShapeMedia(&c1);
    cmb2.getMedia()->add(cmb1.getMedia());
    cmb2.buildShapeMedia(&r2);
    cmb3.getMedia()->add(cmb2.getMedia());
    cmb3.buildShapeMedia(&t1);
    DescriptionVisitor dv;
    cmb3.getMedia()->accept(&dv);
    CHECK(std::string("combo(combo(combo(r(10 0 15 5) c(12 5 2) )r(0 0 25 20) )t(0 20 16 32 25 20) )") == dv.getDescription());
}
TEST(HW4_3, TextMedia){
    Rectangle r(Point(0,0), 10, 20);
    Text t(r, std::string("Hello world"));
    TextMedia tm(t);
    DescriptionVisitor dv;
    tm.accept(&dv);
    AreaVisitor av;
    tm.accept(&av);
    DOUBLES_EQUAL(200, av.getArea(), epsilon);
    CHECK(std::string("Hello world") == dv.getDescription());
}
TEST(HW4_4, RemoveShapeMedia){
    Rectangle r1(Point(10, 0), 15, 5);
    Rectangle r2(Point(0, 0), 25, 20);
    Circle c1(Point(12, 5), 2);
    Triangle t1(Point(0, 20), Point(16, 32), Point(25, 20));
    ComboMediaBuilder cmb1, cmb2, cmb3;
    cmb1.buildComboMedia();
    cmb2.buildComboMedia();
    cmb3.buildComboMedia();
    cmb1.buildShapeMedia(&r1);
    cmb1.buildShapeMedia(&c1);
    cmb2.getMedia()->add(cmb1.getMedia());
    cmb2.buildShapeMedia(&r2);
    cmb3.getMedia()->add(cmb2.getMedia());
    cmb3.buildShapeMedia(&t1);
    cmb3.getMedia()->removeMedia(new ShapeMedia(&r2));
    DescriptionVisitor dv;
    cmb3.getMedia()->accept(&dv);
    CHECK(std::string("combo(combo(combo(r(10 0 15 5) c(12 5 2) ))t(0 20 16 32 25 20) )") == dv.getDescription());
}

TEST(HW4_5, RemoveComboMedia){
    Rectangle r1(Point(10, 0), 15, 5);
    Rectangle r2(Point(0, 0), 25, 20);
    Circle c1(Point(12, 5), 2);
    Triangle t1(Point(0, 20), Point(16, 32), Point(25, 20));
    ComboMediaBuilder cmb1, cmb2, cmb3;
    cmb1.buildComboMedia();
    cmb2.buildComboMedia();
    cmb3.buildComboMedia();
    cmb1.buildShapeMedia(&r1);
    cmb1.buildShapeMedia(&c1);
    cmb2.getMedia()->add(cmb1.getMedia());
    cmb2.buildShapeMedia(&r2);
    cmb3.getMedia()->add(cmb2.getMedia());
    cmb3.buildShapeMedia(&t1);
    cmb3.getMedia()->removeMedia(cmb2.getMedia());
    DescriptionVisitor dv;
    cmb3.getMedia()->accept(&dv);
    CHECK(std::string("combo(t(0 20 16 32 25 20) )") == dv.getDescription());
}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
TEST(HW5_1, Load){
    MyDocument md;
    try{
    CHECK(std::string("combo(r(0 0 3 2) c(0 0 5) combo(r(0 0 5 4) c(0 0 10) )combo(r(0 1 8 7) c(0 1 10) ))") == md.openDocument("myShape.txt"));
    }catch(std::string s){
        std::cout << s << std::endl;
    }
}

TEST(HW5_2, MediaDirector){
    MyDocument md;
    MediaDirector mdr;
    mdr.concrete(md.openDocument("myShape.txt"));
    DescriptionVisitor dv;
    mdr.getMedia()->accept(&dv);
    CHECK(std::string("combo(r(0 0 3 2) c(0 0 5) combo(r(0 0 5 4) c(0 0 10) )combo(r(0 1 8 7) c(0 1 10) ))") == dv.getDescription());
}

TEST(HW5_N, MediaDirector){
    MyDocument md;
    MediaDirector mdr;
    mdr.concrete(md.openDocument("myShape1.txt"));
    DescriptionVisitor dv;
    mdr.getMedia()->accept(&dv);
    CHECK(std::string("r(10 0 5 15) ") == dv.getDescription());
}


#endif // UT_H_INCLUDED
