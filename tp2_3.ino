#include <LPS22HBSensor.h>
#include <LPS22HB_Driver.h>

#include <HTS221_Driver.h>
#include <HTS221Sensor.h>


#include <Nokia_5110.h>
#include <Wire.h>

TwoWire WIRE1(PB11, PB10); //SDA=PB11 & SCL=PB10


#define I2C2_SCL    PB10
#define I2C2_SDA    PB11

#define LEDR 15
#define LEDB 13
#define LEDV 14

#define RST 7
#define CE 6
#define DC 5
#define DIN 4
#define CLK 3
#define BL 2



// Components.

LPS22HBSensor *PressTemp;
TwoWire *dev_i2c;


Nokia_5110 lcd = Nokia_5110(RST, CE, DC, DIN, CLK);

void setup() {
  
  
  pinMode(LEDR,OUTPUT);
  pinMode(LEDB,OUTPUT);
  pinMode(LEDV,OUTPUT);


  lcd.setContrast(65);
  
  //lcd.backlight();
  analogWrite(BL,200);
  
    // Initialize I2C bus.
  dev_i2c = new TwoWire(I2C2_SDA, I2C2_SCL);
  dev_i2c->begin();


  
  // Initlialize components.
  PressTemp = new LPS22HBSensor(dev_i2c);
  PressTemp->Enable();

}

void loop() {
  // Led blinking.
  digitalWrite(LED_BUILTIN, HIGH);
  delay(250);
  digitalWrite(LED_BUILTIN, LOW);
  delay(250);

  // Read pressure.
  float pressure, temperature;
  PressTemp->GetPressure(&pressure);
  PressTemp->GetTemperature(&temperature);

  lcd.print("Pres[hPa]: ");
  lcd.print(pressure, 2);
  lcd.print(" | Temp[C]: ");
  lcd.println(temperature, 2);

   
}
