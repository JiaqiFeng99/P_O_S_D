#ifndef UTSHAPES_H_INCLUDED
#define UTSHAPES_H_INCLUDED

#include "..\cppunitlite\TestHarness.h"
#include "Shapes.h"
#include "ShapeMedia.h"
#include "Analyzer.h"
#include "Command.h"
#include "CommandManager.h"
#include <vector>
using namespace std;
const double epsilon = 0.000001;
// added this line
//TEST (first, Rectangle)
//{
//    Rectangle rect(0,0,4,2);
//    DOUBLES_EQUAL(8,rect.area(),epsilon);
//}
//
//TEST(sencond,Circle)
//{
//    Circle circ(0,0,10);
//    DOUBLES_EQUAL(300,circ.area(),epsilon);
//}
//
//TEST (fifth, sumOfArea)
//{
//    Rectangle r1(0,0,4,2);
//    Circle c1(0,0,10);
//    std::vector<Shape *> ss;
//    ss.push_back(&r1);
//    ss.push_back(&c1);
//    DOUBLES_EQUAL(308,sumOfArea(ss),epsilon);
//}
//
//
//
//
//
//
//TEST ( seven, media ) {
//    Rectangle r1(0,0,4,2);
//    ShapeMedia sR1( &r1 ) ;
//    DOUBLES_EQUAL(8,sR1.area(),epsilon);
//}
//
//TEST ( eight, comboMedia ) {
//    Rectangle r1(0,0,4,2);
//    Rectangle r2(0,0,4,3);
//    ShapeMedia sR1( new  Rectangle (0,0,4,2)) ;
//    ShapeMedia sR2( &r2 ) ;
//    std::vector<Media *> ss{&sR1,&sR2};
//    ComboMedia cm(ss);
//    DOUBLES_EQUAL(20,cm.area(),epsilon) ;
//}
//
//#include <iostream>
//
////TEST (ComboMedia, DescriptionVisitor) {
////    Rectangle r1(0,0,4,2);
////    Circle r2(0,0,10);
////    ShapeMedia sR1( &r1 ) ;
////    ShapeMedia sR2( &r2 ) ;
////    std::vector<Media *> ss{&sR1,&sR2};
////    ComboMedia cm(ss);
////    DescriptionVisitor dv;
////    cm.accept(&dv);
////    CHECK(std::string("x(r(0 0 4 2) c(0 0 10) )") == dv.getDescription());
////}
//
//TEST (ShapeMedia, DescriptionVisitor) {
//    Rectangle r1(0,0,4,2);
//    ShapeMedia sR1( &r1 ) ;
//    DescriptionVisitor dv;
//    sR1.accept(&dv);
//    CHECK(std::string("r(0 0 4 2) ") == dv.getDescription());
//}
//
//TEST (IllegalAdd, ShapeMedia) {
//    Rectangle r1(0,0,4,2);
//    Circle r2(0,0,10);
//    ShapeMedia sR1( &r1 ) ;
//    ShapeMedia sR2( &r2 ) ;
//    try {
//        sR1.add(&sR2);
//        FAIL("should not be here");
//    } catch(std::string s) {
//        CHECK(std::string("Illegal: add on media") == s);
//    }
//}
//
////TEST (ComboMedia2, MediaBuilder) {
////    MediaBuilder mb;
////
////    mb.buildComboMedia();
////    Rectangle r(0,0,4,2);
////    mb.buildShapeMedia(&r);
////    Circle c(0,0,10);
////    mb.buildShapeMedia(&c);
////
////    ComboMedia * combo = mb.getComboMedia();
////    DescriptionVisitor dv;
////    combo->accept(&dv);
////    CHECK(std::string("x(r(0 0 4 2) c(0 0 10) )") == dv.getDescription());
////
////}
//
////TEST (ComboMedia3, MediaBuilder) {
////    MediaBuilder mb;
////
////    try{
////        Rectangle r(0,0,4,2);
////        mb.buildShapeMedia(&r);
////        FAIL("should not be here");
////    }catch(std::string s){
////        CHECK(std::string("null point ex")==s);
////    }
////}
//
////TEST (ComboMedia4, MediaBuilder) {
////    MediaBuilder mb;
////    mb.buildComboMedia();
////
////    Rectangle r(0,0,4,2);
////    mb.buildShapeMedia(&r);
////    Circle c(0,0,10);
////    mb.buildShapeMedia(&c);
////
////    MediaBuilder mb2;
////    mb2.buildComboMedia();
////
////    Rectangle r2(0,0,2,1);
////    mb2.buildShapeMedia(&r2);
////    Circle c2(0,0,5);
////    mb2.buildShapeMedia(&c2);
////
////    ComboMedia *cm = mb2.getComboMedia();
////    mb.buildAddComboMedia(cm);
////
////    DescriptionVisitor dv;
////    mb.getComboMedia()->accept(&dv);
////    // std::cout << dv.getDescription() << std::endl;
////    CHECK(std::string("x(r(0 0 4 2) c(0 0 10) x(r(0 0 2 1) c(0 0 5) ))") == dv.getDescription());
////
////}
////
////#include<stack>
////TEST (ComboMedia5, MediaBuilder) {
////    std::stack<MediaBuilder *> mbs;
////    mbs.push(new MediaBuilder());
////    mbs.top()->buildComboMedia();
////
////    Rectangle r(0,0,4,2);
////    mbs.top()->buildShapeMedia(&r);
////    Circle c(0,0,10);
////    mbs.top()->buildShapeMedia(&c);
////
////    mbs.push(new MediaBuilder());
////    mbs.top()->buildComboMedia();
////
////    Rectangle r2(0,0,2,1);
////    mbs.top()->buildShapeMedia(&r2);
////    Circle c2(0,0,5);
////    mbs.top()->buildShapeMedia(&c2);
////    ComboMedia *cm = mbs.top()->getComboMedia();
////    mbs.pop();
////    mbs.top()->buildAddComboMedia(cm);
////
////    DescriptionVisitor dv;
////    mbs.top()->getComboMedia()->accept(&dv);
////    // std::cout << dv.getDescription() << std::endl;
////
////    CHECK(std::string("x(r(0 0 4 2) c(0 0 10) x(r(0 0 2 1) c(0 0 5) ))") == dv.getDescription());
////
////}
////TEST (MediaDirector,MediaBuilder){
////    MediaDirector md(std::string("x(r(0 0 4 2) c(0 0 10) x(r(0 0 2 1) c(0 0 5) ))"));
////    md.build();
////    Media* m = md.getResult();
////    DescriptionVisitor dv;
////    m->accept(&dv);
////    CHECK(std::string("x(r(0 0 4 2) c(0 0 10) x(r(0 0 2 1) c(0 0 5) ))") == dv.getDescription());
////}
////TEST(problem6_1,Analyzer)
////{
////    Analyzer ana;
////    DescriptionVisitor dv;
////    ana.concrete(":- def rTall = Rectangle(0,0,4,2)");
////    ana.getMediaByName("rTall")->accept(&dv);
////    CHECK(string("r(0 0 4 2) ")==dv.getDescription());
////    CHECK(string("rTall")==ana.getMediaByName("rTall")->getName());
////
////    DescriptionVisitor dv2;
////    ana.concrete(":- def cSmall = Circle(2,1,1)");
////    ana.getMediaByName("cSmall")->accept(&dv2);
////    CHECK(string("c(2 1 1) ")==dv2.getDescription());
////    CHECK(string("cSmall")==ana.getMediaByName("cSmall")->getName());
////    try{
////    DescriptionVisitor dv3;
////    ana.concrete(":- def comboExclamation = combo{rTall,cSmall}");
////    ana.getMediaByName("comboExclamation")->accept(&dv3);
////    CHECK(string("combo(r(0 0 4 2) c(2 1 1) )")==dv3.getDescription());
////    CHECK(string("comboExclamation")==ana.getMediaByName("comboExclamation")->getName());
////    }catch(string s){
////        cout << s;
////    }
////}
//
////---------------------------------------------------------------HW6-------------------------------------------------------------------------
//
//TEST(hw6,Analyzer)
//{
////    Analyzer ana;
////    try{
////    ana.print();
////    }catch(string s){
////        cout << s <<endl;
////    }
//}

