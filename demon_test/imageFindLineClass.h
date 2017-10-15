/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   imageFindLineClass.h
 * Author: aqq
 *
 * Created on 2017年4月19日, 上午9:32
 */

#ifndef IMAGEFINDLINECLASS_H
#define IMAGEFINDLINECLASS_H
#include "man.h"
#include "imagedealwithclass.h"
#include "showAndWebStorageClass.h"
#include "marginFunctorClass.h"
#include "theClass.h"
#include<iostream>

class imageFindLineClass {
public:
    imageFindLineClass();
    imageFindLineClass(Point,Point,Mat &);
    void imageEnlarge();
    void imageMargin();
    void imageSobel();
    void DrawLine(Mat&);
   void  imageGetLine();
   void imageOther();
   void imageOutLine();
   Mat & getCraveImage();
   Point getLineStartPoint();
   Point getLineEndPoint();
   Vec4f getLineParaPoint();
   int getBestCannyPos();
   virtual ~imageFindLineClass();
         
private:
      Point startPoint;
      Point endPoint;
      Mat beforeImage;
      Mat craveImage;
      int  bestCannyPos;
     locationChangeClass* locationCImage;
     vector<Vec4i> lines;  
     Vec4f line_paraPoint;
     marginFunctorClass* maegin;
     dimDealWitch * dimDW;
     Point lineStartPoint;
     Point lineEndPoint;
     
};

#endif /* IMAGEFINDLINECLASS_H */

