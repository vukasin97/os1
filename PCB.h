/*
 * PCB.h
 *
 *  Created on: May 22, 2019
 *      Author: OS1
 */
#ifndef PCB_H_
#define PCB_H_
#include "Lock.h"
#include "Thread.h"
class Data;
class Thread;
	typedef unsigned long StackSize;
	static const unsigned long MIN_STACK = 64000;
	enum ThreadState {NEW=0, OVER, BLOCKED, RUNNING,READY};

	class Que;

	class PCB {


	public:

		PCB(Thread* myThreadd,  StackSize stackSizee, Time timeSlicee);
		~PCB();
		unsigned* pcbSP;
		volatile unsigned  sp,ss,bp;

		Thread* myThread;
		StackSize stackSize;
		Time timeSlice;
		volatile enum ThreadState state;
		static  Que* threads;
		Que* waitQue;
		void createStack();
		unsigned int time_;
		unsigned int expired;
		static void wrapper();

	};





#endif /* PCB_H_ */
