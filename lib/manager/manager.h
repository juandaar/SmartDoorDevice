#include <executionState.h>
#include <ConsoleManager.h>

#include <freertos/semphr.h>
#include <Arduino.h>
#include <String.h>
#include <settings.h>

class Manager
{
private:
	ConsoleManager *console;
	SemaphoreHandle_t consoleSemaphore;

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
