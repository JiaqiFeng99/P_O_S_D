#ifndef UTSHAPES_H_INCLUDED
#define UTSHAPES_H_INCLUDED

#include "..\cppunitlite\TestHarness.h"
#include "Shapes.h"
#include "ShapeMedia.h"
#include <vector>


const double epsilon = 0.000001;
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

#include <iostream>

TEST (ComboMedia, DescriptionVisitor) {
    Rectangle r1(0,0,4,2);
    Circle r2(0,0,10);
    ShapeMedia sR1( &r1 ) ;
    ShapeMedia sR2( &r2 ) ;
    std::vector<Media *> ss{&sR1,&sR2};
    ComboMedia cm(ss);
    DescriptionVisitor dv;
    cm.accept(&dv);
    CHECK(std::string("combo(r(0 0 4 2) c(0 0 10) )") == dv.getDescription());
}

TEST (ShapeMedia, DescriptionVisitor) {
    Rectangle r1(0,0,4,2);
    ShapeMedia sR1( &r1 ) ;
    DescriptionVisitor dv;
    sR1.accept(&dv);
    CHECK(std::string("r(0 0 4 2) ") == dv.getDescription());
}

TEST (IllegalAdd, ShapeMedia) {
    Rectangle r1(0,0,4,2);
    Circle r2(0,0,10);
    ShapeMedia sR1( &r1 ) ;
    ShapeMedia sR2( &r2 ) ;
    try {
        sR1.add(&sR2);
        FAIL("should not be here");
    } catch(std::string s) {
        CHECK(std::string("Illegal: add on media") == s);
    }
}
//----------------------------------------------------HW4----------------------------------------------
TEST(problem1,ShapeMediaBuilder)
{
    Circle c(0,0,5);
    ShapeMediaBuilder sb;
    sb.buildShapeMedia(&c);
    Media* media=sb.getMedia();
    DescriptionVisitor dv;
    media->accept(&dv);

    DOUBLES_EQUAL(75,media->area(),epsilon);
    CHECK(string("c(0 0 5) ")==dv.getDescription());
}
TEST(problem2,MediaBuilder)
{
    Rectangle r1(10,0,15,5);
    Rectangle r2(0,0,25,20);
    Circle c(12,5,2);
    Triangle t(0,20,16,32,25,20);

    ComboMediaBuilder cb1;
    ComboMediaBuilder cb2;
    ComboMediaBuilder cb3;

    cb1.buildComboMedia();
    cb2.buildComboMedia();
    cb3.buildComboMedia();

    cb3.buildShapeMedia(&r1);
    cb3.buildShapeMedia(&c);
    Media *cm3=cb3.getMedia();//combo(r(10 0 15 5) c(0 0 5))
    cb2.buildAddComboMedia(cm3);
    cb2.buildShapeMedia(&r2);
    Media *cm2=cb2.getMedia();//combo(r(0 0 25 20) combo(r(10 0 15 5) c(0 0 5)))
    cb1.buildAddComboMedia(cm2);
    cb1.buildShapeMedia(&t);
    Media *cm=cb1.getMedia();//combo(combo(combo(r(10 0 15 5) c(12 5 2) )r(0 0 25 20) )t(0 20 16 32 25 20))


    DescriptionVisitor dv;
    cm->accept(&dv);
    CHECK(std::string("combo(combo(combo(r(10 0 15 5) c(12 5 2) )r(0 0 25 20) )t(0 20 16 32 25 20) )") == dv.getDescription());
}
TEST(problem3,TextMedia)
{
    Rectangle boundingbox(0,0,2,4);
    string str("this is a rectangle");
    Text text(boundingbox,str);
    TextMedia tm(&text);


    DescriptionVisitor dv;
    tm.accept(&dv);
    DOUBLES_EQUAL(8,tm.area(),epsilon);
    CHECK(string("this is a rectangle")==dv.getDescription());
}
TEST(problem4,removeCombo)
{
    Rectangle r1(10,0,15,5);
    Rectangle r2(0,0,25,20);
    Circle c(12,5,2);
    Triangle t(0,20,16,32,25,20);

    ComboMediaBuilder cb1;
    ComboMediaBuilder cb2;
    ComboMediaBuilder cb3;

    cb1.buildComboMedia();
    cb2.buildComboMedia();
    cb3.buildComboMedia();

    cb3.buildShapeMedia(&r1);
    cb3.buildShapeMedia(&c);
    Media *cm3=cb3.getMedia();//combo(r(10 0 15 5) c(0 0 5))
    cb2.buildAddComboMedia(cm3);
    cb2.buildShapeMedia(&r2);
    Media *cm2=cb2.getMedia();//combo(r(0 0 25 20) combo(r(10 0 15 5) c(0 0 5)))
    cb1.buildAddComboMedia(cm2);
    cb1.buildShapeMedia(&t);
    Media *cm=cb1.getMedia();//combo(combo(combo(r(10 0 15 5) c(12 5 2) )r(0 0 25 20) )t(0 20 16 32 25 20))


    cm->removeMedia(new ShapeMedia(&r2));
    DescriptionVisitor dv;
    cm->accept(&dv);
    CHECK(std::string("combo(combo(combo(r(10 0 15 5) c(12 5 2) ))t(0 20 16 32 25 20) )") == dv.getDescription());
}
#endif // UTSHAPES_H_INCLUDED
