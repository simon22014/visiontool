/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   histImageClass.cpp
 * Author: aqq
 * 
 * Created on 2017年4月24日, 下午1:39
 */

#include "histImageClass.h"

histImageClass::histImageClass() {
}

histImageClass::histImageClass(Mat &beforeImage) 
:beforeImage(beforeImage)
{
       
}
histImageClass::~histImageClass() {
}
 void histImageClass::histImageType()
 {
     cout << "0,gray hist,1,H_S hist,2,BGR hist,3,user defined hist,4:gammaHist"<< endl;
     int choiceHist;
     cin >> choiceHist;
     switch(choiceHist)
     {
         case GRAYHIST:
             imageGrayHist();
             break;
         case H_S_HIST:
             image_H_S_Hist();
             break;
         case BGRHIST:
             imageBGRHist();
             break;
         case USERDEFINEDHIST:
             user_DefinedHist();
             break;
          
         default:
             break;
             
     }
     return;
 }

 void histImageClass::user_DefinedHist()
 {
     Mat srcImage = beforeImage.clone();
     if(!srcImage.data)
     {
         cout <<"the image data is wrong "<<endl;
         return;
     }
          cout << "a"<<endl;
     Mat srcGray;
     cvtColor(srcImage,srcGray,CV_BGR2GRAY);
     const int channels[1] = {0} ;
     const int histSize[1] = {256};
     //[0,60],[61,120],[121,160],[161,220],[221,255]
     float hranges[6] = {0,60,120,160,220,255};
     const float* ranges[1] = {hranges};
     MatND hist;
     calcHist(&srcGray,1,channels,Mat(),hist,1,histSize,ranges);
     cout << "w"<<endl;
     double maxHist = 0;
     minMaxLoc(hist,0,&maxHist,0,0);
     int hist_Size = hist.rows;
     Mat histImg(hist_Size,hist_Size,CV_8U,Scalar(255));
          cout << "e"<<endl;
     for(int h = 0; h < hist_Size; h++)
     {
         float binVal = hist.at<float>(h);
         int intensity = static_cast<int>(binVal * hist_Size / maxHist);
         line(histImg,Point(h,hist_Size),Point(h,hist_Size - intensity),Scalar::all(0));        
     }
     cout << "q"<<endl;
        changeImage = histImg.clone();
     imshow("histImg",histImg);
     waitKey(0);
   
 }
 void histImageClass::imageBGRHist()
 {
     Mat srcImage = beforeImage.clone();
     if(!srcImage.data)
     {
         cout <<"the image data is wrong "<<endl;
         return;
     }
     vector<Mat> bgr_planes;
     split(srcImage,bgr_planes);
     int histSize = 256;
     float range[] = {0,256};
     const float * histRange = { range };
     bool uniform = true;
     bool accumulate = false;
     Mat b_hist, g_hist, r_hist;
     calcHist(&bgr_planes[0],1,0,Mat(),b_hist,1,&histSize,&histRange,uniform,accumulate);
     calcHist(&bgr_planes[1],1,0,Mat(),g_hist,1,&histSize,&histRange,uniform,accumulate);
     calcHist(&bgr_planes[2],1,0,Mat(),r_hist,1,&histSize,&histRange,uniform,accumulate);
     
     int hist_w  = 640;
     int hist_h = 512;
     int bin_w = cvRound((double) hist_w /histSize) ;
     Mat histImage(hist_h ,hist_w,CV_8UC3,Scalar(0,0,0));
     normalize(b_hist,b_hist,0,histImage.rows,NORM_MINMAX,-1,Mat());
     normalize(g_hist,g_hist,0,histImage.rows,NORM_MINMAX,-1,Mat());
     normalize(r_hist,r_hist,0,histImage.rows,NORM_MINMAX,-1,Mat());
     
     for(int i = 1 ; i < histSize; i++)
     {
         line(histImage,Point(bin_w * (i-1),hist_h - cvRound(b_hist.at<float>(i-1))),
                 Point(bin_w *(i),hist_h - cvRound(b_hist.at<float>(i))),
                 Scalar(255,0,0),2,8,0);
         
            line(histImage,Point(bin_w * (i-1),hist_h - cvRound(g_hist.at<float>(i-1))),
                 Point(bin_w *(i),hist_h - cvRound(g_hist.at<float>(i))),
                 Scalar(255,0,0),2,8,0);
            
               line(histImage,Point(bin_w * (i-1),hist_h - cvRound(r_hist.at<float>(i-1))),
                 Point(bin_w *(i),hist_h - cvRound(r_hist.at<float>(i))),
                 Scalar(255,0,0),2,8,0);     
     }
      changeImage = histImage.clone();
     imshow("beforeImage",beforeImage);
     imshow("calcHist",histImage);
     waitKey(0);
     
     
 
 }
 void  histImageClass::image_H_S_Hist()
 {
     Mat srcImage,hsvMat;
     if(beforeImage.empty())
     {
         cout << "the image is empty"<<endl;
         return ;
     }
     srcImage = beforeImage.clone();
     cvtColor(srcImage,hsvMat,CV_BGR2HSV);
     int hbins = 30;
     int sbins = 32;
     int histSize[] = {hbins,sbins};
     
     float hranges[] = {0,60,180};
     float sranges[] = {0,60,120,256};
     const float* ranges[] = {hranges,sranges};
     MatND hist;
     int channels[] = {0 , 1};
     calcHist(&hsvMat,1,channels,Mat(),hist,2,histSize,ranges,true,false);
     double maxVal = 0;
     
     minMaxLoc(hist,0,&maxVal,0,0);
     int scale = 10;
     Mat histImg = Mat::zeros(sbins*scale,hbins*10,CV_8UC3);
     for(int h = 0; h < hbins ; h++)
     {
         for(int s = 0; s < sbins ;s++)
         {
             float binVal = hist.at<float>(h,s);
             int intensity = cvRound(binVal * 255/maxVal);
            rectangle(histImg,Point(h * scale,s * scale),
                     Point((h +1)*scale - 1,(s + 1) * scale -1),
                     Scalar::all(intensity),CV_FILLED);
             
         }
     }
     changeImage = histImg.clone();
     imshow("source",srcImage);
     imshow("h_s",changeImage);
     
     waitKey(0);
     
 
 } 
 void histImageClass::imageGrayHist()
 {
     Mat Image,ImageGray;
     if(beforeImage.empty())
     {
         cout << "the image data is wrong"<<endl;
         return;
     }
#if 0
     Mat theRGBimage;
     theRGBimage =imread("//home//aqq//NetBeansProjects//demon_test//png//findLine.png");
     const int channels[3] = {0,1,2};
     const int histSize[3] = {256,256,256};
     float hranges[2] = {0,255};
     const float *ranges[3] = {hranges,hranges,hranges};
     MatND hist;
     calcHist(&theRGBimage,1,channels,Mat(),hist,3,histSize,ranges);
#else    
     Image = beforeImage.clone();
     cvtColor(Image,ImageGray,CV_BGR2GRAY);
     const int channels[1] = {0};
     const int histSize[1] = {256};
     float pranges[2] = {0,255};
     const float* ranges[1] = {pranges};
     MatND hist;
     calcHist(&ImageGray,1,channels,Mat(),hist,1,histSize,ranges);
#endif   
#if 0 
          cout <<"histISize"<<hist.channels() <<"  "<<hist.size()<<endl;
     for(int i =0;i < 256;i++ )
     {
         cout << "i:"<<i<<"  hist:"<<hist.at<float>(i)<<endl;
     }
    imshow("hist",hist);
     waitKey(0);
#endif     
     int hist_w = 500;
     int hist_h = 500;
     int nHistSize = 255;
     
     //section
     int bin_w = cvRound((double) hist_w / nHistSize) ;
     Mat histImage(hist_w,hist_h,CV_8UC3,Scalar(0,0,0));
     normalize(hist,hist,0,histImage.rows,NORM_MINMAX,-1,Mat());
 
     for(int i = 1;i < nHistSize ;i++)
     {
         line(histImage,Point(bin_w *(i -1),hist_h - cvRound(hist.at<float>(i -1))),
                 Point(bin_w *(i) , 
                 hist_h - cvRound(hist.at<float>(i))),
                 Scalar(0,0,255),2,8,0);
     }
     changeImage = histImage.clone();
     imshow("beforImage",beforeImage);
     imshow("histImage",changeImage);
     
     waitKey(0);

 }