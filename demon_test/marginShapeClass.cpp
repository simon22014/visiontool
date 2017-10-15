/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   marginShapeClass.cpp
 * Author: aqq
 * 
 * Created on 2017年4月28日, 下午2:49
 */

#include "marginShapeClass.h"
Mat srcImage,srcGray;
int thresh = 100;
int max_thresh = 255;
RNG rng(12345);
void thresh_callback(int,void*)
{
    Mat srcTemp = srcImage.clone();
    Mat threMat;
       cout <<"2"<<endl;
    vector<vector<Point > >contours;
    vector<Vec4i> hierarchy;
    
    threshold(srcGray,threMat,thresh,255,THRESH_BINARY);
       cout <<"3"<<endl;
    findContours(threMat,contours,hierarchy,CV_RETR_TREE,CV_CHAIN_APPROX_SIMPLE,Point(0,0));
    
    vector<vector<Point> > pointHull(contours.size());
    vector<vector<int> > intHull(contours.size());
    vector<vector<Vec4i> > hullDefect(contours.size());
       cout <<"4"<<endl;
       cout << contours.size()<<endl;
       if(contours.size()  != 14)
       {
           return;
       }
    for(size_t i = 0; i < contours.size() ; i++)
    {
        convexHull (Mat(contours[i]),pointHull[i] ,false);
        convexHull (Mat(contours[i]),intHull[i],false);
        convexityDefects(Mat(contours[i]),intHull[i],hullDefect[i]);
         
    }
          cout <<"5"<<endl;
    Mat drawing = Mat::zeros(threMat.size(),CV_8UC3);
    for(size_t i = 0; i < contours.size(); i++)
    {
        Scalar color = Scalar(rng.uniform(0,255),rng.uniform(0,255),rng.uniform(0,255));
        drawContours(drawing,contours,i,color,1,8,vector<Vec4i> () ,0, Point());
        
        drawContours(drawing,pointHull,i,color,1,8,vector<Vec4i> () ,0, Point());
           cout <<"6"<<endl;
        size_t count = contours[i].size();
        if(count < 300)
        {
            continue;
        }
        vector<Vec4i>::iterator iterDefects = hullDefect[i].begin();
           cout <<"9"<<endl;
        while(iterDefects  != hullDefect[i].end() )
        {
            Vec4i  &v = (*iterDefects);
            
            int startidx = v[0];
            Point ptStart(contours[i][startidx]);
            
            int endidx = v[1];
            Point ptEnd(contours[i][endidx]);
            
            int faridx = v[2];
            Point ptFar(contours[i][faridx]);
            int depth = v[3] /256;
               cout <<"7"<<endl;
            if(depth > 20 && depth < 80)
            {
                line (drawing,ptStart,ptFar,CV_RGB(0,255,0),2);
                line (drawing,ptEnd,ptFar,CV_RGB(0,255,0),2);
                circle(drawing,ptStart,4,Scalar(255,0,100),2);
                circle(drawing,ptEnd,4,Scalar(255,0,100),2);
                circle(drawing,ptFar,4,Scalar(100,0,255),2);                  
            }
                  cout <<"8"<<endl;
            iterDefects ++;      
        }
    }
    imshow("the result ",drawing);

}
void  marginShapeClass::outlineFrontierTest()
{
    Mat  img (500,500,CV_8UC3);
    RNG &rng = theRNG();
    for(;;)
    {
        int  count = rng.uniform(1,101);
        vector<Point> points;
        for(int i = 0; i < count ;i ++)
        {
            Point pt;
            pt.x = rng.uniform(img.cols / 4,img.cols*3 /4);
            pt.y = rng.uniform(img.rows / 4,img.rows * 3 /4);
            points.push_back(pt);
            
        }
        RotatedRect box = minAreaRect(Mat(points));
        Point2f center,vtx[4];
        float radius = 0;
        
        minEnclosingCircle(Mat(points),center,radius);
       box.points(vtx);
        img = Scalar::all(0);
        
        for(int i = 0; i < count ; i++)
        {
            circle(img,points[i],3,Scalar(0,0,255),CV_FILLED,CV_AA);
        }
        for(int i = 0; i < 4 ; i++)
        {
            line(img,vtx[i],vtx[( i +1 ) % 4],Scalar(0,255,0),1,CV_AA);
        }
        circle(img,center,cvRound(radius),Scalar(0,255,255),1,CV_AA);
        imshow("retc & circle",img);
        waitKey(0);
    }
}
void marginShapeClass::cacBounding(Mat &src)
{
    RNG rng(12345);
    Mat threMat;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    threshold(src,threMat,120,255,THRESH_BINARY);
    imshow("threMat",threMat);
    
    findContours(threMat,contours,hierarchy,CV_RETR_TREE,CV_CHAIN_APPROX_SIMPLE,Point(0,0));
    vector<vector<Point> > conPoint (contours.size());
    vector<Rect> boundRect(contours.size());
    vector<Point2f>center (contours.size());
    vector<float>radius(contours.size());
    for(int i = 0; i < contours.size();i++)
    {
        approxPolyDP(Mat(contours[i]),conPoint[i],3,true);
        boundRect[i] = boundingRect(Mat(conPoint[i]));
        minEnclosingCircle(conPoint[i],center[i],radius[i]);
        
    }
    Mat resultMat = Mat:: zeros(threMat.size(),CV_8UC3);
    for(int i = 0; i < contours.size(); i++)
    {
        Scalar color = Scalar(rng.uniform(0,255),
        rng.uniform(0,255),rng.uniform(0,255));
        drawContours(resultMat,conPoint,i,color,1,8,vector<Vec4i> (),0,Point());
        rectangle(resultMat,boundRect[i].tl(),boundRect[i].br(),color,2,8,0);
        circle(resultMat,center[i],(int)radius[i],color,2,8,0);       
    }
    imshow("boundRectResult",resultMat);
    changeImage = resultMat.clone();
}
void marginShapeClass::cacBoundRectRandomDirection(Mat & src)
{
    RNG rng(12345);
    Mat threMat;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    cout<< "1"<<endl;
    threshold(src,threMat,120,255,THRESH_BINARY);
    findContours(threMat,contours,hierarchy,CV_RETR_TREE,CV_CHAIN_APPROX_SIMPLE,Point(0,0));
    vector<RotatedRect>minRect(contours.size());
    vector<RotatedRect>minEllipse (contours.size());
      cout<< "2"<<endl;
    for(int i = 0 ; i < contours.size(); i++)
    {
        minRect[i] = minAreaRect(Mat(contours[i]));
        
        if(contours[i].size()  > 5)
        {
            minEllipse[i]  = fitEllipse(Mat(contours[i]));
        } 
    }
    Mat resultMat =  Mat::zeros(threMat.size(),CV_8UC3);
    for(int i = 0 ; i < contours.size(); i++)
    {
        Scalar color = Scalar(rng.uniform(0,255),
                rng.uniform(0,255),rng.uniform(0,255));
        drawContours(resultMat,contours,i,color,1,8,vector<Vec4i>() ,0, Point());
        ellipse(resultMat,minEllipse[i],color,2,8);
        Point2f rect_points[4];
        minRect[i].points(rect_points);
        for(int j = 0 ; j< 4; j++)
        {
            line(resultMat,rect_points[j],rect_points[(j+1) %4],color,1,8);
        }
        imshow("rsultImage",resultMat);      
    }


}
 void  marginShapeClass::outlineMu()
 {
     Mat src = beforeImage.clone();
     if(!src.data)
     {
         cout<<"the image data is wrong"<<endl;
         return;
     }
     Mat srcGray;
     vector<vector<Point> > contours;
     vector<Vec4i> hiearachy;
     GaussianBlur(src,src,Size(3,3),0.1,0,BORDER_DEFAULT);
       cout<< "1"<<endl;
     cvtColor(src,srcGray,CV_RGB2GRAY);
     findContours(srcGray,contours,hiearachy,CV_RETR_TREE,CV_CHAIN_APPROX_SIMPLE,Point(0,0));
     //drawContours(src,contours,-1,cvScalar(0,0,255);
     printf("Number of contours: %d \n",(int)contours.size());
     vector<Moments> mu(contours.size());
     for(int i = 0; i < (int)contours.size(); i++)
     {
         mu[i] = moments(contours[i],false);
     }
       cout << (int)contours.size()<<endl;
     for(int i = 0; i < (int)contours.size();i++)
     {
         float area = mu[i].m00;
         int cx = mu[i].m10 / mu[i].m00;
         int cy = mu[i].m01 / mu[i].m00;
         int perimeter = arcLength(contours.at(i),true);
         
         cout <<"area"<<area<<endl;
         char pChar[100];
         sprintf(pChar,"ori:%f",area);
         putText(src,pChar,Point(cx,cy),FONT_HERSHEY_SIMPLEX,0.4,cvScalar(255)); 
                   circle(srcImage,Point(cx,cy),2,Scalar(0,0,255),-1,8,1);       
         
     }
     imshow("result",src);
     waitKey(0);
  
 }
