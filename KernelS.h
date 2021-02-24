/*
 * KernelS.h
 *
 *  Created on: May 27, 2019
 *      Author: OS1
 */

#ifndef KERNELS_H_
#define KERNELS_H_
#include "Que.h"
#include "semaphor.h"

struct Element {
	Que* que;
	Element* next;
	Element(Que* q, Element* n=0);
};
class KernelSem {
public:
	friend class Semaphore;
	KernelSem(Semaphore* mySem, int v);
	int wait(Time maxTimeToWait);
	int  signal(int n);
	int value() const;

	virtual ~KernelSem();
	Semaphore* mySem;
	Que *blocked;
	int val;
	static Element* first;
	static Element* last;
	static void updateSemaphoreList();
private:
	void updateList();
};




#endif /* KERNELS_H_ */
