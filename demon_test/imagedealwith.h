/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   imagedealwith.h
 * Author: aqq
 *
 * Created on 2017年4月14日, 下午2:37
 */

#ifndef IMAGEDEALWITH_H
#define IMAGEDEALWITH_H
#include "man.h"
    enum enum_imagedealwith{
        IMAGE_GRY, //gay   0
        IMAGE_REMAP, //remap 1
        IMAGE_LOCATION_CHANGE, //location change 2
        IMAGE_COLOR_COVERSION,  //Hsv
        IMAGE_THRESHOLDVALUE,
     
};
Mat  imageDealWith(Mat & image_clone); //Image deal with
Mat remap_Image(Mat & image_clone); //remap image
Mat locationChange_Image(Mat & image_clone); // location change image
Mat ImageColorCoversion(Mat & image_clone); //color coversion image
Mat imageThresholdValue(Mat & image_clone); //image threashold value
#endif /* IMAGEDEALWITH_H */

