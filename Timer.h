/*
 * Timer.h
 *
 *  Created on: May 21, 2019
 *      Author: OS1
 */

#ifndef TIMER_H_
#define TIMER_H_


typedef void interrupt (*pInterrupt)(...);

class Timer {
public:
	static volatile int counter;

	static void restoreOldTimer();
	static void setNewTimer();

	static pInterrupt oldR;
	static void interrupt timer(...);

};


#endif /* TIMER_H_ */
