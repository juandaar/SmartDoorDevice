#include <ConsoleManager.h>

class SignalMessageSender
{
private:
    ConsoleManager *console;
    SemaphoreHandle_t *consoleSemaphore;
    static String className;
    static String classContext;

public:
    SignalMessageSender(ConsoleManager *console, SemaphoreHandle_t *consoleSemaphore);
    void hi();
};