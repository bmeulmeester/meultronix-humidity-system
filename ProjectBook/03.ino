#define PIN_D2 2
#define PIN_D3 3
#define PIN_D4 4
#define PIN_D5 5

const int sensorPin = A0;
const float baselineTemp = 20.0;

void setup() 
{
  Serial.begin(9600);

  for (int pinNumber = 2; pinNumber <5; pinNumber++) {
    pinMode(pinNumber, OUTPUT);
    digitalWrite(pinNumber, LOW);
  }
}

void loop()
{
  int sensorVal = analogRead(sensorPin);

  Serial.print("Sensor value: ");
  Serial.print(sensorVal);

  float voltage = (sensorVal / 1024.0) * 5.0;

  Serial.print(", Volts: ");
  Serial.print(voltage);

  float temperature = (voltage - 0.5) * 100;
  
  Serial.print(", degrees C: ");
  Serial.println(temperature);

  if (temperature < baselineTemp + 2) {
    digitalWrite(PIN_D2, HIGH);
    digitalWrite(PIN_D3, LOW);
    digitalWrite(PIN_D4, LOW);
  } else if (temperature >= baselineTemp + 2 && temperature < baselineTemp + 4) {
    digitalWrite(PIN_D2, HIGH);
    digitalWrite(PIN_D3, HIGH);
    digitalWrite(PIN_D4, LOW);
  } else if (temperature >= baselineTemp + 6) {
    digitalWrite(PIN_D2, HIGH);
    digitalWrite(PIN_D3, HIGH);
    digitalWrite(PIN_D4, HIGH);
  }
}