//UnraidGraph.cpp 
#include "UnraidGraph.h"
     
String apikey; // the Auth Creds for the APi Key 
String unraidapiurl; // the url for the unraid API 
bool debugMode = false; // default debugmode 
bool isSecure = false;
bool hasCert = false;
char* rootCACertificate ;




// constructor 
UnraidGraph::UnraidGraph()
{
}

void UnraidGraph::begin(String graphurl,String key){
  apikey = key; 
  unraidapiurl = graphurl;
}

void UnraidGraph::debug(bool mode){
  debugMode = mode; 
}

void UnraidGraph::setSecure(bool mode){
  isSecure = mode; 
}

void UnraidGraph::setCArootCert(char* rootCACert){
  rootCACertificate = rootCACert;
  hasCert = true;
}


JsonDocument UnraidGraph::getGraph(JsonDocument __GraphQuery){  
  JsonDocument __doc;
  if (isSecure) {
     __doc = UnraidGraph::getGraphSecure(__GraphQuery);
  } else {
     __doc = UnraidGraph::getGraphInsecure(__GraphQuery);
  }
  return  __doc;
}

JsonDocument UnraidGraph::getGraphInsecure(JsonDocument __GraphQuery){  
  JsonDocument __doc;
  String __jsonWebcall;
  __doc = UnraidGraph::returnGraphQuery(__GraphQuery);
  if (debugMode){ (__GraphQuery,Serial); }
  serializeJson(__doc,__jsonWebcall);
  __doc = false;
  WiFiClient client;
  HTTPClient http;
  http.begin(client,unraidapiurl);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("x-api-key", apikey);
  if (debugMode) {Serial.println(__jsonWebcall);}
  http.setTimeout(15000);
  http.POST(__jsonWebcall);
  deserializeJson(__doc, http.getString());
  http.end();
  return  __doc;
}


JsonDocument UnraidGraph::getGraphSecure(JsonDocument __GraphQuery){  
  JsonDocument __doc;
  String __jsonWebcall;
  __doc = UnraidGraph::returnGraphQuery(__GraphQuery);
  if (debugMode){ (__GraphQuery,Serial); }
  serializeJson(__doc,__jsonWebcall);
  __doc = false;
  WiFiClientSecure client;
  if (hasCert) {
    client.setCACert(rootCACertificate);
  } else {
    client.setInsecure();
  }
  HTTPClient http;
  http.begin(client,unraidapiurl);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("x-api-key", apikey);
  if (debugMode) {Serial.println(__jsonWebcall);}
  http.setTimeout(15000);
  http.POST(__jsonWebcall);
  deserializeJson(__doc, http.getString());
  http.end();
  return  __doc;
}



JsonDocument UnraidGraph::returnGraphQuery(JsonDocument __query) {
  String __temp;
  serializeJson(__query,__temp);
  //Serial.println("");
  __temp.replace(F(":true"),"");
  __temp.replace(F(":"),"");
  __temp.replace("\"","");
  __temp = __temp.substring(1,__temp.length()-1);

  JsonDocument __tempdoc;
  __tempdoc["query"] = __temp;
  if (debugMode) {
    String __reallytemp; 
    serializeJson(__tempdoc,__reallytemp);
    Serial.println(__reallytemp);
  }
  return __tempdoc;
}

JsonDocument UnraidGraph::getUnraidParityHistory() {
   JsonDocument __resultset;
   JsonDocument __query;
   String __ids[] = {"date","errors","running","speed","status","progress"};
  for(String __id: __ids){
    __query["query"]["parityHistory"][__id]=true;
  }
  if (debugMode) {
    String __reallytemp; 
    serializeJson(__query,__reallytemp);
    Serial.println(__reallytemp);
  }
  __resultset = UnraidGraph::getGraph(__query);
    if (debugMode) {
    String __reallytemp; 
    serializeJson(__resultset,__reallytemp);
    Serial.println(__reallytemp);
  }
   return __resultset; 
}

JsonDocument UnraidGraph::getUnraidDisks() {
   JsonDocument __resultset;
   JsonDocument __query;
   __query["query"]["array"]["capacity"]["kilobytes"]["free"]=true;
   __query["query"]["array"]["capacity"]["kilobytes"]["total"]=true;
   __query["query"]["array"]["state"]=true;
  if (debugMode) {
    String __reallytemp; 
    serializeJson(__query,__reallytemp);
    Serial.println(__reallytemp);
  }
   __resultset = UnraidGraph::getGraph(__query);
   return __resultset; 
}

