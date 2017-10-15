/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   imagedealwithclass.cpp
 * Author: aqq
 * 
 * Created on 2017年4月14日, 下午2:41
 */

#include "imagedealwithclass.h"

locationChangeClass::locationChangeClass() {
}
locationChangeClass::~locationChangeClass() {
}
locationChangeClass::locationChangeClass(Mat & image_clone) 
:formerMat(image_clone)
{

}
void locationChangeClass::locationChangeChoice()
{
    cout <<"location the image "<< endl;
    cout <<"offestimgae:0,scale:1"<< endl;
    int choiceNum;
    cin >> choiceNum;
    switch(choiceNum)
    {
        case IMAGE_OFFSET:
            offsetImage();
              break;
        case IMAGE_SCALE :
            scaleImage();
            printImageWidthHigth();
            break;
        default :
            cout << "you input the num is wrong" << endl;
            break;
    
          
    } 

}
  Mat locationChangeClass ::getTheChangeMat()
  {
      return changeMat;
  }
 void locationChangeClass ::areaAverage(Point_<int>leftPoint,Point_<int>rightPoint,Vec3b & vecTemp)
 {
     int temp1 = 0 , temp2 = 0 , temp3 = 0;
     int nPix = (rightPoint.x - leftPoint.x  + 1)*(rightPoint.y - leftPoint.y  + 1);
     if(nPix == 0)
     {
         return ;
     }
     for(int i = leftPoint.x; i <= rightPoint.x; i++)
     {
         for(int j = rightPoint.y ; j <= rightPoint.y;j++)
         {
             temp1 += formerMat.at<Vec3b> (i,j)[0];
             temp2 += formerMat.at<Vec3b> (i,j)[1]; 
             temp3 += formerMat.at<Vec3b> (i,j)[2];   
         }
     }
     cout <<"nPix"<<nPix<<endl;
     vecTemp[0] = temp1 / nPix;
     vecTemp[1] = temp2 / nPix;
     vecTemp[2] = temp3 / nPix;
     return ;
  
 }
