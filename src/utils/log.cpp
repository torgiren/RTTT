/*
 * log.cpp
 *
 *  Created on: 23-12-2011
 *      Author: crm
 */

#define LOG_CPP

#include <cstdio>
#include <cstdarg>
#include <ctime>

#include "log.h"

namespace Log
	{
	void date();
	void flush();

	int logLvl=ALL;

	FILE *out=stdout;
	va_list args;
	}

void Log::date()
	{
	static char date[64];
	static time_t dtime;
	static tm *ddate;

	dtime=time(NULL);
	ddate=localtime(&dtime);

	strftime(date, 64, "%Y-%m-%d %H:%M:%S", ddate);
	fprintf(out, "[%s] ", date);
	}

void Log::flush()
	{
	fflush(out);
	}

void Log::info(/*const char *loc, */const char *fmt, ...)
	{
	if(!(logLvl&INFO))
		return;
	date();
	fprintf(out, "INFO: ");

	va_start(args, fmt);
	vfprintf(out, fmt, args);
	va_end(args);

	fprintf(out, "\n");
	flush();
	}

void Log::fail(/*const char *loc, */const char *fmt, ...)
	{
	if(!(logLvl&FAIL))
		return;
	date();
	fprintf(out, "FAIL: ");

	va_start(args, fmt);
	vfprintf(out, fmt, args);
	va_end(args);

	fprintf(out, "\n");
	flush();
	}

void Log::ok(/*const char *loc, */const char *fmt, ...)
	{
	if(!(logLvl&OK))
		return;
	date();
	fprintf(out, "OK  : ");

	va_start(args, fmt);
	vfprintf(out, fmt, args);
	va_end(args);

	fprintf(out, "\n");
	flush();
	}

void Log::close()
	{
	if(out!=NULL && out!=stdout)
		fclose(out);
	}

void Log::setOut(FILE *sf)
	{
	if(!sf)
		fail("Log.setOut: NULL");
	else
		out=sf;
	}

void Log::setLogLvl(int flag)
	{
	logLvl=flag;
	}