//---------------------------------------------------------------HW7-------------------------------------------------------------------------

// Problem 2-1
// Use CommandManager to test ExecuteCMD
TEST(hw7_problem2_ExecuteCMD,CommandManager)
{
    //define shapeMedia
    Media* media=new ShapeMedia(new Circle(2,1,1));

    //push shapeMedia into vector
    vector<Media *>mv;
    mv.push_back(media);

    //test ExecuteCMD
    Command *command=new DefineCommand(&mv,media);
    CommandManager cm;
    cm.ExecuteCMD(command);

    DescriptionVisitor dv;
    mv[0]->accept(&dv);
    CHECK(string("c(2 1 1) ")==dv.getDescription());
}

// Problem 2-2
// Use CommandManager to test UndoCMD
TEST(hw7_problem2_UndoCMD,CommandManager)
{
    //define shapeMedia
    Media* media=new ShapeMedia(new Circle(2,1,1));

    //push shapeMedia into vector
    vector<Media *>mv;
    mv.push_back(media);

    //testUndoCMD
    Command *command=new DefineCommand(&mv,media);
    CommandManager cm;
    cm.ExecuteCMD(command);
    cm.UndoCMD();

    //after undo the vector's size should be 0
    DOUBLES_EQUAL(0,mv.size(),epsilon);
}

