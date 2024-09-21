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
    wifi->dnsLoop();
    webServer->loop();
    return EXE_OK;
}
ExecutionState Manager::notificationTaskExecution()
{
    bool flag = wifi->isWifiActive();
    static String taskName = "notificationTask";
    firestoreClient->loop(flag);

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
    wifi->enableAP();
    // wifi->enableCP();
    webServer->setup();
    webServer->start();
    this->messageQueue = xQueueCreate(10, 30);
    rfidManager->setup(&messageQueue);
    firestoreClient = new FirestoreClient(console, &messageQueue);
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