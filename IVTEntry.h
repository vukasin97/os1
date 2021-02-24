/*
 * IVTEntry.h
 *
 *  Created on: May 31, 2019
 *      Author: OS1
 */

#ifndef IVTENTRY_H_
#define IVTENTRY_H_

#include "event.h"

const unsigned char IVTNum = 256;
typedef void interrupt (*pInterrupt)(...);

class IVTEntry {
public:
	IVTEntry(IVTNo ivtN, pInterrupt  newRoutinee);
	~IVTEntry();

	IVTNo EntryNum;
	KernelEv* myKEv;
	pInterrupt oldRoutine, newRoutine;

	static IVTEntry* IVTP[256];

	static IVTEntry* get(IVTNo);


	void callOldRoutine();

	friend class KernelEv;
};




#endif /* IVTENTRY_H_ */
