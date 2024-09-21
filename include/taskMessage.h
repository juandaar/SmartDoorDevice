#ifndef TASK_MESSAGE_H
#define TASK_MESSAGE_H
#include <Arduino.h>
struct TaskMessage
{
    bool isAuthorized;
    String name;
    String cardId;
};
#endif