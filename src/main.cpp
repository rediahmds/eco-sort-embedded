#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <NetWizard.h>

// rename credentials.example.h to credentials.h and fill in the credentials
#include <credentials/credentials.h>

static AsyncWebServer server(80);
static NetWizard netWizard(&server);

void setup()
{
  netWizard.setStrategy(NetWizardStrategy::NON_BLOCKING);
  netWizard.autoConnect(AP_NAME, AP_PASSWORD);

  Serial.begin(9600);
}

void loop()
{
  netWizard.loop();
}
