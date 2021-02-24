/*
 * Semaphore.h
 *
 *  Created on: May 27, 2019
 *      Author: OS1
 */

#ifndef SEMAPHOR_H_
#define SEMAPHOR_H_
class KernelSem;
typedef unsigned int Time;
class Semaphore {
public:
Semaphore (int init=1);
virtual ~Semaphore ();
virtual int wait (Time maxTimeToWait);
virtual int signal(int n=0);
int val () const; // Returns the current value of the semaphore
private:
KernelSem* myImpl;
};




#endif /* SEMAPHOR_H_ */
