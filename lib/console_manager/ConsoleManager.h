#include <String.h>

#ifndef _CONSOLE_MANAGER_h
#define _CONSOLE_MANAGER_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"

#endif

#ifndef LOGGING_LEVEL
#define LOGGING_LEVEL LOW_LEVEL
#endif

#if LOGGING_LEVEL == HIGH_LEVEL
#define SHOW_INF_MESSAGES
#define SHOW_VER_MESSAGES
#endif

#define SHOW_CONSOLE_MESSAGES
#define SHOW_ERR_MESSAGES

typedef enum LogLevel
{
  LOW_LEVEL,
  HIGH_LEVEL
} LogLevel;

typedef enum MsgLogTypes
{
  INF_LOG,
  ERR_LOG,
  EXE_LOG,
  VER_LOG,
  WAR_LOG
} MsgLogType;

class ConsoleManager
{
private:
  Stream &m_stream;

  String m_console_name;

public:
  ConsoleManager(Stream &stream);

  void init(String console_name);

  void publish(String str_context, String str_message, MsgLogType type_message);
};
#endif

extern ConsoleManager console;
