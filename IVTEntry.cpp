/*
 * IVTEntry.cpp
 *
 *  Created on: May 31, 2019
 *      Author: OS1
 */

#include "GlobalP.h"
#include "KernelEv.h"
#include "IVTEntry.h"
#include "event.h"
#include "Lock.h"
//#include "Prepare.h"
#include <iostream.h>
#include <stdio.h>
#include <dos.h>

IVTEntry* IVTEntry::IVTP[256];

IVTEntry::IVTEntry(IVTNo ivtN, pInterrupt newRoutinee) {

	Lock::lock();
	EntryNum = ivtN;
	newRoutine = newRoutinee;

#ifndef BCC_BLOCK_IGNORE
	oldRoutine = getvect(EntryNum);
	setvect(EntryNum, newRoutine);
#endif
    IVTEntry::IVTP[EntryNum] = this;
	Lock::unlock();
}

IVTEntry::~IVTEntry() {

	Lock::lock();
#ifndef BCC_BLOCK_IGNORE
	setvect(EntryNum, oldRoutine);
#endif
	newRoutine = 0;
	oldRoutine = 0;
	Lock::unlock();
	IVTEntry::IVTP[EntryNum]->myKEv=0;
}

IVTEntry* IVTEntry::get(IVTNo entry) {
	return IVTEntry::IVTP[entry];
}

void IVTEntry::callOldRoutine() {
	if (oldRoutine != 0)
		(*oldRoutine)();
}




