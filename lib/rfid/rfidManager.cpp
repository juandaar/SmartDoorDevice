#include <rfidManager.h>

String RFIDManager::className = "RFIDManager";
String RFIDManager::classContext = "RFIDManager::";

RFIDManager::RFIDManager(ConsoleManager *console, SignalMessageSender *signalSender)
{
    SPI.begin();
    static String methodName = "constructor";
    this->console = console;
    this->signalSender = signalSender;
    this->mfrc522 = MFRC522(RFID_SS_PIN, RFID_RST_PIN);
    this->console->publish(classContext + methodName, "The RFIDManager was built", INF_LOG);
}

ExecutionState RFIDManager::setup()
{
    const String methodName = "Setup";
    mfrc522.PCD_Init();
    DeserializationError error = deserializeJson(users, RFID_USERS);
    if (error)
    {
        console->publish(classContext + methodName, "Json Error" + (String)error.c_str(), ERR_LOG);
        return EXE_ERROR;
    }
    console->publish(classContext + methodName, "Setup finished", INF_LOG);
    return EXE_OK;
}

ExecutionState RFIDManager::loop()
{

    RFIDCard card = check();

    if (card.getState() == CARD_OK)
    {
        static String methodName = "loop";
        JsonObject user;
        JsonArray array = users.as<JsonArray>();
        for (JsonObject obj : array)
        {
            String token = obj["uid"];
            String name = obj["name"];
            if (token == card.getValue())
            {
                console->publish(classContext + methodName, "The user " + name + " open the door", INF_LOG);
                signalSender->authorized();
                user = obj;
                break;
            }
        }
        if (!user)
        {
            console->publish(classContext + methodName, "Unauthorized access attempt ->" + card.getValue(), WAR_LOG);
            signalSender->denied();
            return EXE_ABORT;
        }
    }
    return EXE_OK;
}

RFIDCard RFIDManager::check()
{
    const String methodName = "check";

    if (!mfrc522.PICC_IsNewCardPresent())
    {

        return RFIDCard(CARD_NONE);
    }
    if (!mfrc522.PICC_ReadCardSerial())
    {
        return RFIDCard(CARD_NONE);
    }
    String UID = "";
    for (byte i = 0; i < mfrc522.uid.size; i++)
    {
        if (mfrc522.uid.uidByte[i] < 0x10)
            UID = UID + "0";
        UID.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    UID.toUpperCase();
    console->publish(classContext + methodName, "RFID Card found ->" + UID, INF_LOG);
    return RFIDCard(CARD_OK, UID);
}