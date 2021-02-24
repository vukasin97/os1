/*
 * GlobalP.h
 *
 *  Created on: May 21, 2019
 *      Author: OS1
 */

#ifndef GLOBALP_H_
#define GLOBALP_H_
#include "PCB.h"
#include "Thread.h"
class Thread;

class Data {
public:
	Data();
	~Data();
	static PCB* running;
	static PCB* idle ;
	volatile static int dispatchOnDemand;
	static int posID;
	static Thread* begin;



};



#endif /* GLOBALP_H_ */
