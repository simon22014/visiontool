/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   imageSamplingClass.h
 * Author: aqq
 *
 * Created on 2017年4月27日, 下午1:15
 */

#ifndef IMAGESAMPLINGCLASS_H
#define IMAGESAMPLINGCLASS_H
#include"man.h"
class imageSamplingClass {
public:
    imageSamplingClass();
    imageSamplingClass(Mat &);
    virtual ~imageSamplingClass();
    void latelyNextInsertVaule(int,int);
    void bothLinearInsertVaule(int,int);
private:
    Mat beforeImage;
    Mat changeImage;

};

#endif /* IMAGESAMPLINGCLASS_H */

