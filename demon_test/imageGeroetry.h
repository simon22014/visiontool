/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   imageGeroetry.h
 * Author: aqq
 *
 * Created on 2017年4月19日, 上午9:31
 */

#ifndef IMAGEFINDLINE_H
#define IMAGEFINDLINE_H
#include "imageFindLineClass.h"
#include "man.h"
enum GeroetryType{
FINDLINE,
FINDRECTANGLE,


};
void imageGeroetry(Mat &image_m);
void findLineFun(Mat & srcImage1);
void findCornerFun(Mat &srcImag1);


  
  
//void MouseEvent(int event, int x, int y, int flags, void* data);
#endif /* IMAGEFINDLINE_H */

