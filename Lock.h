/*
 * Lock.h
 *
 *  Created on: May 21, 2019
 *      Author: OS1
 */

#ifndef LOCK_H_
#define LOCK_H_

class Lock {

public:
	Lock();
	static int val;
	static void lock();
	static void unlock();
};



#endif /* LOCK_H_ */
