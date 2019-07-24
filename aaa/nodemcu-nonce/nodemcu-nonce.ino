#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Crypto.h>
#define KEY_LENGTH 16

const char* wifiName = "Ayana";
const char* wifiPass = "12345678";
byte mac[6]; 
String stringhmac = "";

//Web Server address to read/write from 
//const char *host = "https://b74e412c.ngrok.io/book";
 
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
 /* Define our */
byte key[KEY_LENGTH] = {'H','A','C','K','T','H','I','S','I','F','Y','O','U','C','A','N'};
/* Create the HMAC instance with our key */
SHA256HMAC hmac(key, KEY_LENGTH);

/* Update the HMAC with just a plain string (null terminated) */
hmac.doUpdate("TEST");

/* Finish the HMAC calculation and return the authentication code */
byte authCode[SHA256HMAC_SIZE];
hmac.doFinal(authCode);

/* authCode now contains our 32 byte authentication code */
for (byte i; i < SHA256HMAC_SIZE; i++)
{
    stringhmac += String(authCode[i], HEX);
}
 Serial.println(stringhmac);
}

 
void loop() {

printmacAdress();

printIPAdress();

  //start connection
  if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status

  // You can use a String as your JSON input.
  // WARNING: the string in the input  will be duplicated in the JsonDocument.
  DynamicJsonDocument doc(1024);
  
   HTTPClient http;    //Declare object of class HTTPClient
 
   http.begin("http://b74e412c.ngrok.io/book");      //Specify request destination
   http.addHeader("Content-Type", "application/json");  //Specify content-type header
    
   int httpCode = http.POST("{\"username\":\"HACKME\"}");   //Send the request
   String payload = http.getString();                  //Get the response payload
 
   //Serial.println(httpCode);   //Print HTTP return code
   Serial.println(payload);    //Print request response payload

    deserializeJson(doc, payload);
    JsonObject obj = doc.as<JsonObject>();
    String hasil = obj["hasil"];
    Serial.println(hasil);
    
   http.end();  //Close connection
   
 
 }

 
 
 else{
 
    Serial.println("Error in WiFi connection");   
 
 }
 
  delay(10000);  //Send a request every 30 seconds
 
}


void printmacAdress(){
    
  String stringmac = "";
  // print macAdress
  Serial.println();
  WiFi.macAddress(mac);
  for (int j=0; j < 6; j++)
  {
      stringmac += String(mac[j], HEX);
  }
   Serial.println(stringmac);
}

void printIPAdress(){

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());   //You can get IP address assigned to ESP

}
