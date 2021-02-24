/*
 * mojtest.cpp
 *
 *  Created on: May 31, 2019
 *      Author: OS1
 */

#include <dos.h>
#include "Thread.h"
#include "Semaphor.h"
#include <iostream.h>

extern int syncPrintf(const char *format, ...);




//void tick() {}
class TestThread : public Thread
{
public:

	TestThread(): Thread() {};
	~TestThread()
	{
		waitToComplete();
	}
protected:

	void run();

};

void TestThread::run()
{
	syncPrintf("Thread %d: loop1 starts\n", getId());

	for(int i=0;i<32000;i++)
	{
		for (int j = 0; j < 32000; j++);
	}

	syncPrintf("Thread %d: loop1 ends, dispatch\n",getId());

	dispatch();

	//syncPrintf("Thread %d: loop2 starts\n",getId());

	for (int k = 0; k < 20000; k++);

	syncPrintf("Thread %d: loop2 ends\n",getId());

}




int userMain()
{
	cout << Thread::getRunningId();
	syncPrintf("User main starts\n");
	TestThread** t = new TestThread*[100];
	for(int i=0; i<100; i++) {
		t[i] = new TestThread();
		t[i]->start();
	}
for(int z=0; z<100; z++) {
	delete t[z];
}
delete t;
	syncPrintf("User main ends\n");
	return 16;
}






