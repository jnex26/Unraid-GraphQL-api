#ifndef UnraidGraph_H
#define UnraidGraph_H


#include <WiFi.h>
#include <WiFiClient.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <String.h>
#include <WiFiClientSecure.h>
//#include <creds.h> 

class UnraidGraph
{

private: 
   
public: 
   //constructor 
   UnraidGraph();
   DynamicJsonDocument getGraph(DynamicJsonDocument __GraphQuery);
   DynamicJsonDocument returnGraphQuery(DynamicJsonDocument __query);
   DynamicJsonDocument getUnraidParityHistory();

};

#endif