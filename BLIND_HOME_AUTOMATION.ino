
String voice;
int LIGHT = 10;
int FAN = 12;
int redLed = 8;
int greenLed = 13;
int buzzer = 4;
int wifiPin = 5;
// Your threshold value
int smokeA0 = A5;
int sensorThres = 430;


void RedOn(){
digitalWrite (LIGHT, HIGH);
}
void RedOff(){
digitalWrite (LIGHT, LOW);
}
void GreenOn(){
digitalWrite (FAN, HIGH);
}
void GreenOff(){
digitalWrite (FAN, LOW);
}

void allon() {
digitalWrite (LIGHT, HIGH);
digitalWrite (FAN, HIGH);

}
void alloff() {
digitalWrite (LIGHT, LOW);
digitalWrite (FAN, LOW);

}

int pirPin=7;
//#define BLYNK_PRINT DebugSerial

//// lowest and highest sensor readings:
const int sensorMin = 0;     // sensor minimum
const int sensorMax = 1024;  // sensor maximum

void setup()
{
  Serial.begin(9600);
  pinMode(pirPin,INPUT); 
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(wifiPin,OUTPUT);
  pinMode(smokeA0, INPUT);

pinMode(LIGHT, OUTPUT);
pinMode(FAN, OUTPUT);

}

void loop()
{
 
//rain sensor
// read the sensor on analog A0:
  int sensorReading = analogRead(A0);
  // map the sensor range (four options):
  // ex: 'long int map(long int, long int, long int, long int, long int)'
  int range = map(sensorReading, sensorMin, sensorMax, 0, 3);
  
  // range value:
  switch (range) {
 case 0:    // Sensor getting wet
    Serial.println("Heavy Leakage");
    digitalWrite(wifiPin,HIGH);
    digitalWrite(greenLed, HIGH);

    break;
 case 1:    // Sensor getting wet
    digitalWrite(wifiPin,HIGH);
    Serial.println("Leakage Warning");
    digitalWrite(greenLed, HIGH);
    break;
 case 2:    // Sensor dry - To shut this up delete the " Serial.println("Not Raining"); " below.
    Serial.println("all ok!!");
    break;
  }
  delay(100);  // delay between reads


//voice command
  while(Serial.available()) {
delay(5);
char c=Serial.read();
if(c=='#')
{break; }
voice += c;
}
if (voice.length() > 0) {
Serial.println(voice);
if (voice == "all on" || voice == "all devices on")
{
allon() ;
}
else if (voice == "all of" || voice=="all devices of")
{
alloff() ;
}
 if(voice =="lights" || voice =="lights on"){
RedOn();
}
else if(voice =="lights of"||voice =="no lights"){
RedOff();
}
else if(voice =="fan on " || voice =="fan on"){
GreenOn();
}
else if( voice =="fan of" ){
GreenOff();
}

voice="";
}



//Smoke Detector

 int analogSensor = analogRead(smokeA0);

  Serial.print("Smoke Value: ");
  Serial.println(analogSensor);
  // Checks if it has reached the threshold value
  if (analogSensor > sensorThres)
  {
    tone(buzzer, 1000, 200);
//    digitalWrite(redLed, HIGH);
//    digitalWrite(greenLed, LOW);
    digitalWrite(wifiPin,HIGH);
  }
  else
  {
//    digitalWrite(redLed, LOW);
//    digitalWrite(greenLed, HIGH);
    noTone(buzzer);
  }
  delay(200);

 //motion sensor
 // Blynk.run();
  int pirValue = digitalRead(pirPin);
  if(pirValue==HIGH)
  {
    Serial.println("motion detected"); 
    digitalWrite(redLed, HIGH);  
    delay(10);
  }
  if(pirValue==LOW)
  {
   Serial.println("NO motion detected");
    digitalWrite(redLed, LOW);
    delay(10); 
  }
  .

  
  }
    
