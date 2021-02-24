/*
 * Lock.cpp
 *
 *  Created on: May 21, 2019
 *      Author: OS1
 */
#include "Lock.h"
#include "Timer.h"
#include "Thread.h"
#include "GlobalP.h"
#include <dos.h>

Lock::Lock() {}

int Lock::val = 0;

void Lock::lock() {
	val++;
}
void Lock::unlock() {
	val--;
	if (Lock::val == 0 && Data::dispatchOnDemand) {
		dispatch();
	}
}



