#include <manager.h>

String Manager::className = "Manager";
String Manager::classContext = "Manager::";

Manager::Manager()
{
    Serial.begin(CONSOLE_STREAMER_BAUDRATE);
    console = new ConsoleManager(CONSOLE_STREAMER, CONSOLE_NAME);
}

ExecutionState Manager::webServiceTaskExecution()
{
    static String taskName = "webServiceTask";

    // Critical section for Task 1
    console->publish(classContext + taskName, "Web Service Task is Running core-> " + String(xPortGetCoreID()), INF_LOG);
    console->publish(classContext + taskName, "DNS Loop-> ", INF_LOG);
    wifi->dnsLoop();
    webServer->loop();
    return EXE_OK;
}
ExecutionState Manager::notificationTaskExecution()
{
    static String taskName = "notificationTask";

    // Critical section for Task 2
    console->publish(classContext + taskName, "Notificiation Task is Running core-> " + String(xPortGetCoreID()), INF_LOG);

    return EXE_OK;
}

ExecutionState Manager::setup()
{
    const String methodName = "Setup";
    console->publish(classContext + methodName, "setup proccess in progress", INF_LOG);
    signalMessageSender = new SignalMessageSender(console);
    wifi = new WiFiManager(console);
    storage = new StorageManager(console);
    webServer = new WebServerManager(console, storage);
    // wifi->enableAP();
    // wifi->enableCP();
    wifi->connectToWIFI("***", "****");
    webServer->setup();
    webServer->start();
    console->publish(classContext + methodName, "setup proccess was succesfully finished", INF_LOG);
    return EXE_OK;
}
ExecutionState Manager::execution()
{
    String methodName = "Execution";
    console->publish(classContext + methodName, "Manager Execution Task is Running core-> " + String(xPortGetCoreID()), INF_LOG);

    signalMessageSender->hi();
    return EXE_OK;
}