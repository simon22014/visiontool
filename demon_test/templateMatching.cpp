/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   templateMatching.cpp
 * Author: aqq
 * 
 * Created on 2017年4月13日, 下午3:06
 */

#include "templateMatching.h"
#include "man.h"



templateMatching::templateMatching()
{
        showAndWebStorageClass *webClass = new showAndWebStorageClass() ;  
         getAndWebShare  = webClass->read_Web_Buf(shareID);        
   cout << "the size is " << SaveMatIntToVector.size() << endl;
    if(SaveMatIntToVector.size() < 2)
     {
         cout <<"there have't two image ,so you can't matching" << endl;
         getAndWebShare->status = status_5_error;
        strcpy(getAndWebShare->error,"there have't two image ,so you can't matching");
         
         webClass->write_Web_buf(getAndWebShare);     
         return ;
     }    
     cout << "please choice input the templalte image"<< endl;
     int j;
     cin >> j;
     int i = 0;      
     vector<SaveMatInt>::iterator  iter;
     for(iter = SaveMatIntToVector.begin() ;iter != SaveMatIntToVector.end();iter++ )
     {
         if (i == j)
         {
             obj = ((*iter).first).clone();
             imshow("obj",obj);
             waitKey(0);
             break;
         }   
         i++;
     }
     cout << "please choice input the test image"<< endl;
     cin.clear();i =0;
     cin >> j;     
     for(iter = SaveMatIntToVector.begin() ;iter != SaveMatIntToVector.end();iter++ )
     {
         if (i == j)
         {
             secne = ((*iter).first).clone();
               imshow("secne",secne);
            waitKey(0);
             break;
         }    
         i++;
     } 
    
}

templateMatching::templateMatching(const templateMatching& orig) {
}

templateMatching::~templateMatching() {
     delete webClass;
     webClass = NULL;
}

void templateMatching::templateMatchingChoiceWay(){
    cout << "please input the matching way"<< endl;
    cout <<"0:sqdiff,1:sqdiffnormed,2:tmccorr,3:tmccorrnormed,4:tmcoeff,5:tmcoeffnormed"<<endl;
    int j;
    cin >> j ;
    switch (j)
    { 
        case SQDIFF:
            g_nMatchMethod = CV_TM_SQDIFF;
            break;          
        case SQDIFFNORMED:
           g_nMatchMethod = CV_TM_SQDIFF_NORMED;
            break;
        case TMCCORR:
           g_nMatchMethod = CV_TM_CCORR;
            break;
        case TMCCORRNORMED:
           g_nMatchMethod = CV_TM_CCORR_NORMED;
            break;
        case TMCOEFF:
            g_nMatchMethod = CV_TM_CCOEFF;
                   break;
        case TMCOEFFNORMED:
            g_nMatchMethod = CV_TM_CCOEFF_NORMED;
           break;
        default :
            cout <<"you input the num is wrong" <<endl;
    }
    cin.clear();
cout << "daSSSd"<<endl;
}
void templateMatching::printMatchingPoint()
{
    cout << "leftPoint.x" << leftPoint.x << "leftPoint.y" << leftPoint.y<< endl;
    cout << "rightPoint.x"<<rightPoint.x << "rightPoint.y" << rightPoint.y << endl;  
        getAndWebShare->status = status_4_done;
       getAndWebShare->x = ( rightPoint.x + leftPoint.x  )/2;
       getAndWebShare->y = (  rightPoint.y + leftPoint.y )/2;    
       Point po;       
      po.x =  getAndWebShare->x ;
       po.y = getAndWebShare->y;
       cout << "x "<<po.x << "y " <<po.y <<endl;
       
         webClass->write_Web_buf(getAndWebShare);
         rectangle(secne,leftPoint,rightPoint,Scalar(0,0,255),2,8,0);
        circle(secne,po,3,Scalar(255,255,0),1); 
//        imshow("secasddne",secne);
 //       waitKey(0);
    return ;
}
void templateMatching::choiceMatching()
{
     
    Mat srcImage  = secne.clone();
//    secne.copyTo(srcImage);
      
     Mat g_resultImgae;
    int resultImage_cols = secne.cols - obj.cols +1;
    int resultImage_rows = secne.rows - obj.rows + 1;
    if(resultImage_cols > 0 && resultImage_rows > 0)
    {
     g_resultImgae.create(resultImage_cols,resultImage_rows,CV_32FC1);
    matchTemplate(secne,obj,g_resultImgae,g_nMatchMethod);
    normalize(g_resultImgae,g_resultImgae,0,1,NORM_MINMAX,-1,Mat());
    double minValue;double maxValue;Point minLocation;Point maxLocation;
    Point matchLocation;
    minMaxLoc(g_resultImgae,&minValue,&maxValue,&minLocation,&maxLocation,Mat());
    if(g_nMatchMethod == CV_TM_SQDIFF  || g_nMatchMethod == CV_TM_SQDIFF_NORMED)
    {
        matchLocation = minLocation;
    }
    else
    {
        matchLocation = maxLocation;
    }
   
    rectangle(srcImage,matchLocation,Point(matchLocation.x + obj.cols,matchLocation.y+obj.rows),Scalar(0,0,255),2,8,0);
    rectangle(g_resultImgae,matchLocation,Point(matchLocation.x + obj.cols,matchLocation.y+obj.rows),Scalar(0,0,255),2,8,0);
    circle(srcImage,matchLocation,3,Scalar(255,255,0),1);
    circle(srcImage,Point(matchLocation.x + obj.cols,matchLocation.y+obj.rows),3,Scalar(255,255,0),1);
   leftPoint.x = matchLocation.x;
   leftPoint.y = matchLocation.y;
   rightPoint.x = matchLocation.x + obj.cols;
   rightPoint.y = matchLocation.y+obj.rows;

    
 // imshow("resule",srcImage);
 //  waitKey(0);

    }
    else
    {
        cout << "you input the template is small than the src image"<< endl;
            getAndWebShare->status = status_5_error;
         strcpy(getAndWebShare->error,"you input the template is small than the src image");
         webClass->write_Web_buf(getAndWebShare);
        return ;
    }
    cout <<"status"<< getAndWebShare->status<<endl;

}


