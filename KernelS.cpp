/*
 * KernelS.cpp
 *
 *  Created on: May 27, 2019
 *      Author: OS1
 */



#include "KernelS.h"
#include "Lock.h"
#include "GlobalP.h"
#include "SCHEDULE.h"
#include "iostream.h"
#include <dos.h>
Element::Element(Que* q, Element* n) {
		que = q;
		next = n;
}
Element* KernelSem::first = 0;
Element* KernelSem::last = 0;
KernelSem::KernelSem(Semaphore* mySem, int v) {
	Lock::lock();
	this->mySem = mySem;
	val = v;
	blocked = new Que();
	updateList();
	Lock::unlock();
}

void KernelSem::updateList() {
	Element* curr = new Element(blocked);
	if (first == 0) {
		first = curr;
		last = first;
	}
	else {
		last->next = curr;
		last = curr;
	}
}
int KernelSem::wait(Time maxTimeToWait) {
	Lock::lock();
			val--;
		if (val >= 0) {
			Lock::unlock();
			return 1;
		}
		Data::running->time_ = maxTimeToWait;
		Data::running->state = BLOCKED;
		blocked->put(Data::running);
		Lock::unlock();
		dispatch();
		if (Data::running->expired == 1)  {
			Data::running->expired = 0;
			return 0;
		}
		return 1;
}
int KernelSem::signal(int n) {
	Lock::lock();
	if (n == 0) {
		if (val++ < 0) {
			PCB* tmp = blocked->getFirst();
					tmp->state = READY;
					Scheduler::put(tmp);
					Lock::unlock();
					return 0;
		}
		else {
			Lock::unlock();
			return 0;
		}

	}
	else if (n < 0) {
		Lock::unlock();
		return n;
	}
	else {
		int deblock = 0;
		int curr = n;
		while(val < 0) {
			val++;
			n--;
			deblock++;
			PCB* tmp = blocked->getFirst();
			tmp->state = READY;
			Scheduler::put(tmp);

		}
	if (n > 0) {
		val += (curr - deblock);
	}

	Lock::unlock();
	return deblock;
	}
}
	int KernelSem::value() const{

		return val;
	}

	void KernelSem::updateSemaphoreList() {
		Element* tmp = first;
		while (tmp != 0) {
			Que* q = tmp->que;
			if(q) {
				q->updateBlockedList();
			}
			tmp = tmp->next;
		}

	}
	KernelSem::~KernelSem() {
		Lock::lock();
		Element* tmp = first;
		Element* prev = 0;
		Element* del = 0;
		while(tmp !=0) {
			if (tmp->que == blocked) {
				if (tmp == first) {
					del = first;
					first = first->next;
					if(first == 0) last =0;
					delete tmp;
				}
				else if (tmp == last && tmp != first) {
				del = tmp;
				prev->next = 0;
				last = prev;
				delete tmp;
							}
				else{
				del = tmp;
				prev->next = tmp->next;
				tmp->next = 0;
				delete tmp;
								}
				break;
			}
			else {
				prev = tmp;
				tmp = tmp->next;
			}
		}
		Lock::unlock();
	}

