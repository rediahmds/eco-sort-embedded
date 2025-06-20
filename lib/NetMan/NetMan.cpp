#include "NetMan.h"
#include "WiFi.h"

NetMan::NetMan(String ssid, String password)
    : NetWizard(nullptr),
      _mode(WiFiMode::MANUAL),
      _ssid(ssid),
      _password(password),
      _server(nullptr) {}

NetMan::NetMan(WebServer *server,
               String APname,
               String APpassword)
    : NetWizard(server),
      _mode(WiFiMode::AUTO),
      _ssid(APname),
      _password(APpassword),
      _server(server) {}

void NetMan::begin()
{
    switch (_mode)
    {
    case WiFiMode::AUTO:
    {
        autoConnect(_ssid.c_str(), _password.c_str());
        break;
    }
    /* --------------------------------------------------------- */
    case WiFiMode::MANUAL:
    default:
    {
        WiFi.mode(WIFI_STA);
        WiFi.begin(_ssid.c_str(), _password.c_str());

        Serial.print(F("[NetMan] Connecting to "));
        Serial.print(_ssid);
        Serial.print(F("..."));

        const unsigned long timeout = 30'000; // 30 s
        unsigned long t0 = millis();
        while (WiFi.status() != WL_CONNECTED && millis() - t0 < timeout)
        {
            delay(250);
            Serial.print('.');
        }
        Serial.println();

        if (WiFi.status() != WL_CONNECTED)
        {
            Serial.println(F("[NetMan] WiFi connection timed out"));
            // Optional: fall back to AP / wizard mode or reset.
            ESP.restart();
            return;
        }
        break;
    }
    }
}
