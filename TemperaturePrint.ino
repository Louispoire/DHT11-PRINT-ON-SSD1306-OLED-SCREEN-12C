#include "DHT.h"
#define DHT11Pin 2
#define DHTType DHT11
//OLED
//In order to make everyhting work, you have to add new librairies. To do so,
//in Arduino, go to tools -> manage librairies -> search SSD1306 and DHT11 -> add both
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

DHT HT(DHT11Pin,DHTType);
float humi;
float tempC;
float tempF;

//Width
#define SCREEN_WIDTH 128
//Height
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(9600);
  HT.begin();
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.display(); //Display logo
  delay(1000); 
  display.clearDisplay();
}

void loop() {
 delay(1000);
 humi = HT.readHumidity();
 tempC = HT.readTemperature();
 tempF = HT.readTemperature(true);

 Serial.print("Humidity:");
 Serial.print(humi,0);
 Serial.print("%");
 Serial.print(" Temperature:");
 Serial.print(tempC,1);
 Serial.print("C ~ ");
 Serial.print(tempF,1);
 Serial.println("F");

 display.clearDisplay();
 oledDisplayHeader();
 

 oledDisplay(3,5,28,humi,"%");
 oledDisplay(2,70,16,tempC,"C");
 oledDisplay(2,70,44,tempF,"F");
 
 display.display(); 
 
}
void oledDisplayHeader(){
 display.setTextSize(1);
 display.setTextColor(WHITE);
 display.setCursor(0, 0);
 display.print("Humidity");
 display.setCursor(60, 0);
 display.print("Temperature");
}
void oledDisplay(int size, int x,int y, float value, String unit){
 int char_lenght=12;
 int xo=x+char_lenght*3.2;
 int xunit=x+char_lenght*3.6;
 int xval = x; 
 display.setTextSize(size);
 display.setTextColor(WHITE);
 
 if (unit=="%"){
   display.setCursor(x, y);
   display.print(value,0);
   display.print(unit);
 } else {
   if (value>99){
    xval=x;
   } else {
    xval=x+char_lenght;
   }
   display.setCursor(xval, y);
   display.print(value,0);
   display.drawCircle(xo, y+2, 2, WHITE);
   display.setCursor(xunit, y);
   display.print(unit);
 }
 
}
