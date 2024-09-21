#include <firestoreClient.h>

String FirestoreClient::className = "FireStoreClient";
String FirestoreClient::classContext = "FireStoreClient::";

FirestoreClient::FirestoreClient(ConsoleManager *console, QueueHandle_t *messageQuote)
{
    this->console = console;
    this->messageQuote = messageQuote;
}

void FirestoreClient::save(bool isAuthorized, String name, String uuid)
{
    static String methodName = "save";

    console->publish(classContext + methodName, "save searching starting", INF_LOG);

    if (!TimeHelper::isWebTime)
    {
        console->println("Searching Time");
        TimeHelper::setCurrentTimeNTP();
    }

    struct tm timeinfo;
    if (!getLocalTime(&timeinfo))
    {
        console->println("Failed to obtain time");
        return;
    }
    char createdAt[30];
    strftime(createdAt, sizeof(createdAt), "%Y-%m-%dT%H:%M:%S.000Z", &timeinfo);
    HTTPClient http;
    String jsonPayload;
    JsonDocument doc;
    doc["fields"]["authorized"]["booleanValue"] = isAuthorized;
    doc["fields"]["name"]["stringValue"] = name;
    doc["fields"]["cardId"]["stringValue"] = uuid;
    doc["fields"]["createdAt"]["timestampValue"] = createdAt;
    serializeJson(doc, jsonPayload);
    doc.clear();
    console->publish(classContext + methodName, "info to sent " + jsonPayload, INF_LOG);
    console->publish(classContext + methodName, "sent to  " + String(FS_COLLECTION_PATH), INF_LOG);
    http.begin(String(FS_COLLECTION_PATH));
    http.addHeader("Content-Type", "application/json");
    // http.addHeader("Authorization", "Bearer " + idToken); // Authorization header for secure access

    int httpResponseCode = http.POST(jsonPayload);

    if (httpResponseCode > 0)
    {
        String response = http.getString();
        console->println("Document created successfully:");
        console->println(response);
    }
    else
    {
        console->print("Error creating document. HTTP Response code: ");
        console->println(String(httpResponseCode));
    }

    http.end();
}

void FirestoreClient::loop(bool hasInternetAccess)
{
    TaskMessage message;
    if (xQueueReceive(*messageQuote, &message, portMAX_DELAY) == pdTRUE)
    {
        if (hasInternetAccess)
            save(message.isAuthorized, String(message.name), String(message.cardId));
    }
}
