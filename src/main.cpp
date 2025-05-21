// rename credentials.example.h to credentials.h and fill in the credentials
#include <credentials/credentials.h>

#include <Arduino.h>
#include <NetWizard.h>
#include <ElegantOTA.h>
#include <WebServer.h>
#include <BlynkSimpleEsp32.h>

#include <sensors/mq2/methane.h>
#include <outputs/lcd/lcd.h>
#include <outputs/servo/servo.h>

static WebServer server(80);
static NetWizard netWizard(&server);

int deg = 0;

void setup()
{
  Serial.begin(9600);
  lcdInit();

  lcdPrint({
      .message = " Setting up WiFi... ",
  });
  netWizard.autoConnect(AP_NAME, AP_PASSWORD);
  const IPAddress ip = netWizard.localIP();
  lcdPrint({
      .message = "Connected!",
      .delay = 2000,
      .clear = true,
  });
  lcdPrint({
      .row = 0,
      .column = 0,
      .message = "IP: " + ip.toString(),
  });

  ElegantOTA.setAuth(OTA_USERNAME, OTA_PASSWORD);
  ElegantOTA.begin(&server);

  server.begin();

  Blynk.config(BLYNK_AUTH_TOKEN);

  servo.attach(SERVO_PIN);
}

void loop()
{
  netWizard.loop();
  ElegantOTA.loop();

  Blynk.run();

  servo.write(45);

  delay(1000);
}

BLYNK_WRITE(V1)
{
  deg = param.asInt();
  servo.write(deg);
  Serial.println("[BLYNK] V2 value changed");
}
