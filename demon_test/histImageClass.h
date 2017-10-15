/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   histImageClass.h
 * Author: aqq
 *
 * Created on 2017年4月24日, 下午1:39
 */

#ifndef HISTIMAGECLASS_H
#define HISTIMAGECLASS_H
#include"histImage.h"
class histImageClass {
public:
    histImageClass();
    histImageClass(Mat &);
    void histImageType();
    void imageGrayHist();
    void  image_H_S_Hist();
    void imageBGRHist();
    void user_DefinedHist();
    virtual ~histImageClass();
private:
     Mat changeImage;   
     Mat beforeImage;
     
     enum hist_type
     {
     GRAYHIST,
     H_S_HIST,
     BGRHIST,
     USERDEFINEDHIST,
     GAMMAHIST,
     };

};

#endif /* HISTIMAGECLASS_H */

