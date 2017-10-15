/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   imageFindCornerClass.h
 * Author: aqq
 *
 * Created on 2017年4月26日, 上午8:30
 */

#ifndef IMAGEFINDCORNERCLASS_H
#define IMAGEFINDCORNERCLASS_H
#include"man.h"
#include"imageFindLineClass.h"
class imageFindCornerClass {
public:
    imageFindCornerClass();
    imageFindCornerClass(vector<Vec4f> ,Mat &);
    void FindLine();
    void printTwoLine();
    void printCrossLine(Point,Mat &);
    void showCornerAngle();
    void showIncludeAngle();
     void getTwoLineCorner(double,double,double,double);
     void showIncludeAngle(double,double,double,double);
    virtual ~imageFindCornerClass( );
private:
     vector<Vec4f> linescorner;
     vector<Vec4f> linesFindLine;
     Point CornerPoint;
     float Angle;
     Mat beforeImage;
     Mat craveImage;
      imageFindLineClass* findLine;
     //  Point tempPoint;

};

#endif /* IMAGEFINDRECTANGLECLASS_H */

