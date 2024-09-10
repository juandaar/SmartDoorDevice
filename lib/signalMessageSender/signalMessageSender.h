#ifndef _SIGNAL_MESSAGE_SENDER_h
#define _SIGNAL_MESSAGE_SENDER_h

#include <ConsoleManager.h>

class SignalMessageSender
{
private:
    ConsoleManager *console;
    SemaphoreHandle_t *consoleSemaphore;
    static String className, classContext;

public:
    SignalMessageSender(ConsoleManager *console);
    void hi();
};

#endif