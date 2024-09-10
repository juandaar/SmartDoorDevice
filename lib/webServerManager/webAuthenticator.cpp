#include <webAuthenticator.h>

String WebAuthenticator::className = "WebAuthenticator";
String WebAuthenticator::classContext = "WebAuthenticator::";

CustomJWT WebAuthenticator::jwt((char *)JWT_SECRET_KEY, (size_t)JWT_MAX_PAYLOAD_LENGTH);

WebAuthenticator::WebAuthenticator(ConsoleManager *console, StorageManager *storage)
{
    const String methodName = "Constructor";
    char key[] = "tester";
    this->console = console;
    this->storage = storage;
    console->publish(classContext + methodName, "Web Authenticator was built", INF_LOG);
}

bool WebAuthenticator::generateJWTToken(String payload)
{
    jwt.clear();
    jwt.allocateJWTMemory();
    jwt.encodeJWT(&payload[0]);
    return bool(jwt.payloadLength);
}
bool WebAuthenticator::verifyJWTverify(String token)
{
    jwt.clear();
    jwt.allocateJWTMemory();
    jwt.decodeJWT(&token[0]);
    return bool(jwt.payloadLength);
}

AuthenticationState WebAuthenticator::verify(const String &token)
{
    return AUTH_OK;
}
String WebAuthenticator::getPayload(const String &token)
{
    return jwt.payload;
}
AuthenticationState WebAuthenticator::authenticate(String username, String password)
{
    return AUTH_OK;
}
String WebAuthenticator::generateToken(String username)
{
    generateJWTToken(username);
    return jwt.out;
}