void locationChangeClass::scaleImage()
{
    double kx ;
    double ky ;
    Vec3b vecTemp;
    cout << "please input the kx and ky" << endl;
    cin  >> kx;
    cin >> ky;
    if (kx > 0 && ky > 0)
    {
    //get the image resolution
    int nRows = cvRound(formerMat.rows *kx);
    int nCols = cvRound(formerMat.cols * ky);
    Mat resultImage(nRows,nCols,formerMat.type());
    int leftRowCoordinate = 0;
    int leftColCoordinate = 0;
    
    for (int i = 0; i < nRows ; i++)
    {
        int x = static_cast<int>((i + 1) / kx + 0.5) - 1;
        for(int j = 0 ; j < nCols ; j++)
        {
            int y = static_cast<int>((j +1) /ky +0.5) -1;
          
                    areaAverage(Point_<int>(leftRowCoordinate,leftColCoordinate),
                    Point_<int>(x,y),vecTemp);
                      resultImage.at<Vec3b>(i,j) = vecTemp;
            leftColCoordinate = y + 1;
        }
            leftColCoordinate = 0;
            leftRowCoordinate = x+1;
    
    }  
    Width =  resultImage.rows;
    Higth =  resultImage.cols;
    imshow("changeMat",resultImage);
    changeMat = resultImage.clone();
    waitKey(0);
    }
    else
    {
        cout << "you inout the kx and ky less than 0 or equal to 0"<< endl;
                return ;
    }
   
}
void locationChangeClass::printImageWidthHigth()
{
    cout << "the new image width:"<< Width<<"higth:"<<Higth << endl;
 
}
void locationChangeClass::printPointNum()
{
    
    Point leftPoint;
    Point rightPoint;
    cout <<"leftPoint.x"<<leftPoint.x<<"leftPoint.y" << leftPoint.y<< endl;
    cout <<"rightPoint.x"<<rightPoint.x<<"rightPoint.y" << rightPoint.y<< endl;

}
void locationChangeClass::offsetImage()
{
    
    int xOffset ;
    int yOffset ;
    
    cout << "please input the xoffset  and y offset"<< endl; 
    cin >> xOffset;
    cin >> yOffset;
    int nRows = formerMat.rows;
    int nCols = formerMat.cols;
    Mat resultImage(formerMat.size(),formerMat.type());
    for(int i = 0; i < nRows ; i ++)
    {
        for(int j = 0; j < nCols ; j++)
        {
            int x = j - xOffset;
            int y = i- yOffset;
            if(x >= 0 && y>= 0 &&x < nCols && y < nRows)
            {
                resultImage.at<Vec3b>(i,j) = 
                        formerMat.ptr<Vec3b>(y)[x];
                        if(x ==0 &&y ==0)
                        {
                            leftPoint.x = j;
                            leftPoint.y = i;
                            rightPoint.x = j;
                            rightPoint.y = i;
                        }                    
            }   
        }
    }
     circle(resultImage,leftPoint,3,Scalar(255,255,0),1);
     circle(resultImage,rightPoint,3,Scalar(255,255,0),1);

    imshow("changeMat",resultImage);
   changeMat = resultImage.clone();
    waitKey(0);
    return;
}
/***************************************************************************************/
/************************the RGB change the other color conversion****************************/
/***************************************************************************************/
 theImageColorCoversion::theImageColorCoversion()
 {
 }
 theImageColorCoversion:: theImageColorCoversion(Mat & image_clone)
 {
     Mat image = image_clone .clone();
     if(image.channels()  != 3)
     {
         cout << "the image have not three channels "<< endl;
         return ;
     }
     int theChoiceNum;
      cout << "please input the choice"<< endl;
      cout <<"0:HSV,1:YCrCb,2:HLS,3:Lab,4:RGBchannels" << endl;
      cin >> theChoiceNum;
             switch(theChoiceNum)
             {
                 case IMAGE_HSV:
                     cvtColor(image,changeImage,CV_BGR2HSV);
                 //     imshow("changeImgae",changeImage);
               //       waitKey(0);
                     getTheHSVOrRGBMat();     
                    
                     break;
                         case IMAGE_YCrCb:
                 cvtColor(image,changeImage,CV_BGR2YCrCb);
                              imshow("changeImgaeCrCb",changeImage);
                     waitKey(0);
                     break;
                         case IMAGE_HLS:
                 cvtColor(image,changeImage,CV_BGR2HLS);
                              imshow("changeImgaeHLS",changeImage);
                     waitKey(0);
                     break;
                         case IMAGE_Lab:
                 cvtColor(image,changeImage,CV_BGR2Lab);
                              imshow("changeImgaeLab",changeImage);
                     waitKey(0);
                     break;
                 case IMAGE_RGB_CHANNELS:
                     changeImage = image_clone.clone();
                          getTheHSVOrRGBMat();    
                          break;
                     
                 default:
                     cout << "you input the num is wrong"<<endl;
                     break;
                           
             }
             
             
 }
 void theImageColorCoversion::getTheHSVOrRGBMat()
 {
     vector<Mat>  hsvChannels;
     split(changeImage,hsvChannels);
    image_H_B = hsvChannels[0];
    image_S_G = hsvChannels[1];
    image_V_R = hsvChannels[2];  
    imshow("image_H",image_H_B);
    imshow("image_S",image_S_G);
    imshow("image_V",image_V_R);
    waitKey(0);
    
 }
    Mat  theImageColorCoversion::  getTheChangeMat()
    {
      return changeImage;
    }
 theImageColorCoversion:: ~theImageColorCoversion()
  {
  }
 /***************************************************************************************/
