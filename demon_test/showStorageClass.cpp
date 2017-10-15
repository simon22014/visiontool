/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   showStorageClass.cpp
 * Author: aqq
 * 
 * Created on 2017年4月18日, 上午9:56
 */

#include "showStorageClass.h"

showStorageClass::showStorageClass() {
}

showStorageClass::showStorageClass(const showStorageClass& orig) {
}

showStorageClass::~showStorageClass() {
}

void showStorageClass::read_buf(int shmid)
{
   //   capBuf = char[capSize];
    capBuf = (char*)shmat(shmid,0,0);
    if(NULL== capBuf)
    {
        perror("shmat is error");
        exit(-1);       
    }
   // printf("%s",capBuf);

}
int showStorageClass::read_number()
{
   
      FILE* readNumber=0;
     //err = fopen(&readNumber,"/home/aqq/NetBeansProjects/memId.conf","r+");
      readNumber = fopen("/home/aqq/NetBeansProjects/memId.conf","r");
     if(readNumber  == 0)
     {
         printf("read the number is wrong");
         exit(-1);
     }
     fscanf(readNumber,"%d",&shmid);
 //    printf("the mumber is %d",shmid);

     return shmid;
}