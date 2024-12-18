#ifndef RFID_CARD_H
#define RFID_CARD_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"

#endif

typedef enum RIFDState
{
    CARD_OK,
    CARD_UNDEFINED,
    CARD_ERROR
} RIFDState;

class RFIDCard
{
private:
    RIFDState state;
    String value;
    QueueHandle_t *messageQuote;

public:
    RFIDCard(RIFDState state);
    RFIDCard(RIFDState state, String value);
    RIFDState getState();
    String getValue();
};

#endif