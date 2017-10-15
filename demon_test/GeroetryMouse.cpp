/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GeroetryMouse.cpp
 * Author: aqq
 * 
 * Created on 2017年4月25日, 下午2:13
 */

#include "GeroetryMouse.h"
Rect roiRect; //所选择的矩形
Point startPoint;
Point endPoint;
bool downFlag = false;
bool upFlag = false;
double thedownUp;
int ad;
 vector<Vec4f> lines;  
Mat srcImage1; //全局变量图像源
GeroetryMouse::GeroetryMouse() {
    
}
void FindCornerMouseEvent(int event, int x, int y, int flags, void* data)
{
    Vec4f lineCorner;
    if(event == EVENT_LBUTTONDOWN)
    {
                                   startPoint.x = x;
		startPoint.y = y;
                  Point centreup;
                  Point centredown;
                  centreup.x = startPoint.x ;
                  centreup.y = startPoint.y -5;
                  centredown.x = startPoint.x  ;
                  centredown.y = startPoint.y  +5;
                  line(srcImage1,centreup,centredown,Scalar(0,0,255),1);
                  centreup.x = startPoint.x  -5;
                  centreup.y = startPoint.y ;
                  centredown.x = startPoint.x  +5;
                  centredown.y = startPoint.y;
                  line(srcImage1,centreup,centredown,Scalar(0,0,255),1);
                  
                                   downFlag = true;
    }
    if(event == EVENT_RBUTTONDOWN)
    {
                                    endPoint.x = x;
                                    endPoint.y = y;
                                         Point centreup;
                  Point centredown;
                  centreup.x = endPoint.x ;
                  centreup.y = endPoint.y -5;
                  centredown.x = endPoint.x  ;
                  centredown.y = endPoint.y  +5;
                  line(srcImage1,centreup,centredown,Scalar(0,0,255),1);
                  centreup.x = endPoint.x  -5;
                  centreup.y = endPoint.y ;
                  centredown.x = endPoint.x  +5;
                  centredown.y = endPoint.y;
                  line(srcImage1,centreup,centredown,Scalar(0,0,255),1);
                       lineCorner[0] = startPoint.x;
                      lineCorner[1] = startPoint.y;
                      lineCorner[2] = endPoint.x;
                      lineCorner[3] = endPoint.y;
                      lines.push_back(lineCorner);
                                    upFlag = true;
    }
    if(event == EVENT_MBUTTONDOWN)
    {
        downFlag = false;
        upFlag = false;
    }
    if(downFlag == true  && upFlag   == true)
    {
#if 0
        Rect rectSlect;
        rectSlect.width = sqrt(pow(abs (endPoint.x - startPoint.x),2)  +pow(abs (endPoint.y - startPoint.y),2) );
        rectSlect.height = 5;
     line(srcImage1,startPoint,endPoint,Scalar(255,0,0),2);
     if(endPoint.x >=  startPoint.x)
     {
      rectSlect.x =abs (endPoint.x - startPoint.x) /2 + startPoint.x;
     }
     else
     {
     rectSlect.x = abs (endPoint.x - startPoint.x) /2 + endPoint.x;
     }
      if(endPoint.y >=  startPoint.y)
     {
      rectSlect.y = abs (endPoint.y - startPoint.y) /2 + startPoint.y;
     }
     else
     {
     rectSlect.y = abs (endPoint.y - startPoint.y) /2 + endPoint.y;
     }
     rectangle(srcImage1,rectSlect,Scalar(255,0,0),3,8,0);
#endif                 
     Point theLastPoint;
  
    line(srcImage1,startPoint,endPoint,Scalar(255,0,0),1);
     double sinAngle = (endPoint.x - startPoint.x) / (sqrt(pow(abs (endPoint.x - startPoint.x),2)  +pow(abs (endPoint.y - startPoint.y),2) ));
     double cosAngle =  (endPoint.y - startPoint.y) / (sqrt(pow(abs (endPoint.x - startPoint.x),2)  +pow(abs (endPoint.y - startPoint.y),2) ));
   //  cout << "qwe "<<sinAngle<<cosAngle<<endl;
     theLastPoint.x = endPoint.x +5*cosAngle;
     theLastPoint.y = endPoint.y +5 * sinAngle;
    rectangle(srcImage1,startPoint,endPoint,Scalar(0,255,0),1,1,0);
    }
  imshow("findCornerImage",srcImage1);
	waitKey(0);
	return;
}
void MouseEvent(int event, int x, int y, int flags, void* data)
{
    Mat dst;
    if(event == EVENT_LBUTTONDBLCLK)
    {
       ad++;
       pyrUp(srcImage1,dst,Size(srcImage1.cols *2 , srcImage1.rows * 2));
       thedownUp = pow(2,ad);
       
          cout <<"thedown"<<thedownUp<<endl;
       srcImage1 = dst.clone();
      if(!srcImage1.data)
       {
            cout << "the image data is wrong"<<endl;
            return;
        }
    }
    
    if(event == EVENT_RBUTTONDBLCLK)
    {     
        ad--;
        pyrDown(srcImage1,dst,Size(srcImage1.cols  /2 , srcImage1.rows  /2));
      thedownUp = pow(2,ad);
           cout <<"theup"<<thedownUp<<endl;
        srcImage1 = dst.clone();
       if(!srcImage1.data)
       {
            cout << "the image data is wrong"<<endl;
           return;
       }
    }
    
	if (event == EVENT_LBUTTONDOWN)
	{
		downFlag = true;
		startPoint.x = x;
		startPoint.y = y;
                 circle(srcImage1,startPoint,0.5,Scalar(255,255,0),1); 
	}     
	if (event == EVENT_LBUTTONUP)
	{
		upFlag = true;
		endPoint.x = x;
		endPoint.y = y;
                 circle(srcImage1,endPoint,0.5,Scalar(255,255,0),1); 
	}
	if (downFlag == true && upFlag == false)
	{
		Point tempPoint;
		tempPoint.x = x;
		tempPoint.y = y;
               circle(srcImage1,tempPoint,0.5,Scalar(255,255,0),1); 
	}
	if (downFlag == true && upFlag == true)
	{
		//获取选择区域的ROI
		roiRect.width = abs(startPoint.x - endPoint.x);
		roiRect.height = abs(startPoint.y - endPoint.y);
		roiRect.x = min(startPoint.x, endPoint.x);
		roiRect.y = min(startPoint.y, endPoint.y);
		Mat roiMat(srcImage1, roiRect);
                          //          imshow("RsdOI", roiMat);
		downFlag = false;
		upFlag = false;  
                  rectangle(srcImage1,startPoint,endPoint,Scalar(255,0,0),1,1,0);
                  Point centreup;
                  Point centredown;
                  centreup.x = (startPoint.x + endPoint.x) /2 ;
                  centreup.y = (startPoint.y + endPoint.y) /2 -10;
                  centredown.x = (startPoint.x + endPoint.x) /2 ;
                  centredown.y = (startPoint.y + endPoint.y) /2 +10;
                  line(srcImage1,centreup,centredown,Scalar(0,0,255),1);
                  centreup.x = (startPoint.x + endPoint.x) /2 -10 ;
                  centreup.y = (startPoint.y + endPoint.y) /2 ;
                  centredown.x = (startPoint.x + endPoint.x) /2 +10;
                  centredown.y = (startPoint.y + endPoint.y) /2 ;
                  line(srcImage1,centreup,centredown,Scalar(0,0,255),1);
                   startPoint.x = startPoint.x  / thedownUp;
                 startPoint.y = startPoint.y  / thedownUp;
                 endPoint.x = endPoint.x    / thedownUp;
                 endPoint.y = endPoint.y  / thedownUp;
           //     imwrite("roiMat.png",roiMat);
	}
    
        imshow("image",srcImage1);
	waitKey(0);
	return;
}
GeroetryMouse::GeroetryMouse(Mat & image)
:image(image)
{
}
void GeroetryMouse::CornerGetPoint()
{
    namedWindow("findCornerImage");
   srcImage1 = image.clone();
   if(!srcImage1.data)
   {
       cout << "the image data is wrong"<<endl;
       return;
   }
 setMouseCallback("findCornerImage", FindCornerMouseEvent, 0); //根据鼠标获取感兴趣的区域 

   waitKey(0);
  // cout <<lines<<endl;
   linescorner = lines;
  vector<Vec4f> ::iterator it;
    Point startPoint;
     Point endPoint;
     for( it = linescorner.begin();  it != linescorner.end() ; it++)
     {
         startPoint.x = (*it)[0];
         startPoint.y = (*it)[1];
         endPoint.x = (*it)[2];
         endPoint.y = (*it)[3];
          cout << "lines"<<startPoint.x<<startPoint.y<<endPoint.x <<endPoint.y<<endl;
     }
    
}
vector<Vec4f> GeroetryMouse::getLinesCorner()
{
    return linescorner;
}
void GeroetryMouse::LineGetStartEndPoint()
{
    thedownUp = 1;
   namedWindow("image");
   srcImage1 = image.clone();
   if(!srcImage1.data)
   {
       cout << "the image data is wrong"<<endl;
       return;
   }
   setMouseCallback("image", MouseEvent, 0); //根据鼠标获取感兴趣的区域 
   waitKey(0);
    cout <<"thedownUp"<< thedownUp<<endl;
      GerStartPoint.x = startPoint.x;
      GerStartPoint.y = startPoint.y;
      GerEndPoint.x = endPoint.x;
      GerEndPoint.y = endPoint.y;
      cout << "1"<<startPoint<<endPoint<<endl;
      cout <<"2"<<GerStartPoint<<GerEndPoint<<endl;
}
GeroetryMouse::~GeroetryMouse() {
}
Point GeroetryMouse::getStartPoint()
{
    return GerStartPoint;
}
Point GeroetryMouse::getEndPoint()
{
      return GerEndPoint;
}
