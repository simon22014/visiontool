/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   imagedealwithclass.h
 * Author: aqq
 *
 * Created on 2017年4月14日, 下午2:41
 */

#ifndef IMAGEDEALWITHCLASS_H
#define IMAGEDEALWITHCLASS_H
#include"imagedealwith.h"
class locationChangeClass {
public:
    locationChangeClass();
    locationChangeClass(Mat & image_clone);
    void locationChangeChoice();
    virtual ~locationChangeClass();
    void  offsetImage();
    void  scaleImage();
    void printPointNum();
    void printImageWidthHigth();
    void  areaAverage(Point_<int>leftPoint,Point_<int>rightPoint,Vec3b&);
    Mat getTheChangeMat();
private:
        enum enum_imagedealwith{
        IMAGE_OFFSET, //offset   0
        IMAGE_SCALE,  //scale 1   
                                                    };
    Mat changeMat;
    Mat formerMat;
    Point leftPoint;
    Point rightPoint;
    float Width;   //location the widht
    float Higth;   //location the hight ;

};
/***************************************************************************************/
/************************the RGB change the other color conversion****************************/
/***************************************************************************************/
class theImageColorCoversion
{
public:
    theImageColorCoversion();
    theImageColorCoversion(Mat &);
    Mat getTheChangeMat();
    void getTheHSVOrRGBMat();
    virtual ~theImageColorCoversion();  
private:
    enum image_change{
        IMAGE_HSV,
        IMAGE_YCrCb,
        IMAGE_HLS,
        IMAGE_Lab,
        IMAGE_RGB_CHANNELS,//get the RGB single R,G,B
    };
    Mat image_H_B;
    Mat image_S_G;
    Mat image_V_R;
    Mat changeImage;   
   
};

/***************************************************************************************/
/****************************the Image threashold value************************************/
/***************************************************************************************/
class theImageThreasholdValue
{
public:
    theImageThreasholdValue();
    theImageThreasholdValue(Mat &);
    Mat getTheChangeMat();
    void ImageOTSUThreashold();
    void ImageOTSUShowImage();
   void  ImageFixationThreashold();
   void ImageSelfThreashold();
    virtual ~theImageThreasholdValue();  
    
private:
        enum threshType
    {
        BINARY,
        ANTIBINARY,
        CUTOFF,
        ZERO,
        ANTIZERO,
    };
    enum image_change{
        IMage_OTSU,
        IMAGE_FIXED,
        IMAGE_SELF,
        IMAGE_BOTH,
        IMAGE_HALF,
    };
    Mat changeImage;   
    Mat beforeImage;
    int threashold;
};

#endif /* IMAGEDEALWITHCLASS_H */

