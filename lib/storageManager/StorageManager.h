#ifndef _STORAGE_MANAGER_H
#define _STORAGE_MANAGER_H

#include <ConsoleManager.h>
#include <ExecutionState.h>
#include <localMemory.h>

class StorageManager
{
private:
    ConsoleManager *console;
    LocalMemory *memory;
    static String className, classContext;

public:
    StorageManager(ConsoleManager *console);
    File getFile(String path);
};

#endif