#include "WebServerManager.h"

String WebServerManager::className = "WebServerManager";
String WebServerManager::classContext = "WebServer::";

WebServerManager::WebServerManager(ConsoleManager *console, StorageManager *storage)
{
    const String methodName = "constructor";
    this->console = console;
    this->storage = storage;
    this->console->publish(classContext + methodName, "Web Service was built", INF_LOG);
}

ExecutionState WebServerManager::setup()
{
    const String methodName = "Setup";
    this->server = new WebServer(WEB_SERVER_PORT);
    this->authenticator = new WebAuthenticator(console, storage);
    this->webServerConfig();
    this->console->publish(classContext + methodName, "Web Service setup", INF_LOG);
    return EXE_OK;
}

void WebServerManager::webServerConfig()
{
    server->on("/login", HTTP_POST, [this]()
               { login(); });
    server->on("/upgrade", HTTP_POST, [this]()
               { upgrade(); });
    server->on("/open", HTTP_POST, [this]()
               { open(); });
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
            i++;
            if (i == 2)
            {
                console->publish(classContext + methodName, "Proccessing request from server ", INF_LOG);
            }
            else if (i > 2 && i % 100 == 0)
            {
                console->print("-");
            }
            server->handleClient();
            server->client();
        } while (millis() - lastMillis < TIMEOUT_SENDING_VIEW);
        if (i > 1)
            console->println("");
    }
    return EXE_OK;
}

void WebServerManager::handleServer()
{
    String path = server->uri();
    const String methodName = "handleServer";
    console->publish(classContext + methodName, "Path: " + path, INF_LOG);
    lastMillis = millis();

    if (path.endsWith("/"))
    {
        console->println("\tindexing path...");
        path += "index.html";
    }

    if (path == PATH_WEB_SERVER)
    {
        path += "/index.html";
        console->println("\tindexing path...");
    }

    String fileType = ContentType(path);
    console->println("File type: " + fileType);

    if (fileType == "text/html")
    {
        String desired_path = PATH_WEB_SERVER;
        desired_path += "/index.html";
        if (path == desired_path)
        {

            path = "/login.html";

            path = "/login.html";

            path = "/bottom.html";
        }
        else
        {
            String pages = WEB_SERVER_REDIRECTED;
            console->println(pages);
            server->send(200, "text/html", pages);
            console->print(pages);
        }
    }
    else if (fileType == "text/plain")
    {
        String pages = WEB_SERVER_REDIRECTED;
        server->send(200, "text/html", pages);
        console->print(pages);
    }

    if (sendStreamFromSd(path) == EXE_OK)
    {
        String message = "imagenes!\n\n";
        message += "URI: ";
        message += server->uri();
        server->send(200, "text/plain", message);
    }
    else
    {
        String message = "Fucking!\n\n";
        message += "URI: ";
        message += server->uri();
        server->send(404, "text/plain", message);
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

ExecutionState WebServerManager::sendStreamFromSd(String path)
{
    File file;
    /*
    if (storage->getFile(SD, &path[0u], file) == EXE_OK)
    {
        server->streamFile(file, "text/html");
        file.close();
        return EXE_OK;
    }
    else
    {
        return EXE_ERROR;
    }
    */
    return EXE_OK;
}

void WebServerManager::login()
{
    const String methodName = "login";

    if (server->arg("USERNAME") && server->arg("PASSWORD"))
    {
        String token = "Bearer " + authenticator->generateToken(server->arg("USERNAME"));
        server->sendHeader("Authorization", token);

        server->send(200, "text/html", "<h1>Hello from ESP32!</h1>");
    }
}

void WebServerManager::upgrade()
{
    /*
    if (server_view_state == LOGIN)
    {
        m_server->send(200, "aplication/json", "{\"code\":\"300\"}");
        return;
    }

    if (!m_server->arg("TOKEN"))
    {
        server_view_state = LOGIN;
        m_server->send(200, "aplication/json", "{\"code\":\"300\"}");
    }
    String token = m_server->arg("TOKEN");
    if (provitional_authentication_cookie_check(token) != EXE_OK)
    {
        server_view_state = LOGIN;
        console->print("ENTRO");
        // m_server->send(200, "aplication/json", "{\"code\":\"300\"}");
        return;
    }
    console->print("JSON: ");
    console->println(*m_json_frame);
    m_server->send(200, "aplication/json", *m_json_frame);
    */
}

void WebServerManager::open()
{
    /*
    if (server_view_state == LOGIN)
    {
        m_server->send(200, "aplication/json", "{\"code\":\"300\"}");
        return;
    }

    if (!m_server->arg("TOKEN"))
    {
        server_view_state = LOGIN;
        // m_server->sendHeader("Content-Type: application/json");
        return;
    }

    String token = m_server->arg("TOKEN");
    if (provitional_authentication_cookie_check(token) != EXE_OK)
    {
        server_view_state = LOGIN;
        // m_server->send(200, "aplication/json", "{\"code\":\"300\"}");
        return;
    }

    m_server->send(200, "aplication/json", "{\"code\":\"200\"}");
    */
}
