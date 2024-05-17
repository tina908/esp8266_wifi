/*
 WiFiEsp test: ClientTest
*/
//#define DEBUG_WIFI
#define AP_SSID "와이파이명"
#define AP_PASS "와이파이비밀번호"
#define SERVER_NAME "10.10.14.56" //서버명
#define SERVER_PORT 5000  
#define LOGID "KYJ_ARD"
#define PASSWD "PASSWD"

#define WIFITX 7  //7:TX -->ESP8266 RX
#define WIFIRX 6 //6:RX-->ESP8266 TX
#define CMD_SIZE 50           
#include "WiFiEsp.h"
#include "SoftwareSerial.h"

char sendBuf[CMD_SIZE];
char recvBuf[CMD_SIZE]; 

SoftwareSerial wifiSerial(WIFIRX, WIFITX); 
WiFiEspClient client;

void setup() {
  // put your setup code here, to run once:
    Serial.begin(115200); //DEBUG
    wifi_Setup();
}

void loop() {
  // put your main code here, to run repeatedly:
  int len;
  while (client.available()) {
    len = client.readBytesUntil('/',recvBuf,CMD_SIZE); 
    Serial.write(recvBuf);
  }

}
void wifi_Setup() {
  wifiSerial.begin(19200);
  wifi_Init();
  server_Connect();
}
void wifi_Init()
{
  do {
    WiFi.init(&wifiSerial);
    if (WiFi.status() == WL_NO_SHIELD) {
#ifdef DEBUG_WIFI    
      Serial.println("WiFi shield not present");
#endif 
    }
    else
      break;   
  }while(1);

#ifdef DEBUG_WIFI    
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(AP_SSID);
#endif     
    while(WiFi.begin(AP_SSID, AP_PASS) != WL_CONNECTED) {   
#ifdef DEBUG_WIFI  
      Serial.print("Attempting to connect to WPA SSID: ");
      Serial.println(AP_SSID);   
#endif   
    }
#ifdef DEBUG_WIFI      
  Serial.println("You're connected to the network");    
  printWifiStatus();
#endif 
}
int server_Connect()
{
#ifdef DEBUG_WIFI     
  Serial.println("Starting connection to server...");
#endif  

  if (client.connect(SERVER_NAME, SERVER_PORT)) {
#ifdef DEBUG_WIFI     
    Serial.println("Connected to server");
#endif  
    client.print("["LOGID":"PASSWD"]"); 
  }
  else
  {
#ifdef DEBUG_WIFI      
     Serial.println("server connection failure");
#endif    
  } 
}
void printWifiStatus()
{
  // print the SSID of the network you're attached to
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength
  long rssi = WiFi.RSSI();
  Serial.print("Signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
