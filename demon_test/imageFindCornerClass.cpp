/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   imageFindCornerClass.cpp
 * Author: aqq
 * 
 * Created on 2017年4月26日, 上午8:30
 */

#include"imageFindCornerClass.h"
imageFindCornerClass::imageFindCornerClass() {
}
void imageFindCornerClass::FindLine()
{
   
      vector<Vec4f> ::iterator it =linescorner.begin();
      Vec4f findCornerLine;
     Point startPoint;
     Point endPoint;

    for( it = linescorner.begin();  it != linescorner.end() ; it++)
     {
         Mat image = beforeImage.clone();
          cout <<"wer "<<  (*it)[0]<<" " << (*it)[1] <<" "<< (*it)[2] <<" "<< (*it)[3] <<" "<< endl;
         startPoint.x = (*it)[0];
         startPoint.y = (*it)[1];
         endPoint.x = (*it)[2];
         endPoint.y = (*it)[3];
         imshow("beforeImage",image);
         waitKey(0);
          cout << "4"<<endl;
          if(image.channels()  == 1)
          {
              cout << "the image channels is 1 ,so you can take the line"<<endl;
              return;
          }
        findLine = new imageFindLineClass(startPoint,endPoint,image);
         findLine->imageEnlarge();
         findLine->imageOutLine();
         
         startPoint = findLine->getLineStartPoint();
         endPoint = findLine->getLineEndPoint();
          findCornerLine[0] = startPoint.x; findCornerLine[1] = startPoint.y;
         findCornerLine[2] = endPoint.x; findCornerLine[3] = endPoint.y;
         linesFindLine.push_back(findCornerLine);

     //    linesFindLine.push_back(findLine ->getLineParaPoint());    
    } 
}
void imageFindCornerClass::printTwoLine()
{
 //    imshow("beforex",beforeImage);
      vector<Vec4f>::iterator it;
      Point startPoint; 
      Point endPoint;
      for(it = linesFindLine.begin();it != linesFindLine.end(); it++)
      {   
         
          startPoint.x = (*it)[0];
         startPoint.y = (*it)[1];
         endPoint.x = (*it)[2];
         endPoint.y = (*it)[3];     
          printCrossLine( startPoint,beforeImage);           
          printCrossLine( endPoint,beforeImage);    
         line(beforeImage,startPoint,endPoint,Scalar(255,0,0),1); 
      }
      cout <<"size" << linesFindLine.size()<<endl;
//      imshow("beforeImagelx",beforeImage);
   //   waitKey(0);
}
void imageFindCornerClass::showIncludeAngle(double k0 ,double b0 ,double k1 ,double b1)
{
    Point P;
    P.x =100;
    P.y=100;
    char str_lx[20];
    float angleK0 = atan(k0) * 180 /PI;
    float angleK1 = atan(k1) * 180 /PI;
    Angle = angleK1 - angleK0;
    sprintf(str_lx,"angle: %f", Angle);
       putText(beforeImage,str_lx,P,CV_FONT_HERSHEY_PLAIN,1,
             Scalar(0,255,0));
    cout <<"angle  "<< Angle<<endl;
    

}
void imageFindCornerClass::showCornerAngle()
{
         vector<Vec4f>::iterator it;
      int i = 0;
      double k0 ,b0,k1,b1;
      for(it = linesFindLine.begin();it != linesFindLine.end(); it++)
      {   
          if( i  == 0)
          {
              if(((*it)[3] == 0) &&( (*it)[1]  == 0) &&  ((*it)[2] == 0) &&((*it)[0] == 0))
              {
                  k0 = b0 =0;
                  continue;
              }
          k0 =((*it)[3] - (*it)[1] ) / ((*it)[2]  -  (*it)[0]);
          b0 =  (*it)[1] - k0 * (*it)[0];
          cout <<(*it)[1] <<" "<<(*it)[0]<<" "<<(*it)[3]<<" "<<(*it)[2] <<" "<<endl;
          cout << " "<<i<<"   "<<k0<<" " <<b0 <<"  " <<endl;
          }
          else
          {
           if(((*it)[3] == 0) &&( (*it)[1]  == 0) &&  ((*it)[2] == 0) &&((*it)[0] == 0))
              {
                  k1 = b1 =0;
                  continue;
              }
            k1 =((*it)[3] - (*it)[1] ) / ((*it)[2]  -  (*it)[0]);
            b1 =  (*it)[1] - k1 * (*it)[0];
           cout <<(*it)[1] <<" "<<(*it)[0]<<" "<<(*it)[3]<<" "<<(*it)[2] <<" "<<endl;
            cout << " "<<i<<"  "<<k1<<"  " <<b1 <<endl;
          }
          i++;
      }
            cout << " g"<<i<<"   "<<k0<<" " <<b0 <<"  "<<k1<<"  " <<b1 <<endl;
            
      getTwoLineCorner(k0,b0,k1,b1);
      showIncludeAngle(k0,b0,k1,b1);
        imshow("beforeragelx",beforeImage);
      waitKey(0);


}
void imageFindCornerClass::getTwoLineCorner(double k0 ,double b0 ,double k1 ,double b1)
{
    char str_lx[20];
     CornerPoint.x = (b1 - b0 )/(k0 - k1);
    CornerPoint.y  = ( CornerPoint.x) * k0 + b0;
     cout << " g"<<" "<<k0<<" " <<b0 <<"  "<<k1<<"  " <<b1 <<endl;
      cout <<"point "<< CornerPoint.x<<"  y  "<<CornerPoint.y<<endl;
     circle(beforeImage,CornerPoint,5,Scalar(0,0,255),1); 
     sprintf(str_lx,"[%d,%d]", CornerPoint.x , CornerPoint.y);
     putText(beforeImage,str_lx,CornerPoint,CV_FONT_HERSHEY_PLAIN,1,
             Scalar(255,0,0));
     cout << "CornerPoint.x"<<  CornerPoint.x<<"CornerPoint.y"<<  CornerPoint.y<<endl;
 
}
 void imageFindCornerClass::printCrossLine(Point startPoint,Mat & image)
 {
                  Point centreup;
                  Point centredown;
                  centreup.x = startPoint.x ;
                  centreup.y = startPoint.y  -10;
                  centredown.x = startPoint.x ;
                  centredown.y = startPoint.y  +10;
                  line(image,centreup,centredown,Scalar(0,0,255),1);
                  centreup.x = startPoint.x -10 ;
                  centreup.y = startPoint.y  ;
                  centredown.x = startPoint.x +10;
                  centredown.y = startPoint.y  ;
                  line(image,centreup,centredown,Scalar(0,0,255),1);
 }
imageFindCornerClass::imageFindCornerClass(vector<Vec4f> linescorner,Mat &beforeImage)
:linescorner(linescorner),beforeImage(beforeImage)
{
#if 0
    cout << "a"<<endl;
          vector<Vec4i> ::iterator  it;
     for( it = linescorner.begin();  it != linescorner.end() ; it++)
     {
         cout <<"wer"<<  (*it)[0] << (*it)[1] << (*it)[2] << (*it)[3] << endl;
    }
#endif 
}
imageFindCornerClass::~imageFindCornerClass() {
                    delete findLine;
                    findLine = NULL;
}

