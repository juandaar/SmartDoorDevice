#include <StorageManager.h>
#

String StorageManager::className = "StorageManager";
String StorageManager::classContext = "StorageManager::";

StorageManager::StorageManager(ConsoleManager *console)
{
    this->console = console;
    this->memory = new LocalMemory(console);
}

File StorageManager::getFile(String path)
{
    return this->memory->getFile(path);
}