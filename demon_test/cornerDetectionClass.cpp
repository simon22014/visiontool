/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   cornerDetectionClass.cpp
 * Author: aqq
 * 
 * Created on 2017年5月4日, 上午8:51
 */

#include "cornerDetectionClass.h"

cornerDetectionClass::cornerDetectionClass() {
}

cornerDetectionClass::cornerDetectionClass(Mat & beforeImage) 
:beforeImage(beforeImage)
{  
}

cornerDetectionClass::~cornerDetectionClass() {
}
void cornerDetectionClass::moravecCorner()
{
   Mat srcImage = beforeImage.clone();
    Mat resMorMat  = beforeImage.clone();
    imshow("the",srcImage);
    CV_Assert(resMorMat.data != NULL);
    int kSize = 4;
    int threshold = 150000;
    int r = kSize / 2;
    const int nRows  =  srcImage.rows;
    const int nCols = srcImage.cols;
    int nConut = 0;
    CvPoint * pPoint = new CvPoint[nRows * nCols];
   cvtColor(srcImage,srcImage,CV_BGR2GRAY);
    for(int i = r; i < srcImage.rows - r ; i++)
    {
        for(int j = r; j < srcImage.cols - r ; j++)
        {
            int wV1 ,wV2 , wV3 , wV4 ;
            wV1 = wV2 = wV3 = wV4 = 0;
            for(int k = -r; k < r ; k++)
            {
                wV1 +=(pow(srcImage.at<uchar>(i , j + k),2) - srcImage.at<uchar>(i , j + k +1) * 
                        (srcImage.at<uchar>(i,j + k ))  + pow(srcImage.at<uchar>(i,j + k + 1),2));             
            }
            for(int k = -r; k < r ; k++)
            {
                wV2 += (pow(srcImage.at<uchar>(i +k, j),2) - srcImage.at<uchar>(i + k +1 , j) * 
                        (srcImage.at<uchar>(i +k ,j))  +pow(srcImage.at<uchar>(i +k +1,j),2));             
            }
            for(int k = -r; k < r ; k++)
            {
                wV3 += (pow(srcImage.at<uchar>(i + k , j + k),2) - srcImage.at<uchar>(i + k+ 1 , j + k +1) * 
                        (srcImage.at<uchar>(i +k,j + k ))  +pow( srcImage.at<uchar>(i + k +1,j + k + 1),2));             
            }
           for(int k = -r; k < r ; k++)
            {
                wV4 +=(pow (srcImage.at<uchar>(i +k, j - k),2) - srcImage.at<uchar>(i + k+ 1, j - k -1) * 
                        (srcImage.at<uchar>(i + k,j - k ))  +pow(srcImage.at<uchar>(i + k + 1,j - k - 1),2));             
            }
    //      cout << wV1<<wV2<<wV3<<wV4<<endl;
            int value  = min(min(wV1,wV2) , min(wV3,wV4));
         //   cout << "value  : "<<value<<endl;
            if( value  > threshold)
            {
                pPoint[nConut] = cvPoint(j,i);
                nConut ++;
            }
        }
    }
    cout <<"nConut"<<nConut<<endl;
    for(int i = 0; i < nConut ; i++)
    {
        circle(resMorMat,pPoint[i] ,5 , Scalar(255,0,255),2,8,0);
    }
    changeImage = resMorMat.clone();
    imshow("resMorMat",resMorMat);
    waitKey(0);

}
void cornerDetectionClass::harrisCorner()
{
    Mat srcImage = beforeImage.clone();
    CV_Assert(srcImage.data != NULL);
    Mat srcGray,result;
    cvtColor(srcImage,srcGray,CV_BGR2GRAY);
    result  = Mat::zeros(srcImage.size(),CV_32FC1);
    
    int blockSize = 1;
    int apertureSize = 3;
    double k = 0.04;
    cornerHarris(srcGray,result,blockSize,apertureSize,k,BORDER_DEFAULT);
    normalize(result,result,0,255,NORM_MINMAX,CV_32FC1,Mat());
    convertScaleAbs(result,result);
    
    for(int j = 0 ; j < result.rows ; j++ )
    {
        for(int i = 0 ; i< result.cols ; i++)
        {
            if((int) result.at<float>(j,i)  > 150 )
            {
                circle(srcImage,Point(i,j) ,5 ,Scalar(255,0,255) ,2,8,0);
            }
        }
    }
    changeImage = srcImage.clone();
    imshow("result",changeImage);
    waitKey(0);

}

void cornerDetectionClass::Shi_TomasiCorner()
{
    Mat srcImage = beforeImage.clone();
    CV_Assert(srcImage.data != NULL);
    Mat srcGray;
    cvtColor(srcImage,srcGray,CV_BGR2GRAY);
    vector<Point2f> vecCorners;
    
    double qualityLevel = 0.01;
    double minDistance = 10;
    int blockSize = 3;
    bool useHarrisDetector = false;
    double k = 0.04;
    
    int maxCorners = 50;
    int maxTrackbar = 100;
    
    Mat result = srcImage.clone();
    
    goodFeaturesToTrack(srcGray,vecCorners,maxCorners,
            qualityLevel,minDistance,Mat(),
            blockSize,useHarrisDetector,k);
    cout << "corners: "<<vecCorners.size() << endl;
    for(int i = 0 ; i < vecCorners.size() ; i++)
    {
        circle(result,vecCorners[i] ,4,Scalar(0,0,255) ,2);
    }
    imshow("srcImage",srcImage);
    imshow("result",result);
    changeImage = result.clone();
    waitKey(0);
}
void cornerDetectionClass::cornerDetectionType()
{
    CV_Assert(beforeImage.data != NULL);
    cout << "0,moravec corner,1;harris.2:Shi_Tomasi"<<endl;
   int choiceNum;
    cin >> choiceNum;
    switch(choiceNum)
    {
        case  MORAVECCORNER:
            moravecCorner();      
            break;
        case HARRISCORNER:
            harrisCorner();
            break;
        case SHI_TOMASICORNER:
            Shi_TomasiCorner();
            break;
        default:
            break;
    
    
    }
    return;
}

