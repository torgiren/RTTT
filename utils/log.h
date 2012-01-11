/*
 * log.h
 *
 *  Created on: 23-12-2011
 *      Author: crm
 */

#ifndef LOG_H_
#define LOG_H_

namespace Log
	{
	enum LogLvl {NONE=0x0, INFO=0x1, FAIL=0x2, OK=0x4, ALL=INFO|FAIL|OK};

	void info(/*const char *loc, */const char *fmt, ...);
	void fail(/*const char *loc, */const char *fmt, ...);
	void ok  (/*const char *loc, */const char *fmt, ...);

	void close();

	void setOut(FILE *sf);
	void setLogLvl(int flag);
	}

#ifndef LOG_CPP
#include <cstdio>
#define printf Log::info
#endif

#endif /* LOG_H_ */
