/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   marginGeometryClass.cpp
 * Author: aqq
 * 
 * Created on 2017年4月27日, 下午4:47
 */

#include "marginGeometryClass.h"

marginGeometryClass::marginGeometryClass() {
}
void  marginGeometryClass::marginGeomrtryType()
{
    cout << "0:hoff,1:LSD,2:circle"<<endl;
     int  choiceNum;
    cin >>  choiceNum;
    switch(choiceNum)
    {
       case  HOFFGLEOMRTRY:
           marginHoffGeomrtry();
           break;
        case LSDFASTGEOMRTRY:
            LSDFastGeomrtry();
            break;
        case CIRCLEGEOMRTRY:
             circleGeomrtry();
             break;
            
             
        default:
            break;
    }
}
 void marginGeometryClass::circleGeomrtry()
 {
     Mat srcImage = beforeImage.clone();
     Mat src_canny;
     CV_Assert(srcImage.data != NULL);

     gerMouse = new GeroetryMouse (srcImage);
     gerMouse->LineGetStartEndPoint();
     Point startPoint = gerMouse ->getStartPoint();
     Point endPoint = gerMouse ->getEndPoint();

     if(srcImage.channels()  == 1)
     {
              cout << "the image channels is 1 ,so you can take the line"<<endl;
              return;
    }
     
      findLine = new imageFindLineClass(startPoint,endPoint,srcImage);
     findLine->imageEnlarge();
     int bestCannyPos =  findLine->getBestCannyPos();  
    src_canny =  findLine -> getCraveImage();
    
     Canny(src_canny,src_canny,bestCannyPos,bestCannyPos*3,3);
   
     vector<Vec3f> circles;
     
    HoughCircles(src_canny,circles,CV_HOUGH_GRADIENT,1,100,200,10,0,0);
    cout << "the circles size :"<<circles.size()<<endl;
#if 0
     CV_EXPORTS_W void HoughCircles( InputArray image, OutputArray circles,
                               int method, double dp, double minDist,
                               double param1=100, double param2=100,
                               int minRadius=0, int maxRadius=0 );
#endif 
     for(size_t i = 0; i < circles.size(); i++ )
     {
        Vec3f  circlesCenter;
        char str_lx[20];
         Point center(cvRound(circles[i][0]  + startPoint.x) ,cvRound(circles[i][1]  + startPoint.y));
         int radius = cvRound(circles[i][2]);
         circlesCenter[0] = cvRound(circles[i][0]  + startPoint.x);
         circlesCenter[1] = cvRound(circles[i][1]  + startPoint.y);
         circlesCenter[2] = cvRound(circles[i][2]);
         sprintf(str_lx,"C[%.2f,%.2f] R=%d",circlesCenter[0], circlesCenter[1] ,radius);
       putText(srcImage,str_lx,Point(circlesCenter[0], circlesCenter[1]),CV_FONT_HERSHEY_PLAIN,1,
             Scalar(0,255,0));
       
         circle(srcImage,center,2,Scalar(0,0,255),-1,8,1);       
         circle(srcImage,center,radius,Scalar(255,0,0),2,8,0);
         Findcircles.push_back(circlesCenter);
     }
     imshow("srcImage",srcImage);
     waitKey(0);
     
 }
void  marginGeometryClass::LSDFastGeomrtry()
{
    cout << "the LSD is opecv3.0 above ,but now is opencv2.4.8"<<endl;
    return ;
#if 0
    Mat srcImage = beforeImage.clone();
    CV_Assert(srcImage.data  != NULL);
    Canny(srcImage,srcImage,50,200,3);
#if 1
    Ptr<LineSegmentDetector> lsd = 
            createLineSegmentDetector(LSD_REFINE_NONE);   
#else
    Ptr<LineSegmentDetector> lsd = 
            createLineSegmentDetector(LSD_REFINE_NONE);
#endif
    double start = double (getTickCount());
    vector<Vec4f> vecLines;
    lsd ->detect(srcImage,vecLines);
    double times = (double(getTickCount())  - start ) * 1000 /
    getTickFrequency();
    cout <<"times: "<<times<<" ms "<<endl;
    Mat resLineMat(srcImage);
    lsd-> drawSegments(resLineMat,vecLines);
    imshow("resLineMat",resLineMat);
    waitKey(0);   
#endif     
}
void  marginGeometryClass::marginHoffGeomrtry()
{
    Mat srcImage = beforeImage.clone();
    CV_Assert(srcImage.data != NULL);
    Mat edgeMat,houghMat;
    Canny(srcImage,edgeMat,50,200,3);
    cvtColor(edgeMat,houghMat,CV_GRAY2BGR);
#if 0
    vector <Vec2f> lines;
    HoughLines(edgeMat,lines,1,CV_PI/180,100,0,0);
    for(size_t i = 0; i <lines.size(); i)
    {
        float rho = lines[i][0], theta = lines[i][1];
        Point pt1,pt2;
        double a = cos(theta) ,b = sin(theta);
        double x0 = a * rho ,y0 = b *rho;
        pt1.x = cvRound(x0 + 10 *(-b));
        pt1.y = cvRound(y0 + 10 * (a));
        pt2.x = cvRound(x0 - 10 *(-b));
        pt2.y = cvRound(y0 - 10 * (a));
        line(houghMat,pt1,pt2,Scalar(0,0,255),3,CV_AA);
              
    }
#else
    HoughLinesP(edgeMat,lines,1,CV_PI/180,50,50,10);
    for(size_t i = 0; i < lines.size() ; i++ )
    {
        Vec4i linePoint = lines[i];
        cout << "the line : "<< linePoint <<endl;
        line(srcImage,Point(linePoint[0],linePoint[1]),Point(linePoint[2],linePoint[3]),Scalar(0,0,255),3,CV_AA);
    }
#endif
    changeImage = srcImage.clone();
    imshow("changeImage",changeImage);
    imshow("srcImage",beforeImage);
    waitKey(0);
}
marginGeometryClass::marginGeometryClass(Mat &beforeImage) 
:beforeImage(beforeImage)
{
}

marginGeometryClass::~marginGeometryClass() {
   delete findLine;
   findLine = NULL;
   delete gerMouse;
   gerMouse = NULL;
}

