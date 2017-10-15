/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   theClass.cpp
 * Author: aqq
 * 
 * Created on 2017年4月12日, 下午1:51
 */
#include "theClass.h"

theClass::theClass() {
}

theClass::theClass(const theClass& orig) {
}

theClass::~theClass() {
}
/*****************************************************************************/
/********************lest the image change the ray****************************/

/****************************************************************************/
changeRay::changeRay(bool isOrNot, cv::Mat & image)
: isOrNot(isOrNot) {
    imageRay = image.clone();
    if (isOrNot == true) {
        cvtColor(image, imageRay, CV_RGB2GRAY);
    }


}

Mat& changeRay::getImageRag() {
    return imageRay;
}

void changeRay::printNum() {
    cout << "image x" << imageRay.cols << "image y" << imageRay.rows << endl;

}

changeRay::changeRay() {
}

changeRay::~changeRay() {
}
/*****************************************************************************/
/**********************dim deal with the image********************************/

/*****************************************************************************/
dimDealWitch::dimDealWitch(cv::Mat & image)
:image(image)
{
    
}
void dimDealWitch::dimDealWithType()
{
  std::cout << "choice the dim" << std::endl;
    std::cout << "0:Blue,1:GaussianBlur,2:MedianBlur,3:BilaterFilter,4:BoxFilter,5:NULL" << endl;
    Mat dim_obj;
    cin >> Dim;
    switch (Dim) {
        case dim_Blue: //mean value blue 0
            blur(image,image,Size(3,3),Point(-1,-1));           
            break;
        case dim_GaussianBlur:  //1 gaussian blur 1
            GaussianBlur(image, image, cv::Size(1, 1), 1.5, 1.5);
            break;
        case dim_MedianBlur:
            medianBlur(image,image,3); //median blur 2
            break;
        case dim_BilateralFilter: //bilateral filter  3
            bilateralFilter(image,dim_obj,2,3.0,1.0);
            image = dim_obj.clone();
            break;
        case dim_BoxFilter:
            boxFilter(image,image,IPL_DEPTH_8U,Size(3,3),Point(-1,-1),true,BORDER_DEFAULT);
            break;
        case dim_Null:
            return;
        default :
            cout <<"you inupt the num is wrong" << endl;
            break;
            
    }
    
  //  imshow("blur",image);
 //  waitKey(0);

}
Mat & dimDealWitch::returnImage()
{
    return image;
}
dimDealWitch::dimDealWitch() {
}

dimDealWitch::~dimDealWitch() {
}

/*****************************************************************************/
/*******************feaPointArithmetic SIFT,SUIF,ORB an so********************/

/*****************************************************************************/

void feaPointAri::showTheMatchingWay() {
    std::cout << "choice the dim" << std::endl;
    cout << "0:SIFT,1:SUFT,2:ORB,3:more pthread" << endl;
    int Dim;
    cin >> Dim;
    switch (Dim) {
        case feaPointAri_SIFT:
                 showFeaPointSIFT();
            break;
        case feaPointAri_SUFT:
            showFeaPointSUFT();
            break;
        case feaPointAri_ORB:
            showFeaPointORB();
            break;
        case COMPOSITESIFTSUFTORB:
            compositeSiftSuftOrb();            
            break;    
        default:
            break;
            

    }

}
 pthreadLock * pLock;    
  vector<Point2f > threadPoint;
 void *surtFunc(void* pParam)
 {
     //     pLock->Lock();
         Point2f Point;
          feaPointAri * feaPointP = (feaPointAri*)pParam;
 //            feaPointP->templateMatchingChoiceWay();
          feaPointP-> showFeaPointSUFT();
          Point = feaPointP->printCenterPoint();
          threadPoint.push_back(Point);
      
            cout<<Point<<endl;
      //     pLock->Unlock();
          cout<<"pthread surf"<<endl;
 }
  void *siftFunc(void* pParam)
 {
       cout<<"12"<<endl;
     //   pLock->Lock();
        Point2f Point;
        feaPointAri * feaPointP = (feaPointAri*)pParam;
        feaPointP-> showFeaPointSIFT();
        feaPointP->printCenterPoint();
        Point = feaPointP->printCenterPoint();
        threadPoint.push_back(Point);
        cout<<Point<<endl;
    //    pLock->Unlock();
         cout<<"pthread sift"<<endl;
 }
   void *orbFunc(void* pParam)
 {
        cout<<"13"<<endl;
       //  pLock->Lock();
         Point2f Point;
         feaPointAri * feaPointP = (feaPointAri*)pParam;
    //        feaPointP->templateMatchingChoiceWay();
         feaPointP-> showFeaPointORB();
         feaPointP->printCenterPoint();
         Point = feaPointP->printCenterPoint();
         threadPoint.push_back(Point);
           cout<<Point<<endl;
    //     pLock->Unlock();
         cout<<"pthread orb"<<endl;
 }
