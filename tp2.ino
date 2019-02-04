#include <vl53l0x_class.h>

#include <Nokia_5110.h>

#include <Wire.h>

TwoWire WIRE1(PB11, PB10); //SDA=PB11 & SCL=PB10
VL53L0X sensor_vl53l0x(&WIRE1, PC6, PC7); //XSHUT=PC6 & INT=PC7


#define LEDR 15
#define LEDB 13
#define LEDV 14

#define RST 7
#define CE 6
#define DC 5
#define DIN 4
#define CLK 3
#define BL 2


Nokia_5110 lcd = Nokia_5110(RST, CE, DC, DIN, CLK);

void setup() {

  
  pinMode(LEDR,OUTPUT);
  pinMode(LEDB,OUTPUT);
  pinMode(LEDV,OUTPUT);

  int status;

   lcd.setContrast(70);
  
  //lcd.backlight();
  analogWrite(BL,200);
  
  // Initialisation I2C bus.
  WIRE1.begin();                         

  // Switch off VL53L0X component.
  sensor_vl53l0x.VL53L0X_Off();

  status = sensor_vl53l0x.InitSensor(0x10);
  if(status)
  {
    lcd.println("Init sensor_vl53l0x failed...");
}

}

void loop() {
 
  digitalWrite(LEDR,1);
  digitalWrite(LEDV,0);
  digitalWrite(LEDB,0);

  //AFFICHAGE DISTANCE SUR ECRAN LCD
  uint32_t distance;
  int status;
  status = sensor_vl53l0x.GetDistance(&distance);

  char report[64];
  snprintf(report, sizeof(report), "| Distance [mm]: %ld |", distance);
  lcd.println(report);

  if( distance > 300 || distance == 0) {
    analogWrite(LEDR,0);
    analogWrite(LEDV,100);
  }
  else if(distance < 100) {
    analogWrite(LEDR,255);
    analogWrite(LEDV,0);
  }
  else if(distance < 300){
    analogWrite(LEDR,255);
    analogWrite(LEDV,10); 
  }
  
  
}
