/*
 * KernelEv.cpp
 *
 *  Created on: May 31, 2019
 *      Author: OS1
 */
#include "GlobalP.h"
#include "Lock.h"
#include "KernelEv.h"
#include "IVTEntry.h"
#include "event.h"
#include "PCB.h"
#include "SCHEDULE.h"

KernelEv::KernelEv(IVTNo entry) {
	entryNum = entry;
	owner = Data::running;
	value = 1;
	IVTEntry::get(entryNum)->myKEv=this;
}

KernelEv::~KernelEv(){
	Lock::lock();

	if(IVTEntry::IVTP[entryNum]!=0)
		IVTEntry::get(entryNum)->myKEv=0;
	Lock::unlock();
}

void KernelEv::wait() {

	if (owner == Data::running ) {
	if (value == 0) {
		owner->state = BLOCKED;

		dispatch();
	}
	else
		{
			value = 0;
		}
									}
}

void KernelEv::signal() {
	Lock::lock();
	if(value == 0 && owner->state == BLOCKED) {
		owner->state = READY;
		Scheduler::put(owner);
	}
	else {
		value = 1;
	}
		Lock::unlock();
}



