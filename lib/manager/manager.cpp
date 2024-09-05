#include <manager.h>

String Manager::className = "Manager";
String Manager::classContext = "Manager::";

Manager::Manager()
{
    consoleSemaphore = xSemaphoreCreateMutex();
    Serial.begin(CONSOLE_STREAMER_BAUDRATE);
    console = new ConsoleManager(CONSOLE_STREAMER);
}

ExecutionState Manager::webServiceTaskExecution()
{
    static String taskName = "webServiceTask";
    if (xSemaphoreTake(consoleSemaphore, portMAX_DELAY))
    {
        // Critical section for Task 2
        console->publish(classContext + taskName, "Web Service Task is Running", INF_LOG);
        vTaskDelay(500 / portTICK_PERIOD_MS);
        xSemaphoreGive(consoleSemaphore);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    return EXE_OK;
}
ExecutionState Manager::notificationTaskExecution()
{
    static String taskName = "notificationTask";
    if (xSemaphoreTake(consoleSemaphore, portMAX_DELAY))
    {
        // Critical section for Task 2
        console->publish(classContext + taskName, "Notificiation Task is Running", INF_LOG);
        vTaskDelay(500 / portTICK_PERIOD_MS);
        xSemaphoreGive(consoleSemaphore);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    return EXE_OK;
}

void Manager::DIExecution() {}

ExecutionState Manager::setup()
{
    const String method_name = "Setup";
    console->init(CONSOLE_NAME);
    console->publish(classContext + method_name, "Console streamer was set successfully", INF_LOG);
    return EXE_OK;
}
ExecutionState Manager::execution()
{
    String methodName = "Execution";
    if (xSemaphoreTake(consoleSemaphore, portMAX_DELAY))
    {

        console->publish(classContext + methodName, "Manager Execution Task is Running", INF_LOG);
        vTaskDelay(500 / portTICK_PERIOD_MS);
        xSemaphoreGive(consoleSemaphore);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    return EXE_OK;
}