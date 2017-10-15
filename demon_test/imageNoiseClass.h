/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   imageNoiseClass.h
 * Author: aqq
 *
 * Created on 2017年4月27日, 下午3:02
 */

#ifndef IMAGENOISECLASS_H
#define IMAGENOISECLASS_H
#include"man.h"
#include"theClass.h"
class imageNoiseClass {
public:
    imageNoiseClass();
    imageNoiseClass(Mat &);
    virtual ~imageNoiseClass();
    void addSaltNoise(int,int);
    void addGaussianNoise();
    double generateGuassianNoise(double,double );
private:
    Mat beforeImage;
    Mat changeImage;
    dimDealWitch* dim;
    


};

#endif /* IMAGENOISECLASS_H */

