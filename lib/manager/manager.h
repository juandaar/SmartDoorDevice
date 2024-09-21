#ifndef _MANAGER_h
#define _MANAGER_h
#include "esp_spi_flash.h"
#include <executionState.h>
#include <ConsoleManager.h>
#include <wifiManager.h>
#include <signalMessageSender.h>
#include <freertos/semphr.h>
#include <Arduino.h>
#include <String.h>
#include <settings.h>
#include <webServerManager.h>
#include <StorageManager.h>
#include <rfidManager.h>
#include <FirestoreClient.h>
#include <TaskMessage.h>

class Manager
{
private:
	ConsoleManager *console;
	SignalMessageSender *signalMessageSender;
	WiFiManager *wifi;
	WebServerManager *webServer;
	StorageManager *storage;
	RFIDManager *rfidManager;
	FirestoreClient *firestoreClient;
	QueueHandle_t messageQueue;
	static String className, classContext;

public:
	Manager();
	ExecutionState setup();
	ExecutionState execution();
	ExecutionState webServiceTaskExecution();
	ExecutionState notificationTaskExecution();
};

#endif
