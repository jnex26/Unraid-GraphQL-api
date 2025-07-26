//UnraidGraph.cpp 
#include "UnraidGraph.h"
     
String apikey; // the Auth Creds for the APi Key 
String unraidapi; // the url for the unraid API 



// constructor 
UnraidGraph::UnraidGraph()
{
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
  http.begin(client,unraidapi);
  http.setTimeout(5000);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("x-api-key", apikey);
  Serial.println(__jsonWebcall);
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
  return __tempdoc;
}

DynamicJsonDocument UnraidGraph::getUnraidParityHistory() {
   DynamicJsonDocument __resultset(4096);
   DynamicJsonDocument __query(1024);
   String __ids[] = {"date","errors","running","speed","status","progress"};
  for(String __id: __ids){
    __query["query"]["parityHistory"][__id]=true;
  }
  __resultset = UnraidGraph::getGraph(__query);
   return __resultset; 
}