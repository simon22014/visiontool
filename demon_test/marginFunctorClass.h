/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   marginFunctorClass.h
 * Author: aqq
 *
 * Created on 2017年4月24日, 上午8:46
 */
#include"marginFunctor.h"

#ifndef MARGINFUNCTORCLASS_H
#define MARGINFUNCTORCLASS_H

class marginFunctorClass {
public:
    marginFunctorClass();
    marginFunctorClass(Mat &);
    void marginChoice();
     void marginSobelFun();
     void marginLaplaceFun();
     void marginRobertsFun();
     void marginPrewittFun();
     void marginCanny();
     void marginMarr_Hildreth();
     Mat & returnImage();
    virtual ~marginFunctorClass();
private:
    Mat changeImage;   
    Mat beforeImage;
    Mat changeImageSobel;
    enum MarginType {
           MARGINSOBEL,
           MARGINLAPLACE,
           MARGINROBERTS,
           MARGINPREWITT,
           MARGINCANNY,
           MARRHILDRETH,
    };

};

#endif /* MARGINFUNCTORCLASS_H */