/****************************the Image threashold value************************************/
/***************************************************************************************/
theImageThreasholdValue::theImageThreasholdValue()
{
}
theImageThreasholdValue::theImageThreasholdValue(Mat &image_clone)
{
beforeImage = image_clone .clone();
     if(beforeImage.channels()  != 1)
     {
         cout << "the image have not 1 channels ,so it auto gray "<< endl;
         cvtColor(beforeImage,beforeImage,CV_BGR2GRAY);
     //    return ;
     }

        int theChoiceNum;
      cout << "please input the choice"<< endl;
      cout <<"0:image OTSU,1:fixation,2:self-adaption,3:both threshold,4:half threshold" << endl;
      cin >> theChoiceNum;
             switch(theChoiceNum)
             {
                 case IMage_OTSU:
                          ImageOTSUThreashold();        
                          ImageOTSUShowImage();
                     break;
                  case IMAGE_FIXED:
                           ImageFixationThreashold();                                      
                     break;
                 case  IMAGE_SELF:
                          ImageSelfThreashold();               
                     break;
                 case IMAGE_BOTH:
                
                     break;
                 case IMAGE_HALF:
                    
                          break;
                     
                 default:
                     cout << "you input the num is wrong"<<endl;
                     break;
                           
             }        
}
void theImageThreasholdValue::ImageSelfThreashold()
{
    int blockSize = 5;
    int constValue = 10;
    const int maxVal = 255;
    /*
     * 0:ADAPTIVE_THRESH_MEAN_C
     * 1:ADAPTIVE_THRESH_GAUSSIAN_C
     * 
     * 0:THRESH_BINARY
     * 1:THRESH_BINARY_INV
     *    
      */
    adaptiveThreshold( beforeImage,changeImage,maxVal,ADAPTIVE_THRESH_MEAN_C,THRESH_BINARY_INV,
            blockSize,constValue);
    imshow("changeImage",changeImage);
    waitKey(0);

}
void theImageThreasholdValue::ImageFixationThreashold()
{
    int thresh;
    int threshType;
    cout<< "please input the thresh" << endl;
    cin >> thresh;
    const int maxVal = 255;
    cout << "please input the 0:binary,1:anti binary,2:cut off ,3:zero,4:anti zero"<<endl;
   cin.clear();
    cin >> threshType;
    if(threshType > 5)
    {
        cout <<"you input the num  is wrong"<<endl;
    }
    threshold(beforeImage,changeImage,thresh,maxVal,threshType);       
imshow("changeImage",changeImage);
waitKey(0);
}

Mat theImageThreasholdValue::getTheChangeMat()
{
    return changeImage;
}
void theImageThreasholdValue::ImageOTSUShowImage()
{
    Mat otsuResultImage = Mat:: zeros  (beforeImage.rows,beforeImage.cols,CV_8UC1);
    for(int i = 0 ; i <beforeImage.rows; i++)
    {
        for(int j = 0;j <beforeImage.cols;j++)
        {
            if(beforeImage.at<uchar>(i,j)  > threashold)
            {
            otsuResultImage.at<uchar>(i,j)  = 255;
            }
            else{
            otsuResultImage.at<uchar>(i,j)  = 0;
            }
        }
        changeImage = otsuResultImage.clone();
    
    }
    
    imshow("otsuimage",otsuResultImage);
    waitKey(0);

}
theImageThreasholdValue::~theImageThreasholdValue()
{
}
 void theImageThreasholdValue:: ImageOTSUThreashold()
 {
    int nCols = beforeImage.cols;
    int nRows = beforeImage.rows;
    threashold = 0;
     // init the num
    float nSumPix[256];
    float nProDis[256];
    for(int i = 0;i < 256 ;i++)
    {
        nSumPix[i]  = 0;
        nProDis[i]  = 0;
    }
    //info gay in the image num
    for(int i = 0 ; i < nCols ;i++)
    {
        for(int j = 0 ;j < nRows;j++)
        {
            nSumPix[(int)beforeImage.at<uchar>(i,j)]++;
            cout << (int)beforeImage.at<uchar>(i,j) <<"  ad "<< nSumPix[(int)beforeImage.at<uchar>(i,j)]<< endl;

        }
    }
    for(int i = 0; i <256;i++)
    {
        nProDis[i]  = (float)nSumPix[i] /(nCols * nRows);
    }
    float w0,w1,u0_temp,u1_temp,u0,u1,delta_temp;
    double delta_max = 0.0;
    for(int i = 0 ; i < 256; i++)
    {
        w0 = w1 = u0_temp = u0 = u1 = delta_temp = 0;
        for(int j = 0 ; j < 256; j++)
    {
            if( j <=  i)
            {
                w0 += nProDis[j];
                u0_temp +=j * nProDis[j];
            }
            else
            {
                w1 += nProDis[j];
                u1_temp += j * nProDis[j];
            }
    }
        u0 = u0_temp /w0;
        u1 = u1_temp /w1;
        delta_temp = (float)(w0 * w1 *pow((u0 - u1),2)) ;
        if(delta_temp > delta_max)
        {
            delta_max = delta_temp;
            threashold = i;
        }
    }
    cout <<"threashold"<<threashold <<endl;
 }
