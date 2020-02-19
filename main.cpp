#include <Arduino.h>

#define PIN_LED 3
#define PIN_POTI 7

int raw, lin;

int cal[][2] = {
  {0, 0},
  {9, 123},
  {54, 281},
  {326, 429},
  {615, 578},
  {914, 726},
  {1011, 875},
  {1023, 1023}
};

int linearize(int x)
{
  int i = 0;
  while (x > cal[i+1][0])
    i++;
  return cal[i][1]+((double)(cal[i+1][1]-cal[i][1]))*(x-cal[i][0])/(cal[i+1][0]-cal[i][0]);
}

void setup() {
  pinMode(PIN_LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  //10 bit Analogwert
  raw = analogRead(PIN_POTI);
  lin = linearize(raw);

  //8 bit Tastgrad
  analogWrite(PIN_LED, lin >> 2);

  Serial.print(raw);
  Serial.print("  ");
  Serial.print(lin);
  Serial.print("  ");
  Serial.println(lin >> 2);
  delay(250);
  
}