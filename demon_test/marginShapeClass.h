/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   marginShapeClass.h
 * Author: aqq
 *
 * Created on 2017年4月28日, 下午2:49
 */

#ifndef MARGINSHAPECLASS_H
#define MARGINSHAPECLASS_H
#include"man.h"
class marginShapeClass {
public:
    marginShapeClass();
    marginShapeClass(Mat &);
    void marginShapeType();
    void  outlineFrontierTest();
    void outlineFrontierContours();
    void outlineDetection();
    void  outlineMu();
    void cacBounding(Mat &);
    void cacBoundRectRandomDirection(Mat &);
    
    virtual ~marginShapeClass();
private:
    enum marginShapeEnum
    {
    OUTLINEDETECTION,
    OUTLINEFRONTIER,
    OUTLINEMU,
    };
    Mat changeImage;   
    Mat beforeImage;

};

#endif /* MARGINSHAPECLASS_H */

