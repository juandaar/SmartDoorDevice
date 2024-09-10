#ifndef _STORAGE_MANAGER_H
#define _STORAGE_MANAGER_H

#include <ConsoleManager.h>

class StorageManager
{
private:
    ConsoleManager *console;

public:
    StorageManager(ConsoleManager *console);
};

#endif