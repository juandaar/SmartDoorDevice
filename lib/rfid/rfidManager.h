#ifndef RFID_MANAGER
#define RFID_MANAGER

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"

#endif

#define RFID_USERS "[{\"uid\":\"B6EA443D\",\"name\":\"Christian Charry\"},{\"uid\":\"06F7473D\",\"name\":\"David Arias\"},{\"uid\":\"1AF7F5B5\",\"name\":\"Simon Plante\"}]"

#define JSON_STATIC_MEMORY_RFID_USERS 200

#include <rfidCard.h>
#include <SPI.h>
#include <MFRC522.h>
#include <ConsoleManager.h>
#include <ArduinoJson.h>
#include <SignalMessageSender.h>
#include <PinMap.h>
#include <executionState.h>
#include <TaskMessage.h>

class RFIDManager
{
private:
    ConsoleManager *console;
    SignalMessageSender *signalSender;
    MFRC522 mfrc522;
    JsonDocument users;
    QueueHandle_t *messageQuote;
    RFIDCard check();
    static String className, classContext;

public:
    RFIDManager(ConsoleManager *console, SignalMessageSender *signalSender);
    ExecutionState setup(QueueHandle_t *messageQuote);
    ExecutionState loop();
};

#endif