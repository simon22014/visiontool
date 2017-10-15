/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   marginGeometryClass.h
 * Author: aqq
 *
 * Created on 2017年4月27日, 下午4:47
 */

#ifndef MARGINGEOMETRYCLASS_H
#define MARGINGEOMETRYCLASS_H
#include"man.h"
#include"imageFindLineClass.h"
#include"GeroetryMouse.h"
class marginGeometryClass {
public:
    marginGeometryClass();
    marginGeometryClass(Mat &);
    void  marginGeomrtryType();
    void  marginHoffGeomrtry();
    void  LSDFastGeomrtry();
    void circleGeomrtry();
    virtual ~marginGeometryClass();
private:
    Mat changeImage;   
    Mat beforeImage;
     vector <Vec4i> lines;
     vector<Vec3f> Findcircles;
    imageFindLineClass* findLine;
    GeroetryMouse *gerMouse;
    enum marginGeometry{
        HOFFGLEOMRTRY,
        LSDFASTGEOMRTRY,
        CIRCLEGEOMRTRY,
    
    
    };
    

};

#endif /* MARGINGEOMETRYCLASS_H */

