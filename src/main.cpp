// rename credentials.example.h to credentials.h and fill in the credentials
#include <credentials/credentials.h>

#include <Arduino.h>
#include <ElegantOTA.h>
#include <WebServer.h>
#include <BlynkSimpleEsp32.h>
#include <NetWizard.h>

#include <sensors/mq2/methane.h>
#include <sensors/hcsr/ultrasonic.h>
#include <outputs/lcd/lcd.h>
#include <outputs/servo/servo.h>

static WebServer server(80);
static BlynkTimer timer;
static NetWizard netMan(&server);

const unsigned long blynkInterval = 5000L;

int deg = 0;
int methaneADC = 0;
int binLevelNonOrganic = 0;
int binLevelOrganic = 0;

void sendSensorData();

void setup()
{
  Serial.begin(9600);
  lcdInit();

  lcdPrint({.message = " Setting up WiFi... "});
  netMan.autoConnect(AP_NAME, AP_PASSWORD);
  const IPAddress ip = netMan.localIP();
  lcdPrint({
      .message = "Connected!",
      .delay = 2000,
      .clear = true,
  });
  lcdPrint({.message = "IP : " + ip.toString()});

  ElegantOTA.setAuth(OTA_USERNAME, OTA_PASSWORD);
  ElegantOTA.begin(&server);

  server.begin();

  Blynk.config(BLYNK_AUTH_TOKEN);
  timer.setInterval(blynkInterval, sendSensorData);

  servo.attach(SERVO_PIN);
  servo.write(0);
}

void loop()
{
  ElegantOTA.loop();
  netMan.loop();

  Blynk.run();
  timer.run();

  methaneADC = readMethane();
  printMethane(methaneADC);

  binLevelNonOrganic = readLevelBinNonOrganic();
  binLevelOrganic = readLevelBinOrganic();
  printLevels({
      .binsNonOrganic = binLevelNonOrganic,
      .binsOrganic = binLevelOrganic,
  });

  delay(1000);
}

BLYNK_WRITE(V0)
{
  String inferenceResult = param.asString();

  if (inferenceResult == "organic")
  {
    lcdPrint({.row = 3, .message = "Organic"});
    servo.write(70);
  }
  else
  {
    lcdPrint({.row = 3, .message = "Non Organic"});
    servo.write(150);
  }
}

BLYNK_WRITE(V1)
{
  deg = param.asInt();
  servo.write(deg);
  Serial.println("[BLYNK] V2 value changed");
}

void sendSensorData()
{
  Blynk.virtualWrite(V2, binLevelOrganic);
  Blynk.virtualWrite(V3, binLevelNonOrganic);

  Blynk.virtualWrite(V4, methaneADC);

  Serial.println("Sensor data sent successfully!");
}
