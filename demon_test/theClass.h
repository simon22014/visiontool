/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   theClass.h
 * Author: aqq
 *
 * Created on 2017年4月12日, 下午1:51
 */

#ifndef THECLASS_H
#define THECLASS_H
#include <opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/nonfree/features2d.hpp>
#include<opencv2/nonfree/nonfree.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/legacy/legacy.hpp>
#include <opencv2/core/core.hpp>
#include <cstdio>
#include <iostream>
#include <pthread.h>
#include <signal.h>
#include<unistd.h>
#include <semaphore.h>
#include <cstdlib>
#include "man.h"
#include "pthreadLock.h"
using namespace std;
using namespace cv;

class theClass {
public:
    theClass();
    theClass(const theClass& orig);
    virtual ~theClass();
private:
    

};
/*****************************************************************************/
 /********************lest the image change the ray****************************/
 /****************************************************************************/
class changeRay {
public:
    changeRay();
    changeRay(bool,cv::Mat &);
    virtual ~changeRay();
    void printNum();
    Mat& getImageRag();
private:
    bool isOrNot ;
    Mat imageRay;
   
};
/*****************************************************************************/
/**********************dim deal with the image********************************/
/*****************************************************************************/
class dimDealWitch {
public:
    dimDealWitch();
    dimDealWitch(cv::Mat &image );
    Mat & returnImage();
    void dimDealWithType();
    virtual ~dimDealWitch();
private:
   enum enum_Dim{
	dim_Blue,
	dim_GaussianBlur,  
	dim_MedianBlur, 
	dim_BilateralFilter,  
	dim_BoxFilter, 
        dim_Null,
                };
   int Dim;    
   Mat image;
};
/*****************************************************************************/
/*******************feaPointArithmetic SIFT,SUIF,ORB an so********************/
/*****************************************************************************/
class feaPointAri {
public:
    feaPointAri();
    feaPointAri(Mat & image);
    void showFeaPoint();  //share the Point
    virtual ~feaPointAri();
   void templateMatchingChoiceWay(); //choice the the template and test image 
    void showTheMatchingWay();    //choice the matching way 
     Mat getTheMat();  //get the Mat 
     void showFeaPointORB();  //using the ORB arithmetic
     void showFeaPointSIFT(); //using the SIFT arithmetic 
     void  showFeaPointSUFT();  //using the SUFT arithmetic
     void compositeSiftSuftOrb();
     void printNum();    //printf the Pointx and pointy  
     Point2f printCenterPoint();
private:
   enum enum_feaPoint{
	feaPointAri_SIFT,
	feaPointAri_SUFT, 
	feaPointAri_ORB, 
        COMPOSITESIFTSUFTORB,
                };
                
   pthreadLock * pLock;    
    Mat obj_show_point;
    Mat  obj;
    Mat  secne;  
    Point2f  point1;
    Point2f  point2;
    Point2f  point3;
    Point2f  point4; 
    Point2f pointCenter;
};



#endif /* THECLASS_H */

