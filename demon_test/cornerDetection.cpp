/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include"cornerDetection.h"
#include"cornerDetectionClass.h"
 void  imageCornerDetection(Mat &image_m)
 {
     Mat image = image_m.clone();
       //  cornerDetectionClass *gerMouse = new  cornerDetectionClass(image);
     std::auto_ptr<cornerDetectionClass> getCorner ( new cornerDetectionClass(image));
     getCorner->cornerDetectionType();
 
 }
