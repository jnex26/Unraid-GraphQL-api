//UnraidGraph.cpp 
#include "UnraidGraph.h"
     
String apikey; // the Auth Creds for the APi Key 
String unraidapiurl; // the url for the unraid API 
bool debugMode = false; // default debugmode 



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

DynamicJsonDocument UnraidGraph::getGraph(DynamicJsonDocument __GraphQuery){  
  DynamicJsonDocument __doc(4096);
  String __jsonWebcall;
  __doc = UnraidGraph::returnGraphQuery(__GraphQuery);
  serializeJson(__GraphQuery,Serial);
  serializeJson(__doc,__jsonWebcall);
  __doc = false;
  WiFiClient client;
  HTTPClient http;
  http.begin(client,unraidapiurl);
  http.setTimeout(5000);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("x-api-key", apikey);
  if (debugMode) {Serial.println(__jsonWebcall);}
  http.POST(__jsonWebcall);
  deserializeJson(__doc, http.getString());
  http.end();
  return  __doc;
}


DynamicJsonDocument UnraidGraph::returnGraphQuery(DynamicJsonDocument __query) {
  String __temp;
  serializeJson(__query,__temp);
  Serial.println("");
  __temp.replace(F(":true"),"");
  __temp.replace(F(":"),"");
  __temp.replace("\"","");
  __temp = __temp.substring(1,__temp.length()-1);

  DynamicJsonDocument __tempdoc(2036);
  __tempdoc["query"] = __temp;
  if (debugMode) {
    String __reallytemp; 
    serializeJson(__tempdoc,__reallytemp);
    Serial.println(__reallytemp);
  }
  return __tempdoc;
}

DynamicJsonDocument UnraidGraph::getUnraidParityHistory() {
   DynamicJsonDocument __resultset(4096);
   DynamicJsonDocument __query(1024);
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