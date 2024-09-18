#include <ConsoleManager.h>

ConsoleManager::ConsoleManager(Stream &stream, String consoleName = "Console") : stream(stream)
{
  this->consoleName = consoleName;
  consoleSemaphore = xSemaphoreCreateMutex();
}

void ConsoleManager::publish(String context, String message, MsgLogType logType)
{
#if defined(SHOW_CONSOLE_MESSAGES) & (defined(SHOW_ERR_MESSAGES) || defined(SHOW_INF_MESSAGES) || defined(SHOW_VER_MESSAGES) || defined(SHOW_WAR_MESSAGES))
  String auxString = "";
  switch (logType)
  {
  case INF_LOG:
#ifdef SHOW_INF_MESSAGES
    auxString = "\033[37m " + consoleName + "\033[36m >>\033[35m " + context + "\033[36m >> \033[32m INF \033[36m >>\033[0m " + message;
#endif
    break;
  case ERR_LOG:
#ifdef SHOW_ERR_MESSAGES
    auxString = "\033[37m " + consoleName + " \033[36m >>\033[35m " + context + "\033[36m >> \033[31m ERR \033[36m >>\033[0m " + message;
#endif
    break;
  case VER_LOG:
#ifdef SHOW_VER_MESSAGES
    auxString = "\033[37m " + consoleName + " \033[36m >>\033[35m " + context + "\033[36m >> \033[32m VER \033[36m >>\033[0m " + message;
#endif
    break;
  case EXE_LOG:
#ifdef SHOW_VER_MESSAGES
    auxString = "\033[37m " + consoleName + " \033[36m >>\033[35m " + context + "\033[36m >> \033[32m EXE \033[36m >>\033[0m " + message;
#endif
    break;
  case WAR_LOG:
#ifdef SHOW_WAR_MESSAGES
    auxString = "\033[37m " + consoleName + "\033[36m >>\033[35m " + context + " \033[36m >>\033[33m WAR  \033[36m >>\033[0m " + message;
#endif
    break;
  default:
    auxString = "\033[37m " + consoleName + "\033[36m >> \033[35m default_message\033[36m >>\033[31m ERR  \033[36m >>\033[0m No valid type message";
    break;
  }

  if (xSemaphoreTake(consoleSemaphore, portMAX_DELAY))
  {
    stream.println(auxString);
    // vTaskDelay(100 / portTICK_PERIOD_MS);
    xSemaphoreGive(consoleSemaphore);
    // vTaskDelay(100 / portTICK_PERIOD_MS);
  }
#endif
}

void ConsoleManager::print(String message)
{
  if (xSemaphoreTake(consoleSemaphore, portMAX_DELAY))
  {
    stream.print(message);
    // vTaskDelay(100 / portTICK_PERIOD_MS);
    xSemaphoreGive(consoleSemaphore);
    // vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void ConsoleManager::println(String message)
{
  if (xSemaphoreTake(consoleSemaphore, portMAX_DELAY))
  {
    stream.println(message);
    // vTaskDelay(100 / portTICK_PERIOD_MS);
    xSemaphoreGive(consoleSemaphore);
    // vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}