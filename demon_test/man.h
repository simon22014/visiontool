/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   man.h
 * Author: aqq
 *
 * Created on 2017年4月13日, 上午9:27
 */



#ifndef MAN_H
#define MAN_H
#include <cstdlib>
#include <stdio.h>
#include <ctime>
#include <opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/nonfree/features2d.hpp>
#include<opencv2/nonfree/nonfree.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/legacy/legacy.hpp>
//#include<opencv2/core/utility.hpp>
#include<opencv2/imgproc/imgproc.hpp>
//#include<opencv2/imgcodecs.hpp>
#include<string>
#include <iostream>
#include <pthread.h>
#include <signal.h>
#include<unistd.h>
#include <semaphore.h>
#include <vector>
#include<math.h>
#include<memory>
#define  PI  3.1415

using namespace std;
using namespace cv;
typedef pair<Mat,int> SaveMatInt;
extern vector<SaveMatInt> SaveMatIntToVector; 
extern int shareID;

#endif /* MAN_H */

