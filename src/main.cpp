#include <Arduino.h>
#include <pinMap.h>
#include <settings.h>
#include <imperialMarch.h>
#include <manager.h>
#include <freertos/FreeRTOS.h>

#ifndef WEB_SERVICE_TASK_STACK_SIZE
#define WEB_SERVICE_TASK_STACK_SIZE 16384
#endif

#ifndef NOTIFICATION_STACK_SIZE
#define NOTIFICATION_STACK_SIZE 8192
#endif

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

  xTaskCreatePinnedToCore(loop2, "Notification", NOTIFICATION_STACK_SIZE, NULL, 1, loop2Handler, 1);
  xTaskCreatePinnedToCore(loop1, "Web Server", WEB_SERVICE_TASK_STACK_SIZE, NULL, 1, loop1Handler, 0);
}

void loop()
{
  manager->execution();
}
