#ifndef _WIFI_MANAGER_h
#define _WIFI_MANAGER_h

#if defined(ARDUINO) && ARDUINO >= 100
#include <arduino.h>
#else
#include <WProgram.h>
#endif
#include <Settings.h>
#include <ConsoleManager.h>
#include <DNSServer.h>
#include <WiFi.h>
#include <WiFiMulti.h>

/*------ AP = ACCESS POINT!!!! --------------*/
/*------ CP = CAPTIVE PORTAL!!!! --------------*/
#if !defined(AP_SSID)
#define AP_SSID "systematix-PoC"
#endif

#if !defined(AP_PASSWORD)
#define AP_PASSWORD "admin123"
#endif

#ifndef AP_IP
#define AP_IP IPAddress(192, 168, 4, 1)
#endif

#ifndef AP_MASK
#define AP_MASK IPAddress(255, 255, 255, 0)
#endif

#ifndef AP_DNS_PORT
#define AP_DNS_PORT 53
#endif

#ifndef MAX_ATTEMPTS_TO_CONNECT_WIFI
#define MAX_ATTEMPTS_TO_CONNECT_WIFI 20
#endif

class WiFiManager
{
private:
    char *ssid, *password;
    DNSServer *dnsServer;
    WiFiMulti *wifiMulti;
    bool apState, wifiState, cpState;
    ConsoleManager *console;
    static String className, classContext;

public:
    WiFiManager(ConsoleManager *);
    bool connectToWIFI(String ssid, String password);
    bool disconnectFromWIFI();
    bool stateWifi();
    bool enableAP();
    bool disableAP();
    bool enableCP();
    bool disableCP();
    bool dnsLoop();
};
#endif
