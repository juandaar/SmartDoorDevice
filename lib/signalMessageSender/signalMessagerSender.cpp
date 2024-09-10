#include <signalMessageSender.h>

String SignalMessageSender::className = "SignalMessager";
String SignalMessageSender::classContext = "SignalMessager::";
SignalMessageSender::SignalMessageSender(ConsoleManager *console)
{
    this->console = console;
}

void SignalMessageSender::hi()
{
    static String taskName = "HI";
    // Critical section for Task 2
    console->publish(classContext + taskName, "Signal Message Sender says HI", INF_LOG);
}