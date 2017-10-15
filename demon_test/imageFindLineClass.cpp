/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 0
 * File:   imageFindLineClass.cpp
 * Author: aqq
 * 
 * Created on 2017年4月19日, 上午9:32
 */

#include "imageFindLineClass.h"
#include"opencv/cxcore.hpp"
    int bestPos;
imageFindLineClass::imageFindLineClass() {
}

imageFindLineClass::    imageFindLineClass(Point startPoint,Point endPoint,Mat &beforeImage)
:startPoint(startPoint),endPoint(endPoint),beforeImage(beforeImage)
{
    Mat craveMat((endPoint.x-startPoint.x),(endPoint.y-startPoint.y),beforeImage.type());
    beforeImage(Rect(startPoint.x,startPoint.y,(endPoint.x-startPoint.x),(endPoint.y-startPoint.y))).copyTo(craveMat);
    craveImage = craveMat.clone();

 // locationCImage = new locationChangeClass(craveImage);

 //      dimDW = new dimDealWitch(craveImage);
   

}
Mat &imageFindLineClass:: getCraveImage()
{
       return craveImage;
}
   void onChangeTrackBarx(int sizeTrackBarx,void* data )
   {   

       Vec3b vecTemp;
              Mat imae = (*(Mat*)(data));      
       Mat srcImage =  imae.clone();
     locationChangeClass* locationCImage = new locationChangeClass(srcImage);    
      double kx ;
    double ky ;
    kx = sizeTrackBarx;
    ky = sizeTrackBarx;
 
    //get the image resolution
    int nRows = cvRound(srcImage.rows *kx);
    int nCols = cvRound(srcImage.cols * ky);
    Mat resultImage(nRows,nCols,srcImage.type());
    int leftRowCoordinate = 0;
    int leftColCoordinate = 0;
   cout <<"Nrows"<<nRows<<"Ncols" <<nCols <<endl;
    for (int i = 0; i < nRows ; i++)
    {
        int x = static_cast<int>((i + 1) / kx + 0.5) - 1;
        for(int j = 0 ; j < nCols ; j++)
        {  
            int y = static_cast<int>((j +1) /ky +0.5) -1;
                    locationCImage->areaAverage(Point_<int>(leftRowCoordinate,leftColCoordinate),
                    Point_<int>(x,y),vecTemp);
                       resultImage.at<Vec3b>(i,j) = vecTemp;
                   
            leftColCoordinate = y + 1;
        }
            leftColCoordinate = 0;
            leftRowCoordinate = x+1;
    
    }  
       cout << "nRodfdsws"<<endl;
    imshow("craveImage",resultImage);
           
   }
#if 0
     void onChangeTrackBary(int sizeTrackBary,void* data )
   {
    
      Mat srcImage =  *(Mat*)(data);
 
   }
#endif 
  void onChangeTrackBar(int pos ,void* data)
  {
      Mat canny_output;
      Mat srcImage =  *(Mat*)(data);
     Canny(srcImage,canny_output,pos,pos*3,3);
     bestPos = pos;
       cout << "pos"<<pos<<endl;
     imshow("craveImage",canny_output);
     
  }
  
   int imageFindLineClass::getBestCannyPos()
   {
       return bestCannyPos;
   }
   
