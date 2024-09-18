#ifndef _SIGNAL_MESSAGE_SENDER_h
#define _SIGNAL_MESSAGE_SENDER_h

#include <ConsoleManager.h>
#include <pinMap.h>

#ifndef BUZZER_PIN
#define BUZZER_PIN 2
#endif

#define BUZZER_FIRST_FREQUENCY 3000
#define BUZZER_DENIED_FREQUENCY 500
#define BUZZER_ACCESS_FREQUENCY 2500 // Specified in Hz
#define BUZZER_DENIED_TIMEOUT 330
#define BUZZER_ACCESS_TIMEOUT 1000
#define BUZZER_FIRST_TIMEOUT 5000

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"

#endif

class SignalMessageSender
{
private:
    SemaphoreHandle_t signalSemaphore;
    static String className, classContext;

public:
    SignalMessageSender();
    void setup();
    void authorized();
    void denied();
    void connection();
    void connected();
};

#endif