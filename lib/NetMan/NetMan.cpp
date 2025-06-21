#include "NetMan.h"
#include "WiFi.h"
#include "Lcd.h"

NetMan::NetMan(String ssid, String password, LCD &lcd)
    : NetWizard(nullptr),
      _mode(WiFiMode::MANUAL),
      _ssid(ssid),
      _password(password),
      _server(nullptr),
      _lcd(lcd) {}

NetMan::NetMan(WebServer *server,
               String APname,
               String APpassword,
               LCD &lcd)
    : NetWizard(server),
      _mode(WiFiMode::AUTO),
      _ssid(APname),
      _password(APpassword),
      _server(server),
      _lcd(lcd) {}

void NetMan::begin()
{
    switch (_mode)
    {
    case WiFiMode::AUTO:
    {
        autoConnect(_ssid.c_str(), _password.c_str());
        onConnectionStatus([&](NetWizardConnectionStatus status)
                           {
            _lcd.clearRow(0);
            switch (status)
            {
            case NetWizardConnectionStatus::DISCONNECTED:
                {
                    _lcd.printScrollLeft(0, "WiFi disconnected");
                    break;
                }
            case NetWizardConnectionStatus::CONNECTING:
            {
                _lcd.printScrollLeft(0, "WiFi is connecting...");
                break;
            }
            case NetWizardConnectionStatus::CONNECTED:
            {
                _lcd.printScrollLeft(0, "WiFi connected successfully");
                break;
            }
            case NetWizardConnectionStatus::CONNECTION_FAILED:
            {
                _lcd.printScrollLeft(0, "WiFi connection failed");
                break;
            }
            case NetWizardConnectionStatus::CONNECTION_LOST:
            {
                _lcd.printScrollLeft(0, "WiFi connection lost");
                break;
            }
            case NetWizardConnectionStatus::NOT_FOUND:
            default:
            {
                _lcd.printScrollLeft(0, "WiFi connection not found");
                break;
            }
            } });

        onPortalState([&](NetWizardPortalState state) {
            
        });
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

void NetMan::_connectionStatusCallback(NetWizardConnectionStatus status)
{
    switch (status)
    {
    case NetWizardConnectionStatus::DISCONNECTED:
    {

        break;
    }

    default:
        break;
    }
}