imageFindLineClass::~imageFindLineClass() {
    
     //    delete locationCImage;
     //    locationCImage = NULL;
     //    delete maegin;
     //    maegin = NULL;
   //      delete dimDW;
   //      dimDW = NULL;
}
 void imageFindLineClass::imageEnlarge()
 {
#if 0
 //  Mat image =  locationCImage->getTheChangeMat();
      int thresh = 30;
     Mat canny_output;
     Mat image_before = beforeImage.clone(); 
     Mat image_argy;
     cvtColor(image_before,image_argy,CV_BGR2GRAY);
     blur(image_argy,image_argy,Size(3,3));
     Canny(image_argy,canny_output,thresh,thresh*3,3);
     namedWindow("canny");
     imshow("canny", canny_output);
     waitKey(0);
#endif 
     
     if( !craveImage.data)
     {
         cout << "the data creaeImage is noting"<<endl;
         return;
     }
     int poiTrackBar = 100;
     int sizeTrackBarx = 1;
  //    int sizeTrackBary = 0;
     Mat canny_output;
     Mat image_before = craveImage.clone(); 
     Mat image_argy;
     cvtColor(image_before,image_argy,CV_BGR2GRAY);
     blur(image_argy,image_argy,Size(3,3));
     imshow("image_argy",image_argy);
     namedWindow("craveImage");
       createTrackbar ("canny","craveImage",&poiTrackBar,250,  
                   onChangeTrackBar ,&image_argy); 
   //    createTrackbar ("sizex","craveImage",&sizeTrackBarx,20,  
      //             onChangeTrackBarx ,&image_argy); 
         onChangeTrackBar(poiTrackBar,(void*)&image_argy );//轨迹条回调函数  
   //      onChangeTrackBarx(sizeTrackBarx,(void*)&image_argy );
     //     onChangeTrackBary(sizeTrackBary,(void*)&image_argy );
   //      cout << "poiTrackBar"<<endl;
      waitKey(0);
      if(bestPos == 0)
      {
          bestCannyPos = poiTrackBar;
      }
      else
      {
     bestCannyPos = bestPos;
      }
     cout <<"bestCannyPos"<<bestCannyPos<<endl;
 }
 void imageFindLineClass::imageOther()
 {
#if 0
  Mat imageGray;
     Mat contours;

      cvtColor(craveImage,imageGray,CV_BGR2GRAY);
           Mat testMat(craveImage.rows,1,craveImage.type());
     vector<Mat> testMatCols;
           blur(imageGray,imageGray,Size(3,3));
     Canny(imageGray,contours,bestCannyPos,bestCannyPos*3,3);
     //以灰度模式载入图像并显示
     for(int i = 0 ;i < contours.rows;i++)         
     {
      int* pt = contours.ptr<int>(i);
      for(int j = 0;j <contours.cols;j++)
      {
          testMat.ptr<int> 
      }
     }
           
#endif         

 }
 void imageFindLineClass::imageSobel()
 {
     Mat imageGray;
     Mat contours;
      cvtColor(craveImage,imageGray,CV_BGR2GRAY);
           blur(imageGray,imageGray,Size(3,3));
     Canny(imageGray,contours,bestCannyPos,bestCannyPos*3,3);
     //以灰度模式载入图像并显示
	Mat cornerStrength;  
	cornerHarris(contours, cornerStrength, 2, 3, 0.01);

	//对灰度图进行阈值操作，得到二值图并显示  
	Mat harrisCorner;  
	threshold(cornerStrength, harrisCorner, 0.00001, 255, THRESH_BINARY);  
                  imshow("craveImage",craveImage);
	imshow("角点检测后的二值效果图", harrisCorner);  
        
         for(int i = 0;i < harrisCorner.cols;i++)
     {
         int* pt = harrisCorner.ptr<int>(i);
         for(int j =0;j < harrisCorner.rows;j++)
         {
             if(pt[j]   != 0)
             {
             Point pt1;
             pt1.x = j;
             pt1.y = i;
                 circle(imageGray,pt1,1,Scalar(255,255,0),1); 
              }
         }
         }
  //      imshow("craveImage",craveImage);
        imshow("角点效果图gray", imageGray);  
        imshow("contours",contours);
//line(image,pt1,pt2,Scalar(0,0,255),1); //  线条宽度设置为2 
       //      circle(image,pt1,2,Scalar(0,255,0),1); 
       //       circle(image,pt2,2,Scalar(255,0,0),1);                      
	waitKey(0);  
        return;
 }
  void imageFindLineClass:: DrawLine(Mat & cannyOut)
  {
      Point pt1;
      Point pt2;
      Point pt3;
      Point pt4;
      for(int i = 0 ;i < 11;i++)
      {
            pt1.x = 0;
      pt1.y = ((craveImage.rows  *2) /10)*i;
      pt2.x = craveImage.cols *2 -(( craveImage.cols *2)/10)*i ;
       pt2.y = craveImage.rows  *2;
        line(cannyOut,pt1,pt2, Scalar(255,0,0), 1, 1,1);
    pt3.x = ((craveImage.cols *2) /10) *i;
    pt3.y =0;
    pt4.y = craveImage.rows  *2 - (( craveImage.rows  *2)/10)*i;
    pt4.x = craveImage.cols *2;
     line(cannyOut,pt3,pt4, Scalar(255,0,0), 1, 1,1);
      }
  }
 void imageFindLineClass::imageMargin()
 {
#if 0
     //      Mat imageGray;
       Mat image = craveImage.clone();
          vector<vector<Point> > contours; 
             Mat contoursImage; 
             Mat imageGray;
// cvtColor(image,imageGray,CV_BGR2GRAY); 
      cvtColor(image,imageGray,CV_BGR2GRAY);
     blur(imageGray,imageGray,Size(3,3));
     Canny(imageGray,contoursImage,bestCannyPos,bestCannyPos*3,3);
     cout << "bestCann"<<bestCannyPos<<endl;
  //  threshold(contoursImage,contoursImage,0,255,THRESH_BINARY); 
     imshow("contoursImage",contoursImage);
     
    
     // find 
     findContours(contoursImage,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE); 
    // draw 
     Mat result(imageGray.size(),CV_8U,Scalar(0)); 
     drawContours(imageGray,contours,-1,Scalar(255),1); 
            
     namedWindow("contours"); 
     imshow("contours",imageGray); 
     waitKey(0); 
     return ; 
#endif   
#if 0
     Mat image = craveImage.clone();
     Mat src_gray;
    // cvtColor(image,src_gray,CV_BGR2GRAY);
  //  blur(src_gray,src_gray,Size(3,3));
//  
    imshow("gray",src_gray);
    Mat cannyOut; 
    Point po;
   Canny(image,cannyOut,bestCannyPos,bestCannyPos*3,3);
    cvtColor(cannyOut,src_gray,CV_BGR2GRAY);
    cout <<"cannles"<< cannyOut.channels() <<endl;
#if 0
    for(int i = 0;i < cannyOut.rows;i++)
    {
        int* pt = cannyOut.ptr<int>(i);
        for(int j =0;j < cannyOut.cols;j++)
        {
            if(pt[j]  > bestCannyPos*3)
            {
                pt[j] = 255;
    //         circle(craveImage,po,0.4,Scalar(255,0,0),1); 
            }
            else
            {
                pt[j] = 0;
            }

        }
    }
#endif 
 //  DrawLine(cannyOut);   
  
    vector<Vec2f> lines;
    HoughLines(cannyOut,lines,1,CV_PI/180,150,0,0);
    
    for(size_t i = 0;i < lines.size();i++)
    {
        float rho = lines[i][0],theta = lines[i][1];
        Point pt1,pt2;
        double a = cos(theta),b = sin(theta);
        double x0 = a*rho,y0 =b*rho;
        pt1.x = cvRound(x0 + 1000*(-b));
      pt1.y= cvRound(y0 + 1000*(a));
        pt2.x = cvRound(x0 + 1000*(-b));
          pt2.y = cvRound(y0 + 1000*(a));
          line(image,pt1,pt2,Scalar(205,12,31),1,CV_AA);
          
    }
    
    imshow("can",cannyOut);
    imshow("craveImage",image);
    waitKey(0); 

    

	RNG rng(12345);
	Mat src_gray;
	cvtColor(craveImage, src_gray, CV_BGR2GRAY);//灰度化  

										 //	GaussianBlur(src_gray, src_gray, Size(3, 3), 0.1, 0, BORDER_DEFAULT);
	blur(src_gray, src_gray, Size(3, 3)); //滤波  
	namedWindow("image", CV_WINDOW_AUTOSIZE);
	imshow("image", craveImage);
	moveWindow("image", 20, 20);
	//定义Canny边缘检测图像  
	Mat canny_output;


	vector<vector<Point> > tenplate;


	vector<Vec4i> hierarchy;
	//利用canny算法检测边缘  
	hierarchy.reserve(100000);
	Canny(src_gray, canny_output, bestCannyPos, bestCannyPos * 3, 3);
	namedWindow("canny", CV_WINDOW_AUTOSIZE);
	imshow("canny", canny_output);
	moveWindow("canny", 550, 20);
	//查找轮廓  
	findContours(canny_output, tenplate, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	//计算轮廓矩  
	vector<Moments> mu(tenplate.size());
	for (int i = 0; i < tenplate.size(); i++)
	{
		mu[i] = moments(tenplate[i], false);
	}
	//计算轮廓的质心  
	vector<Point2f> mc(tenplate.size());
	for (int i = 0; i < tenplate.size(); i++)
	{
		mc[i] = Point2d(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);
	}

	//画轮廓及其质心并显示  
	Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
	printf("\t\t 几何特性\n");

	for (int i = 0; i< tenplate.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(drawing, tenplate, i, color, 2, 8, hierarchy, 0, Point());

	//	circle(drawing, mc[i],5, color, -1, 2, 0);
	//	rectangle(drawing, boundingRect(tenplate.at(i)), cvScalar(0, 255, 0));
	//	printf("目标%d - 面积：%.2f - 周长: %.2f \n", i, mu[i].m00, contourArea(tenplate[i]), arcLength(tenplate[i]));


	}
	cout << "contours.size() = " << tenplate.size() << endl;
	imshow("Contours", drawing);
        waitKey(0);
	return;
#endif 
        Mat imageGray;
        Mat image = craveImage.clone();                      
    Mat contours; 
        Mat dst ;
      cvtColor(image,imageGray,CV_BGR2GRAY);
     blur(imageGray,imageGray,Size(3,3));
     Canny(imageGray,contours,bestCannyPos,bestCannyPos*3,3);
#if 0
 dst = Scalar::all(0);
     imageGray.copyTo(dst,contours);
//     threshold(dst,dst,10,255,THRESH_BINARY);
     for(int i = 0;i < dst.cols;i++)
     {
  //       int* pt = dst.ptr<int>(i);
         for(int j =0;j < dst.rows;j++)
         {
 //            cout << "the pointdst" <<pt[j] <<endl; 
                cout << "the pointdst" <<*(dst.ptr<int>(i,j)) <<endl;
              if(*(dst.ptr<int>(i,j))  >= 255)
              {
                  *(dst.ptr<int>(i,j))  = 255;
                  Point pi;
                  pi.x = i;
                  pi.y = j;
                  circle(dst,pi,2,Scalar(0,255,0),2); 
                  
              }
                
         }
     }
     
     imshow("dst",dst);
     
#endif   
 //   vector<Vec4i> lines; 
    // 检测直线，最小投票为90，线条不短于50，间隙不小于10 
 //   HoughLinesP(contours,lines,1,CV_PI/180,8,1,5); 
      HoughLinesP(contours,lines,1,CV_PI/180,8,5,5); 
    {
           // 将检测到的直线在图上画出来 
     float mun;
          float max;
          vector<Vec4i>::const_iterator postion;
          int table =0;
        vector<Vec4i>::const_iterator it=lines.begin();
        Point pt1((*it)[0],(*it)[1]); 
        Point pt2((*it)[2],(*it)[3]);
            float abs_nm = abs(abs (pt2.x -pt1.x)*abs(pt2.x -pt1.x) - abs(abs(pt2.y -pt1.y)*abs(pt2.y -pt1.y)) );
                mun =      cvSqrt(abs_nm);
        while(it!=lines.end()) 
        { 
                   pt1.x = (*it)[0];
           pt1.y = (*it)[1];
              pt2.x = (*it)[3];
            pt2.y = (*it)[4];
   
           Point pt1((*it)[0],(*it)[1]); 
           Point pt2((*it)[2],(*it)[3]);
         //      float abs_num = abs(abs(pt2.y -pt1.y)*abs(pt2.y -pt1.y) -  abs(abs (pt2.x -pt1.x)*abs(pt2.x -pt1.x)));
             float abs_num = abs(abs (pt2.x -pt1.x)*abs(pt2.x -pt1.x) - abs(abs(pt2.y -pt1.y)*abs(pt2.y -pt1.y)) );
                 max =      cvSqrt(abs_num);
                 
             if(mun >=  max)
              {
               mun = max;
                     cout <<"max"<<mun <<endl;
                  postion = it;
              }
            else
           {
        postion = it;
           cout <<"max"<<mun <<endl;
          }
            cout << "pt1.x"<<pt1.x<<"pt1.y"<<pt1.y<<endl;
            cout << "pt2.x"<<pt2.x<<"pt2.y"<<pt2.y<<endl;
            
         line(image,pt1,pt2,Scalar(0,0,255),1); //  线条宽度设置为2 
             circle(image,pt1,2,Scalar(0,255,0),1); 
              circle(image,pt2,2,Scalar(255,0,0),1); 
            ++it; 
     table++;
        //    cout << "it" << it<<endl;
        } 
                cout <<"table"<<table<<endl;
       Point pt3((*(it))[0],(*(it))[1]); 
       Point pt4((*(it))[2],(*(it))[3]);
      line(image,pt3,pt4,Scalar(255,255,0),2); //  线条宽度设置为2 
    }
      DrawLine(image);
      
    namedWindow("Lines"); 
    imshow("Lines",image); 
   imshow("image",contours);
    waitKey(0); 
    return ; 

 }
 void imageFindLineClass:: imageOutLine()
 {

   Mat imageGray;
   Mat image=craveImage.clone();
   cvtColor(image,image,CV_BGR2GRAY); 
   blur(image,imageGray,Size(3,3));
    Canny(imageGray,image,bestCannyPos,bestCannyPos*3,3);
#if 0 
    Mat image;
     dimDW-> dimDealWithType(); 
    maegin = new marginFunctorClass(dimDW->returnImage());
     maegin -> marginChoice();
     image = maegin->returnImage();
#endif
     vector<vector<Point> > contours; 
     // find 
     findContours(image,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE); 
    // draw 
 //    Mat result(image.size(),CV_8U,Scalar(0)); 
  //   cout<<"size"<<contours.size()<<endl;
 //    drawContours(craveImage,contours,-1,Scalar(255),2); 
      vector<vector<Point> >::iterator it;
      vector<Point>::iterator is;
      Point thefirst;
      Vec4f line_para;   
      for(it = contours.begin();it != contours.end();it++)
      {
            bool thepoint = false;
                  for(is = (*it).begin();is != (*it).end();is++)
                  {
                      if(!thepoint)
                      {
                          thefirst.x = (*is).x  +startPoint.x ;
                          thefirst.y = (*is).y  + startPoint.y;
                          thepoint = true;
                      }
                      else
                      {
                             Point circleP;
                              circleP.x = (*is).x + startPoint.x;
                              circleP.y = (*is).y + startPoint.y;
                      line(beforeImage,thefirst,circleP,Scalar(0,255,0),1); //  线条宽度设置为2 
                         thefirst.x = circleP.x;
                         thefirst.y =  circleP.y ;
                      }
                      Point circlePoint;
                      circlePoint.x = (*is).x + startPoint.x;
                      circlePoint.y = (*is).y + startPoint.y;
                       circle(beforeImage,circlePoint,1,Scalar(255,0,0),2); 
                  }
               fitLine((*it), line_para, CV_DIST_HUBER , 0, 0.01, 0.01);  

//std::cout << "line_para = " << line_para << std::endl;  
//获取点斜式的点和斜率  
Point point0;  
point0.x = line_para[2];  
point0.y = line_para[3];  
double k = line_para[1]*1.0/ line_para[0];  
   //cout << "poi"<< line_para[1]<< " "<< line_para[0]<<endl;
//计算直线的端点(y = k(x - x0) + y0)  
cv::Point point1, point2;  
point1.x = 0 + startPoint.x;  
point1.y = k * (0 - point0.x) + point0.y   +startPoint.y;  
point2.x = 200 + startPoint.x;  
point2.y = k * (200 - point0.x) + point0.y  + startPoint.y;  
#if 0
cv::Point point1, point2;  
point1.x = line_para[0] + startPoint.x;
point1.y = line_para[1] + startPoint.y;
point2.x = line_para[2] + startPoint.x;
point2.y = line_para[3] + startPoint.y;
#endif 
if((line_para[0]  > -0.0001) && (line_para[0]  < 0.0001))
{
  //     Point point3 , point4;  
       point1.x = line_para[2] + startPoint.x;
       point1.y = line_para[3] + startPoint.y;
       point2.x = point1.x;
       point2.y = point1.y + 200;
        lineStartPoint = point1;
        lineEndPoint  = point2;
cv::line(beforeImage, point1, point2, cv::Scalar(0, 0, 255), 1, 8, 0);  
}
else
{
      lineStartPoint = point1;
      lineEndPoint  = point2;
cv::line(beforeImage, point1, point2, cv::Scalar(0, 0, 255), 1, 8, 0);  
}
cout<<"point1:"<<point1 <<"  point2:"<<point2<<endl;
                  Point centreup;
                  Point centredown;
                  centreup.x = point1.x ;
                  centreup.y = point1.y -10;
                  centredown.x = point1.x  ;
                  centredown.y = point1.y  +10;
                  line(beforeImage,centreup,centredown,Scalar(0,255,0),1);
                  centreup.x =point1.x  -10 ;
                  centreup.y = point1.y  ;
                  centredown.x = point1.x +10;
                  centredown.y = point1.y  ;
              
                  line(beforeImage,centreup,centredown,Scalar(0,255,0),1);
                  
      }
 //    DrawLine(craveImage);          
      cout << "as"<<lineStartPoint<<lineEndPoint<<endl;
     namedWindow("contours"); 
     imshow("craveImage",craveImage);
     imshow("contours",beforeImage); 
     waitKey(0); 
 }
 Vec4f imageFindLineClass::getLineParaPoint()
 {
     return line_paraPoint;
 }
 Point imageFindLineClass::getLineStartPoint()
 {
     return lineStartPoint;
 }
 Point imageFindLineClass::getLineEndPoint()
 {
   
   return lineEndPoint;
 }
 void imageFindLineClass::imageGetLine()
 {      
     
     cout << "1"<<endl;
      vector<Vec4i> theAllLine;
       Vec4i thelin;
        vector<Vec4i>::iterator iti  ;
        vector<Vec4i>::iterator itj ;
        vector<Vec4i>::iterator itk ;
  //      vector<Vec4i>::iterator itt  ;
        int min = 0;
      theAllLine.push_back(*(lines.begin()));
for(iti = lines.begin(); iti != lines.end() ;iti++)
{
      itk =iti;
 //     iti++;
      for(itj =++iti;itj != lines.end();itj++)
     {  
        Point pt1((*itk)[0],(*itk)[1]); 
        Point pt2((*itk)[2],(*itk)[3]);
        Point pt3((*itj)[0],(*itj)[1]); 
        Point pt4((*itj)[2],(*itj)[3]);
         float abs_num = abs(abs (pt3.x -pt2.x)*abs(pt3.x -pt2.x) - abs(abs(pt3.y -pt2.y)*abs(pt3.y -pt2.y)) );
 //        min = cvSqrt(abs_num);
        if( min  <= cvSqrt(abs_num) )
        {
            min = cvSqrt(abs_num) ;
            thelin[0] = (*itj)[0];
            thelin[1] = (*itj)[1];
            thelin[2] = (*itj)[2];
            thelin[3] = (*itj)[3];
        }
     }
       theAllLine.push_back(thelin);

}        
 vector<Vec4i> theAllLineq;
       Vec4i thelinq;
     vector<Vec4i>::const_iterator it  = theAllLine.begin();
     
        Point pt1((*it)[0],(*it)[1]); 
        Point pt2((*it)[2],(*it)[3]);
        it++;
        bool pt1pt2 = false;
                    Point thecenter;
     for(it != theAllLine.end();it != theAllLine.end();it++)
     {
         if(pt1pt2)
         {
             pt1.x = (*it)[0];
             pt1.y  =(*it)[1]  ;
             pt2.x =(*it)[2];
             pt2.y =(*it)[3];         
             pt1pt2 = false;            
         }
            Point pt3((*it)[0],(*it)[1]); 
            Point pt4((*it)[2],(*it)[3]);          

            if((abs(pt3.x - pt2.x) <= 5) &&(abs(pt3.y -pt2.y)   <= 5))
      //      if(1)
            {
          //      pt2.x = pt3.x;
         //       pt2.y = pt3.y;
                thecenter.x =pt4.x;
                thecenter.y =pt4.y;
                  cout << "pt4,x"<<pt4.x<<"pt4.y"<<pt4.y<<endl;
                  pt2.x = pt4.x;
                pt2.y = pt4.y;            
            }
            else
            {
               thelinq[0] =pt1.x;    
                thelinq[1] =pt1.y;
                thelinq[2] =thecenter.x;
                  thelinq[3] =thecenter.y;        
                 cout << "pt1,x"<<thecenter.x<<"pt1.y"<< thecenter.y<<endl;
                theAllLineq.push_back(thelinq);   
                pt1pt2 = true;
            }     
     }
              // 将检测到的直线在图上画出来 
        vector<Vec4i>::iterator itt=theAllLineq.begin(); 
        while(itt!=theAllLineq.end()) 
        { 
            Point pt1((*itt)[0],(*itt)[1]); 
            Point pt2((*itt)[2],(*itt)[3]); 
            if(pt2.x ==0  && pt2.y == 0)
            {           
            }
            else
            {
            line(craveImage,pt1,pt2,Scalar(0,255,0),2); //  线条宽度设置为2 
            circle(craveImage,pt1,2,Scalar(0,255,0),2); 
            circle(craveImage,pt2,2,Scalar(255,0,0),2); 
            cout <<"p.x"<<pt1.x << pt1.y<<endl;
              cout <<"p.x"<<pt2.x << pt2.y<<endl; 
            }
            ++itt; 
        } 
        imshow("sim09on",craveImage);
        waitKey(0);
        return;
 }

