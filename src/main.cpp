#include <Arduino.h>

#include <MTAccessPoint.h>
#include <MTLedPin.h>

LedPin *builtInLedPin;
MTAccessPoint *accessPoint;

void setup()
{
  // Serial port for debugging purposes
  Serial.begin(115200);

  builtInLedPin = new LedPin(LED_BUILTIN);

  accessPoint = new MTAccessPoint("Meultronix", "BSM1992!", 80);
  accessPoint->startBroadcasting();
}

void loop()
{
  // put your main code here, to run repeatedly:
  builtInLedPin->setEnabled(true);
  delay(1000);
  builtInLedPin->setEnabled(false);
  delay(1000);
}
