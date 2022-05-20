//Library
#include <avr/sleep.h>

//Temp Pin
int tempSensor = A0;
//Turbidity Pin
int turbiditySensor = A1;
//Buzzer Pin7
int buzzerPin = 13;
//Motor Pin
int motorPin = 12;

//Variables
int tempInput;
double temp;
float turbidityInput;
float turbidity;

void setup() {
  // Set up sleep mode
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);

  //Set up serial output (for debug)
  Serial.begin(9600);
  
  //set digital pin type
  pinMode(buzzerPin, OUTPUT);
  pinMode(motorPin, OUTPUT);
  pinMode(turbiditySensor, INPUT);

  //Turn on power relay
  digitalWrite(motorPin, HIGH);
}

void loop() {
 //Check if temp is more than 65C
 if(checkTemp()>65){
    playBuzzer(1);
    digitalWrite(motorPin, LOW);
    sleep_mode();
  }
  //Check if water is turbid
  if(checkTurbidity()>900){
    playBuzzer(0);
    digitalWrite(motorPin, LOW);
    sleep_mode();
  }
}


int checkTemp(){
  tempInput = analogRead(tempSensor); //read the analog sensor and store it
  temp = (((tempInput*5)/1024)+.21)*100;//find temp in celcius
  Serial.print("Temp: ");
  Serial.println(temp);
  return temp;
}

int checkTurbidity(){
  turbidityInput = analogRead(turbiditySensor);
  turbidity = turbidityInput;
  Serial.print("Tur: ");
  Serial.println(turbidity);
  return turbidity;
}

void playBuzzer(int song){
  if(song == 0){playFinishedTone();}
  else if (song == 1){playHotTone();}
  else {playErrorTone();}
}

void playFinishedTone(){
  tone(buzzerPin, 196);
  delay(500);
  tone(buzzerPin, 220);
  delay(250);
  tone(buzzerPin, 246);
  delay(500);
  tone(buzzerPin, 220);
  delay(250);
  tone(buzzerPin, 246);
  delay(1000);
  noTone(buzzerPin);
}

void playHotTone(){
  tone(buzzerPin, 185);
  delay(500);
  tone(buzzerPin, 155);
  delay(500);
  tone(buzzerPin, 138);
  delay(500);
  tone(buzzerPin, 116);
  delay(500);
  noTone(buzzerPin);
}

void playErrorTone(){
  tone(buzzerPin, 392);
  delay(250);
  tone(buzzerPin, 392);
  delay(250);
  tone(buzzerPin, 392);
  delay(500);
  noTone(buzzerPin);
  delay(500);
  tone(buzzerPin, 392);
  delay(250);
  tone(buzzerPin, 392);
  delay(250);
  tone(buzzerPin, 392);
  delay(500);
  noTone(buzzerPin);
}
