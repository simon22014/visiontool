/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: aqq
 *
 * Created on 2017年3月28日, 下午5:29
 */

#include <cstdlib>
#include <stdio.h>
#include "showStorageClass.h"
#include"showAndWebStorageClass.h"
#include <ctime>
#include <opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/nonfree/features2d.hpp>
#include<opencv2/nonfree/nonfree.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/legacy/legacy.hpp>
#include <iostream>
#include <pthread.h>
#include <signal.h>
#include<unistd.h>
#include <semaphore.h>
#include "theClass.h"
#include "feaPoint.h"
#include "man.h"
#include "template.h"
#include "imagedealwith.h"
#include "webStructClass.h"
#include "pthreadLock.h"
#include "imageGeroetry.h"
#include"marginFunctor.h"
#include"histImage.h"
#include"demarcate.h"
 #include"imageSmoothness.h"
#include"ChangeGray.h"
#include"cornerDetection.h"
 #include"callPython.h"
using namespace std;
using namespace cv;
 int  changeNumber[capHeight][capWidth][3]; //capWidt
//Mat srcscene;
//void theAlgFunction(Mat & obj, Mat & scene, shStorage*  getAndWebShare);
sem_t sem ;
 cv::Mat  Image_input_Mat;  //the photo save from the save storage
 cv::Mat  Mat_Image_template;
 cv::Mat  Mat_Image_test;
pthreadLock*shareLock;
shStorage*  getAndWebShare ;
//typedef std::pair<cv::Mat,int> SaveMatInt;
 vector<SaveMatInt>  SaveMatIntToVector; 
  int shareID;
  //  showAndWebStorageClass *webClass  = new showAndWebStorageClass();
