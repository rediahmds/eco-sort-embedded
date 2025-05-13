#include "oled/oled.h"

Adafruit_SSD1306 oled(OLED_WIDTH, OLED_HEIGHT, &Wire, OLED_RESET);

bool oledBegin()
{
    bool isInitialized = oled.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS);

    if (!isInitialized)
    {
        Serial.println("[ERROR] Failed to initialize OLED");
        delay(1000);
        ESP.restart();
    }

    oled.clearDisplay();

    oled.setCursor(0, 0);
    oled.println("EcoSort Embedded");
    oled.display();

    delay(2000);

    oled.clearDisplay();

    return isInitialized;
}
