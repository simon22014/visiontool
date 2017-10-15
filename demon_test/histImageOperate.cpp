/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   histImageOperate.cpp
 * Author: aqq
 * 
 * Created on 2017年4月24日, 下午4:01
 */

#include "histImageOperate.h"

histImageOperate::histImageOperate() {
}

histImageOperate::histImageOperate(Mat & beforeImage) 
:beforeImage(beforeImage)
{
}
void histImageOperate::histImageOperateType()
{
    cout << "0,hist equal,1,rgb equal,2,histvary find,3,histvary addup,4:Rverse Projection" << endl;
    int histType;
    cin >> histType;
    switch(histType)
    {
        case GRAYHISTEQUAL:
            grayHistEqual();
            break;
        case RGBHISTEQUAL:
            rgbHistEqual();
            break;
        case HISTVARYFIND:
            histVaryFind();
            break;
        case HISTVARYADDUP:
            histVaryAddup();
            break;
        case HISTRVERSEPROJECTION:
            histRverseProjection();
            break;
        default:
            break;
    
    }

}
void histImageOperate::histRverseProjection()
{
    Mat srcImage = beforeImage.clone();
    if( !beforeImage.data)
    {
        cout<< "the image data is wrong" <<endl;
        return ;
    }
    Mat hsvImage;
    cvtColor(srcImage,hsvImage,CV_BGR2HSV);
    Mat hueImage;
    hueImage.create(hsvImage.size(),hsvImage.depth());
    int ch[] = {0,0};
    mixChannels (&hsvImage,1,&hueImage,1,ch,1);
    
    int bins = 25;
    MatND hist;
    int histSize = MAX(bins,2);
    float hue_range[] = {0,100};
    const float* ranges = { hue_range };
    calcHist(&hueImage,1,0,Mat(),hist,1,&histSize,&ranges,true,false);
    normalize(hist,hist,0,255,NORM_MINMAX,-1,Mat());
    MatND backproj;
    calcBackProject(&hueImage,1,0,hist,backproj,&ranges,1,true);
    
    int w = 320 ; int h = 360;
    int bin_w = cvRound((double)w  / histSize);
    Mat histImg = Mat::zeros (w,h,CV_8UC3);
    for(int i = 0; i < bins ; i++)
    {
        rectangle(histImg,Point(i*bin_w,h),Point((i +1)*bin_w,h -cvRound(hist.at<float>(i) * h /255.0)),
                Scalar(0,0,255) , -1);
    }
    imshow("backproj",backproj);
    imshow("srcImage",srcImage);
    imshow("histogram",histImg);
    equalizeHist(backproj,backproj);
    imshow("backproj",backproj);
    waitKey(0);

}
void histImageOperate::histVaryAddup()
{
  Mat srcImage = beforeImage.clone();
    if( !beforeImage.data)
    {
        cout<< "the image data is wrong" <<endl;
        return ;
    }
   Mat srcGray;
   cvtColor(srcImage,srcGray,CV_BGR2GRAY);
   const int channels[1] = {0};
   const int histSize[1]  = {256};
   float hranges[2] = {0,255};
   const float* ranges[1] = {hranges};
   MatND hist;
   calcHist(&srcGray,1,channels,Mat(),hist,1,histSize,ranges);
   float table[256];
   int nPix = srcGray.cols * srcGray.rows;
   for(int i = 0; i < 256 ; i++)
   {
       float temp[256];
       temp[i] = hist.at<float>(i) / nPix * 255;
       if( i != 0)
       {
           table[i] = table[i - 1] + temp[i];
       }
       else{
           table[i] = temp[i];
       }
   }
   Mat lookUpTable(Size(1,256),CV_8U);
   for(int i = 0; i < 256; i++)
   {
       lookUpTable.at<uchar>(i)  = static_cast<uchar>(table[i]);
   }
   Mat histTransResult;
   LUT(srcGray,lookUpTable,histTransResult);
   changeImage = histTransResult.clone();
   imshow("srcGray",srcGray);
   imshow("histTransResult",changeImage);
   waitKey(0);
   

}
void histImageOperate::histVaryFind()
{
   Mat srcImage = beforeImage.clone();
    if( !beforeImage.data)
    {
        cout<< "the image data is wrong" <<endl;
        return ;
    }
   Mat srcGray;
   cvtColor(srcImage,srcGray,CV_BGR2GRAY);
   
   const int channels[1] = {0};
   const int histSize[1] = {256};
   float hranges[2] = {0,255};
   const float* ranges[1] = {hranges};
   MatND hist;
   calcHist(&srcGray,1,channels,Mat(),hist,1,histSize,ranges);
   
   int segThreshold = 150;
   int iLow = 0;
   for(;iLow < histSize[0] ; iLow++)
   {
       if(hist.at<float>(iLow)  > segThreshold)
       {
           break;
       }
   }
   int iHigh = histSize[0]  -1;
   for(;iHigh >= 0 ; iHigh--)
   {
       if(hist.at<float>(iHigh)  > segThreshold)
       {
           break;
       }
   }
   Mat lookUpTable(Size(1,256),CV_8U);
   for(int i = 0; i < 256; i++)
   {
       if(i < iLow)
       {
           lookUpTable.at<uchar>(i)  = 0;
       }
       else if( i > iHigh)
       {
           lookUpTable.at<uchar>(i)  = 255;
       }
       else
       {
           lookUpTable.at<uchar>(i) = static_cast<uchar>(255.0 * (i - iLow) /
                   (iHigh - iLow + 0.5));
       }
       
   }
   Mat histTransResult;
   LUT(srcImage,lookUpTable,histTransResult);
   changeImage = histTransResult.clone();
   imshow("srcImage",srcImage);
   imshow("histTransResult",changeImage);
   waitKey(0);
}
 void histImageOperate::rgbHistEqual()
 {
   Mat srcImage = beforeImage.clone();
    if( !beforeImage.data)
    {
        cout<< "the image data is wrong" <<endl;
        return ;
    }
   Mat colorHeqImage;
   vector<Mat> BGR_plane;
   split(srcImage,BGR_plane);
   for(int i = 0 ;i < BGR_plane.size() ; i++) 
   {
       equalizeHist(BGR_plane[i],BGR_plane[i]);
   }
       merge(BGR_plane,colorHeqImage);
       changeImage = colorHeqImage.clone();
       imshow("srcImage",srcImage);
       imshow("colorHeqImage",colorHeqImage);
       waitKey(0);
 }
void  histImageOperate:: grayHistEqual()
{
    Mat srcImage = beforeImage.clone();
    Mat srcGray;
    if( !beforeImage.data)
    {
        cout<< "the image data is wrong" <<endl;
        return ;
    }
    cvtColor(srcImage,srcGray,CV_BGR2GRAY);
    Mat heqResult;
    equalizeHist(srcGray,heqResult);
    changeImage = heqResult.clone();
    imshow("heqResult",changeImage);
    imshow("beforeImage",beforeImage);
    waitKey(0);
   
}
histImageOperate::~histImageOperate() {
}

