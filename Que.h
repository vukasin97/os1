/*
 * Que.h
 *
 *  Created on: May 22, 2019
 *      Author: OS1
 */

#ifndef QUE_H_
#define QUE_H_

#include <stdlib.h>
#include "PCB.h"

class PCB;
struct Elem {
	PCB* pcb;
	Elem* next;
	Elem(PCB* p, Elem* n = 0);
};
class Que {
public:
	Que();
	~Que();
	void put(PCB* pcb);
	void insert(PCB* pcb);
	 Thread* getThread(ID d);
	PCB* getFirst();
	void updateBlockedList();
	Elem *first, *last;
private:
	int deletePCB(PCB* deletePCB);
	};



#endif /* QUE_H_ */
