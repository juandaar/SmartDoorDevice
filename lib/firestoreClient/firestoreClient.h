#ifndef FIRESTORE_CLIENT_H
#define FIRESTORE_CLIENT_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFiClientSecure.h>
#include <ConsoleManager.h>
#include <HTTPClient.h>
#include <TaskMessage.h>
#include <timeHelper.h>

// Firebase credentials
#define FS_BP "https://firestore.googleapis.com/v1/projects/"
#define FS_PROJECT_ID "systematix-poc"
#define FS_API_KEY "AIzaSyBFZez8JPua0g1qWPCfa5kbzXxcguzNTRw"
#define FS_COLLECTION_NAME "LOGIN"
#define FS_COLLECTION_PATH FS_BP FS_PROJECT_ID "/databases/(default)/documents/" FS_COLLECTION_NAME "?key=" FS_API_KEY

class FirestoreClient
{
private:
    ConsoleManager *console;
    QueueHandle_t *messageQuote;
    static String className, classContext;
    void save(bool isAuthorized, String name, String uuid);

public:
    FirestoreClient(ConsoleManager *console, QueueHandle_t *messageQuote);
    void loop(bool hasInternetAccess);
};
#endif