#include <signalMessageSender.h>

String SignalMessageSender::className = "SignalMessager";
String SignalMessageSender::classContext = "SignalMessager::";
SignalMessageSender::SignalMessageSender()
{
    signalSemaphore = xSemaphoreCreateMutex();
}

void SignalMessageSender::setup()
{
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(LED_PIN, OUTPUT);
}

void SignalMessageSender::authorized()
{
    if (xSemaphoreTake(signalSemaphore, portMAX_DELAY))
    {
        digitalWrite(LED_PIN, HIGH);
        tone(BUZZER_PIN, BUZZER_ACCESS_FREQUENCY);
        delay(BUZZER_ACCESS_TIMEOUT);
        // digitalWrite(GREEN_PIN,HIGH);
        noTone(BUZZER_PIN);
        digitalWrite(BUZZER_PIN, HIGH);
        delay(2000);
        digitalWrite(LED_PIN, LOW);
        xSemaphoreGive(signalSemaphore);
    }
}
void SignalMessageSender::denied()
{
    if (xSemaphoreTake(signalSemaphore, portMAX_DELAY))
    {
        tone(BUZZER_PIN, BUZZER_DENIED_FREQUENCY);
        delay(BUZZER_DENIED_TIMEOUT);
        noTone(BUZZER_PIN);
        digitalWrite(BUZZER_PIN, HIGH);
        delay(BUZZER_DENIED_TIMEOUT);
        tone(BUZZER_PIN, BUZZER_DENIED_FREQUENCY);
        delay(BUZZER_DENIED_TIMEOUT);
        noTone(BUZZER_PIN);
        digitalWrite(BUZZER_PIN, HIGH);
        delay(2000);
        xSemaphoreGive(signalSemaphore);
    }
}
void SignalMessageSender::connection()
{
    if (xSemaphoreTake(signalSemaphore, portMAX_DELAY))
    {

        xSemaphoreGive(signalSemaphore);
    }
}
void SignalMessageSender::connected()
{
    xSemaphoreTake(signalSemaphore, portMAX_DELAY);

    xSemaphoreGive(signalSemaphore);
}