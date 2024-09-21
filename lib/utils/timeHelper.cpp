#include <TimeHelper.h>

String TimeHelper::className = "SignalMessager";
String TimeHelper::classContext = "SignalMessager::";

bool TimeHelper::isWebTime = false;

void TimeHelper::setCurrentTimeManual()
{
    if (!isWebTime)
    {
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
    }
}

void TimeHelper::setCurrentTimeNTP()
{
    configTime(GMT_OFF_SET_SEC, DAY_LIGHT_OFF_SET, POOL_NTP, TIME_NIST);
    delay(2000);
    isWebTime = true;
}
