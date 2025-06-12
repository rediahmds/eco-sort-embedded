// rename credentials.example.h to credentials.h and fill in the credentials
#include <credentials/credentials.h>

#include <Arduino.h>
#include <ElegantOTA.h>
#include <WebServer.h>
#include <BlynkSimpleEsp32.h>
#include <NetWizard.h>

#include <outputs/servo/servo.h>

#include <MQ2.h>
#include <Bins.h> // ultrasonic
#include <Lcd.h>

static WebServer server(80);
static BlynkTimer timer;
static NetWizard netMan(&server);

static Bins organicWasteBin(
    SENSOR_TRIG_ORGANIC_PIN,
    SENSOR_ECHO_ORGANIC_PIN);
static Bins anorganicWasteBin(
    SENSOR_TRIG_ANORGANIC_PIN,
    SENSOR_ECHO_ANORGANIC_PIN);
static MQ2 methaneSensor(SENSOR_MQ2_PIN);

static LCD lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);

const unsigned long blynkInterval = 50000L;

int deg = 0;
int methaneADC = 0;
float binLevelNonOrganic = 0;
float binLevelOrganic = 0;

void sendSensorData();

const bool IoTMode = true;

void setup()
{
  Serial.begin(9600);
  lcd.initialize();

  if (IoTMode)
  {
    lcd.printMessageAt(0, 0, " Setting up WiFi... ");
    netMan.autoConnect(AP_NAME, AP_PASSWORD);

    ElegantOTA.setAuth(OTA_USERNAME, OTA_PASSWORD);
    ElegantOTA.begin(&server);

    server.begin();

    Blynk.config(BLYNK_AUTH_TOKEN);
    timer.setInterval(blynkInterval, sendSensorData);
  }

  lcd.clear();

  servo.attach(SERVO_PIN);
  servo.write(45);
}

void loop()
{
  if (IoTMode)
  {
    ElegantOTA.loop();
    netMan.loop();

    Blynk.run();
    timer.run();
  }

  methaneADC = methaneSensor.readCH4();

  lcd.clearRow(1);
  lcd.clearRow(2);
  binLevelNonOrganic = anorganicWasteBin.readLevelPercentage();
  binLevelOrganic = organicWasteBin.readLevelPercentage();
  lcd.printMessageAt(0, 2, "O: " + String(binLevelOrganic) + "%");
  lcd.printMessageAt(0, 3, "A: " + String(binLevelNonOrganic) + "%");

  delay(1000);
}

BLYNK_CONNECTED()
{
  const IPAddress ipv4 = netMan.localIP();
  const char *ssid = netMan.getSSID();

  Blynk.virtualWrite(V5, ipv4.toString());
  Blynk.virtualWrite(V6, ssid);
}

BLYNK_WRITE(V0)
{
  String inferenceResult = param.asString();

  lcd.clearRow(3);
  if (inferenceResult == "organic")
  {
    lcd.printCentered(3, "Organic");
    servo.write(70);
  }
  else
  {
    lcd.printCentered(3, "Non-organic");
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
