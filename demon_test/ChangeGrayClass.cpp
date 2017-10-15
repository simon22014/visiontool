/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ChangeGrayClass.cpp
 * Author: aqq
 * 
 * Created on 2017年5月2日, 下午3:24
 */

#include "ChangeGrayClass.h"

ChangeGrayClass::ChangeGrayClass() {
}
 void ChangeGrayClass::ChGrayClassType()
 {
     cout << "0:gamma,1:linear change"<<endl;
     int choiceNum;
     cin>>choiceNum;
     switch(choiceNum)
     {
         case GAMMAHIST:
             gammaHist();
             break;
         case LINEARCHANGE:
             linearChange();
             break;
         case LOGCHANGE:
             logChange();
             break;
         default:
             break;

     }
     
     
 }
 Mat  ChangeGrayClass::logTransForm3(Mat &srcImage,float c)
 {
   
     if(srcImage.empty())
     {
         cout <<"the image data is NULL"<<endl;
         return (Mat){0,0,0};
     }
     Mat resultImage = Mat::zeros(srcImage.size(),srcImage.type());
     srcImage.convertTo(resultImage,CV_32F);
     resultImage = resultImage + 1;
     
     log(resultImage,resultImage);
     resultImage = c * resultImage;
     normalize(resultImage,resultImage,0,255,NORM_MINMAX);
     convertScaleAbs(resultImage,resultImage);
     changeImage = resultImage.clone();
     return resultImage;
 }
void  ChangeGrayClass::logChange()
{
    Mat srcImage = beforeImage.clone();
    if(!srcImage.data)
    {
        cout << "the image data is NULL"<<endl;
        return;
    }
    float c = 1.2;
    Mat resultImage;
    double tTime = (double)getTickCount();
    const int nTimes = 100;
    for(int i = 0 ; i < nTimes ; i++)
    {
        resultImage = logTransForm3(srcImage,c); 
    }
    tTime = 1000 * ((double)getTickCount() - tTime) / getTickFrequency();
    tTime /= nTimes;
    imshow("resultImage",resultImage);
    imshow("beforeImage",beforeImage);
    waitKey(0);
    
   
}
void  ChangeGrayClass::linearChange()
{
    Mat srcImage = beforeImage.clone();
    if(!srcImage.data)
    {
        cout<<"the image data is NULL"<<endl;
        return;     
    }
    float a= 5;
    int b = 10;
    const int nRows = srcImage.rows;
    const int nCols = srcImage.cols;
    Mat resultImage = Mat::zeros(srcImage.size(),srcImage.type());
    for(int i = 0; i < nRows ; i++)
    {
        for(int j = 0; j < nCols ; j++)
        {
            for(int c = 0 ; c < 3 ; c++)
            {
                resultImage.at<Vec3b>(i,j)[c]  = saturate_cast<uchar>(a *(srcImage.at<Vec3b>(i,j)[c]) +b);
            }
        }
    }
    changeImage = resultImage.clone();
    imshow("srcImage",srcImage);
    imshow("resultImage",resultImage);
    waitKey(0);
}
void  ChangeGrayClass::gammaHist()
{
    Mat srcImage = beforeImage.clone();
    if(!srcImage.data)
    {
        cout << "the image data is NULL"<<endl;
        return;
    }
    float kFactor = 0.3;
    unsigned char LUT[256];
    for(int i = 0 ;i < 256; i++)
    {
        LUT[i] = saturate_cast<uchar>(pow((float) (i / 255.0 ),kFactor)  * 255.0f);
        
    }
   Mat resultImage = srcImage.clone();
   if(srcImage.channels() == 1)
   {
       MatIterator_<uchar> iterator = resultImage.begin<uchar>();
       MatIterator_<uchar>iteratorEnd = resultImage.end<uchar>();
       for(; iterator != iteratorEnd ; iterator ++)
       {
       *iterator = LUT[(*iterator)];
       }  
   }
   else
   {
       MatIterator_<Vec3b> iterator = resultImage.begin<Vec3b>();
       MatIterator_<Vec3b> iteratorEnd = resultImage.end<Vec3b>();
       for(; iterator != iteratorEnd ; iterator++ )
       {
       (*iterator)[0] = LUT[((*iterator)[0])];
       (*iterator)[1] = LUT[((*iterator)[1])];
       (*iterator)[2] = LUT[((*iterator)[2])]; 
       }
   }
   changeImage = resultImage.clone();
   imshow("resultImage",resultImage);
   
   waitKey(0);   
}
ChangeGrayClass::ChangeGrayClass(Mat & beforeImage) 
:beforeImage(beforeImage)
{
    
}

ChangeGrayClass::~ChangeGrayClass() {
}

