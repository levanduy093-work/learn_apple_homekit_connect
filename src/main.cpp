#include <WiFi.h>
#include <HomeSpan.h>


struct LED : Service::LightBulb {
  int ledPin;                                       
  SpanCharacteristic *power;                        

  LED(int ledPin) : Service::LightBulb() {
    power = new Characteristic::On();                 
    this->ledPin = ledPin;                            
    pinMode(ledPin, OUTPUT);                         
  }

  boolean update() {            
    digitalWrite(ledPin, power->getNewVal());        
    return true;                                   
  }
};

void setup() {
  Serial.begin(115200);  

  homeSpan.setPairingCode("11122333");
  homeSpan.begin(Category::Lighting, "My Lights");

  new SpanAccessory();                              
    new Service::AccessoryInformation();           
      new Characteristic::Identify();               
  new LED(2);                                      
}

void loop() {
  homeSpan.poll();                                
}