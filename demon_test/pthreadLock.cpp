/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   pthreadLock.cpp
 * Author: aqq
 * 
 * Created on 2017年4月18日, 下午1:50
 */

#include "pthreadLock.h"

pthreadLock::pthreadLock() {
   //   mutex = PTHREAD_MUTEX_INITIALIZER;
      pthread_mutex_init(&mutex, NULL);  
}

pthreadLock::pthreadLock(const pthreadLock& orig) {
}

pthreadLock::~pthreadLock() {
    pthread_mutex_destroy(&mutex);     
}
 void pthreadLock:: Lock()
 {
    pthread_mutex_lock(&mutex);
}
  void pthreadLock:: Unlock()
 {
   pthread_mutex_unlock(&mutex);
  }

