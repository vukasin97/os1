/*
 * syncPrintf.cpp
 *
 *  Created on: May 25, 2019
 *      Author: OS1
 */
#include <DOS.H>
#include <STDIO.H>
#include <STDARG.H>
#include "Lock.h"
int syncPrintf(const char *format, ...)
{
	int res;
	va_list args;
	Lock::lock();
		va_start(args, format);
	res = vprintf(format, args);
	va_end(args);
	Lock::unlock();
		return res;
}



