/*
 * Prepare.h
 *
 *  Created on: May 31, 2019
 *      Author: OS1
 */

#ifndef PREPARE_H_
#define PREPARE_H_
#include "IVTEntry.h"
#include "KernelEv.h"
#define PREPAREENTRY(numEntry, callOld)\
void interrupt inter##numEntry(...);\
IVTEntry newEntry##numEntry(numEntry, inter##numEntry);\
void interrupt inter##numEntry(...){\
	if (newEntry##numEntry.myKEv != 0) newEntry##numEntry.myKEv->signal();\
	if(callOld==1 /*&& newEntry##numEntry.oldRoutine*/)\
		newEntry##numEntry.callOldRoutine();\
		dispatch();\
}




#endif /* PREPARE_H_ */
