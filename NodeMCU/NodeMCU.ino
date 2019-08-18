#include"function.h"


long Time_Restart;
long Time_Update;

void setup() {
  
  INIT();
  Update_Status_Socket();// update socket
  Time_Restart=millis();
  Time_Update=millis();
}
void loop() {
  if(millis()-Time_Restart>300000){
    Serial.print("Reset System");
    int temp_1=EEPROM.read(1);
    int temp_2=EEPROM.read(2);
    int temp_3=EEPROM.read(3);
    int temp_4=EEPROM.read(4);
    if(Stt_Led_1!=temp_1){     
      EEPROM.write(1,Stt_Led_1); 
      EEPROM.end();   
    }
    if(Stt_Led_2!=temp_2){
      EEPROM.write(2,Stt_Led_2);  
      EEPROM.end();   
    }
    if(Stt_Fan_1!=temp_3){     
      EEPROM.write(3,Stt_Fan_1); 
      EEPROM.end();   
    }
    if(Stt_Fan_2!=temp_4){
      EEPROM.write(4,Stt_Fan_2);  
      EEPROM.end();   
    }
    ESP.restart();
  }  

  if (Firebase.failed()) {
    Serial.println("streaming error");
    Serial.println(Firebase.error());
  }
  
  if (Firebase.available()) {
    FirebaseObject event = Firebase.readEvent();
    String eventType = event.getString("type");
    Serial.print("event: ");
    Serial.println(eventType);
    if (eventType == "put") {
      String path = event.getString("path");
      String data = event.getString("data");
      Serial.println(String("data: ") + data);
      
      if (path.equals("/First Light/value")) {
        if (data.equals("Off")) {
          Stt_Led_1=0;
          Serial.println("First Light is Off");
        } else {
          Stt_Led_1=1;
          Serial.println("First Light is On");
        }
      }
      if (path.equals("/Second Light/value")) {
        if (data.equals("Off")) {
          Stt_Led_2=0;
          Serial.println("Second Light is Off");
        } else {
          Stt_Led_2=1;
          Serial.println("Second Light is On");
        }
      }
      if (path.equals("/First Fan/value")) {
        if (data.equals("Off")) {
          Stt_Fan_1=0;
          Serial.println("First Fan is Off");
        } else {
          Stt_Fan_1=1;
          Serial.println("First Fan is On");
        }
      }
      if (path.equals("/Second Fan/value")) {
        if (data.equals("Off")) {
          Stt_Fan_2=0;
          Serial.println("Second Fan is Off");
        } else {
          Stt_Fan_2=1;
          Serial.println("Second Fan is On");
        }
      }
      
    }
  }

  digitalWrite(Led_1,Stt_Led_1);
  digitalWrite(Led_2,Stt_Led_2);
  digitalWrite(Fan_1,Stt_Fan_1);
  digitalWrite(Fan_2,Stt_Fan_2);
  //Update status
  if(millis()-Time_Update>60000){
    Serial.println("Update data");
    Update_Status_GG();
    Update_Status_Socket();
    Time_Update=millis();
  }
  Socket.loop();
}
