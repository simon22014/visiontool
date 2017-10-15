/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
// * File:   templateMatching.h
 * Author: aqq
 *
 * Created on 2017年4月13日, 下午3:06
 */

#ifndef TEMPLATEMATCHING_H
#define TEMPLATEMATCHING_H
#include "template.h"
#include "showAndWebStorageClass.h"
class templateMatching {
public:
    templateMatching();
    templateMatching(const templateMatching& orig);
    virtual ~templateMatching();
    void templateMatchingChoiceWay();
    void choiceMatching();
    void  printMatchingPoint();
private:
    enum enum_template_Matching{
        SQDIFF,
        SQDIFFNORMED,
        TMCCORR,
        TMCCORRNORMED,
        TMCOEFF,
        TMCOEFFNORMED,    
};
Mat  obj;
Mat  secne;
int g_nMatchMethod;
Point leftPoint;
Point rightPoint;
showAndWebStorageClass *webClass;
 shStorage*  getAndWebShare;

};

#endif /* TEMPLATEMATCHING_H */

