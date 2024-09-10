#ifndef _WEB_SERVER_MANAGER_h
#define _WEB_SERVER_MANAGER_h

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <Settings.h>
#include <WiFiManager.h>
#include <WebServer.h>
#include <ExecutionState.h>
#include <ConsoleManager.h>
#include <arduinojson.h>
#include <StorageManager.h>
#include <webAuthenticator.h>
#include <FS.h>

#define TIMEOUT_SENDING_VIEW 3000

#ifndef WEB_SERVER_PORT
#define WEB_SERVER_PORT 80
#endif

#ifndef USER_BUFFER
#define USER_BUFFER 500
#endif

#ifndef PASSWORD_FILE
#define PASSWORD_FILE "password.txt"
#endif

#ifndef WEB_SERVER_PAGE
#define WEB_SERVER_PAGE "www.systematix-poc.qc.ca"
#define PATH_WEB_SERVER "/platform"
#endif

#define WEB_SERVER_REDIRECTED                                                          \
    "<!DOCTYPE html><html><head><meta http-equiv=\"Refresh\" content=\"1;url=http://"; \
    pages += WEB_SERVER_PAGE;                                                          \
    pages += PATH_WEB_SERVER;                                                          \
    pages += "/\"> </head></html>"

class WebServerManager
{
private:
    bool serverState;
    String name;
    int userLevel;
    String authToken;
    String company;
    String *jsonFrame;
    unsigned long lastMillis;
    WebServer *server;
    void webServerConfig();
    void login();
    void upgrade();
    void open();
    void handleServer();
    String ContentType(String path);
    ExecutionState sendStreamFromSd(String path);
    ConsoleManager *console;
    StorageManager *storage;
    WebAuthenticator *authenticator;
    static String className, classContext;

public:
    WebServerManager(ConsoleManager *, StorageManager *);
    ExecutionState setup();
    ExecutionState init(String *data);
    ExecutionState start();
    ExecutionState stop();
    ExecutionState loop();
};
#endif