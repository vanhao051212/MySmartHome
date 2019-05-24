#include "function.h"

long Time_Restart;
void(* resetFunc) (void) = 0;
void setup() {
  // put your setup code here, to run once:

  INIT();
  Update_Status();
  Time_Restart=millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(millis()-Time_Restart>30000){
    Serial.print("Reset System");
    int temp_1=EEPROM.read(1);
    int temp_2=EEPROM.read(2);
    if(Stt_1!=temp_1){     
      EEPROM.write(1,Stt_1); 
      EEPROM.end();   
    }
    if(Stt_2!=temp_2){
      EEPROM.write(2,Stt_2);  
      EEPROM.end();   
    }
    ESP.restart();
  }
  if(Serial.available()>0){
    char Character =Serial.read();
    if(Character=='a'){
      digitalWrite(Led_1,1);
      Stt_1=true;
      Serial.print("Led 1 on");
    }
    if(Character=='b'){
      digitalWrite(Led_1,0);
      Stt_1=false;
      Serial.print("Led 1 off");
      
    } 
    if(Character=='c'){
      digitalWrite(Led_2,1);
      Stt_2=true;
      Serial.print("Led 2 on");
    }
    if(Character=='d'){
      digitalWrite(Led_2,0);
      Stt_2=false;
      Serial.print("Led 2 off");
      
    } 
    Update_Status(); 
  }
  
  Socket.loop();
}
