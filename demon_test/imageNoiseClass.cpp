/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   imageNoiseClass.cpp
 * Author: aqq
 * 
 * Created on 2017年4月27日, 下午3:02
 */

#include "imageNoiseClass.h"

imageNoiseClass::imageNoiseClass() {
}
imageNoiseClass::imageNoiseClass(Mat & beforeImage) 
:beforeImage(beforeImage)
{
     
}
double imageNoiseClass::generateGuassianNoise(double mu,double sigma)
{
    const double epsilon = numeric_limits<double>::min();
    static double z0,z1;
    static bool flag = false;
    flag = !flag;
    if (!flag)
    {
        return z1 * sigma + mu;
    }
    double u1,u2;
    do 
    {
        u1 = rand() * (1.0 / RAND_MAX);
        u2 = rand() * (1.0 / RAND_MAX);
    }while( u1 <= RAND_MAX );
    
    z0 = sqrt( -2.0 * log(u1)) * cos(2 * CV_PI  * u2 );
    z1 = sqrt(-2.0 * log(u1))  * sin( 2 * CV_PI  * u2);
    return z0  * sigma + mu;

}
void imageNoiseClass::addGaussianNoise()
{
    Mat resultImage = beforeImage.clone();
    CV_Assert(resultImage.data != NULL);
    int channels = resultImage.channels();
    int nRows = resultImage.rows;
    int nCols = resultImage.cols * channels;
    if(resultImage.isContinuous())
    {
        nCols *= nRows;
        nRows = 1;
    }
    for(int i = 0 ; i < nRows ; i ++)
    {
        for(int j = 0; j < nCols ; j++)
        {
            int val = resultImage.ptr<uchar>(i)[j]  +
                            generateGuassianNoise(2,0.8) * 32;
            if(val < 0)
            {
                val = 0;
            }
            if(val > 255)
            {
                val = 255;
            }
            resultImage.ptr<uchar>(i)[j] = (uchar)val;         
        }
    }
    changeImage = resultImage.clone();
    imshow("changeImage",changeImage);
    waitKey(0);
}
void imageNoiseClass::addSaltNoise(int n,int salt)
{
    Mat resultImage = beforeImage.clone();
    CV_Assert(resultImage.data != NULL);
    for(int k = 0; k < n; k++)
    {
        int i = rand () % resultImage.cols;
        int j = rand() % resultImage.rows;
        
        if(resultImage.channels() == 1)
        {
            resultImage.at<uchar>(j,i) = salt;
        }
        else
        {
            resultImage.at<Vec3b>(j,i)[0] = salt;
            resultImage.at<Vec3b>(j,i) [1] = salt;
            resultImage.at<Vec3b>(j,i)[2] = salt;
        }
    }
    Mat blurImage;
    changeImage = resultImage.clone();
    dim = new dimDealWitch(resultImage);
   //     blur(changeImage,blurImage,Size(3,3),Point(-1,-1));
      dim->dimDealWithType();
      blurImage  =  dim->returnImage();
    imshow("chanegImge",changeImage);
    imshow("blurImage",blurImage);
    waitKey(0);
}
imageNoiseClass::~imageNoiseClass() {
     delete dim;
     dim = NULL;
}

