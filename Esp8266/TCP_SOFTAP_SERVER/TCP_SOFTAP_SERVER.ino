#include <ESP8266WiFi.h>

WiFiServer wifiServer(80); //initialise wifi server via port 80(tcp)
const char* ssid = "tcp_server"; //wifi server ssid
const char* pass = "spj56spj"; //password to wifi
IPAddress staticIP(192,168,0,1); //static ip of server
IPAddress gateway(192,168,0,2); //gateway of server
IPAddress subnet(255,255,255,0); //subnet mask

void setup() {
  ESP.eraseConfig();
  Serial.begin(115200);
  WiFi.disconnect(true);
  WiFi.mode(WIFI_AP);
  Serial.println("");
  Serial.print("configuring wifi settings: ");
  Serial.println(WiFi.softAPConfig(staticIP, gateway, subnet) ? "Successful" : "Failed");
  Serial.print("Sarting soft-AP server: ");
  Serial.println(WiFi.softAP(ssid, pass) ? "Sucessful" : "Failed");
  Serial.print("Server IP: ");
  Serial.println(WiFi.softAPIP());
  wifiServer.begin();
}

void loop() {
  WiFiClient client = wifiServer.available();
  if(client){
    while(client.connected()){
      char clientread[] = "";
      while(client.available()>0){
        char cache = client.read();
        strncat(clientread,&cache,1);
      }
      if(strlen(clientread)>0){
        Serial.println(clientread);
        client.write("success");
      }
    }
    client.stop();
    Serial.println("Client disconnected");
  }
}
