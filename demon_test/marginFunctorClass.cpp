/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   marginFunctorClass.cpp
 * Author: aqq
 * 
 * Created on 2017年4月24日, 上午8:46
 */

#include "marginFunctorClass.h"

marginFunctorClass::marginFunctorClass() {
}

marginFunctorClass::marginFunctorClass(Mat & image_m)
{
    beforeImage = image_m.clone();
    if(!beforeImage.data)
    {
        cout <<"the image data is wrong" <<endl;
        return ;        
   }
}
 Mat & marginFunctorClass:: returnImage()
 {
     return changeImage;
 }
 void marginFunctorClass:: marginChoice()
 {
     cout << "0,Sobel and Scharr.1,laplace,2,roberts,3,prewitt,4,canny,5,Marr_hildreth"<<endl;
    int number;
    cin >> number;
    switch(number)
    {
      case MARGINSOBEL:
            marginSobelFun();
            break;
        case MARGINLAPLACE:
            marginLaplaceFun();
            break;
        case MARGINROBERTS:
            marginRobertsFun();
            break;
        case MARGINPREWITT:
            marginPrewittFun();
            break;
        case MARGINCANNY:
            marginCanny();
            break;
        case MARRHILDRETH:
            marginMarr_Hildreth();
            break;
        default:
            break;

    }
    cin.clear();
    cout << "choice is over"<<endl;
 
 
 }
 void marginFunctorClass::marginMarr_Hildreth()
 {
     Mat result;
     Mat src = beforeImage.clone();
     cvtColor(src,src,CV_BGR2GRAY);
     if(!src.data)
     {
         cout <<"the image data is wrong"<<endl;
         return ;
     }
     int kerValue = 9;
     double delta = 1.6;
      Mat kernel;
      int kerLen = kerValue / 2;
      kernel = Mat_<double>(kerValue,kerValue);
      for(int i = -kerLen; i <= kerLen;i++)
      {
          for(int j = -kerLen; j <= kerLen ; j++)
          {
              kernel.at<double>(i + kerLen,j + kerLen) =
              exp(-( (pow(j , 2 )  + pow( i , 2))   /
              ( pow (delta,2) * 2)))  * 
              (((pow(j ,2) + pow( i , 2) - 2*pow(delta , 2) )   / (2 * pow(delta,4))));
          }
      }
      int kerOffset = kerValue / 2;
      Mat laplacian = (Mat_<double> (src.rows - kerOffset * 2,
              src.cols - kerOffset*2));
      result = Mat::zeros(src.rows - kerOffset*2,src.cols - kerOffset*2 ,src.type());
      double sumLaplacian;
      for(int i = kerOffset; i <src.rows - kerOffset ; ++i)
      {
          for(int j = kerOffset;j < src.cols - kerOffset ; ++j)
          {
              sumLaplacian = 0;
              for(int k = -kerOffset; k <= kerOffset ; ++k)
              {
                  for(int m = -kerOffset ; m <= kerOffset ;++m)
                  {
                      sumLaplacian += src.at<uchar>(i + k, j + m) * 
                              kernel.at<double> (kerOffset +k ,kerOffset + m);
                  }           
              }
            laplacian.at <double>(i - kerOffset,j - kerOffset) = sumLaplacian;  
          }
      }
      for(int y = 1; y < result.rows - 1 ;++y)
      {
          for(int x = 1; x < result.cols -1 ;++x)
          {
              result.at<uchar>(y,x)  = 0;
              if(laplacian.at<double>(y-1,x) * 
                      laplacian.at<double>(y+1,x) < 0)
              {
                  result.at<uchar>(y,x)  = 255;
              }
              if(laplacian.at<double>(y ,x - 1) *
                      laplacian.at<double>(y  ,x + 1)  < 0)
              {
                  result.at<uchar>(y,x)  = 255;
              }
                     result.at<uchar>(y,x)  = 0;
              if(laplacian.at<double>(y+1,x - 1) * 
                      laplacian.at<double>(y-1,x +1) < 0)
              {
                  result.at<uchar>(y,x)  = 255;
              }
              if(laplacian.at<double>(y -1 ,x - 1) *
                      laplacian.at<double>(y + 1 ,x + 1)  < 0)
              {
                  result.at<uchar>(y,x)  = 255;
              }
                  
          }
      }
      imshow("src",src);
      imshow("edge",result);
      changeImage = result.clone();
      waitKey(0);

 }
  void marginFunctorClass :: marginCanny()
  {
     Mat srcImage = beforeImage.clone();
     cvtColor(srcImage,srcImage,CV_BGR2GRAY);
     if(!srcImage.data)
     {
         cout << "the image data is wrong "<<endl;
         return ;
     }
     int edgeThresh;
     cout << "please input the edge thresh"<<endl;
     cin >> edgeThresh;
     Canny(srcImage,changeImage,edgeThresh,edgeThresh*3,3);
     imshow("changeImage",changeImage);
     waitKey(0);
     
  
  }
 void marginFunctorClass::marginPrewittFun()
 {
     bool verFlag = false;
     Mat srcImage = beforeImage.clone();
     cvtColor(srcImage,srcImage,CV_BGR2GRAY);
     if(!srcImage.data)
     {
         cout << "the image data is wrong "<<endl;
         return ;
     }
     srcImage.convertTo(srcImage,CV_32FC1);
     Mat prewitt_kernel  =  
             (Mat_<float> (3,3) <<  0.1667,0.1667,0.1667,
                                                0,         0,         0,
                                               -0.1667,-0.1667,-0.1667);
     if(verFlag)
     {
         prewitt_kernel = prewitt_kernel.t () ;
         Mat z1 = Mat::zeros (srcImage.rows,1,CV_32FC1);
         Mat z2 = Mat::zeros(1,srcImage.cols,CV_32FC1);
         z1.copyTo(srcImage.col(0));
         z1.copyTo(srcImage.col(srcImage.cols - 1));
         z2.copyTo(srcImage.row(0));
         z2.copyTo(srcImage.row(srcImage.rows - 1));        

     
     }
     Mat edges;
     filter2D(srcImage,edges,srcImage.type(),prewitt_kernel);
     Mat mag;
     multiply(edges,edges,mag);
     //put out vertical and  black side
     if(verFlag)
     {
         Mat black_region = srcImage < 0.03;
         Mat se = Mat::ones(5,5,CV_8UC1);
         dilate(black_region,black_region,se);
         mag.setTo(0,black_region);  
     }
     
     double thresh = 4.0f * mean(mag).val[0];
     
     Mat dstImage = Mat::zeros(mag.size(),mag.type());
     float * dptr = (float*)mag.data;
     float * tptr = (float*)dstImage.data;
     int r = edges.rows,c = edges.cols;
     for(int i = 1;i != r -1 ;++i)
     {
         for(int j = 1;j != c-1 ;++j)
         {
             bool b1 = (dptr[i*c +j]    > dptr[i * c + j -1]);
             bool b2 = (dptr[i *c + j]  > dptr[i * c + j +1]);
             bool b3 = (dptr[i * c + j] > dptr[(i - 1) * c + j]);
             bool b4 = (dptr[i * c +j]  > dptr[(i + 1) * c +i]);
             tptr[i * c +j] = 255 * ((dptr[i * c + j] > thresh)   &&  (( b1 && b2) || (b3 && b4)));  
         } 
     }
     
     dstImage.convertTo(dstImage,CV_8UC1);
     changeImage = dstImage.clone();
      cout << "black_region" << changeImage<<endl;
     imshow("dstImage",changeImage);  
     waitKey(0);
     
     
 }
 void marginFunctorClass ::marginRobertsFun()
 {
     Mat srcImage = beforeImage.clone();
     cvtColor(srcImage,srcImage,CV_BGR2GRAY);
    Mat dstImage = srcImage.clone();
 //   Mat dstImage(srcImage.size(),srcImage.type());
     if((!srcImage.data) || (!dstImage.data))
     {
         cout<< "the image data is wrong"<<endl;
         return ;
     }
     int nRows = dstImage.rows;
     int nCols = dstImage.cols;
     for(int i = 0; i < nRows - 1 ; i++)
     {
         for(int j = 0 ; j < nCols - 1 ;j++)
         {
             int t1 = (srcImage.at<uchar>(i,j)  -
             srcImage.at<uchar>(i+1,j+1)) *
             (srcImage.at<uchar>(i,j) - 
             srcImage.at<uchar>(i+1,j+1));
             
              int t2 = (srcImage.at<uchar>(i+1,j)  -
             srcImage.at<uchar>(i,j+1)) *
             (srcImage.at<uchar>(i+1,j) - 
             srcImage.at<uchar>(i,j+1));
         
              dstImage.at<uchar>(i,j) = (uchar)sqrt(t1 + t2);
         }
     }
     cout << "we"<<endl;
     changeImage = dstImage.clone();     
     imshow("beforeImage",srcImage);
     imshow("dstImage",dstImage);
     
     waitKey(0);
 
 }