void feaPointAri::compositeSiftSuftOrb()
{
    Mat image = secne.clone();
    imshow("obj",secne);
      CV_Assert(secne.data != NULL);
    pLock = new  pthreadLock(); 
    pthread_t surt;
   pthread_t  sift;
    pthread_t orb;
          pLock->Lock();
     if(pthread_create(&surt,NULL,surtFunc,this)  != 0)
    {
            printf("create the pthread is wrrong");
             exit(-1);
    }
           pLock->Unlock();
              pLock->Lock();
        if(pthread_create(&sift,NULL,siftFunc,this)  != 0)
    {
            printf("create the pthread is wrrong");
             exit(-1);
    }
                 pLock->Unlock();
                 pLock->Lock();
            if(pthread_create(&orb,NULL,orbFunc,this)  != 0)
    {
            printf("create the pthread is wrrong");
             exit(-1);
    }
                   pLock->Unlock();
          cout<<"3"<<endl;
    pthread_join(surt,NULL);
    pthread_join(sift,NULL);
    pthread_join(orb,NULL);
        vector<Point2f >::iterator itt;
        for(itt =threadPoint.begin() ;  itt != threadPoint.end() ; itt++)
        {
            Point2f pt = *itt;
            cout <<pt<<endl;
           circle(image,pt,2,Scalar(255,0,0),2);     
        }
        imshow("image",image);
        waitKey(0);
        
    
     delete pLock;
     pLock = NULL;
 
}
 void  feaPointAri:: showFeaPointSUFT() //using the SUFT arithmetic
 {
     Mat image;
     image = obj.clone();
     obj = secne.clone();
     secne = image.clone();
     float para = 1000;
     CV_Assert(obj.data != NULL &&secne.data != NULL);
     if (1 != secne.channels() &&1 != obj.channels())
    {
        cout << "you have't  the gry,it will not very correct"<< endl;           
    }
     //init the SURF
     SurfFeatureDetector surfDetector(para);
     SurfDescriptorExtractor surfExtractor;
     //declaration the keypoints and Mat
     vector<KeyPoint> keypoints1,keypoints2;
     Mat  descriptorMat1,descriptorMat2;
    
     //count the  SURF the points
     surfDetector.detect(secne,keypoints1);
     surfDetector.detect(obj,keypoints2);
     
     //count SURF the MAT
     surfExtractor.compute(secne,keypoints1,descriptorMat1);
     surfExtractor.compute(obj,keypoints2,descriptorMat2);
     
     float result = 0;
     
     //point matching
     if(keypoints1.size() > 0 && keypoints2.size() > 0)
     {
             //count teh point matching
         FlannBasedMatcher matcher;
         //point vector quantity
         vector<DMatch> matches;
         //accord with point vector quantity
         vector<DMatch> viewMatches;
         matcher.match(descriptorMat1,descriptorMat2,matches);
         
         //if it is the ture matching
         double minDist = 100;
         for(int i = 0;i < matches.size();i++)
         {
             if(matches[i].distance < minDist)
             {
                 minDist = matches[i].distance;
             }
         }
          //count the point whitch is accord with the points
         int num = 0;
         cout << "minDist" << minDist << endl;
         for(int i = 0 ; i < matches.size();i++)
         {
             if(matches[i].distance <= 2* minDist)
             {
                 result += matches[i].distance *matches[i].distance;
                 viewMatches.push_back(matches[i]);
                 num++;      
             }        
         }
         result /=num;
         Mat matchMat;
         drawMatches(secne,keypoints1,obj,keypoints2,matches,matchMat);

           
  vector <KeyPoint>::iterator scene_iter;
    vector <KeyPoint>::iterator obj_iter;
    Point2f obj_start;
    Point2f scene_end;
    obj_iter = (keypoints1).begin();
    scene_iter = (keypoints2).begin();
    //保存匹配对序号  
    vector<int> queryIdxs(matches.size()), trainIdxs(matches.size());
    for (size_t i = 0; i < matches.size(); i++) {
        queryIdxs[i] = matches[i].queryIdx;
        trainIdxs[i] = matches[i].trainIdx;
    }
    Mat H12; //变换矩阵  
    vector<Point2f> points1;
    KeyPoint::convert(keypoints1, points1, queryIdxs);
    vector<Point2f> points2;
    KeyPoint::convert(keypoints2, points2, trainIdxs);
    int ransacReprojThreshold = 5; //拒绝阈值  

    //findHomography()函数直接通过两个平面上相匹配的特征点求出变换公式，
    //之后代码又对原图的四个边缘点进行变换，在右图上画出对应的矩形。这个图也很好地解释了所谓透视变换的“Viewing Plane”。
    H12 = findHomography(Mat(points1), Mat(points2), CV_RANSAC, ransacReprojThreshold);
    //
    vector<char> matchesMask(matches.size(), 0);
    Mat points1t;
    cv::perspectiveTransform(Mat(points1), points1t, H12);

    for (size_t i1 = 0; i1 < points1.size(); i1++) //保存‘内点’  
    {
        if (norm(points2[i1] - points1t.at<Point2f>((int) i1, 0)) <= ransacReprojThreshold) //给内点做标记  
        {
            matchesMask[i1] = 1;
        }
    }
    Mat match_img2; //滤除‘外点’后  
    drawMatches(secne, keypoints1, obj, keypoints2, matches, match_img2, Scalar(0, 0, 255), Scalar::all(-1), matchesMask);
    //画出目标位置  
    std::vector<Point2f> obj_corners(4);
    obj_corners[0] = cvPoint(0, 0);
    obj_corners[1] = cvPoint(secne.cols, 0);
    obj_corners[2] = cvPoint(secne.cols, secne.rows);
    obj_corners[3] = cvPoint(0, secne.rows);
    std::vector<Point2f> scene_corners(4);
    perspectiveTransform(obj_corners, scene_corners, H12);

    vector<KeyPoint> ::iterator iterz;
    for (iterz = (keypoints1).begin(); iterz != (keypoints1).end(); iterz++) {
        //printf("secene_keypoints: %f\n", (*iterz).pt.x);
    }   
     point1.x =  (scene_corners[0] + Point2f(static_cast<float> (secne.cols))).x;
     point1.y =   (scene_corners[0] + Point2f(static_cast<float> (secne.cols))).y;
     point2.x =  (scene_corners[1] + Point2f(static_cast<float> (secne.cols))).x;
     point2.y =  (scene_corners[1] + Point2f(static_cast<float> (secne.cols))).y;
     point3.x =  (scene_corners[2] + Point2f(static_cast<float> (secne.cols))).x;
     point3.y =  (scene_corners[2] + Point2f(static_cast<float> (secne.cols))).y;
     point4.x =  (scene_corners[3] + Point2f(static_cast<float> (secne.cols))).x;
     point4.y =  (scene_corners[3] + Point2f(static_cast<float> (secne.cols))).y;
     line(match_img2, point1, point2, Scalar(255, 255, 255), 3, 0);
     line(match_img2, point2, point3, Scalar(255, 255, 255), 3, 3);
     line(match_img2, point3, point4, Scalar(255, 255, 255), 3, 3); 
     line(match_img2, point4, point1, Scalar(255, 255, 255), 3, 0);

         
         imshow("matchMat",match_img2);
         waitKey(0);
     }

     return ;
 }
