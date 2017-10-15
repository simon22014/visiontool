/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   showAndWebStorageClass.h
 * Author: aqq
 *
 * Created on 2017年4月18日, 上午9:57
 */

#ifndef SHOWANDWEBSTORAGECLASS_H
#define SHOWANDWEBSTORAGECLASS_H
#include <stdio.h>
#include <cstdlib>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <pthread.h>
#include <iostream>
#include <pthread.h>
#include <signal.h>
#include<unistd.h>
#include <semaphore.h>
#include <vector>
#include <string.h>
#include "showStorageClass.h"
#include "dataStruct.h"
#include "pthreadLock.h"
class showAndWebStorageClass {
public:
    showAndWebStorageClass();
    showAndWebStorageClass(const showAndWebStorageClass& orig);
    void CreateShowWebStorage();
    shStorage* read_Web_Buf(int );
    void   write_Web_buf(shStorage*buf);
    void   read_web_number();
    showAndWebStorageClass* getInstance();
    int getShareID();
    virtual ~showAndWebStorageClass();
private:
     showAndWebStorageClass *webClass;
    shStorage* readBuf;
    int shmid;
    pthreadLock* shareLock;

};


#endif /* SHOWANDWEBSTORAGECLASS_H */

