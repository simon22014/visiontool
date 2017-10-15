/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   cornerDetectionClass.h
 * Author: aqq
 *
 * Created on 2017年5月4日, 上午8:51
 */

#ifndef CORNERDETECTIONCLASS_H
#define CORNERDETECTIONCLASS_H
#include"cornerDetection.h"
class cornerDetectionClass {
public:
    cornerDetectionClass();
    cornerDetectionClass(Mat &);
    void cornerDetectionType();
    void moravecCorner();      
    void harrisCorner();
    void  Shi_TomasiCorner();
    virtual ~cornerDetectionClass();
private:
    enum corner
    {
    MORAVECCORNER,
    HARRISCORNER,
    SHI_TOMASICORNER,
    };
    Mat beforeImage;
    Mat changeImage;
    

};

#endif /* CORNERDETECTIONCLASS_H */

