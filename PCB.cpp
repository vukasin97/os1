



#include<dos.h>
#include "PCB.h"
#include <iostream.h>
#include "Que.h"
#include "Lock.h"
#include "GlobalP.h"
#include "IdleT.h"
#include "SCHEDULE.H"
Que *  PCB::threads = new Que();
PCB::PCB(Thread* myThreadd,StackSize stackSizee, Time timeSlicee ){

	this->timeSlice = timeSlicee;
	this->myThread = myThreadd;
	if(stackSizee > 65535) this->stackSize = 65535;
	this->stackSize = stackSizee;
	pcbSP =0;
	this->state = NEW;
	Lock::lock();
	waitQue = new Que();
	time_ = 0;
	expired = 0;
	Lock::unlock();
	this->stackSize /= sizeof(StackSize);



}

PCB::~PCB() {
	Lock::lock();
		Elem* tmp = threads->first;
		Elem* prev = 0;
		while(tmp != 0) {
			if (tmp->pcb == this) {
				if (tmp == threads->first) {
					threads->first = threads->first->next;
					if (threads->first == 0) threads->last = 0;
					tmp = 0;
				}
				else if (tmp == threads->last && tmp != threads->first) {
					prev->next = 0;
					threads->last = prev;
					tmp = 0;
				}
				else {
					prev->next = tmp->next;
					tmp = 0;
				}
			}
			else tmp = tmp->next;
		}

	delete waitQue;
	delete pcbSP;
	Lock::unlock();
}
void PCB::wrapper() {
		Data::running->myThread->run();

	PCB *newPCB = Data::running->waitQue->getFirst();

	while (newPCB != 0) {
		Lock::lock();
		newPCB->state = READY;
		Scheduler::put(newPCB);
		newPCB = Data::running->waitQue->getFirst();
		Lock::unlock();
	}
	Lock::lock();
	Data::running->state = OVER;
	Lock::unlock();
	dispatch();
}
void PCB::createStack() {
		Lock::lock();
	this->pcbSP = new unsigned [stackSize];
 #ifndef  BCC_BLOCK_IGNORE
	pcbSP[stackSize - 1] = 0x200;
		pcbSP[stackSize - 2] = FP_SEG(wrapper);
		pcbSP[stackSize - 3] = FP_OFF(wrapper);
		sp = FP_OFF(pcbSP+ stackSize - 12);
		bp = FP_OFF(pcbSP + stackSize - 12);
		ss = FP_SEG(pcbSP + stackSize - 12);
		state = READY;
                 #endif
	Lock::unlock();
}