// Problem 2-3
// Use CommandManager to test RedoCMD
TEST(hw7_problem2_RedoCMD,CommandManager)
{
    //define shapeMedia
    Media* media=new ShapeMedia(new Circle(2,1,1));

     //push shapeMedia into vector
    vector<Media *>mv;
    mv.push_back(media);

    //testUndoCMD
    Command *command=new DefineCommand(&mv,media);
    CommandManager cm;
    cm.ExecuteCMD(command);
    cm.UndoCMD();
    cm.RedoCMD();

    DescriptionVisitor dv;
    mv[0]->accept(&dv);
    CHECK(string("c(2 1 1) ")==dv.getDescription());
}

// Problem 3
// Implement undo/redo adding Media into comboMedia.
TEST(hw7_problem3,CommandManager)
{
    //define comboMedia
    Media* media1=new ShapeMedia(new Circle(2,1,1));
    vector<Media *>v;
    v.push_back(media1);
    Media* combo=new ComboMedia(v);

    //push comboMedia into vector
    vector<Media *>mv;
    mv.push_back(combo);

    //test before add
    DescriptionVisitor dv;
    mv[0]->accept(&dv);
    CHECK(string("combo(c(2 1 1) )")==dv.getDescription());

    //add shapeMedia into comboMedia
    Media* media2=new ShapeMedia(new Rectangle(1,10,2,8));
    combo->add(media2);
    Command *command=new AddCommand(combo,media2);

    //test after add
    DescriptionVisitor dv1;
    mv[0]->accept(&dv1);
    CHECK(string("combo(c(2 1 1) r(1 10 2 8) )")==dv1.getDescription());

    //test undo method of AddCommand
    command->Undo();
    DescriptionVisitor dv2;
    mv[0]->accept(&dv2);
    CHECK(string("combo(c(2 1 1) )")==dv2.getDescription());

    //test redo method of AddCommand
    command->Execute();
    DescriptionVisitor dv3;
    mv[0]->accept(&dv3);
    CHECK(string("combo(c(2 1 1) r(1 10 2 8) )")==dv3.getDescription());

}

// Problem 4-1
// Implement undo/redo definition shapeMedia.
TEST(hw7_problem4_1,CommandManager)
{
    //define shapeMedia
    Media* media=new ShapeMedia(new Circle(2,1,1));

     //push shapeMedia into vector
    vector<Media *>mv;
    mv.push_back(media);

    //test define
    Command *command=new DefineCommand(&mv,media);
    DescriptionVisitor dv;
    mv[0]->accept(&dv);
    CHECK(string("c(2 1 1) ")==dv.getDescription());

    //test undo method of DefineCommand, after undo the vector's size should be 0
    command->Undo();
    DOUBLES_EQUAL(0,mv.size(),epsilon);

    //test redo method of DefineCommand
    command->Execute();
    DescriptionVisitor dv1;
    mv[0]->accept(&dv1);
    CHECK(string("c(2 1 1) ")==dv1.getDescription());
}

