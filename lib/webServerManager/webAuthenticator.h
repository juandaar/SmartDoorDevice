
#ifndef _WEB_AUTHENTICATOR_h
#define _WEB_AUTHENTICATOR_h

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <CustomJWT.h>
#include <ArduinoJson.h>
#include <StorageManager.h>
#include <ConsoleManager.h>

#ifndef JWT_SECRET_KEY
#define JWT_SECRET_KEY "test-key"
#endif

#ifndef JWT_MAX_PAYLOAD_LENGTH
#define JWT_MAX_PAYLOAD_LENGTH 256
#endif

typedef enum AuthenticationState
{
    AUTH_UNAUTHENTICATED,
    AUTH_OK,
    AUTH_FAIL,
    AUTH_EXPIRED
} AuthenticationState;

class WebAuthenticator
{
private:
    ConsoleManager *console;
    StorageManager *storage;
    static CustomJWT jwt;
    static String className, classContext;
    bool generateJWTToken(String payload);
    bool verifyJWTverify(String token);

public:
    WebAuthenticator(ConsoleManager *console, StorageManager *storage);
    AuthenticationState verify(const String &token);
    String getPayload(const String &token);
    AuthenticationState authenticate(String username, String password);
    String generateToken(String username);
};

#endif