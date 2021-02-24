/*
 * event.cpp
 *
 *  Created on: May 31, 2019
 *      Author: OS1
 */

#include "KernelEv.h"
#include "Lock.h"

Event::Event(IVTNo ivtNo) {

	Lock::lock();
	myImpl = new KernelEv(ivtNo);
	Lock::unlock();
}

Event::~Event() {

	Lock::lock();
	delete myImpl;
	Lock::unlock();
}

void Event::wait() {
if (myImpl != 0)  myImpl->wait();

}

void Event::signal() {

	if (myImpl != 0)
	myImpl->signal();
}



