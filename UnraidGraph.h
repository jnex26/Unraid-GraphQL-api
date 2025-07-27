#ifndef UnraidGraph_H
#define UnraidGraph_H


#include <WiFi.h>
#include <WiFiClient.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <String.h>
#include <WiFiClientSecure.h> 

class UnraidGraph
{

private: 
   
public: 
   //constructor 
   UnraidGraph();
   void begin(String graphurl,String key);
   void debug(bool mode);
   DynamicJsonDocument getGraph(DynamicJsonDocument __GraphQuery);
   DynamicJsonDocument returnGraphQuery(DynamicJsonDocument __query);
   DynamicJsonDocument getUnraidParityHistory();

};

#endif