void feaPointAri::showFeaPointSIFT()
{
    CV_Assert(secne.data != NULL && obj.data != NULL);
    if (1 != secne.channels() &&1 != obj.channels())
    {
        cout << "you have't  the gry,it will not very correct"<< endl;
   //     cvtColor     
    }
    normalize(secne,secne,0,255,NORM_MINMAX);
    normalize(obj,obj,0,255,NORM_MINMAX);
    // define the SIFT
    SiftFeatureDetector detector;
    SiftDescriptorExtractor extractor;
    //the dim point test
    vector<KeyPoint> keypoints1;
    detector.detect(secne,keypoints1);
    vector<KeyPoint> keypoints2;
    detector.detect(obj,keypoints2);
    //count the point descriptor
    Mat descriptors1;
    extractor.compute(secne,keypoints1,descriptors1);
     Mat descriptors2;
    extractor.compute(obj,keypoints2,descriptors2);
    //point matching
    vector<DMatch> matches;
    BruteForceMatcher<L2<float> > matcher;
    //bruteForce
    matcher.match(descriptors1,descriptors2,matches);
    //two sort
    
    int N = 80;
    nth_element(matches.begin(), matches.begin() + N + 1 ,matches.end());
    matches.erase(matches.begin() + N ,matches.end());
    
    //the result
    Mat matchMat;
    drawMatches(secne,keypoints1,obj,keypoints2,matches,matchMat);

  
  
  vector <KeyPoint>::iterator scene_iter;
    vector <KeyPoint>::iterator obj_iter;
    Point2f obj_start;
    Point2f scene_end;
    obj_iter = (keypoints1).begin();
    scene_iter = (keypoints2).begin();
    //保存匹配对序号  
    vector<int> queryIdxs(matches.size()), trainIdxs(matches.size());
    for (size_t i = 0; i < matches.size(); i++) {
        queryIdxs[i] = matches[i].queryIdx;
        trainIdxs[i] = matches[i].trainIdx;
    }
    Mat H12; //变换矩阵  
    vector<Point2f> points1;
    KeyPoint::convert(keypoints1, points1, queryIdxs);
    vector<Point2f> points2;
    KeyPoint::convert(keypoints2, points2, trainIdxs);
    int ransacReprojThreshold = 5; //拒绝阈值  

    //findHomography()函数直接通过两个平面上相匹配的特征点求出变换公式，
    //之后代码又对原图的四个边缘点进行变换，在右图上画出对应的矩形。这个图也很好地解释了所谓透视变换的“Viewing Plane”。
    H12 = findHomography(Mat(points1), Mat(points2), CV_RANSAC, ransacReprojThreshold);
    //
    vector<char> matchesMask(matches.size(), 0);
    Mat points1t;
    cv::perspectiveTransform(Mat(points1), points1t, H12);

    for (size_t i1 = 0; i1 < points1.size(); i1++) //保存‘内点’  
    {
        if (norm(points2[i1] - points1t.at<Point2f>((int) i1, 0)) <= ransacReprojThreshold) //给内点做标记  
        {
            matchesMask[i1] = 1;
        }
    }
    Mat match_img2; //滤除‘外点’后  
    drawMatches(secne, keypoints1, obj, keypoints2, matches, match_img2, Scalar(0, 0, 255), Scalar::all(-1), matchesMask);
    //画出目标位置  
    std::vector<Point2f> obj_corners(4);
    obj_corners[0] = cvPoint(0, 0);
    obj_corners[1] = cvPoint(secne.cols, 0);
    obj_corners[2] = cvPoint(secne.cols, secne.rows);
    obj_corners[3] = cvPoint(0, secne.rows);
    std::vector<Point2f> scene_corners(4);
    perspectiveTransform(obj_corners, scene_corners, H12);

    vector<KeyPoint> ::iterator iterz;
    for (iterz = (keypoints1).begin(); iterz != (keypoints1).end(); iterz++) {
        //printf("secene_keypoints: %f\n", (*iterz).pt.x);
    }   
     point1.x =  (scene_corners[0] + Point2f(static_cast<float> (secne.cols))).x;
     point1.y =   (scene_corners[0] + Point2f(static_cast<float> (secne.cols))).y;
     point2.x =  (scene_corners[1] + Point2f(static_cast<float> (secne.cols))).x;
     point2.y =  (scene_corners[1] + Point2f(static_cast<float> (secne.cols))).y;
     point3.x =  (scene_corners[2] + Point2f(static_cast<float> (secne.cols))).x;
     point3.y =  (scene_corners[2] + Point2f(static_cast<float> (secne.cols))).y;
     point4.x =  (scene_corners[3] + Point2f(static_cast<float> (secne.cols))).x;
     point4.y =  (scene_corners[3] + Point2f(static_cast<float> (secne.cols))).y;
     line(match_img2, point1, point2, Scalar(255, 255, 255), 1, 0);
     line(match_img2, point2, point3, Scalar(255, 255, 255), 1, 0);
     line(match_img2, point3, point4, Scalar(255, 255, 255), 1, 0); 
     line(match_img2, point4, point1, Scalar(255, 255, 255), 1, 0);

 
  imshow("matchMat",match_img2);
    waitKey(0);
    return ;
    
}
void feaPointAri::showFeaPointORB() {
        CV_Assert(secne.data != NULL && obj.data != NULL);
        
    vector<KeyPoint> obj_keypoints, scene_keypoints;
    obj_keypoints.reserve(100000);
    scene_keypoints.reserve(100000);
    Mat obj_descriptors, scene_descriptors;
    ORB detector; //采用ORB算法提取特征点  
    detector.detect(obj, obj_keypoints);
    detector.detect(secne, scene_keypoints);
    detector.compute(obj, obj_keypoints, obj_descriptors);
    detector.compute(secne, scene_keypoints, scene_descriptors);
    BFMatcher matcher(NORM_HAMMING, true); //汉明距离做为相似度度量  
    vector<DMatch> matches;
    matches.reserve(100000);
    matcher.match(obj_descriptors, scene_descriptors, matches);
    Mat match_img;
    drawMatches(obj, obj_keypoints, secne, scene_keypoints, matches, match_img);
   //// imshow("Filter before the match", match_img);
   // waitKey(0);

    vector <KeyPoint>::iterator scene_iter;
    vector <KeyPoint>::iterator obj_iter;
    Point2f obj_start;
    Point2f scene_end;
    obj_iter = (obj_keypoints).begin();
    scene_iter = (scene_keypoints).begin();

    //保存匹配对序号  
    vector<int> queryIdxs(matches.size()), trainIdxs(matches.size());
    for (size_t i = 0; i < matches.size(); i++) {
        queryIdxs[i] = matches[i].queryIdx;
        trainIdxs[i] = matches[i].trainIdx;
        obj_start.x = (*(obj_iter + queryIdxs[i])).pt.x;
        obj_start.y = (*(obj_iter + queryIdxs[i])).pt.y;
        scene_end.x = (*(scene_iter + trainIdxs[i])).pt.x + obj.rows;
        scene_end.y = (*(scene_iter + trainIdxs[i])).pt.y;
        line(match_img, obj_start, scene_end, Scalar(255, 255, 255), 1, 0);
    }


 //  cv::imshow("滤除误匹配前123", match_img);
    cout << "match_img.cols" << match_img.cols << "match_img.rows" << match_img.rows << endl;
    cout << "obj.cols" << obj.cols << "obj.rows" << obj.rows << endl;
    cout << "scene.cols" << secne.cols << "scene.rows" << secne.rows << endl;

    Mat H12; //变换矩阵  

    vector<Point2f> points1;
    KeyPoint::convert(obj_keypoints, points1, queryIdxs);
    vector<Point2f> points2;
    KeyPoint::convert(scene_keypoints, points2, trainIdxs);
    int ransacReprojThreshold = 5; //拒绝阈值  

    //findHomography()函数直接通过两个平面上相匹配的特征点求出变换公式，
    //之后代码又对原图的四个边缘点进行变换，在右图上画出对应的矩形。这个图也很好地解释了所谓透视变换的“Viewing Plane”。
    H12 = findHomography(Mat(points1), Mat(points2), CV_RANSAC, ransacReprojThreshold);
    //
    vector<char> matchesMask(matches.size(), 0);
    Mat points1t;
    cv::perspectiveTransform(Mat(points1), points1t, H12);

    for (size_t i1 = 0; i1 < points1.size(); i1++) //保存‘内点’  
    {
        if (norm(points2[i1] - points1t.at<Point2f>((int) i1, 0)) <= ransacReprojThreshold) //给内点做标记  
        {
            matchesMask[i1] = 1;
        }
    }


    Mat match_img2; //滤除‘外点’后  
    drawMatches(obj, obj_keypoints, secne, scene_keypoints, matches, match_img2, Scalar(0, 0, 255), Scalar::all(-1), matchesMask);

    //画出目标位置  
    std::vector<Point2f> obj_corners(4);
    obj_corners[0] = cvPoint(0, 0);
    obj_corners[1] = cvPoint(obj.cols, 0);
    obj_corners[2] = cvPoint(obj.cols, obj.rows);
    obj_corners[3] = cvPoint(0, obj.rows);
    std::vector<Point2f> scene_corners(4);
    perspectiveTransform(obj_corners, scene_corners, H12);


    vector<KeyPoint> ::iterator iterz;
    for (iterz = (scene_keypoints).begin(); iterz != (scene_keypoints).end(); iterz++) {
        //printf("secene_keypoints: %f\n", (*iterz).pt.x);
    }   
     point1.x =  (scene_corners[0] + Point2f(static_cast<float> (obj.cols))).x;
     point1.y =   (scene_corners[0] + Point2f(static_cast<float> (obj.cols))).y;
     point2.x =  (scene_corners[1] + Point2f(static_cast<float> (obj.cols))).x;
     point2.y =  (scene_corners[1] + Point2f(static_cast<float> (obj.cols))).y;
     point3.x =  (scene_corners[2] + Point2f(static_cast<float> (obj.cols))).x;
     point3.y =  (scene_corners[2] + Point2f(static_cast<float> (obj.cols))).y;
     point4.x =  (scene_corners[3] + Point2f(static_cast<float> (obj.cols))).x;
     point4.y =  (scene_corners[3] + Point2f(static_cast<float> (obj.cols))).y;
      line(match_img2, point1, point2, Scalar(255, 255, 255), 1, 0);
      line(match_img2, point2, point3, Scalar(255, 255, 255), 1, 0);
      line(match_img2, point3, point4, Scalar(255, 255, 255), 1, 0); 
      line(match_img2, point4, point1, Scalar(255, 255, 255), 1, 0);
#if 0
    line(match_img2, scene_corners[0] + Point2f(static_cast<float> (obj.cols), 0),
            scene_corners[1] + Point2f(static_cast<float> (obj.cols), 0), Scalar(0, 0, 255), 2);
    line(match_img2, scene_corners[1] + Point2f(static_cast<float> (obj.cols), 0),
            scene_corners[2] + Point2f(static_cast<float> (obj.cols), 0), Scalar(0, 0, 255), 2);
    line(match_img2, scene_corners[2] + Point2f(static_cast<float> (obj.cols), 0),
            scene_corners[3] + Point2f(static_cast<float> (obj.cols), 0), Scalar(0, 0, 255), 2);
    line(match_img2, scene_corners[3] + Point2f(static_cast<float> (obj.cols), 0),
            scene_corners[0] + Point2f(static_cast<float> (obj.cols), 0), Scalar(0, 0, 255), 2);

    printf("\n  the point1: x is %f,y is %f\n ", (scene_corners[0] + Point2f(static_cast<float> (obj.cols))).x,
            (scene_corners[0] + Point2f(static_cast<float> (obj.cols))).y);
    printf("the point2: x is %f,y is %f\n ", (scene_corners[1] + Point2f(static_cast<float> (obj.cols))).x,
            (scene_corners[1] + Point2f(static_cast<float> (obj.cols))).y);
    printf("the point3: x is %f,y is %f\n ", (scene_corners[2] + Point2f(static_cast<float> (obj.cols))).x,
            (scene_corners[2] + Point2f(static_cast<float> (obj.cols))).y);
    printf("the point4（）: x is %f,y is %f\n ", (scene_corners[3] + Point2f(static_cast<float> (obj.cols))).x,
            (scene_corners[3] + Point2f(static_cast<float> (obj.cols))).y);
    printf("中心点:x is %f ,y is %f\n", ((scene_corners[0] + Point2f(static_cast<float> (obj.cols))).x + (scene_corners[1] + Point2f(static_cast<float> (obj.cols))).x) / 2,
            ((scene_corners[0] + Point2f(static_cast<float> (obj.cols))).y + (scene_corners[2] + Point2f(static_cast<float> (obj.cols))).y) / 2);

#endif 
   imshow("滤除误匹配后", match_img2);

   waitKey(0);
}
 Point2f  feaPointAri::printCenterPoint()
{
     pointCenter.x = point1.x  + (point2.x  - point1.x )/2;
     pointCenter.y = point1.y + (point3.y  - point1.y  )/2;
     cout << "pointCenter "<<pointCenter<<endl;
}
void feaPointAri::printNum()
{
    cout << "Point1.x   " <<point1.x<<"Point1.y   " << point1.y<<endl;
    cout << "Point2.x   " <<point2.x<<"Point2.y   " << point2.y<<endl;
    cout << "Point3.x   " <<point3.x<<"Point3.y   " << point3.y<<endl;   
    cout << "Point4.x   " <<point4.x<<"Point4.y   " << point4.y<<endl;  
}

