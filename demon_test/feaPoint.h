/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   feaPoint.h
 * Author: aqq
 *
 * Created on 2017年4月12日, 下午3:45
 */


#ifndef FEAPOINT_H
#define FEAPOINT_H
#include <opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/nonfree/features2d.hpp>
#include<opencv2/nonfree/nonfree.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/legacy/legacy.hpp>
#include <opencv2/core/core.hpp>
#include <cstdio>
#include <iostream>
#include <pthread.h>
#include <signal.h>
#include<unistd.h>
#include <semaphore.h>
#include <cstdlib>
using namespace std;
using namespace cv;



#ifdef __cplusplus
extern "C" {
#endif
    


Mat  feaPointChangeRay(Mat & image);
void feaPointdimDealWitch(Mat &image);    
Mat feaPointArithmetic(Mat &image);
void feaPointMatching();   
void peinFeaPointMat(Mat & image);
   
#ifdef __cplusplus
}
#endif
#endif /* FEAPOINT_H */

