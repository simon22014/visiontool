/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   histImageOperate.h
 * Author: aqq
 *
 * Created on 2017年4月24日, 下午4:01
 */

#ifndef HISTIMAGEOPERATE_H
#define HISTIMAGEOPERATE_H
#include "histImage.h"
class histImageOperate {
public:
    histImageOperate();
    histImageOperate(Mat &);
    void histImageOperateType();
    void rgbHistEqual();
    void   grayHistEqual();
    void histVaryFind();
    void histVaryAddup();
    void histRverseProjection();
    
    virtual ~histImageOperate();
private:
     Mat changeImage;   
     Mat beforeImage;
     enum Hist_equal
     {
     GRAYHISTEQUAL,
     RGBHISTEQUAL,
     HISTVARYFIND,
     HISTVARYADDUP,
     HISTRVERSEPROJECTION,
     };
};

#endif /* HISTIMAGEOPERATE_H */

