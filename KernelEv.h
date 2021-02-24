/*
 * KernelEv.h
 *
 *  Created on: May 31, 2019
 *      Author: OS1
 */

#ifndef KERNELEV_H_
#define KERNELEV_H_

#include "GlobalP.h"
#include "KernelEv.h"
#include "IVTEntry.h"
#include "event.h"
class KernelEv {

public:

	int value;
	IVTNo entryNum;
	PCB* owner;
	Event* event;

	KernelEv(IVTNo);
	~KernelEv();
	void signal();
	void wait();
};




#endif /* KERNELEV_H_ */