JsonDocument UnraidGraph::getUnraidArrayCapacity() {
   JsonDocument __resultset;
   JsonDocument __query;
   __query["query"]["array"]["capacity"]["kilobytes"]["free"]=true;
   __query["query"]["array"]["capacity"]["kilobytes"]["total"]=true;
   __query["query"]["array"]["state"]=true;
  if (debugMode) {
    String __reallytemp; 
    serializeJson(__query,__reallytemp);
    Serial.println(__reallytemp);
  }
   __resultset = UnraidGraph::getGraph(__query);
   return __resultset; 
}

JsonDocument UnraidGraph::getUnraidContainers() {
   JsonDocument __resultset;
   JsonDocument __query;
   unsigned long keepmilli = millis();
   __query["query"]["docker"]["containers"]["id"]=true;
   __query["query"]["docker"]["containers"]["names"]=true;
   __query["query"]["docker"]["containers"]["status"]=true;
   __query["query"]["docker"]["containers"]["state"]=true;
   __query["query"]["docker"]["containers"]["autoStart"]=true;
  if (debugMode) {
    String __reallytemp; 
    serializeJson(__query,__reallytemp);
    Serial.println(__reallytemp);

  }
   Serial.println("Starting Transaction");
   Serial.println(keepmilli);
   __resultset = UnraidGraph::getGraph(__query);
   Serial.println(millis());
   Serial.println("Ending Transaction");

   return __resultset; 
}

JsonDocument UnraidGraph::getUnraidVMs() {
   JsonDocument __resultset;
   JsonDocument __query;
   __query["query"]["vms"]["id"]=true;
   __query["query"]["vms"]["domain"]["names"]=true;
   __resultset = UnraidGraph::getGraph(__query);
  if (debugMode) {
    String __reallytemp; 
    serializeJson(__query,__reallytemp);
    Serial.println(__reallytemp);
  }
   return __resultset; 
}

JsonDocument UnraidGraph::getUnraidArrayParity() {
   JsonDocument __resultset;
   JsonDocument __query;
   String __ids[] = {"device","format","numErrors","size","status","critical","rotational","id","warning","type"};
  for(String __id: __ids){
    __query["query"]["array"]["parities"][__id]=true;
  }
  if (debugMode) {
    String __reallytemp; 
    serializeJson(__query,__reallytemp);
  //  Serial.println(__reallytemp);
  }
  __resultset = UnraidGraph::getGraph(__query);
   return __resultset; 
}

JsonDocument UnraidGraph::getUnraidMemory() {
   JsonDocument __resultset;
   JsonDocument __query;
   String __ids[] = {"available","free","max","swapfree","swaptotal","swapused","total","used"};
  for(String __id: __ids){
    __query["query"]["info"]["memory"][__id]=true;
  }
  if (debugMode) {
    String __reallytemp; 
    serializeJson(__query,__reallytemp);
    Serial.println(__reallytemp);
  }
  __resultset = UnraidGraph::getGraph(__query);
   return __resultset; 
}

JsonDocument UnraidGraph::getUnraidArrayDisks() {
   JsonDocument __resultset;
   JsonDocument __query;
   String __ids[] = {"device","format","numErrors","size","status","critical","rotational","id","warning","type"};
  for(String __id: __ids){
    __query["query"]["array"]["disks"][__id]=true;
  }
  if (debugMode) {
    String __reallytemp; 
    serializeJson(__query,__reallytemp);
    Serial.println(__reallytemp);
  }
  __resultset = UnraidGraph::getGraph(__query);
   return __resultset; 
}

JsonDocument UnraidGraph::getUnraidArrayDisksCapacity() {
   JsonDocument __resultset;
   JsonDocument __query;
   String __ids[] = {"idx","fsFree","fsUsed","status","fsSize"};
  for(String __id: __ids){
    __query["query"]["array"]["disks"][__id]=true;
  }
  if (debugMode) {
    String __reallytemp; 
    serializeJson(__query,__reallytemp);
    Serial.println(__reallytemp);
  }
  __resultset = UnraidGraph::getGraph(__query);
   return __resultset; 
}

JsonDocument UnraidGraph::getUnraidCacheCapacity() {
   JsonDocument __resultset;
   JsonDocument __query;
   String __ids[] = {"idx","fsFree","fsUsed","status","fsSize","name"};
  for(String __id: __ids){
    __query["query"]["array"]["caches"][__id]=true;
  }
  if (debugMode) {
    String __reallytemp; 
    serializeJson(__query,__reallytemp);
    Serial.println(__reallytemp);
  }
  __resultset = UnraidGraph::getGraph(__query);
   return __resultset; 
}





