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
   String __Query;
   
   
public: 
   //constructor 
   UnraidGraph();
   void begin(String graphurl,String key);
   void debug(bool __mode);
   void setSecure(bool __mode);
   void setCArootCert(char* __rootCACert);
   void settimeOut(int __timeout);

   JsonDocument getGraph(JsonDocument __GraphQuery);
   JsonDocument getGraphInsecure(JsonDocument __GraphQuery);
   JsonDocument getGraphSecure(JsonDocument __GraphQuery);
   JsonDocument returnGraphQuery(JsonDocument __query);
   
   // This is the pre-canned queies. 

   JsonDocument getUnraidParityHistory();
   JsonDocument getUnraidArrayParity();
   JsonDocument getUnraidArrayDisks();
   JsonDocument getUnraidArrayDisksCapacity();
   JsonDocument getUnraidContainers();
   JsonDocument getUnraidArrayCapacity();
   JsonDocument getUnraidDisks();
   JsonDocument getUnraidMemory();
   JsonDocument getUnraidVMs();
   JsonDocument getUnraidCacheCapacity();

};

#endif