#include <executionState.h>
#include <ConsoleManager.h>
#include <signalMessageSender.h>
#include <freertos/semphr.h>
#include <Arduino.h>
#include <String.h>
#include <settings.h>

class Manager
{
private:
	ConsoleManager *console;
	SemaphoreHandle_t consoleSemaphore;
	SignalMessageSender *signalMessageSender;

	void DIExecution();
	static String className;
	static String classContext;

public:
	Manager();
	ExecutionState setup();
	ExecutionState execution();
	ExecutionState webServiceTaskExecution();
	ExecutionState notificationTaskExecution();
};
