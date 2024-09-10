#include <TimeHelper.h>

String TimeHelper::className = "SignalMessager";
String TimeHelper::classContext = "SignalMessager::";

bool TimeHelper::isWebTime = false;

ConsoleManager TimeHelper::*console = nullptr;

void TimeHelper::setCurrentTimeManual()
{
    if (!isWebTime)
    {
        static String methodName = "setCurrentTimeManual";
        struct tm t;
        t.tm_year = LOCAL_YEAR - 1900; // Year since 1900
        t.tm_mon = LOCAL_MONTH - 1;    // Month, 0 - jan
        t.tm_mday = LOCAL_DAY;         // Day of the month
        t.tm_hour = LOCAL_HOUR;        // Hours since midnight
        t.tm_min = LOCAL_MINUTE;       // Minutes after the hour
        t.tm_sec = LOCAL_SECOND;       // Seconds after the minute
        time_t t_of_day = mktime(&t);
        struct timeval tv = {t_of_day, 0};
        settimeofday(&tv, nullptr);
        time_t now = time(nullptr);
        console->publish(className + methodName, "Current Time set from Manual config\n\tCurrent Time:" + String(ctime(&now)), INF_LOG);
    }
}

void TimeHelper::setCurrentTimeNTP()
{
    static String methodName = "setCurrentTimeNTP";
    configTime(0, 0, POOL_NTP, TIME_NIST);
    time_t now = time(nullptr);
    while (now < 8 * 3600 * 2)
    {
        delay(500);
    }
    isWebTime = true;
    console->publish(className + methodName, "Current Time set from NTP\n\tCurrent Time:" + String(ctime(&now)), INF_LOG);
}

void TimeHelper::setConsole(ConsoleManager *consoleManager)
{
    console = consoleManager;
}