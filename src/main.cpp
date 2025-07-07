// rename credentials.example.h to credentials.h and fill in the credentials
#include <credentials/credentials.h>

#include <Arduino.h>
#include <ElegantOTA.h>
#include <WebServer.h>
#include <BlynkSimpleEsp32.h>
#include <NetWizard.h>
#include <NetMan.h>

#include <MQ2.h>
#include <Bins.h> // ultrasonic
#include <Lcd.h>
#include <ServoPositioner.h>

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
static ServoPositioner servo;

const unsigned long blynkInterval = 50'000;

int deg = 0;
int methaneADC = 0;
float binLevelNonOrganic = 0;
float binLevelOrganic = 0;
String inferenceResult = "--";

void sendSensorData();

void setup()
{
  Serial.begin(9600);
  lcd.initialize();

  netMan.autoConnect(AP_NAME, "");
	
	// Connect to specific AP without opening a portal, input WiFi auth manually
	// netMan.connect("AP", "Pass");

	netMan.onConnectionStatus([&](NetWizardConnectionStatus status)
							  { NetMan::handleConnectionChanges(status, lcd); });
	netMan.onPortalState([&](NetWizardPortalState state)
						 { NetMan::handlePortalChanges(state, lcd); });

  ElegantOTA.setAuth(OTA_USERNAME, OTA_PASSWORD);
  ElegantOTA.begin(&server);

  server.begin();

  Blynk.config(BLYNK_AUTH_TOKEN);
  timer.setInterval(blynkInterval, sendSensorData);

  lcd.clear();
  servo.attach(SERVO_PIN);
}

void loop()
{
  ElegantOTA.loop();
  netMan.loop();

  Blynk.run();
  timer.run();

	lcd.clearRow(0);
	lcd.printMessageAt(0, 0, "Result: " + inferenceResult);

  lcd.clearRow(1);
  methaneADC = methaneSensor.readCH4();
  lcd.printMessageAt(0, 1, "CH4: " + String(methaneADC));

  lcd.clearRow(2);
  lcd.clearRow(3);
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

  const bool isServoAttached = servo.attached();
  if (isServoAttached)
  {
    Blynk.virtualWrite(V7, "Attached");
  }
  else
  {
    Blynk.virtualWrite(V7, "Not Attached");
  }
}

BLYNK_WRITE(V0)
{
	inferenceResult = param.asString();

  if (inferenceResult == "organic")
  {
		lcd.printMessageAt(0, 9, "Organic");
		servo.tiltToOrganincBin();
		delay(300);
  }
  else
  {
		lcd.printMessageAt(0, 9, "Non-organic");
		servo.tiltToAnorganicBin();
		delay(300);
  }

	servo.toInitialPosition();
}

BLYNK_WRITE(V1)
{
  deg = param.asInt();
  servo.write(deg);
  Serial.println("[BLYNK] V2 value changed");
}

BLYNK_WRITE(V8)
{
  const bool isResetPressed = param.asInt();
  if (isResetPressed)
  {
    netMan.reset();
    ESP.restart();
  }
}

void sendSensorData()
{
  Blynk.virtualWrite(V2, binLevelOrganic);
  Blynk.virtualWrite(V3, binLevelNonOrganic);

  Blynk.virtualWrite(V4, methaneADC);

  Serial.println("Sensor data sent successfully!");
}