void marginFunctorClass::marginLaplaceFun()
{
    Mat image = beforeImage.clone();
    if(!image.data)
    {
        cout << "the data is wrong"<<endl;
        return ;
    }
    GaussianBlur(image,image,Size(3,3),
            0,0,BORDER_DEFAULT);
    cvtColor(image,image,CV_RGB2GRAY);
    Mat dstImage;
    Laplacian(image,dstImage,CV_16S,3);
    convertScaleAbs(dstImage,dstImage);
    cout << "dstImage : "<<dstImage.channels() <<endl;
    
     changeImage = dstImage.clone();
    imshow("dstImage",changeImage);
    imshow("image",beforeImage);
    waitKey(0);
    

}
void marginFunctorClass::marginSobelFun()
{
    cout <<" q"<<endl;
    Mat srcGray;
    cvtColor(beforeImage,srcGray,CV_RGB2GRAY);
  //  srcGray = beforeImage.clone();
    Mat edgeMat,edgeXMat,edgeYMat;
     //get x the sobel
    Sobel(srcGray,edgeXMat,CV_16S,1,0,3,1,0,
            BORDER_DEFAULT);   
    //get the y sobel
    Sobel(srcGray,edgeYMat,CV_16S,0,1,3,1,0
            ,BORDER_DEFAULT);
  //  cout <<"edgeYMat"<<edgeYMat.channels() <<endl;
    //get the 8
    convertScaleAbs(edgeXMat,edgeXMat);
    convertScaleAbs(edgeYMat,edgeYMat);

    //x and y tiejia
    
    addWeighted(edgeXMat,0.5,edgeYMat,0.5,0,edgeMat);
    
    //get y Scharr
    Mat edgeMatS,edgeXMatS,edgeYMatS;
   Scharr(srcGray,edgeXMatS,CV_16S,1,0,1,0,
           BORDER_DEFAULT);
   convertScaleAbs(edgeXMatS,edgeXMatS);
   
    Scharr(srcGray,edgeYMatS,CV_16S,0,1,1,
            0,BORDER_DEFAULT);
    convertScaleAbs(edgeYMatS,edgeYMatS);
    
    addWeighted(edgeXMatS,0.5,edgeYMatS,0.5,0,edgeMatS);
    imshow("edgeMatS",edgeMatS);
    
    
    imshow("edgeYMat",edgeYMat);
    imshow("edgeXMat",edgeXMat);
    imshow("edgeMat",edgeMat);
    
   imshow("srcgray",srcGray);
    changeImageSobel = edgeMat.clone();
    changeImage = edgeMatS.clone();
    waitKey(0);
    
     
}
marginFunctorClass::~marginFunctorClass() {
}

