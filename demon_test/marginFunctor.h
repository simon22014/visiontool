/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   marginFunctor.h
 * Author: aqq
 *
 * Created on 2017年4月24日, 上午8:46
 */

#ifndef MARGINFUNCTOR_H
#define MARGINFUNCTOR_H
#include "man.h"
#include <opencv2/imgproc/imgproc.hpp>
enum MarginType
{
MARGINFUNCTOR,
MARGINGEOMETRY,
MARGINSHAPE,

};
void imageMarginFunctor(Mat image_m);

#endif /* MARGINFUNCTOR_H */

