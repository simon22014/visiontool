/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   imageSmoothness.h
 * Author: aqq
 *
 * Created on 2017年4月27日, 下午12:56
 */
/*the tool about image smoothness */
#ifndef IMAGESMOOTHNESS_H
#define IMAGESMOOTHNESS_H
#include"man.h"
#include"imageSamplingClass.h"
enum image_smoothess
{
IMAGESAMPLING,
IMAGENOISE,
};

void  imageSmoothness(Mat &image_m);



#endif /* IMAGESMOOTHNESS_H */