Mat feaPointAri::getTheMat() {
    return obj_show_point;

}

void feaPointAri::templateMatchingChoiceWay() {

    cout << "the size is " << SaveMatIntToVector.size() << endl;
    if (SaveMatIntToVector.size() < 2) {
        cout << "there have't two image ,so you can't matching" << endl;
        return;
    }
    cout << "please choice input the templalte image" << endl;
    int j;
    cin >> j;
    int i = 0;
    vector<SaveMatInt>::iterator iter;
    for (iter = SaveMatIntToVector.begin(); iter != SaveMatIntToVector.end(); iter++) {
        if (i == j) {
            obj = ((*iter).first).clone();
            break;
        }
        i++;
    }
    imshow("templalte",obj);
    cout << "please choice input the test image" << endl;
    cin.clear();
    i = 0;
    cin >> j;
    for (iter = SaveMatIntToVector.begin(); iter != SaveMatIntToVector.end(); iter++) {
        if (i == j) {
            secne = ((*iter).first).clone();
            break;
        }
        i++;
    }
    imshow("test",secne);
    waitKey(0);

}

void feaPointAri::showFeaPoint() {

    vector<KeyPoint> obj_keypoints;
    obj_keypoints.reserve(100000);
    ORB detector;
    detector.detect(obj_show_point, obj_keypoints);
    vector<KeyPoint> ::iterator iter;
    for (iter = obj_keypoints.begin(); iter != obj_keypoints.end(); iter++) {
        cout << "x :" << (*iter).pt.x << "y :" << (*iter).pt.y << endl;
        circle(obj_show_point, Point(((*iter).pt.x), ((*iter).pt.y)), 3, Scalar(255, 255, 0), 1);

    }
    //  imshow("OBJ show feat point" ,obj);
    //  waitKey(0);    

}

feaPointAri::feaPointAri() {
}

feaPointAri::feaPointAri(Mat & image) {
    obj_show_point = image.clone();

}

feaPointAri::~feaPointAri() {

}
/**************************************************************************************/
 /*************************fea point is over************************************************/
 /**************************************************************************************/