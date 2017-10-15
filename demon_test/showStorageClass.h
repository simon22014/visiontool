/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   showStorageClass.h
 * Author: aqq
 *
 * Created on 2017年4月18日, 上午9:56
 */

#ifndef SHOWSTORAGECLASS_H
#define SHOWSTORAGECLASS_H
#include <sys/ipc.h>
#include<sys/shm.h>
#include<errno.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>

#define cameraWidth 640
#define camerHight  480
#define capWidth 656
#define  capHeight 492
#define capSize capWidth*capHeight*3*2

class showStorageClass {
public:
    showStorageClass();
    showStorageClass(const showStorageClass& orig); 
    void read_buf(int shmid);
    int read_number();

    virtual ~showStorageClass();
private:
        char* capBuf ;
        int shmid;

};

#endif /* SHOWSTORAGECLASS_H */

