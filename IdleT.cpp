/*
 * IdleT.cpp
 *
 *  Created on: May 22, 2019
 *      Author: OS1
 */

#include"IdleT.h"
#include "Thread.h"
#include "PCB.h"
#include <stdio.h>
#include <iostream.h>
#include "Lock.h"
#include <dos.h>
IdleThread::IdleThread():Thread( defaultStackSize,1	) {}

void IdleThread::run() {

	while(1) {

	}
}



