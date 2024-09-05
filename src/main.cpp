#include <Arduino.h>
#include <pinMap.h>
#include <settings.h>
#include <imperialMarch.h>
#include <manager.h>
#include <freertos/FreeRTOS.h>

TaskHandle_t *loop1Handler = NULL;
TaskHandle_t *loop2Handler = NULL;

ImperialMarch *imperialMarch = new ImperialMarch();

Manager *manager = new Manager();

void loop1(void *pvParameters)
{
  for (;;)
  {
    manager->webServiceTaskExecution();
  }
}

void loop2(void *pvParameters)
{
  for (;;)
  {
    manager->notificationTaskExecution();
  }
}

void setup()
{
  // imperialMarch->starWars();
  manager->setup();

  xTaskCreate(loop1, "Web Task", 1000, NULL, 1, loop1Handler);
  xTaskCreate(loop2, "Notification", 1000, NULL, 1, loop2Handler);
}

void loop()
{
  manager->execution();
}