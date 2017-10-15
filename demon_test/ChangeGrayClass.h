/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ChangeGrayClass.h
 * Author: aqq
 *
 * Created on 2017年5月2日, 下午3:24
 */

#ifndef CHANGEGRAYCLASS_H
#define CHANGEGRAYCLASS_H
#include"man.h"
class ChangeGrayClass {
public:
    ChangeGrayClass();
    ChangeGrayClass(Mat &);
    void ChGrayClassType();
    void   gammaHist();
    void   linearChange();
    void   logChange();
    Mat  logTransForm3(Mat &,float ); 
    virtual ~ChangeGrayClass();
private:
    enum GrayChange
    {
        GAMMAHIST,
        LINEARCHANGE, 
        LOGCHANGE,
    };
    Mat beforeImage;
    Mat changeImage;

};

#endif /* CHANGEGRAYCLASS_H */

