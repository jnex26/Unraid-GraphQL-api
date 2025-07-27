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
   JsonDocument getGraph(JsonDocument __GraphQuery);
   JsonDocument returnGraphQuery(JsonDocument __query);
   
   // This is the pre-canned queies. 

   JsonDocument getUnraidParityHistory();
   JsonDocument getUnraidArrayParity();
   JsonDocument getUnraidArrayDisks();
   JsonDocument getUnraidContainers();
   JsonDocument getUnraidArrayCapacity();
   JsonDocument getUnraidDisks();
   JsonDocument getUnraidMemory();
   JsonDocument getUnraidVMs();

};

#endif