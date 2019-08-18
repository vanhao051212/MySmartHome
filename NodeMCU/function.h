#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <SocketIoClient.h>
#include <EEPROM.h>
#include <Ticker.h>

#define FIREBASE_HOST "my-home-bdbda.firebaseio.com"
#define FIREBASE_AUTH "oaC7ME7mBzTiIiXgLahszrTlotaEIXIVCvQzDraE"
const char* ssid     = "NaOH+HCl->?";
//const char* ssid     = "Van Hao";
const char* password = "17520451";
SocketIoClient Socket;
const char* Host_Socket = "vanhao.herokuapp.com";
unsigned int Port_Socket=80;
/******************* Define sth *****************/
Ticker Check;
#define Time_Check 1
#define B_Led_1 D4
#define B_Led_2 D1
#define B_Fan_1 D2
#define B_Fan_2 D3
#define Led_1   D5
#define Led_2   D6
#define Fan_1   D7
#define Fan_2   D8
int Stt_Led_1=0;
int Stt_Led_2=0;
int Stt_Fan_1=0;
int Stt_Fan_2=0;

long Time_Wifi;
/*************** Define some function ***************/
void INIT();
void Ticker_Check();
void Reply_1(const char * payload, size_t length);
void Reply_2(const char * payload, size_t length);
void Reply_3(const char * payload, size_t length);
void Reply_4(const char * payload, size_t length);
void Send_Stt(const char * payload, size_t length);
void Update_Status_Socket();
void Update_Status_GG();
/*************** Describe function ******************/
void INIT(){
  Serial.begin(115200);
  EEPROM.begin(512);
  Stt_Led_1=EEPROM.read(1);
  Stt_Led_2=EEPROM.read(2);
  Stt_Fan_1=EEPROM.read(3);
  Stt_Fan_2=EEPROM.read(4);
  pinMode(Led_1,OUTPUT);
  pinMode(Led_2,OUTPUT);
  pinMode(Fan_1,OUTPUT);
  pinMode(Fan_2,OUTPUT);
  digitalWrite(Led_1,Stt_Led_1);
  digitalWrite(Led_2,Stt_Led_2);
  digitalWrite(Fan_1,Stt_Fan_1);
  digitalWrite(Fan_2,Stt_Fan_2);
  Check.attach_ms(Time_Check,Ticker_Check);
  pinMode(B_Led_1,INPUT_PULLUP);
  pinMode(B_Led_2,INPUT_PULLUP);
  pinMode(B_Fan_1,INPUT_PULLUP);
  pinMode(B_Fan_2,INPUT_PULLUP);
  // connect to wifi.
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  Time_Wifi=millis();
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if(millis()-Time_Wifi>30000){
//      ESP.restart();
      break;
    }
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Socket.on("server_reply_1",Reply_1);
  Socket.on("server_reply_2",Reply_2);
  Socket.on("server_reply_3",Reply_3);
  Socket.on("server_reply_4",Reply_4);
  Socket.on("Update",Send_Stt);
  Socket.begin(Host_Socket, Port_Socket, "/socket.io/?transport=websocket");
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.stream("/ESP8266");
}

void Ticker_Check(){
  if(!digitalRead(B_Fan_1)){
    while(!digitalRead(B_Fan_1));
    Serial.print("Stt Fan 1 change");
    Stt_Fan_1^=1;
    Serial.println(Stt_Fan_1);
  }
  if(!digitalRead(B_Fan_2)){
    while(!digitalRead(B_Fan_2));
    Serial.print("Stt Fan 2 change");
    Stt_Fan_2^=1;
    Serial.println(Stt_Fan_2);
  }
  if(!digitalRead(B_Led_1)){
    while(!digitalRead(B_Led_1));
    Serial.print("Stt Led 1 change");
    Stt_Led_1^=1;
    Serial.println(Stt_Led_1);
  }
  if(!digitalRead(B_Led_2)){
    while(!digitalRead(B_Led_2));
    Serial.print("Stt Led 2 change");
    Stt_Led_2^=1;
    Serial.println(Stt_Led_2);
  }  
}

void Reply_1(const char * payload, size_t length){
  if(String(payload)=="ON"){
    Stt_Led_1=1;  
    Serial.println("Led 1 ON");
  }
  if(String(payload)=="OFF"){
    Stt_Led_1=0;  
    Serial.println("Led 1 OFF");
  }
  digitalWrite(Led_1,Stt_Led_1);
}

void Reply_2(const char * payload, size_t length){
  if(String(payload)=="ON"){
    Stt_Led_2=1;
    Serial.println("Led 2 ON");
  }
  if(String(payload)=="OFF"){   
    Stt_Led_2=0;
    Serial.println("Led 2 OFF");
  }
  digitalWrite(Led_2,Stt_Led_2);
}

void Reply_3(const char * payload, size_t length){
  if(String(payload)=="ON"){
    Stt_Fan_1=1;  
    Serial.println("Fan 1 ON");
  }
  if(String(payload)=="OFF"){
    Stt_Fan_1=0;  
    Serial.println("Fan 1 OFF");
  }
  digitalWrite(Fan_1,Stt_Fan_1);
}

void Reply_4(const char * payload, size_t length){
  if(String(payload)=="ON"){
    Stt_Fan_2=1;
    Serial.println("Fan 2 ON");
  }
  if(String(payload)=="OFF"){   
    Stt_Fan_2=0;
    Serial.println("Fan 2 OFF");
  }
  digitalWrite(Fan_2,Stt_Fan_2);
}

void Send_Stt(const char * payload, size_t length){
  Update_Status_Socket();
}

void Update_Status_Socket(){
  if(Stt_Led_1){
    Socket.emit("Client_update_1_on");
  }
  else{
    Socket.emit("Client_update_1_off");
  }
  if(Stt_Led_2){
    Socket.emit("Client_update_2_on");
  }
  else{
    Socket.emit("Client_update_2_off");
  }
  if(Stt_Fan_1){
    Socket.emit("Client_update_3_on");
  }
  else{
    Socket.emit("Client_update_3_off");
  }
  if(Stt_Fan_2){
    Socket.emit("Client_update_4_on");
  }
  else{
    Socket.emit("Client_update_4_off");
  }
}

void Update_Status_GG(){
  if(Stt_Fan_1){
    Firebase.setString("/ESP8266/First Fan/value","On");
  }else{
    Firebase.setString("/ESP8266/First Fan/value","Off");
  }
  if(Stt_Fan_2){
    Firebase.setString("/ESP8266/Second Fan/value","On");
  }else{
    Firebase.setString("/ESP8266/Second Fan/value","Off");
  }
  if(Stt_Led_1){
    Firebase.setString("/ESP8266/First Light/value","On");
  }else{
    Firebase.setString("/ESP8266/First Light/value","Off");
  }
  if(Stt_Led_2){
    Firebase.setString("/ESP8266/Second Light/value","On");
  }else{
    Firebase.setString("/ESP8266/Second Light/value","Off");
  }
  if (Firebase.failed()) {
  Serial.print("setting /message failed:");
  Serial.println(Firebase.error());  
  }
    
}
