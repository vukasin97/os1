/*
 * Que.cpp
 *
 *  Created on: May 22, 2019
 *      Author: OS1
 */
#include <iostream.h>
#include <dos.h>
#include "Que.h"
#include "PCB.h"
#include "SCHEDULE.h"
#include "Lock.h"
#include "GlobalP.h"
#include <dos.h>
	Elem::Elem(PCB* p, Elem* n){
		pcb = p;
		next = n;
	}

	Que::Que() {
			first = 0;
			last = 0;
		}

	Que::~Que() {
			Elem* tmp, *dele;
			tmp = first;
			while(tmp != 0) {
				dele = tmp;
				tmp = tmp->next;
				delete dele;
			}
		}

	void Que::put(PCB* pcb) {
		Elem* tmp = new Elem(pcb);

		if (first == 0){
			first = tmp;
			last = tmp;}

		else{
			last->next = tmp;
		last = last->next;
		}
	}
	void Que::insert(PCB* pcb) {
		Lock::lock();
			Elem* tmp = new Elem(pcb);

			if (first == 0){
				first = tmp;
				last = tmp;
			}

			else{
				last->next = tmp;
			last = last->next;
			}
			Lock::unlock();
		}

	PCB* Que::getFirst() {
			if (first == 0)
				return 0;

			Elem* tmp = first;
			first = first->next;
			if(first == 0) last = 0;

			PCB* pcb = tmp->pcb;
			tmp = 0;

			return pcb;

		}
	Thread* Que::getThread(ID d) {
		Elem*	tmp = first;
			while (tmp != 0) {
			if(tmp->pcb->myThread->getId() == d) return tmp->pcb->myThread;
			tmp = tmp->next;
			}
			return 0;
	}

	void Que::updateBlockedList() {
		Elem* tmp = first;
		Elem* prev = 0;
		Elem* del = 0;
		while(tmp != 0) {
			del = tmp->next;
			if (tmp->pcb->time_ > 0) {
				tmp->pcb->time_ = tmp->pcb->time_ - 1;
				if (tmp->pcb->time_ == 0) {
					if (tmp == first) {
						del = first->next;
							first = first->next;
							if (first == 0) last = 0;
					}
					else if(tmp == last && tmp != first) {
						del = tmp->next;
						prev->next = 0;
						last = prev;
					}
					else {
						del = tmp->next;
						prev->next = tmp->next;
						tmp->next = 0;
						}
						PCB* pcb = tmp->pcb;
						pcb->expired = 1;
						pcb->state = READY;
						Scheduler::put(pcb);
				}
			}
			prev = tmp;
			tmp = del;
		}
		tmp = 0;
		prev = 0;
		del = 0;

	}









