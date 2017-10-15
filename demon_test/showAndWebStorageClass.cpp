/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   showAndWebStorageClass.cpp
 * Author: aqq
 * 
 * Created on 2017年4月18日, 上午9:57
 */

#include "showAndWebStorageClass.h"
using namespace std;
showAndWebStorageClass::showAndWebStorageClass() {
   shareLock = new pthreadLock();
   readBuf = new shStorage;
   if(readBuf  == NULL)
   {
       cout << "nimadebu"<<endl;
   }
}

showAndWebStorageClass::showAndWebStorageClass(const showAndWebStorageClass& orig) {
}

showAndWebStorageClass::~showAndWebStorageClass() {
    delete webClass;
    webClass = NULL;
    delete  shareLock;
    shareLock = NULL;
}
void   showAndWebStorageClass::CreateShowWebStorage()
{
   shmid=  shmget(IPC_PRIVATE,sizeof(shStorage),IPC_CREAT|0666);
    if(-1 == shmid)
    {
        perror("error");
        exit(-1);
    }
       
     printf ("%d\n",shmid); 
//       char code[20] ;       
 //      sprintf(code,"%d",shmid);
       FILE* fp = fopen("/home/aqq/NetBeansProjects/webrec.conf","w+");
       if(NULL == fp)
       {
           printf("open the fp is wrror");
           exit(-1);
       }
        fprintf(fp,"%d",shmid);
      
          //      fscanf(readNumber,"%d",&shmid);
#if 0
    shStorage* buf = shmat(shmid,0,0);
    if(-1 == buf)
    {
        perror("shmat is error");
        exit(-1);
        
    }
    write_buf(buf);
    printf ("%d\n",shmid);
#endif 
    fclose(fp);
    fp = NULL;

}
shStorage* showAndWebStorageClass::read_Web_Buf(int shareID)
{
    shareLock->Lock();
   //   capBuf = char[capSize];
   readBuf  = ( shStorage* )shmat(shareID,0,0);
    if(NULL== readBuf)
    {
        perror("shmat is error");
        exit(-1);       
    }
   return readBuf;
   shareLock->Unlock();
}
void   showAndWebStorageClass::write_Web_buf(shStorage*buf)
{
     cout << "1"<<endl;
#if 0
 //strcpy( (char*)readBuf,(char*)buf);
 //   *readBuf = *buf;
 //    memcpy(readBuf,buf,sizeof(readBuf));
#endif 
     cout << "1"<<endl;
  printf("k%d\n",buf->status);
    shmdt(buf);
}
void   showAndWebStorageClass::read_web_number()
{
      FILE* readNumberweb=0;
     //err = fopen(&readNumber,"/home/aqq/NetBeansProjects/memId.conf","r+");
      readNumberweb = fopen("/home/aqq/NetBeansProjects/webrec.conf","r");
     if(readNumberweb  == 0)
     {
         printf("read the number is wrong");
         exit(-1);
     }
     fscanf(readNumberweb,"%d",&shmid);
 //    printf("the mumber is %d",shmid);
}
 showAndWebStorageClass*showAndWebStorageClass:: getInstance()
    {
                         if(webClass == NULL)
                 {
                           webClass = new showAndWebStorageClass();
                 }
            return webClass;
    }
   int showAndWebStorageClass::getShareID()
   {
       return shmid;
  }
     
      
      
