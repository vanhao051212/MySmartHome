#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <SocketIoClient.h>
#include <EEPROM.h>
SocketIoClient Socket;

//const char* ssid     = "Van Hao";
//const char* password = "17520451";

const char* ssid     = "NaOH+HCl->?";
const char* password = "17520451";

const char* Host_Socket = "vanhao.herokuapp.com";
unsigned int Port_Socket=80;
//const char* Host_Socket = "192.168.137.1";
//unsigned int Port_Socket=8000;

void Reply_1(const char * payload, size_t length);
void Reply_2(const char * payload, size_t length);
void Send_Stt(const char * payload, size_t length);
void Update_Status();
#define Led_1 D5
#define Led_2 D6
int Stt_1=0;
int Stt_2=0;  
void INIT() {
  Serial.begin(115200);
  EEPROM.begin(512);
  Stt_1=EEPROM.read(1);
  Stt_2=EEPROM.read(2);
  pinMode(Led_1,OUTPUT);
  pinMode(Led_2,OUTPUT);
  digitalWrite(Led_1,Stt_1);
  digitalWrite(Led_2,Stt_2);


  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

 while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP()); 

  // socket
  
  Socket.on("server_reply_1",Reply_1);
  Socket.on("server_reply_2",Reply_2);
  Socket.on("Update",Send_Stt);
  Socket.begin(Host_Socket, Port_Socket, "/socket.io/?transport=websocket");

}

void Reply_1(const char * payload, size_t length){
  if(String(payload)=="ON"){
    Stt_1=1;  
    Serial.println("Led 1 ON");
  }
  if(String(payload)=="OFF"){
    Stt_1=0;  
    Serial.println("Led 1 OFF");
  }
  digitalWrite(Led_1,Stt_1);
}
void Reply_2(const char * payload, size_t length){
  if(String(payload)=="ON"){
    Stt_2=1;
    Serial.println("Led 2 ON");
  }
  if(String(payload)=="OFF"){   
    Stt_2=0;
    Serial.println("Led 2 OFF");
  }
  digitalWrite(Led_2,Stt_2);
}

void Send_Stt(const char * payload, size_t length){
  Update_Status();
}
void Update_Status(){
  if(Stt_1==1){
    Socket.emit("Client_update_1_on");
  }
  else{
    Socket.emit("Client_update_1_off");
  }
  if(Stt_2==1){
    Socket.emit("Client_update_2_on");
  }
  else{
    Socket.emit("Client_update_2_off");
  }
}
