#include <Adafruit_CircuitPlayground.h>
#include <string.h>
#include <math.h>

void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();

}

int temp;
int heat_case;
void loop() {
  CircuitPlayground.clearPixels();
  // put your main code here, to run repeatedly:
  temp = (9/5) * CircuitPlayground.temperature() + 32;
  if (temp > 70) heat_case = 0; //hot
  if (temp > 60 && temp <= 70) heat_case = 1; //warm
  if (temp > 50 && temp <= 60) heat_case = 2; //cold
  if (temp <= 50) heat_case = 3; //very cold
  switch (heat_case) {
    case 0:
      heat_case = 100; //red
      break;
    case 1:
      heat_case = 40; //orange
      break;
    case 2:
      heat_case = 240; //yellow
      break;
    case 3:
      heat_case = 170; //blue
      break;
  }
  Serial.println(temp);
  for (int j = 11; j >= 0; j--) {
    if (temp >= pow(2, j)) {
      temp = temp - pow(2, j);
      CircuitPlayground.setPixelColor(j, CircuitPlayground.colorWheel(heat_case));
    }
  }
  delay(1000);
}
