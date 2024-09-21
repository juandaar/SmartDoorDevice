#include <Arduino.h>
#include <pinMap.h>
#include <settings.h>
#include <manager.h>
#include <freertos/FreeRTOS.h>

#ifndef WEB_SERVICE_TASK_STACK_SIZE
#define WEB_SERVICE_TASK_STACK_SIZE 15000
#endif

#ifndef NOTIFICATION_STACK_SIZE
#define NOTIFICATION_STACK_SIZE 15000
#endif

TaskHandle_t *loop1Handler = NULL;
TaskHandle_t *loop2Handler = NULL;

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
    if (WiFi.status() == WL_CONNECTED)
    {
    }
    manager->notificationTaskExecution();
  }
}

void setup()
{

  manager->setup();

  xTaskCreatePinnedToCore(loop2, "Notification", NOTIFICATION_STACK_SIZE, NULL, 1, loop2Handler, 1);
  xTaskCreatePinnedToCore(loop1, "Web Server", WEB_SERVICE_TASK_STACK_SIZE, NULL, 1, loop1Handler, 0);
}

void loop()
{
  manager->execution();
}