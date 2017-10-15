/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   imageSamplingClass.cpp
 * Author: aqq
 * 
 * Created on 2017年4月27日, 下午1:15
 */

#include "imageSamplingClass.h"

imageSamplingClass::imageSamplingClass() {
}

imageSamplingClass::imageSamplingClass(Mat & beforeImage) 
:beforeImage(beforeImage)
{   

}
imageSamplingClass::~imageSamplingClass() {
}
void imageSamplingClass::bothLinearInsertVaule(int changeRows,int changeCols)
{
    Mat srcImage = beforeImage.clone();
    CV_Assert(srcImage.data != NULL);
    int srcRows = srcImage.rows;
    int srcCols = srcImage.cols;
    int srcStep = srcImage.step;
    
    Mat dstImage = Mat(Size(changeRows,changeCols),srcImage.type(),Scalar::all(0));
    int dstRows = dstImage.rows;
    int dstCols = dstImage.cols;
    int dstStep = dstImage.step;
    
    IplImage src = srcImage;
    IplImage dst = dstImage;
    cout << "srcCols: "<<srcCols<<" srcRows: "<<srcRows<<
            " srcStep: "<<srcStep<< endl;
    cout <<"dstCols: "<<dstCols<<" dstRows: "<<dstRows <<" dstStep: "<<endl;
    float srcX = 0 ,srcY = 0;
    float t1X = 0,t1Y = 0,t1Z = 0;
    float t2X =0 ,t2Y = 0,t2Z = 0;
    for(int j = 0; j < dstRows - 1; j++ )
    {
        for(int i = 0 ; i < dstCols - 1 ; i++ )
        {
            srcX = (i +0.5) * ((float) srcCols)  / (dstCols)  - 0.5 ;
            srcY = (j + 0.5) * ((float)srcRows) / (dstRows) - 0.5;
            int iSrcX = (int )srcX; 
            int iSrcY = (int)srcY;
t1X = ((uchar*) (src.imageData + srcStep * iSrcY)) [iSrcX * 3 + 0] * (1 - abs(srcX - iSrcX)) +
         ((uchar*) (src.imageData + srcStep * iSrcY)) [(iSrcX+1) * 3 + 0] * (srcX - iSrcX);
         
t1Y = ((uchar*) (src.imageData + srcStep * iSrcY)) [iSrcX * 3 + 1] * (1 - abs(srcX - iSrcX)) +
         ((uchar*) (src.imageData + srcStep * iSrcY)) [(iSrcX+1) * 3 + 1] *  (srcX - iSrcX);
         
t1Z = ((uchar*) (src.imageData + srcStep * iSrcY)) [iSrcX * 3 + 2] * (1 - abs(srcX - iSrcX)) +
         ((uchar*) (src.imageData + srcStep * iSrcY)) [(iSrcX+1) * 3 + 2] *  (srcX - iSrcX);
 
t2X = ((uchar*) (src.imageData + srcStep *( iSrcY +1))) [iSrcX * 3 + 0] * (1 - abs(srcX - iSrcX)) +
         ((uchar*) (src.imageData + srcStep * (iSrcY + 1))) [(iSrcX+1) * 3 + 0] *  (srcX - iSrcX);
         
t2Y = ((uchar*) (src.imageData + srcStep * ( iSrcY +1))) [iSrcX * 3 + 1] * (1 - abs(srcX - iSrcX)) +
         ((uchar*) (src.imageData + srcStep * ( iSrcY +1))) [(iSrcX+1) * 3 + 1] *  (srcX - iSrcX);
         
t2Z = ((uchar*) (src.imageData + srcStep * ( iSrcY +1))) [iSrcX * 3 + 2] * (1 - abs(srcX - iSrcX)) +
         ((uchar*) (src.imageData + srcStep * ( iSrcY +1))) [(iSrcX+1) * 3 + 2] *  (srcX - iSrcX);
  
         ((uchar*) (dst.imageData + dstStep*j)) [i * 3] = 
                 t1X *(1 - abs(srcY - iSrcY )) + t2X *(abs(srcY - iSrcY));
         
         ((uchar*) (dst.imageData + dstStep*j)) [i * 3 +1] = 
                 t1X *(1 - abs(srcY - iSrcY )) + t2Y *(abs(srcY - iSrcY));
         
         ((uchar*) (dst.imageData + dstStep*j)) [i * 3 + 2 ] = 
                 t1X *(1 - abs(srcY - iSrcY )) + t2Z *(abs(srcY - iSrcY));
        }
         ((uchar*)(dst.imageData + dstStep * j))[(dstCols -1) * 3] = 
                 ((uchar*)(dst.imageData  + dstStep *j ))[(dstCols -2) *3];
               
          ((uchar*)(dst.imageData + dstStep * j))[(dstCols -1) * 3 +1] = 
                 ((uchar*)(dst.imageData  + dstStep *j ))[(dstCols -2) *3 + 1];
                 
         ((uchar*)(dst.imageData + dstStep * j))[(dstCols -1) * 3 + 2] = 
                 ((uchar*)(dst.imageData  + dstStep *j ))[(dstCols -2) *3 + 2];
    }     
                 for(int i = 0; i < dstCols * 3 ; i++)
                 {
                 ((uchar*)(dst.imageData +dstStep *(dstRows -1))) [i] = 
                         ((uchar*)(dst.imageData + dstStep*(dstRows -2)))[i];
                 }
    imshow("dst",(Mat)&dst);
    changeImage =((Mat) (&dst)).clone();
    waitKey(0);

}
void imageSamplingClass::latelyNextInsertVaule(int changeRows,int changeCols)
{
    Mat srcImage = beforeImage.clone();
    CV_Assert(srcImage.data !=NULL );
    int rows = srcImage.rows;
    int cols = srcImage.cols;
    Mat dstImage  = Mat(Size(changeRows,changeCols),srcImage.type(),Scalar::all(0));
    int dstRows = dstImage.rows;
    int dstCols = dstImage.cols;
    float cx = (float)cols / dstCols;
    float ry = (float)rows / dstRows;
    cout << "cols "<<cols <<"rows "<< rows<<endl;
    cout << "cx: "<<cx <<"ry: "<<ry<<endl;
    for(int i = 0; i <dstCols ;i++ )
    {
        int ix = cvFloor( i * cx);
        for(int j = 0 ; j < dstRows ; j++ )
        {
            int jy = cvFloor(j * ry);
            if(ix > cols -1)
            {
                ix = cols -1 ;
            }
            if(jy > rows -1)
            {
               jy  = rows -1;
            }
            dstImage.at<Vec3b>(i,j) = srcImage.at<Vec3b>(jy,ix);
        }
    }
    changeImage = dstImage.clone();
    imshow("dstImage",changeImage);
    waitKey(0);
 
}
