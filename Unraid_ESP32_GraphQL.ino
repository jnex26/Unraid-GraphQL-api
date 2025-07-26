//
// An Attempt at hacking GraphQL into an ESP32. 
//
//Tested on a S3 and C3 Micro seems to work.. still need to figure out the timeouts 
//

#include <WiFi.h>
#include <WiFiClient.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <String.h>
#include <WiFiClientSecure.h>
#include <creds.h> 

//
//   Pre-Canned Queries here !! 
//
//
//

DynamicJsonDocument getUnraidDisks() {
   DynamicJsonDocument __resultset(2048);
   DynamicJsonDocument __query(1024);
   __query["query"]["array"]["capacity"]["kilobytes"]["free"]=true;
   __query["query"]["array"]["capacity"]["kilobytes"]["total"]=true;
   __query["query"]["array"]["state"]=true;
   __resultset = getGraph(__query);
   return __resultset; 
}

DynamicJsonDocument getUnraidMemory() {
   DynamicJsonDocument __resultset(2048);
   DynamicJsonDocument __query(1024);
   __query["query"]["array"]["capacity"]["kilobytes"]["free"]=true;
   __query["query"]["array"]["capacity"]["kilobytes"]["total"]=true;
   __query["query"]["array"]["state"]=true;
   __resultset = getGraph(__query);
   return __resultset; 
}

DynamicJsonDocument getUnraidContainers() {
   DynamicJsonDocument __resultset(4096);
   DynamicJsonDocument __query(1024);
   __query["query"]["docker"]["containers"]["labels"]=true;
   __query["query"]["docker"]["containers"]["names"]=true;
   __query["query"]["docker"]["containers"]["status"]=true;
   __query["query"]["docker"]["containers"]["state"]=true;
   __query["query"]["docker"]["containers"]["ports"]["publicPort"]=true;
   __resultset = getGraph(__query);
   return __resultset; 
}

//
//  Actual work below. 
//
//

DynamicJsonDocument returnGraphQuery(DynamicJsonDocument __query) {
  String __temp;
  // Graph QL is close to JSON but no cigar so I'm beaving irrisponcbiliy and just removing elements, seems to work for now... 
  // I'll have to become a bit more creative as some point. 
  //
  //  this function takes the original JSON document and translates it into something close enough for the unraid graphQL api. 
  //
  //
  //
  serializeJson(__query,__temp);
  Serial.println("");
  __temp.replace(F(":true"),"");
  __temp.replace(F(":"),"");
  __temp.replace("\"","");
  __temp = __temp.substring(1,__temp.length()-1);
  DynamicJsonDocument __tempdoc(2036);
  __tempdoc["query"] = __temp;
  return __tempdoc;
}


DynamicJsonDocument getGraph(DynamicJsonDocument __GraphQuery){  
  //
  //  this takes the formatted not quite GraphQL language and packs it up with the API key and the right headers to submit the query 
  //
  //
  DynamicJsonDocument __doc(4096);
  String __jsonWebcall;
  __doc = returnGraphQuery(__GraphQuery);
  serializeJson(__GraphQuery,Serial);
  serializeJson(__doc,__jsonWebcall);
  __doc = false;
  WiFiClient client;
  HTTPClient http;
  http.begin(client,unraidapi);
  http.setTimeout(5000);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("x-api-key", unraidapiey);
  Serial.println(__jsonWebcall);
  http.POST(__jsonWebcall);
  deserializeJson(__doc, http.getString());
  http.end();
  return  __doc;
}

void configureWifi() {
  //
  //  this is normal behaviour for me I bundle up my Wifi Connection into a function, so I copy and paste between codesets. 
  //  At somepoint I'll write a header/library file for this... 
  //
  WiFi.begin(ssid, password);  
  Serial.print("Starting Wifi - Connecting to :");
  Serial.print(ssid);
  Serial.print(" Connecting");
  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
      Serial.print(".");
      delay(1000);
  }
  Serial.println("Connected");
}


//
// I do most of the work in Setup becuase I'm testing i have no need for anything looping atm. 
//
//
void setup() {
  Serial.begin(115200);
  delay(100);
  Serial.print("Hello! World");
  DynamicJsonDocument tempdoc(2036);
  DynamicJsonDocument tempdoc2(2036);
  tempdoc["query"]["notifications"]["id"]=true;
  String test;
  serializeJson(tempdoc2,Serial);
  configureWifi();
  tempdoc = getGraph(tempdoc);
  serializeJson(tempdoc,Serial);
  tempdoc = getUnraidDisks();
  serializeJson(tempdoc,Serial);
  tempdoc = getUnraidContainers();
  serializeJson(tempdoc,Serial);
  tempdoc = getUnraidMemory();
  serializeJson(tempdoc,Serial);
}

void loop() {
  // put your main code here, to run repeatedly:

}
