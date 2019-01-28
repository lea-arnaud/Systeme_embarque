#include <Wire.h>
#include <vl53l0x_class.h>

// Create components.
TwoWire WIRE1(PB11, PB10);  //SDA=PB11 & SCL=PB10
VL53L0X sensor_vl53l0x(&WIRE1, PC6, PC7); //XSHUT=PC6 & INT=PC7

#include <Nokia_5110.h>

#define RST 7
#define CE 6
#define DC 5
#define DIN 4
#define CLK 3
#define BL 2

#define LEDV D15                                                                                      
#define LEDR D13
#define LEDB D14


Nokia_5110 lcd = Nokia_5110(RST, CE, DC, DIN, CLK);

void setup() {
  int status;
  
  pinMode(LEDR,OUTPUT);
  pinMode(LEDB,OUTPUT);
  pinMode(LEDV,OUTPUT);
  
  lcd.setContrast(50);
  
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
  //AFFICHAGE ECRAN
   // Read Range.
  uint32_t distance;
  int status;
  status = sensor_vl53l0x.GetDistance(&distance);

  if (status == VL53L0X_ERROR_NONE)
  {
    // Output data.
    char report[64];
    snprintf(report, sizeof(report), "| Distance [mm]: %ld |", distance);
    lcd.println(report);
  }

  //distance LED
  if(distance < 100){
    digitalWrite(LEDR,1);
  }

  else if(distance < 300){
    digitalWrite(LEDB,1);
  }
  
}
