#include <Adafruit_Sensor.h>

#include <DHT_U.h>
#include <DHT.h>

 #include <avr/dtostrf.h>

#include <LiquidCrystal.h>

#define DIGITAL_PIN_2 2
#define DIGITAL_PIN_7 7
#define DIGITAL_PIN_9 9
#define DIGITAL_PIN_10 10
#define DIGITAL_PIN_11 11
#define DIGITAL_PIN_12 12
#define DIGITAL_PIN_13 13

#define DHT_TYPE DHT22

const int lcdCols = 16;
const int lcdRows = 2;

const int rs = DIGITAL_PIN_7;
const int en = DIGITAL_PIN_9;
const int db4 = DIGITAL_PIN_10;
const int db5 = DIGITAL_PIN_11;
const int db6 = DIGITAL_PIN_12;
const int db7 = DIGITAL_PIN_13;

char tempString[100];
char humString[100];

LiquidCrystal lcd(rs, en, db4, db5, db6, db7);
DHT dht(DIGITAL_PIN_2, DHT_TYPE);

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);

    setupLcd();
    setupDht();
}

void setupLcd()
{
    lcd.begin(lcdCols, lcdRows);
    lcd.print("Waiting ... ");
}

void setupDht()
{
    dht.begin();
}

void loop()
{
    blinkBuiltInLed();
    measureDht();
}

void blinkBuiltInLed()
{
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(250);
}

void measureDht()
{
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    Serial.println(h);
    Serial.println(t);

    lcd.clear();
    lcd.setCursor(0, 0);

    char outstr[5];

    dtostrf(t, 5, 2, outstr);

    lcd.write(outstr);
}
