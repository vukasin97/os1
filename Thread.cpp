/*
 * Thread.cpp
 *
 *  Created on: May 21, 2019
 *      Author: OS1
 */
#include "GlobalP.h"
#include "Thread.h"
#include "PCB.h"
#include <iostream.h>
#include <dos.h>
#include "Que.h"
#include "Timer.h"
#include "Lock.h"
#include "SCHEDULE.H"

int Thread::poc_id = 10;
Thread::Thread (StackSize stackSize , Time timeSlice ){
		Lock::lock();
		myPCB = new PCB(this,stackSize,timeSlice);
		id = poc_id++;
		PCB::threads->insert(myPCB);

		Lock::unlock();
	}

	Thread::~Thread() {

		waitToComplete();
		Lock::lock();
	    delete myPCB;
	    Lock::unlock();
	}

void Thread::waitToComplete() {
if(myPCB->state == OVER || myPCB->state == NEW) {
	return;
}
if (myPCB != Data::running && myPCB != Data::idle &&  Data::running->state != OVER && Data::running->state != NEW && myPCB != 0 &&
			this != Data::begin)
	{

		Lock::lock();
			Data::running->state = BLOCKED;
			myPCB->waitQue->put(Data::running);
	Lock::unlock();
			dispatch();


	}


}




void dispatch() {
#ifndef BCC_BLOCK_IGNORE
	asm pushf
	asm cli
#endif
	Data::dispatchOnDemand = 1;
	Timer::timer();
	Data::dispatchOnDemand	= 0;
#ifndef BCC_BLOCK_IGNORE
	asm popf
#endif


}


void Thread::start() {

	if (myPCB == 0 && myPCB->state != NEW) return;
	Lock::lock();

		myPCB->state = READY;
		myPCB->createStack();
		Scheduler::put(myPCB);
	Lock::unlock();
}
Thread* Thread::getThreadById(ID id) {
	return PCB::threads->getThread(id);
}
ID Thread::getRunningId() {
		PCB* pcb = Data::running;
		if (pcb != 0) {
			return pcb->myThread->getId();
		}
		else return -1;
}
ID Thread::getId() {
	return id;
}


