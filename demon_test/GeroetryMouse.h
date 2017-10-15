/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GeroetryMouse.h
 * Author: aqq
 *
 * Created on 2017年4月25日, 下午2:13
 */

#ifndef GEROETRYMOUSE_H
#define GEROETRYMOUSE_H
#include"man.h"
class GeroetryMouse {
public:
    GeroetryMouse();
    GeroetryMouse(Mat &);
    virtual ~GeroetryMouse();
    Point getStartPoint();
    Point getEndPoint();
    void LineGetStartEndPoint();
    void CornerGetPoint();
    vector<Vec4f>  getLinesCorner();
private:
    Point GerStartPoint;
    Point GerEndPoint;
    vector<Vec4f> linescorner;   
    Mat image;
};

#endif /* GEROETRYMOUSE_H */

