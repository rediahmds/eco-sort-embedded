#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <NetWizard.h>
#include <ElegantOTA.h>

// rename credentials.example.h to credentials.h and fill in the credentials
#include <credentials/credentials.h>
#include <sensors/mq2/methane.h>
#include "oled/oled.h"

static AsyncWebServer server(80);
static NetWizard netWizard(&server);

void setup()
{
  Serial.begin(9600);
  oledBegin();

  netWizard.autoConnect(AP_NAME, AP_PASSWORD);
  netWizard.setStrategy(NetWizardStrategy::NON_BLOCKING);

  ElegantOTA.setAuth(OTA_USERNAME, OTA_PASSWORD);
  ElegantOTA.begin(&server);

  server.begin();
}

void loop()
{
  netWizard.loop();
  ElegantOTA.loop();

  Serial.print("IP Address: ");
  Serial.println(netWizard.localIP());

  printMethane();

  delay(1000);
}
