/*
 * IdleT.h
 *
 *  Created on: May 22, 2019
 *      Author: OS1
 */

#ifndef IDLET_H_
#define IDLET_H_

#include "Thread.h"

	class Thread;

	class IdleThread:public Thread	{

	public:
		IdleThread();
		virtual void run();
		int getIdle(){return 1;}


	};




#endif /* IDLET_H_ */
