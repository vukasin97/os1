/*
 * Semaphore.cpp
 *
 *  Created on: May 27, 2019
 *      Author: OS1
 */
#include "Lock.h"
#include "KernelS.h"
#include "semaphor.h"
Semaphore::Semaphore (int init){

	Lock::lock();
	myImpl = new KernelSem(this,init);
	Lock::unlock();
}

Semaphore::~Semaphore(){
	Lock::lock();
	delete myImpl;
	Lock::unlock();
}

int Semaphore::wait(Time maxTimeToWait) {
	int ret = myImpl->wait(maxTimeToWait);
	return ret;
}
int Semaphore::signal(int n) {
	int ret = myImpl->signal(n);
	return ret;
}
int Semaphore::val() const {
Lock::lock();
int s = myImpl->value();
Lock::unlock();
return s;
}


