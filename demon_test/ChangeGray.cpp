/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include"ChangeGray.h"
#include"ChangeGrayClass.h"
 void   imageChangeGray(Mat & image)
 {
     Mat srcImage = image.clone();
     if(!srcImage.data)
     {
         cout <<"the image data is NULL"<<endl;
         return;
     }
       //          ChangeGrayClass * ChGrayClass = new ChangeGrayClass(image_m);
        std::auto_ptr<ChangeGrayClass> ChGrayClass ( new ChangeGrayClass(srcImage));
        ChGrayClass->ChGrayClassType();
 
 }
