#ifndef _TIME_HELPER_h
#define _TIME_HELPER_h

#include <sys/time.h>
#include <time.h>
#include <ConsoleManager.h>

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#define POOL_NTP "pool.ntp.org"
#define TIME_NIST "time.nist.gov"

#define LOCAL_YEAR 2100
#define LOCAL_MONTH 1
#define LOCAL_DAY 1
#define LOCAL_HOUR 0
#define LOCAL_MINUTE 0
#define LOCAL_SECOND 0
class TimeHelper
{
private:
    static ConsoleManager *console;
    static bool isWebTime;

public:
    static String className, classContext;
    static void setCurrentTimeManual();
    static void setCurrentTimeNTP();
    static void setConsole(ConsoleManager *);
};

#endif