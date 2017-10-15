/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   pthreadLock.h
 * Author: aqq
 *
 * Created on 2017年4月18日, 下午1:50
 */

#ifndef PTHREADLOCK_H
#define PTHREADLOCK_H
#include<pthread.h>
class pthreadLock {
public:
    pthreadLock();
    pthreadLock(const pthreadLock& orig);
    void Lock();
    void Unlock();
    virtual ~pthreadLock();
private:
  pthread_mutex_t mutex;
};


#endif /* PTHREADLOCK_H */

