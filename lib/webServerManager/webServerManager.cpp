#include "WebServerManager.h"

String WebServerManager::className = "WebServerManager";
String WebServerManager::classContext = "WebServer::";

WebServerManager::WebServerManager(ConsoleManager *console, StorageManager *storage, WiFiManager *wifiManager)
{
    const String methodName = "constructor";
    this->console = console;
    this->storage = storage;
    this->wifiManager = wifiManager;
    this->console->publish(classContext + methodName, "Web Service was built", INF_LOG);
}

ExecutionState WebServerManager::setup()
{
    const String methodName = "Setup";
    this->server = new WebServer(WEB_SERVER_PORT);
    this->webServerConfig();
    this->console->publish(classContext + methodName, "Web Service setup", INF_LOG);
    return EXE_OK;
}

void WebServerManager::webServerConfig()
{
    server->on("/network", HTTP_POST, [this]()
               { connectToNetwork(); });
    server->on("/network", HTTP_GET, [this]()
               { networks(); });
    server->on("/network/state", HTTP_GET, [this]()
               { networkState(); });
    server->onNotFound([this]()
                       { handleServer(); });
    this->serverState = false;
}

ExecutionState WebServerManager::start()
{
    const String methodName = "start";
    server->begin();
    this->serverState = true;
    console->publish(classContext + methodName, "The web server was enabled", INF_LOG);
    return EXE_OK;
}

ExecutionState WebServerManager::stop()
{
    const String methodName = "stop";
    server->stop();
    server->close();
    serverState = false;
    console->publish(classContext + methodName, "The web server was disabled", INF_LOG);

    return EXE_OK;
}

ExecutionState WebServerManager::loop()
{
    if (serverState)
    {
        const String methodName = "loop";

        int i = 0;
        do
        {
            server->handleClient();
            server->client();
        } while (millis() - lastMillis < TIMEOUT_SENDING_VIEW);
    }
    return EXE_OK;
}

void WebServerManager::handleServer()
{
    String stringHelper;
    JsonDocument doc;
    String path = server->uri();
    const String methodName = "handleServer";
    console->publish(classContext + methodName, "Path: " + path, INF_LOG);
    lastMillis = millis();

    if (path.endsWith("/"))
        path += "index.html";

    if (path == PATH_WEB_SERVER)
        path += "/index.html";

    String fileType = ContentType(path);

    if (sendStreamFile(path, fileType) == EXE_OK)
    {
        String message = "imagenes!\n\n";
        message += "URI: ";
        message += server->uri();
        server->send(200, "text/plain", message);
    }
    else
    {
        console->publish(classContext + methodName, "File not Found: " + path, WAR_LOG);
        server->send(404, "text/plain", "Not Found->" + path);
    }
}

String WebServerManager::ContentType(String filename)
{
    if (filename.endsWith(".htm"))
        return "text/html";
    else if (filename.endsWith(".html"))
        return "text/html";
    else if (filename.endsWith(".css"))
        return "text/css";
    else if (filename.endsWith(".js"))
        return "application/javascript";
    else if (filename.endsWith(".png"))
        return "image/png";
    else if (filename.endsWith(".gif"))
        return "image/gif";
    else if (filename.endsWith(".jpg"))
        return "image/jpeg";
    else if (filename.endsWith(".jpeg"))
        return "image/jpeg";
    else if (filename.endsWith(".ico"))
        return "image/x-icon";
    else if (filename.endsWith(".xml"))
        return "text/xml";
    else if (filename.endsWith(".pdf"))
        return "application/x-pdf";
    else if (filename.endsWith(".zip"))
        return "application/x-zip";
    else if (filename.endsWith(".gz"))
        return "application/x-gzip";
    else if (filename.endsWith(".otf"))
        return "application / x - font - opentype";
    else if (filename.endsWith(".ttf"))
        return "application / x - font - truetype";
    return "text/plain";
}

ExecutionState WebServerManager::sendStreamFile(String path, String contentType)
{
    File file = storage->getFile(path);
    if (!file)
    {
        file.close();
        return EXE_ERROR;
    }

    server->streamFile(file, contentType);
    file.close();
    return EXE_OK;
}

void WebServerManager::connectToNetwork()
{
    const String methodName = "connectToNetwork";
    String stringHelper;
    JsonDocument doc;

    if (server->hasArg("plain"))
    {
        console->publish(classContext + methodName, "The request has arguments ", INF_LOG);
        String json = String(server->arg("plain"));
        DeserializationError error = deserializeJson(doc, json);
        if (error)
        {
            doc.clear();
            doc["msg"] = "Il y a un probleme avec le Json";
            serializeJson(doc, stringHelper);
            doc.clear();
            server->send(200, "application/json", stringHelper);
            return;
        }
    }
    const String ssid = doc["ssid"];
    const String password = doc["password"];
    console->println("\t\tssid: " + ssid);
    console->println("\t\tpassword: " + password);
    if (wifiManager->isWifiActive())
    {
        if (wifiManager->wifiStatus())
        {
            doc.clear();
            doc["msg"] = "There is a configured network";
            serializeJson(doc, stringHelper);
            doc.clear();
            server->send(200, "application/json", stringHelper);

            return;
        }
    }
    if (ssid == NULL || ssid == "")
    {
        console->publish(classContext + methodName, "SSID is missing", ERR_LOG);
        doc.clear();
        doc["msg"] = "Le SSID est manquant";
        serializeJson(doc, stringHelper);
        doc.clear();
        server->send(400, "application/json", stringHelper);
        return;
    }
    if (password == NULL || password == "")
    {
        console->publish(classContext + methodName, "Password is missing", ERR_LOG);
        doc.clear();
        doc["msg"] = "Le mot de passe est manquant";
        serializeJson(doc, stringHelper);
        doc.clear();
        server->send(400, "application/json", stringHelper);
        return;
    }
    console->publish(classContext + methodName, "Connecting to-> " + ssid, INF_LOG);
    if (wifiManager->connectToWIFI(ssid, password))
    {
        console->publish(classContext + methodName, "The devices was successfully connected" + ssid, INF_LOG);
        doc.clear();
        doc["msg"] = "connexion réussie";
        serializeJson(doc, stringHelper);
        doc.clear();
        server->send(200, "application/json", stringHelper);
        return;
    }
    console->publish(classContext + methodName, "The connection failed" + ssid, ERR_LOG);
    doc.clear();
    doc["msg"] = "La connexion a échoué, réessayez s'il vous plaît";
    serializeJson(doc, stringHelper);
    doc.clear();
    server->send(400, "application/json", stringHelper);
}

void WebServerManager::networks()
{
    const String methodName = "networks";
    JsonDocument doc;
    JsonArray array = doc["networks"].to<JsonArray>();
    String stringHelper;
    console->publish(classContext + methodName, "network scanning", INF_LOG);
    int n = WiFi.scanNetworks();
    if (n > 0)
    {
        console->publish(classContext + methodName, "networks availables-> " + String(n), INF_LOG);
        for (int i = 0; i < n; ++i)
        {
            array.add(WiFi.SSID(i));
            delay(10);
        }
    }
    serializeJson(doc, stringHelper);
    doc.clear();
    server->send(200, "application/json", stringHelper);
}

void WebServerManager::networkState()
{
    const String methodName = "networkState";
    JsonDocument doc;
    doc["state"] = wifiManager->wifiStatus();
    String stringHelper;
    server->send(200, "application/json", stringHelper);
}

void WebServerManager::terminal()
{
    server->send(200, "application/json", "{\"msg\":\"oli\"}");
}