void sig_alrm( int)
{
       showAndWebStorageClass *webClass = new showAndWebStorageClass() ;
       getAndWebShare  = webClass->read_Web_Buf(shareID);
       if( status_4_done != getAndWebShare->status)
       {
           cout<<"the user hav't not finish"<<endl;
           return ;
       }
       WebStrucetCLASS* WebClass =  new  WebStrucetCLASS(getAndWebShare);
      WebClass ->readRgbDataMode();
      Mat_Image_template = WebClass ->carveImageTemplate();
      Mat_Image_test  = WebClass ->readRgbDataTest();     
       switch(getAndWebShare->status)
       {
           case status_1_nothing:
               break;       
           case status_2_work:                  
                
                 sem_post(&sem);                    
               break;

           case 44:
           {
               WebClass->readRgbDataTest();
      
               cout << "q"<<endl;
               break;
               
           }
           default:
               cout << "the status is wrong" <<endl;
               break;
       
       }
       alarm(1);
    return ;
}    
void *CallOnDmemoyFunc(void* pParam)
{  
      signal(SIGALRM,sig_alrm);
        alarm(1);
       sleep(1);       
}   
void *showImageFunc(void* pParam)
{
   sem_wait(&sem);    
    Mat image_m ;
    Mat image_clone;
    Mat image_centre;
    SaveMatInt image_save;       
 bool  ifReturn= true;
 cout << "i init is success"<< endl;
 sleep(1);
 cout << "please input the thing  "<< endl;
  cout << "0: input the image,1:change ray,2:dim deal with,3:find the fea point,4:save the image,5:matching,6:template matching,7:deal with image8:test image,9:geroetry,10,margin,11,hist,12,smoothness,13,image change,14,corner test,15quit"<<endl;

 while(ifReturn)
 {
                 switch(getAndWebShare->code)
		{
                     case 100:
                         main_temarcate();
                         break;
                     case 44:
                image_m = imread("//home//aqq//NetBeansProjects//demon_test//png//12_GasketBad.JPG");
                    image_clone = image_m.clone();
                    image_save.first = image_m.clone();
                    image_save.second = GETTHEIMAGE;                  
			break;
                     case GETTHEIMAGE :   //0 get the image 
         //        image_m = imread("//home//aqq//NetBeansProjects//demon_test//png//findLine.png"); 
              image_m = imread("//home//aqq//NetBeansProjects//demon_test//png//Image00001.BMP");
            //         image_m = imread("//home//aqq//NetBeansProjects//demon_test//png//9_Left_Hand.bmp"); 
           //            image_m =  Mat_Image_template.clone();
                    image_clone = image_m.clone();
                    image_save.first = image_m.clone();
                    image_save.second = GETTHEIMAGE;                  
			break;
                     case TESTIMAGE: //8
               //        image_m = imread("image22.png");
                        image_m = Mat_Image_test.clone();
                //          image_clone = image_m.clone();
                         image_save.first = image_m.clone();
                         image_save.second = GETTHEIMAGE;                         
                      break;   
		     case GETTHEIMAGERAG:  //1 get the image and ray                 
                    image_centre = feaPointChangeRay(image_clone); 
                    image_save.first = image_centre.clone();
                    image_save.second = GETTHEIMAGERAG;                  
			break;
                     case DIMDEALWITCH:   //2 get the DIm Point
                      feaPointdimDealWitch(image_clone);
                      
                    image_save.first = image_clone.clone();
                    image_save.second = DIMDEALWITCH;               
                    break;
                     case  FEAPOINTALG: //3 feature points arithmetic
                    image_centre = feaPointArithmetic(image_clone);             
                    
                    image_save.first = image_centre.clone();
                    image_save.second = FEAPOINTALG;  
                    break;
                     case SAVELATERUSE:  //4 save teh image 
                         SaveMatIntToVector.push_back(image_save);
                         cout << "save is success" << endl;
                         break;
                     case FEAPOINTMATCHING: //5 matching 
                         feaPointMatching();
                         cout << "Matching is success"<< endl;
                         break;
                     case TEMPLATEMATCHING: //6 template matching
                         cout << "template matching" << endl;
                         templateMating();
                                 break;    
                     case IMAGEDEAL_WITH:   //7 image deal with
                         image_centre  = imageDealWith(image_clone);
                         image_save.first = image_centre.clone();
                         image_save.second = FEAPOINTALG;  
                         break;
                    case IMAGE_GEROETRY:   //9find the image line
                        imageGeroetry(image_m);
                    //     imageFindLine(image_m);
                         break;
                     case IMAGEMARGINFUNCTOR:  //10margin functor test
                         imageMarginFunctor(image_m);
                         break;
                     case IMAGEHIST:  //11hist
                         imageHist(image_m);
                         break;
                        case IMAGESMOOTHNESS: // 12image smoothness
                         imageSmoothness(image_m);
                         break;
                     case IMAGECHANGEGRAY:  //13 image change
                         imageChangeGray(image_m);
                         break;
                     case IMAGECORNERDETECTION:
                         imageCornerDetection(image_m);
                         break;
                     case 1000:
                         callPythonTestHello();
                         break;
                       case QUIT: //10 quit
                         cout << "it is end" << endl;
                         return (void*)0;         
                     default :
                         cout << "you input the order is wrong" <<endl;
                         break;    
                         
                 }
 
                 cin.clear();
 
  cout << "please input the thing  "<< endl;
  cout << "0: input the image,1:change ray,2:dim deal with,3:find the fea point,4:save the image,5:matching,6:template matching,7:deal with image8:test image,9:geroetry,10,margin,11,hist,12,smoothness, 13,image change,14,corner test,15quit"<<endl;
                                          }
}
int main(int argc,char** argv)
{
    showAndWebStorageClass *webClass = new showAndWebStorageClass() ;
      webClass->CreateShowWebStorage();
    webClass->  read_web_number();
    
    shareID = webClass->getShareID();
      cout << shareID<<endl;
     
      int res = sem_init (&sem,0,0);
 
      if (res == -1)
      {
          printf("create the sem is error");
          exit(-1);
      }

    pthread_t  CallOnDmemoy;
    pthread_t    showImage;
  //  int i = 10;
    if(pthread_create(&CallOnDmemoy,NULL,CallOnDmemoyFunc,NULL)  != 0)
    {
            printf("create the pthread is wrrong");
             exit(-1);
    }
        if(pthread_create(&showImage,NULL,showImageFunc,NULL)  != 0)
    {
            printf("create the pthread is wrrong");
             exit(-1);
    }
    pthread_join(CallOnDmemoy,NULL);
    pthread_join(showImage,NULL);
    sem_destroy(&sem);
   
return 0;
}
#if 0
void theAlgFunction(Mat & obj, Mat & scene,shStorage*  getAndWebShare)
{
	if (obj.empty() || scene.empty())
	{
		cout << "Can't open the picture!\n";
		return ;
	}
	vector<KeyPoint> obj_keypoints, scene_keypoints;
	obj_keypoints.reserve(100000);
	scene_keypoints.reserve(100000);
	Mat obj_descriptors, scene_descriptors;
	ORB detector;     //采用ORB算法提取特征点  
	detector.detect(obj, obj_keypoints);
	detector.detect(scene, scene_keypoints);
	detector.compute(obj, obj_keypoints, obj_descriptors);
	detector.compute(scene, scene_keypoints, scene_descriptors);
	BFMatcher matcher(NORM_HAMMING, true); //汉明距离做为相似度度量  
	vector<DMatch> matches;
	matches.reserve(100000);
	matcher.match(obj_descriptors, scene_descriptors, matches);
	Mat match_img;
	drawMatches(obj, obj_keypoints, scene, scene_keypoints, matches, match_img);
	imshow("Filter before the match", match_img);

	//保存匹配对序号  
	vector<int> queryIdxs(matches.size()), trainIdxs(matches.size());
	for (size_t i = 0; i < matches.size(); i++)
	{
		queryIdxs[i] = matches[i].queryIdx;
		trainIdxs[i] = matches[i].trainIdx;
	}

	Mat H12;   //变换矩阵  

	vector<Point2f> points1; KeyPoint::convert(obj_keypoints, points1, queryIdxs);
	vector<Point2f> points2; KeyPoint::convert(scene_keypoints, points2, trainIdxs);
	int ransacReprojThreshold = 5;  //拒绝阈值  

	//findHomography()函数直接通过两个平面上相匹配的特征点求出变换公式，
	//之后代码又对原图的四个边缘点进行变换，在右图上画出对应的矩形。这个图也很好地解释了所谓透视变换的“Viewing Plane”。
	H12 = findHomography(Mat(points1), Mat(points2), CV_RANSAC, ransacReprojThreshold);
	//
	vector<char> matchesMask(matches.size(), 0);
	Mat points1t;
	perspectiveTransform(Mat(points1), points1t, H12);
	for (size_t i1 = 0; i1 < points1.size(); i1++)  //保存‘内点’  
	{
		if (norm(points2[i1] - points1t.at<Point2f>((int)i1, 0)) <= ransacReprojThreshold) //给内点做标记  
		{
			matchesMask[i1] = 1;
		}
	}
	Mat match_img2;   //滤除‘外点’后  
	drawMatches(obj, obj_keypoints, scene, scene_keypoints, matches, match_img2, Scalar(0, 0, 255), Scalar::all(-1), matchesMask);

	//画出目标位置  
	std::vector<Point2f> obj_corners(4);
	obj_corners[0] = cvPoint(0, 0); obj_corners[1] = cvPoint(obj.cols, 0);
	obj_corners[2] = cvPoint(obj.cols, obj.rows); obj_corners[3] = cvPoint(0, obj.rows);
	std::vector<Point2f> scene_corners(4);
	perspectiveTransform(obj_corners, scene_corners, H12);


	line(match_img2, scene_corners[0] + Point2f(static_cast<float>(obj.cols), 0),
		scene_corners[1] + Point2f(static_cast<float>(obj.cols), 0), Scalar(0, 0, 255), 2);
	line(match_img2, scene_corners[1] + Point2f(static_cast<float>(obj.cols), 0),
		scene_corners[2] + Point2f(static_cast<float>(obj.cols), 0), Scalar(0, 0, 255), 2);
	line(match_img2, scene_corners[2] + Point2f(static_cast<float>(obj.cols), 0),
		scene_corners[3] + Point2f(static_cast<float>(obj.cols), 0), Scalar(0, 0, 255), 2);
	line(match_img2, scene_corners[3] + Point2f(static_cast<float>(obj.cols), 0),
		scene_corners[0] + Point2f(static_cast<float>(obj.cols), 0), Scalar(0, 0, 255), 2);

	printf("\n  the point1: x is %f,y is %f\n ", (scene_corners[0] + Point2f(static_cast<float>(obj.cols))).x,
		(scene_corners[0] + Point2f(static_cast<float>(obj.cols))).y);
	printf("the point2: x is %f,y is %f\n ", (scene_corners[1] + Point2f(static_cast<float>(obj.cols))).x,
		(scene_corners[1] + Point2f(static_cast<float>(obj.cols))).y);
	printf("the point3: x is %f,y is %f\n ", (scene_corners[2] + Point2f(static_cast<float>(obj.cols))).x,
		(scene_corners[2] + Point2f(static_cast<float>(obj.cols))).y);
	printf("the point4（）: x is %f,y is %f\n ", (scene_corners[3] + Point2f(static_cast<float>(obj.cols))).x,
		(scene_corners[3] + Point2f(static_cast<float>(obj.cols))).y);
	printf("中心点:x is %f ,y is %f\n", ((scene_corners[0] + Point2f(static_cast<float>(obj.cols))).x + (scene_corners[1] + Point2f(static_cast<float>(obj.cols))).x) / 2,
		((scene_corners[0] + Point2f(static_cast<float>(obj.cols))).y + (scene_corners[2] + Point2f(static_cast<float>(obj.cols))).y) / 2);
getAndWebShare->x1=  (scene_corners[0] + Point2f(static_cast<float>(obj.cols))).x;
getAndWebShare->y1=  (scene_corners[0] + Point2f(static_cast<float>(obj.cols))).y;
getAndWebShare->x2=  (scene_corners[1] + Point2f(static_cast<float>(obj.cols))).x;
getAndWebShare->y2 =  (scene_corners[1] + Point2f(static_cast<float>(obj.cols))).y;
getAndWebShare->x= ((scene_corners[0] + Point2f(static_cast<float>(obj.cols))).x + (scene_corners[1] + Point2f(static_cast<float>(obj.cols))).x) / 2;
getAndWebShare->y=  ((scene_corners[0] + Point2f(static_cast<float>(obj.cols))).y + (scene_corners[2] + Point2f(static_cast<float>(obj.cols))).y) / 2;

//CreateShowWebStorage();
#if 0
	line(match_img2, scene_corners[0] + Point2f(static_cast<float>(obj.cols), 0),
		scene_corners[1] + Point2f(static_cast<float>(obj.cols), 0), Scalar(0, 0, 255), 250);
	line(match_img2, scene_corners[1] + Point2f(static_cast<float>(obj.cols), 0),
		scene_corners[2] + Point2f(static_cast<float>(obj.cols), 0), Scalar(0, 0, 255), 250);
	line(match_img2, scene_corners[2] + Point2f(static_cast<float>(obj.cols), 0),
		scene_corners[3] + Point2f(static_cast<float>(obj.cols), 0), Scalar(0, 0, 255), 250);
	line(match_img2, scene_corners[3] + Point2f(static_cast<float>(obj.cols), 0),
		scene_corners[0] + Point2f(static_cast<float>(obj.cols), 0), Scalar(0, 0, 255), 250);
#endif 

	imshow("Filter after the match", match_img2);
	waitKey(10);
}
#endif 


