#include <manager.h>

String Manager::className = "Manager";
String Manager::classContext = "Manager::";

Manager::Manager()
{
    Serial.begin(CONSOLE_STREAMER_BAUDRATE);
    console = new ConsoleManager(CONSOLE_STREAMER, CONSOLE_NAME);
    signalMessageSender = new SignalMessageSender();
    rfidManager = new RFIDManager(console, signalMessageSender);
}

ExecutionState Manager::webServiceTaskExecution()
{
    static String taskName = "webServiceTask";

    // Critical section for Task 1
    // console->publish(classContext + taskName, "Web Service Task is Running core-> " + String(xPortGetCoreID()), INF_LOG);
    // console->publish(classContext + taskName, "DNS Loop-> ", INF_LOG);
    wifi->dnsLoop();
    webServer->loop();
    return EXE_OK;
}
ExecutionState Manager::notificationTaskExecution()
{
    static String taskName = "notificationTask";

    // Critical section for Task 2
    // console->publish(classContext + taskName, "Notificiation Task is Running core-> " + String(xPortGetCoreID()), INF_LOG);

    return EXE_OK;
}

ExecutionState Manager::setup()
{
    const String methodName = "Setup";
    console->publish(classContext + methodName, "setup proccess in progress", INF_LOG);
    wifi = new WiFiManager(console);
    storage = new StorageManager(console);
    webServer = new WebServerManager(console, storage, wifi);
    signalMessageSender->setup();
    rfidManager->setup();
    wifi->enableAP();
    // wifi->enableCP();
    webServer->setup();
    webServer->start();
    console->publish(classContext + methodName, "setup proccess was succesfully finished", INF_LOG);
    return EXE_OK;
}
ExecutionState Manager::execution()
{
    String methodName = "Execution";
    if (rfidManager->loop() != EXE_OK)
    {
        console->publish(classContext + methodName, "Execution process was not finished", ERR_LOG);
    }
    return EXE_OK;
}