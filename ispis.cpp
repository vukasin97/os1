/*
 * ispis.cpp
 *
 *  Created on: May 25, 2019
 *      Author: OS1
 */


#include "Lock.h"
#include "Thread.h"
#include "PCB.h"
#include "Timer.h"
#include "IdleT.h"
//#include "Prepare.h"
#include <iostream.h>
#include <stdio.h>
#include <dos.h>


extern int userMain(int argc, char* argv[]);


int main(int argc, char* argv[]) {

	Timer::setNewTimer();
	int value = userMain(argc, argv);
	Timer::restoreOldTimer();
	return value;

}