// Problem 4-2
// Implement undo/redo definition comboMedia.
TEST(hw7_problem4_2,CommandManager)
{
    //define comboMedia
    Media* media1=new ShapeMedia(new Circle(2,1,1));
    Media* media2=new ShapeMedia(new Rectangle(1,10,2,8));
    vector<Media *>v;
    v.push_back(media1);
    v.push_back(media2);
    Media* combo=new ComboMedia(v);

    //push comboMedia into vector
    vector<Media *>mv;
    mv.push_back(combo);

    //test define
    Command *command=new DefineCommand(&mv,combo);
    DescriptionVisitor dv;
    mv[0]->accept(&dv);
    CHECK(string("combo(c(2 1 1) r(1 10 2 8) )")==dv.getDescription());
    DOUBLES_EQUAL(1,mv.size(),epsilon);

    //test undo method of DefineCommand, after undo the vector's size should be 0
    command->Undo();
    DOUBLES_EQUAL(0,mv.size(),epsilon);

    //test redo method of DefineCommand
    command->Execute();
    DescriptionVisitor dv1;
    mv[0]->accept(&dv1);
    CHECK(string("combo(c(2 1 1) r(1 10 2 8) )")==dv1.getDescription());
    DOUBLES_EQUAL(1,mv.size(),epsilon);
}

// Problem 5-1
// Implement undo/redo delete Media from comboMedia
TEST(hw7_problem5_1,CommandManager)
{
    ///define comboMedia
    Media* media1=new ShapeMedia(new Circle(2,1,1));
    Media* media2=new ShapeMedia(new Rectangle(1,10,2,8));
    vector<Media *>v;
    v.push_back(media1);
    v.push_back(media2);
    Media* combo=new ComboMedia(v);

    //push comboMedia into vector
    vector<Media *>mv;
    mv.push_back(combo);

    //test before delete
    DescriptionVisitor dv;
    mv[0]->accept(&dv);
    CHECK(string("combo(c(2 1 1) r(1 10 2 8) )")==dv.getDescription());

    //delete c from combo
    Command *command=new DeleteFromComboCommand(combo,media1,0);
    combo->removeMedia(media1);

    //test after delete
    DescriptionVisitor dv1;
    mv[0]->accept(&dv1);
    CHECK(string("combo(r(1 10 2 8) )")==dv1.getDescription());

    //test undo method of DeleteFromComboCommand
    command->Undo();
    DescriptionVisitor dv2;
    mv[0]->accept(&dv2);
    CHECK(string("combo(c(2 1 1) r(1 10 2 8) )")==dv2.getDescription());

    //test redo method of DeleteFromComboCommand
    command->Execute();
    DescriptionVisitor dv3;
    mv[0]->accept(&dv3);
    CHECK(string("combo(r(1 10 2 8) )")==dv3.getDescription());

}
TEST(hw7_problem5_2,CommandManager)
{
    ///define Media
    Media* media1=new ShapeMedia(new Circle(2,1,1));
    Media* media2=new ShapeMedia(new Rectangle(1,10,2,8));

    //push Media into vector
    vector<Media *>mv;
    mv.push_back(media1);
    mv.push_back(media2);

    //test before delete, mv[0] should be c, size should be 2
    DescriptionVisitor dv;
    mv[0]->accept(&dv);
    CHECK(string("c(2 1 1) ")==dv.getDescription());
    DOUBLES_EQUAL(2,mv.size(),epsilon);

    //delete Media
    Command *command=new DeleteCommand(&mv,media1,0);
    mv.erase(mv.begin()+0);

    //test after delete, so m[0] will be r, size should be 1
    DescriptionVisitor dv1;
    mv[0]->accept(&dv1);
    CHECK(string("r(1 10 2 8) ")==dv1.getDescription());
    DOUBLES_EQUAL(1,mv.size(),epsilon);

    //test undo method of DeleteFromComboCommand, mv[0] should be c, size should be 2
    command->Undo();
    DescriptionVisitor dv2;
    mv[0]->accept(&dv2);
    CHECK(string("c(2 1 1) ")==dv2.getDescription());
    DOUBLES_EQUAL(2,mv.size(),epsilon);

    //test redo method of DeleteFromComboCommand, mv[0] should be r, size should be 1
    command->Execute();
    DescriptionVisitor dv3;
    mv[0]->accept(&dv3);
    CHECK(string("r(1 10 2 8) ")==dv3.getDescription());
    DOUBLES_EQUAL(1,mv.size(),epsilon);

}
#endif // UTSHAPES_H_INCLUDED
