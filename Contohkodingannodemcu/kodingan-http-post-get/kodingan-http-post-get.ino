#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* wifiName = "Ayana";
const char* wifiPass = "12345678";
byte mac[6]; 
 
//Web Server address to read/write from 
const char *host = "http://4bc4e9cb.ngrok.io/book";
 
void setup() {

  Serial.begin(115200);
  delay(10);
  Serial.println();
  
  Serial.print("Connecting to ");
  Serial.println(wifiName);
 
  WiFi.begin(wifiName, wifiPass);

 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  WiFi.macAddress(mac);
  Serial.print("MAC: ");
  Serial.print(mac[5],HEX);
  Serial.print(":");
  Serial.print(mac[4],HEX);
  Serial.print(":");
  Serial.print(mac[3],HEX);
  Serial.print(":");
  Serial.print(mac[2],HEX);
  Serial.print(":");
  Serial.print(mac[1],HEX);
  Serial.print(":");
  Serial.println(mac[0],HEX);

  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());   //You can get IP address assigned to ESP
}
 
void loop() {
  // print macAdress
  WiFi.macAddress(mac);
  Serial.print("MAC: ");
  Serial.print(mac[5],HEX);
  Serial.print(":");
  Serial.print(mac[4],HEX);
  Serial.print(":");
  Serial.print(mac[3],HEX);
  Serial.print(":");
  Serial.print(mac[2],HEX);
  Serial.print(":");
  Serial.print(mac[1],HEX);
  Serial.print(":");
  Serial.println(mac[0],HEX);

  //print IP Adress
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  //start connection
  if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
  
  DynamicJsonDocument doc(1024);
  
  HTTPClient http;    //Declare object of class HTTPClient
 
  http.begin("http://f82c75d3.ngrok.io/book");      //Specify request destination
  http.addHeader("Content-Type", "application/json");  //Specify content-type header
 
  int httpCode = http.POST("{'angka':5}");   //Send the request
  String payload = http.getString();                  //Get the response payload
 
 //  Serial.println(httpCode);   //Print HTTP return code
   Serial.println(payload);    //Print request response payload

  deserializeJson(doc, payload);
  JsonObject obj = doc.as<JsonObject>();
  String hasil = obj["hasil"];
  Serial.println(hasil);
    
   http.end();  //Close connection
 
 }else{
 
    Serial.println("Error in WiFi connection");   
 
 }
 
  delay(30000);  //Send a request every 30 seconds
 
}

