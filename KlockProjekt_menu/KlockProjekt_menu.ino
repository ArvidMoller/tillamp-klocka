/*
* Name: Clock and temp project
* Author: Arvid Möller
* Date: 2024-10-10
* Description: This project uses a ds3231 to measure time and displays the time to an 1306 oled display,
* Further, it measures temprature with a analog temprature module and displays a mapped value to a 9g-servo-motor
*/

// Include Libraries
#include <RTClib.h>
#include <Wire.h>
#include <U8glib.h>
#include <Servo.h>

// Init constants
const int tmpPin = A0;
const int potPin = A1;
const int btnPin = 8;
const int servoPin = 9;

// Init global variables
bool state = false;

// construct objects
RTC_DS3231 rtc;
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);
Servo tmpServo;
DateTime timerdt;

void setup() {
  // init communication
  Serial.begin(9600);
  Wire.begin();

  // Init Hardware
  rtc.begin();
  tmpServo.attach(servoPin);
  pinMode(tmpPin, INPUT);
  pinMode(potPin, INPUT);
  pinMode(btnPin, OUTPUT);

  // Settings
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));  // Adjusts time to the local time on your computer
  u8g.setFont(u8g_font_unifont);
}

void loop() {
  // unsigned long sampleTime = millis();

  if ((analogRead(potPin)) > 1023 / 2) {
    Serial.println("Clock");
    oledWrite(30, 30, getTime());
  } else if ((analogRead(potPin)) <= 1023 / 2) {
    Serial.println("Timer");
    oledWrite(30, 30, timer());
  }


  servoWrite(getTemp());

  // while(millis() - sampleTime <= 1000){
  // }
}


/*
*This function reads time from an ds3231 module and package the time as a String
*Parameters: Void
*Returns: time in hh:mm:ss as String
*/
String getTime() {
  DateTime now = rtc.now();

  if (now.second() < 10 && now.minute() < 10) {
    return String(now.hour()) + ":0" + String(now.minute()) + ":0" + String(now.second());
  } else if (now.second() < 10) {
    return String(now.hour()) + ":" + String(now.minute()) + ":0" + String(now.second());
  } else if (now.minute() < 10) {
    return String(now.hour()) + ":0" + String(now.minute()) + ":" + String(now.second());
  } else {
    return String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second());
  }
}


/*
* This function reads an analog pin connected to an analog temprature sensor and calculates the corresponding temp
*Parameters: Void
*Returns: temprature as float
*/
float getTemp() {
  int Vo;
  float R1 = 10000;  // value of R1 on board
  float logR2, R2, T;
  float c1 = 0.001129148, c2 = 0.000234125, c3 = 0.0000000876741;  //steinhart-hart coeficients for thermistor

  Vo = analogRead(tmpPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);  //calculate resistance on thermistor
  logR2 = log(R2);
  T = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));  // temperature in Kelvin
  T = T - 273.15;                                              //convert Kelvin to Celcius

  return T;
}


/*
* This function takes a string and draws it to an oled display
*Parameters: - text: String to write to display
*Returns: void
*/
void oledWrite(int x, int y, String text) {
  u8g.firstPage();

  do {
    u8g.drawStr(x, y, text.c_str());

  } while (u8g.nextPage());
}


/*
* takes a temprature value and maps it to corresppnding degree on a servo
*Parameters: - val: temprature
*Returns: void
*/
void servoWrite(float val) {
  tmpServo.write(map(val, 15, 40, 0, 180));
}


/*
*This is the timer, it samples the time when it's started and calculates the elapsed time.
*Paratemers: void
*Returns: The current timer time as a string
*/
String timer() {
  DateTime now = rtc.now();

  int timerH;
  int timerM;
  int timerS;

  if (stateSwitch() == 0) {
    sampleTimer();

    return String("00:00:00");
  } else {
    timerH = now.hour() - timerdt.hour();
    timerM = now.minute() - timerdt.minute();
    timerS = now.second() - timerdt.second();

    Serial.println(timerH);
    Serial.println(timerdt.hour());
  }

  if (timerS < 10 && timerM < 10) {
    return String(timerH) + ":0" + String(timerM) + ":0" + String(timerS);
  } else if (timerS < 10) {
    return String(timerH) + ":" + String(timerM) + ":0" + String(timerS);
  } else if (timerM < 10) {
    return String(timerH) + ":0" + String(timerM) + ":" + String(timerS);
  } else {
    return String(timerH) + ":" + String(timerM) + ":" + String(timerS);
  }
}


void sampleTimer(){
  timerdt = rtc.now();
}


/*This is a state switch for the timer, used to stop and start timer
*Parameters: void
*Returns: the current state as boolean
*/
bool stateSwitch() {
  if (digitalRead(btnPin) == HIGH) {
    if (state == HIGH) {
      state = LOW;
    } else {
      state = HIGH;
    }
    delay(100);
  }

  Serial.println(state);
  return state;
}