/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   webStructClass.h
 * Author: aqq
 *
 * Created on 2017年4月17日, 下午2:52
 */

#ifndef WEBSTRUCTCLASS_H
#define WEBSTRUCTCLASS_H
#include <cstdlib>
#include <stdio.h>
#include <ctime>
#include <opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/nonfree/features2d.hpp>
#include<opencv2/nonfree/nonfree.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/legacy/legacy.hpp>
#include <iostream>
#include <pthread.h>
#include <signal.h>
#include<unistd.h>
#include <semaphore.h>
#include <vector>
#include "showAndWebStorageClass.h"
using namespace std;
using namespace cv;
class WebStrucetCLASS
{
public :
    WebStrucetCLASS();
    WebStrucetCLASS(shStorage*);
    Mat  GetImage(Mat & ,char *  );
    void ChangeMatChar(Mat & );
    void change16To10(char* );
     char getCharByNum(int );
    void  getRGBInNum(int *RGBInNum,int row,int cols);
    Mat readRgbDataMode();
    Mat readRgbDataTest();
    Mat carveImageTemplate();
    virtual ~WebStrucetCLASS();
private:
    shStorage*  getAndWebShare;   
    char rgbData_mode[capSize]; //模板rgb数据   
    char rgbData_test[capSize]; //待测试rgb数据
     int  changeNumber[capHeight][capWidth][3]; //capWidth
  Mat  Mat_Image_template;
  Mat  Mat_Image_test;

   
};

#endif /* WEBSTRUCTCLASS_H */

