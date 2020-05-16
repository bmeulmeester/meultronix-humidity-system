#include <Adafruit_Sensor.h>

#include <DHT_U.h>
#include <DHT.h>

#include <LiquidCrystal.h>

#define DIGITAL_PIN_2 2
#define DIGITAL_PIN_5 5
#define DIGITAL_PIN_6 6
#define DIGITAL_PIN_7 7
#define DIGITAL_PIN_9 9
#define DIGITAL_PIN_10 10
#define DIGITAL_PIN_11 11
#define DIGITAL_PIN_12 12
#define DIGITAL_PIN_13 13

#define FAN_PIN_LOW DIGITAL_PIN_5
#define FAN_PIN_HIGH DIGITAL_PIN_6

#define DHT_TYPE DHT22

#define MAX_TEMP 24

#define HUM_LOW 60
#define HUM_HIGH 80

const int lcdCols = 16;
const int lcdRows = 2;

const int rs = DIGITAL_PIN_7;
const int en = DIGITAL_PIN_9;
const int db4 = DIGITAL_PIN_10;
const int db5 = DIGITAL_PIN_11;
const int db6 = DIGITAL_PIN_12;
const int db7 = DIGITAL_PIN_13;

LiquidCrystal lcd(rs, en, db4, db5, db6, db7);
DHT dht(DIGITAL_PIN_2, DHT_TYPE);

void setup()
{ 
  pinMode(FAN_PIN_LOW, OUTPUT);
  pinMode(FAN_PIN_HIGH, OUTPUT);
  
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
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  testEnableFan(h, t);

  printDht(h, t);
  
  delay(1000);
}

void testEnableFan(int humidity, int temperature)
{
  if (humidity >= HUM_HIGH) {
    setFanHigh();
  } else if (humidity >= HUM_LOW) {
    setFanLow();
  } else {
    disableFan();
  }
}

void setFanLow()
{
  digitalWrite(FAN_PIN_LOW, HIGH);
  digitalWrite(FAN_PIN_HIGH, LOW);
}

void setFanHigh()
{
  digitalWrite(FAN_PIN_LOW, LOW);
  digitalWrite(FAN_PIN_HIGH, HIGH);
}

void disableFan()
{
 digitalWrite(FAN_PIN_LOW, LOW);
  digitalWrite(FAN_PIN_HIGH, LOW); 
}

void printDht(float humidity, float temperature)
{
  lcd.clear();
  lcd.setCursor(0, 0);

  char tempOutStr[4];
  dtostrf(temperature, 4, 1, tempOutStr);

  lcd.write("Temp. ");
  lcd.write(tempOutStr);
  lcd.write(" C.");

  char humOutStr[4];
  dtostrf(humidity, 4, 1, humOutStr);

  lcd.setCursor(0, 1);
  lcd.write("Hum.  ");
  lcd.write(humOutStr);
  lcd.write(" %");
}