#include <signalMessageSender.h>

String SignalMessageSender::className = "SignalMessager";
String SignalMessageSender::classContext = "SignalMessager::";
SignalMessageSender::SignalMessageSender(ConsoleManager *console, SemaphoreHandle_t *consoleSemaphore)
{
    this->console = console;
    this->consoleSemaphore = consoleSemaphore;
}

void SignalMessageSender::hi()
{
    static String taskName = "HI";
    if (xSemaphoreTake(*consoleSemaphore, portMAX_DELAY))
    {
        // Critical section for Task 2
        console->publish(classContext + taskName, "Signal Message Sender says HI", INF_LOG);
        delay(5000);
        xSemaphoreGive(*consoleSemaphore);
    }
}