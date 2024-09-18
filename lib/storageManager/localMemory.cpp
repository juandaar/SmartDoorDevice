#include <localMemory.h>

String LocalMemory::className = " LocalMemory";
String LocalMemory::classContext = " LocalMemory::";

LocalMemory::LocalMemory(ConsoleManager *console)
{
    this->console = console;
    LittleFS.begin();
}

File LocalMemory::getFile(String path)
{
    String methodName = "getFile";
    console->publish(classContext + methodName, "getFile->" + path, INF_LOG);
    File file = LittleFS.open(path, FILE_READ);
    if (!file || !file.available())
    {
        console->publish(classContext + methodName, "The file" + path + " was not found", WAR_LOG);
        return File();
    }
    return file;
}
