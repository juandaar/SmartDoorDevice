#include <rfidCard.h>

RFIDCard::RFIDCard(RIFDState state)
{
    this->state = state;
}
RFIDCard::RFIDCard(RIFDState state, String value)
{
    this->state = state;
    this->value = value;
}
RIFDState RFIDCard::getState() { return state; };
String RFIDCard::getValue() { return value; };