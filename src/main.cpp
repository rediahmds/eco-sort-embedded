// rename credentials.example.h to credentials.h and fill in the credentials
#include <credentials/credentials.h>

#include <Arduino.h>
#include <ElegantOTA.h>
#include <WebServer.h>
#include <BlynkSimpleEsp32.h>
#include <NetWizard.h>
#include <NetMan.h>

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

static LCD lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);
static ServoPositioner servo;

const unsigned long blynkInterval = 5'000;

int deg = 0;

float binLevelRecyclable = 0;
float binLevelOrganic = 0;
float recyclablePercentage = 0;
float organicPercentage = 0;

String inferenceResult = "--";

void sendSensorData();

void setup()
{
	Serial.begin(9600);
	lcd.initialize();

	netMan.onConnectionStatus([&](NetWizardConnectionStatus status)
							  { NetMan::handleConnectionChanges(status, lcd); });
	netMan.onPortalState([&](NetWizardPortalState state)
						 { NetMan::handlePortalChanges(state, lcd); });

	netMan.autoConnect(AP_NAME, "");
	// Connect to specific AP without opening a portal, input WiFi auth manually
	// netMan.connect("AP", "Pass");

	ElegantOTA.setAuth(OTA_USERNAME, OTA_PASSWORD);
	ElegantOTA.begin(&server);

	server.begin();

	Blynk.config(BLYNK_AUTH_TOKEN);
	timer.setInterval(blynkInterval, sendSensorData);

	lcd.clear();

	servo.attach(SERVO_PIN);
	servo.toInitialPosition();
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
	lcd.clearRow(2);
	lcd.clearRow(3);

	binLevelRecyclable = anorganicWasteBin.readFilledHeightCm();
	recyclablePercentage = anorganicWasteBin.calculatePercentage(binLevelRecyclable);

	binLevelOrganic = organicWasteBin.readFilledHeightCm();
	organicPercentage = organicWasteBin.calculatePercentage(binLevelOrganic);

	lcd.printCentered(1, "[PERSENTASE TERISI]");
	lcd.printMessageAt(0, 2, "Organik   : " + String(organicPercentage) + "%");
	lcd.printMessageAt(0, 3, "Daur ulang: " + String(recyclablePercentage) + "%");

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
		Blynk.virtualWrite(V7, "ready");
	}
}

// --- Inference result event handler
BLYNK_WRITE(V0)
{
	inferenceResult = param.asString();

	Blynk.virtualWrite(V7, "busy");
	if (inferenceResult == "Organik")
	{
		lcd.printMessageAt(0, 9, inferenceResult);
		servo.tiltToOrganincBin();
	}
	else if (inferenceResult == "Daur ulang")
	{
		lcd.printMessageAt(0, 9, "Daur ulang");
		servo.tiltToAnorganicBin();
	}
	else
	{
		return;
	}
	delay(3000);

	servo.toInitialPosition();
	delay(300);
	Blynk.virtualWrite(V7, "ready");

	Blynk.virtualWrite(V0, "--");
	lcd.printMessageAt(0, 9, "--");
}

// --- Servo slide event handler
BLYNK_WRITE(V1)
{
	deg = param.asInt();
	servo.write(deg);
	Serial.println("[BLYNK] Servo is tilting..");
}

// --- Button reset wifi event handler
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
	Blynk.virtualWrite(V2, organicPercentage);
	Blynk.virtualWrite(V3, recyclablePercentage);

	Blynk.virtualWrite(V9, organicWasteBin.ping_cm());
	Blynk.virtualWrite(V10, anorganicWasteBin.ping_cm());

	Serial.println("Sensor data sent successfully!");
}

BLYNK_WRITE(V11)
{
	const bool isOpenCommand = param.asInt();

	if (isOpenCommand)
	{
		Blynk.virtualWrite(V7, "busy");
		servo.tiltToAnorganicBin();
	}
	else
	{
		servo.toInitialPosition();
		Blynk.virtualWrite(V7, "ready");
	}
	delay(400);
}

BLYNK_WRITE(V12)
{
	const bool isOpenCommand = param.asInt();

	if (isOpenCommand)
	{
		Blynk.virtualWrite(V7, "busy");
		servo.tiltToOrganincBin();
	}
	else
	{
		servo.toInitialPosition();
		Blynk.virtualWrite(V7, "ready");
	}
	delay(400);
}
