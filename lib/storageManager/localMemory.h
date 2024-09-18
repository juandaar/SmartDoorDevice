#ifndef _LOCAL_MEMORY_H
#define _LOCAL_MEMORY_H

#include <LittleFS.h>
#include <ConsoleManager.h>

class LocalMemory
{
private:
    ConsoleManager *console;
    static String className, classContext;

public:
    LocalMemory(ConsoleManager *console);
    File getFile(String path);
};
#endif