#define MAG_ADDRESS 0x1E
#define MAG_XOUT_H 0x03
#define MAG_XOUT_L 0x04
#define MAG_ZOUT_H 0x05
#define MAG_ZOUT_L 0x06
#define MAG_YOUT_H 0x07
#define MAG_YOUT_L 0x08


#include <HMC5883L.h>
#include <Wire.h>
#include <PWM.h>


HMC5883L compass;
 

int32_t frequency = 38270;

int Nturns=34; 
float findDutyRatio(float B){
   return (((8.49222*0.01)/B)*1.15)/24;
}


void setup() {
  InitTimersSafe(); 
  //sets the frequency for the specified pin
  SetPinFrequencySafe(3, frequency);
  SetPinFrequencySafe(5, frequency);
  SetPinFrequencySafe(6, frequency);
  SetPinFrequencySafe(7, frequency);
  SetPinFrequencySafe(8, frequency);
  SetPinFrequencySafe(9, frequency);

  Wire.begin();

  
  // Initialize the magnetometer
  Wire.beginTransmission(MAG_ADDRESS);
  Wire.write(0x02); // Mode register
  Wire.write(0x00); // Continuous measurement mode
  Wire.endTransmission();
  
  //Forward PWM wave
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  //Reverse PWM wave
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  
  
 
}

void loop(){
  Wire.beginTransmission(MAG_ADDRESS);
  Wire.write(MAG_XOUT_H);
  Wire.endTransmission(false);
  Wire.requestFrom(MAG_ADDRESS, 6);
  
  // Combine the high and low bytes for each axis
  float x = ((Wire.read() << 8) | Wire.read())/1000;
  float y = ((Wire.read() << 8) | Wire.read())/1000;
  float z = ((Wire.read() << 8) | Wire.read())/1000;
 
  float ratioX = findDutyRatio(0.33);

    delay(1000);
  
  //Forward March!!!
    analogWrite(3,ratioX); 
    Serial.begin(9600); 
    char buffer[40];
    sprintf(buffer, "X = %d",ratioX);
    Serial.println(buffer); 
   } 
