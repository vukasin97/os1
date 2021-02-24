/*
 * GlobalP.cpp
 *
 *  Created on: May 21, 2019
 *      Author: OS1
 */
#include "GlobalP.h"
#include "PCB.h"
#include "Que.h"
#include "Thread.h"

Data::Data() {

}

PCB* Data::running = 0;
PCB* Data::idle = 0;
int Data::posID = 0;
volatile int Data::dispatchOnDemand = 0;

Thread* Data::begin = 0;



