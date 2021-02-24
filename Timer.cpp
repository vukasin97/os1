/*
 * Timer.cpp
 *
 *  Created on: May 21, 2019
 *      Author: OS1
 */
#include <dos.h>
#include <stdio.h>
#include <iostream.h>
#include <stdlib.h>
#include "GlobalP.h"
#include "PCB.h"
#include  "Thread.h"
#include "Que.h"
#include "IdleT.h"
#include "SCHEDULE.h"
#include "Timer.h"
#include "Lock.h"
#include "KernelS.h"
volatile unsigned tsp;
volatile unsigned tss;
volatile unsigned tbp;

pInterrupt Timer::oldR = 0;
volatile int Timer::counter = 0;

extern void tick();

void Timer::setNewTimer() {
#ifndef BCC_BLOCK_IGNORE
	asm pushf;
	asm cli;
	Timer::oldR = getvect(8);
	setvect(0x60, Timer::oldR);
	setvect(8, Timer::timer);
	asm popf;
#endif


	Data::begin = new Thread();
	Data::begin->myPCB->state = RUNNING;
	Data::running = Data::begin->myPCB;
	Timer::counter = Data::running->timeSlice;
	Thread* idle = new IdleThread();
	Data::idle = idle->myPCB;
	idle->start();
	Scheduler::get();
}

void Timer::restoreOldTimer() {

	if (Data::running != Data::begin->myPCB)
		return;
#ifndef BCC_BLOCK_IGNORE
	asm pushf;
	asm cli;
	setvect(8, Timer::oldR);
	asm popf;
#endif


 delete PCB::threads;
	delete Data::begin;
}


void interrupt Timer::timer(...) {
/*cout << "Dovde dolazi";
asm cli*/
	if(Data::dispatchOnDemand == 0 && counter>0){
			counter--;
	}
	if (Data::dispatchOnDemand == 0) {
		tick();
		KernelSem::updateSemaphoreList();
	#ifndef BCC_BLOCK_IGNORE
				asm {
					  int 0x60
				}
	#endif
		}

	if(Data::dispatchOnDemand || Data::running->state == (BLOCKED || OVER) || counter == 0 || Data::running == Data::idle){
		if(Lock::val == 0){

			Data::dispatchOnDemand = 0;
#ifndef BCC_BLOCK_IGNORE
		asm{
			mov tsp, sp
			mov tss, ss
			mov tbp, bp
		}
#endif

		Data::running->sp = tsp;
		Data::running->ss = tss;
		Data::running->bp = tbp;


		if(Data::running->state == RUNNING && Data::running != Data::idle) {
			Data::running->state = READY;
			Scheduler::put(Data::running);
		}

		if(!(Data::running=Scheduler::get())){
			Data::running = Data::idle;
		}

		Data::running->state = RUNNING;
		tsp = Data::running->sp;
		tss = Data::running->ss;
		tbp = Data::running->bp;

		counter = Data::running->timeSlice;

		if(counter == 0) counter = -1;
#ifndef  BCC_BLOCK_IGNORE

		asm{
			mov sp, tsp
			mov ss, tss
			mov bp, tbp
		}
#endif
		}
		else Data::dispatchOnDemand = 1;
	}



}
