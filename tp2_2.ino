#include <LSM6DSL_ACC_GYRO_Driver.h>
#include <LSM6DSLSensor.h>
#include <vl53l0x_class.h>
#include <Nokia_5110.h>
#include <Wire.h>

TwoWire WIRE1(PB11, PB10); //SDA=PB11 & SCL=PB10



#define LEDR 15
#define LEDB 13
#define LEDV 14

#define RST 7
#define CE 6
#define DC 5
#define DIN 4
#define CLK 3
#define BL 2

#define I2C2_SCL    PB10
#define I2C2_SDA    PB11


// Components.
LSM6DSLSensor *AccGyr;
TwoWire *dev_i2c;
Nokia_5110 lcd = Nokia_5110(RST, CE, DC, DIN, CLK);

void setup() {
  
  // Initialize I2C bus.
  dev_i2c = new TwoWire(I2C2_SDA, I2C2_SCL);
  dev_i2c->begin();
  
  pinMode(LEDR,OUTPUT);
  pinMode(LEDB,OUTPUT);
  pinMode(LEDV,OUTPUT);

  int status;

  lcd.setContrast(65);
  
  //lcd.backlight();
  analogWrite(BL,200);

   // Initlialize components.
  AccGyr = new LSM6DSLSensor(dev_i2c, LSM6DSL_ACC_GYRO_I2C_ADDRESS_LOW);
  //AccGyr->Enable_X();
  AccGyr->Enable_X();

  

}

void loop() {
    analogWrite(LEDR,0);

  //analogWrite(LEDR,0);
  //analogWrite(LEDB,0);
  
  // Read accelerometer and gyroscope.
  int32_t accelerometer[3];
  int32_t gyroscope[3];
  //AccGyr->Get_X_Axes(accelerometer);
  AccGyr->Get_X_Axes(gyroscope);


//  if(accelerometer[0] >=100 || accelerometer[0] <= -100) {
//    analogWrite(LEDR,255);
//    delay(1000);
//  }
//  if(accelerometer[1] >=100 || accelerometer[1] <= -100) {
//    analogWrite(LEDB,255);
//    delay(1000);
//  }
  




   // Output data.
  //lcd.print("Acc[mg]: ");
  //lcd.println(accelerometer[0]);
  
  //lcd.println(" ");
//lcd.print(accelerometer[1]);
//  lcd.println(" ");
//  lcd.println(accelerometer[2]);
  //lcd.println(" | Gyr[mdps]: ");
lcd.print(gyroscope[0]);
lcd.print(" ");
lcd.println(gyroscope[1]);
delay(1000);
lcd.clear();
//  lcd.print(" ");
//  lcd.println(gyroscope[2]);

   
}