void marginShapeClass::outlineFrontierContours()
{
    Mat srcImage = beforeImage.clone();
    if(!srcImage.data)
    {
        cout << "the image data is NULL"<<endl;
        return ;
    }
    Mat srcGray,blurMat;
    cvtColor(srcImage,srcGray,CV_BGR2GRAY);
    blur(srcGray,blurMat,Size(3,3));
    
   // imshow("blurMat",blurMat);
    cacBoundRectRandomDirection(blurMat);
    
 //   cacBounding(blurMat);
    imshow("srcImage",srcImage);
    waitKey(0);
       
}
void marginShapeClass::outlineDetection()
{
   
    srcImage = beforeImage.clone();
    CV_Assert(srcImage.data != NULL);
    cvtColor(srcImage,srcGray,CV_BGR2GRAY);
    blur(srcGray,srcGray,Size(3,3));
    namedWindow("Source",CV_WINDOW_AUTOSIZE);
    imshow("Source",srcImage);
    cout <<"1"<<endl;
  //  createTrackbar("Threshold","Source",&thresh,max_thresh,thresh_callback);
    thresh_callback(0,0);
    waitKey(0);
    return ;

}

marginShapeClass::marginShapeClass() {
}

marginShapeClass::marginShapeClass(Mat & beforeImage) 
:beforeImage(beforeImage)
{
}
void marginShapeClass::marginShapeType()
{
    cout << "0:outline,1:outline frontier,2:outline Mu"<<endl;
    int choiceNum;
    cin >> choiceNum;
    switch(choiceNum)
    {
        case OUTLINEDETECTION:
            outlineDetection();
            break;
        case  OUTLINEFRONTIER:
        //    outlineFrontierTest();
            outlineFrontierContours();
            break;
        case OUTLINEMU:
    //        outlineMu();
            cout<<"the mu is not well"<<endl;
            break;
        default:
            break;

    }

}

marginShapeClass::~marginShapeClass() {
}

