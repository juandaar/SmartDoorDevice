// Pendant::::Create wifi monitor
#include "WiFiManager.h"

String WiFiManager::className = "WiFiManager";
String WiFiManager::classContext = "WiFiManager::";

WiFiManager::WiFiManager(ConsoleManager *console)
{
    const String methodName = "constructor";
    this->console = console;

    this->wifiMulti = new WiFiMulti;
    this->dnsServer = new DNSServer;
    apState, wifiActive, cpState = false;
    console->publish(classContext + methodName, "the network manager was correctly built ", INF_LOG);
}

bool WiFiManager::connectToWIFI(String ssid, String password)
{
    const String methodName = "connectToWifi";
    this->ssid = &ssid[0u];
    this->password = &password[0u];
    short attempts = 0;
    console->publish(classContext + methodName, "Connecting to network", INF_LOG);
    console->publish(classContext + methodName, "Connecting to:\n\t\tSSID " + ssid + "\n\t\tPassword: ******", INF_LOG);

    wifiMulti->addAP(this->ssid, this->password);
    wifiMulti->run();
    delay(4000);
    while (wifiMulti->run() != WL_CONNECTED)
    {

        console->print(".");
        if (++attempts == MAX_ATTEMPTS_TO_CONNECT_WIFI)
        {
            console->println("");
            console->publish(classContext + methodName, "Impossible connect to the network!", ERR_LOG);
            return false;
        }
        delay(1000);
    }
    WiFi.setAutoConnect(true);
    WiFi.setAutoReconnect(true);
    console->print(" ");
    console->publish(classContext + methodName, "Wifi connection was successfull!\tIP Address: " + WiFi.localIP().toString(), INF_LOG);
    return true;
}

bool WiFiManager::disconnectFromWIFI()
{
    const String methodName = "disconnectFromWIFI";

    if (WiFi.disconnect(true))
    {
        console->publish(classContext + methodName, "Wifi disconnection was successfull!", INF_LOG);
        return true;
    }
    else
    {
        console->publish(classContext + methodName, "Wifi disconnection failed", ERR_LOG);
        return false;
    }
}

bool WiFiManager::wifiStatus()
{
    const String methodName = "stateWifi";
    if (wifiMulti->run() == WL_CONNECTED)
        return true;
    return false;
}

bool WiFiManager::isWifiActive()
{
    return wifiActive;
}

bool WiFiManager::enableAP()
{
    const String methodName = "enableAP";

    console->publish(classContext + methodName, "Configuring access point...", INF_LOG);

    for (int i = 0; i < 5; i++)
    {
        if (WiFi.softAPConfig(AP_IP, AP_IP, AP_MASK))
        {
            delay(100);
            break;
        }
        delay(100);
    }

    delay(500);

    if (WiFi.softAP((char *)AP_SSID, (char *)AP_PASSWORD))
    {
        delay(1000);
        console->publish(classContext + methodName, "AP IP address: " + WiFi.softAPIP().toString() + " AP MAC address: " + ((String)WiFi.macAddress()), INF_LOG);
        apState = true;
        return true;
    }
    else
    {
        console->publish(classContext + methodName, "Impossible configure the AP ", ERR_LOG);
        return false;
    }
}

bool WiFiManager::disableAP()
{

    const String methodName = "disableAP";

    if (WiFi.softAPdisconnect())
    {
        console->publish(classContext + methodName, "AP Disconnection was successful", INF_LOG);
        apState = false;
        return true;
    }
    else
    {
        console->publish(classContext + methodName, "There was an error disconnecting the AP ", WAR_LOG);
        return false;
    }
}

bool WiFiManager::enableCP()
{
    const String methodName = "enableCP";

    if (dnsServer->start(AP_DNS_PORT, "*", WiFi.softAPIP()))
    {
        console->publish(classContext + methodName, "Captive Portal was started correctly", INF_LOG);
        cpState = true;
        return true;
    }
    console->publish(classContext + methodName, "Captive Portal was not  started correctly", ERR_LOG);
    return false;
}

bool WiFiManager::disableCP()
{
    const String methodName = "disableCP";
    dnsServer->stop();
    cpState = false;
    console->publish(classContext + methodName, "Captive Portal was not  started correctly", ERR_LOG);
    return true;
}

bool WiFiManager::dnsLoop()
{
    if (cpState)
        dnsServer->processNextRequest();
    return true;
}
