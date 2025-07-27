

# Unraid-GraphQL-api
This is an attempt at getting a ESP32 to query a graphQL 

you will need your own creds.h file to compile and build... these are the following definitions you will need 

const char* ssid = STASSID;

const char* password = STAPSK;

const char* unraidapiey = UNRAIDAPI;

const char* unraidapi = UNRAIDURL;


tested on ESP32-S3 ESP32-C3... 


Notes on the creds.h file. needs to look like below. 

```
#ifndef STASSID                        // either use an external .h file containing STASSID and STAPSK - or 
//                                     // add defines to your boards - or
#define STASSID "<YOUR SSID HERE>"            // ... modify these line to your SSID
#define STAPSK  "<YOUR PASSWORD HERE >"        // ... and set your WIFI password
#define UNRAIDAPI "<YOUR UNRAID API KEY HERE" // just the Key. 
#define UNRAIDURL "<YOUR UNRAID GRAPHQL LOCATION HERE> " // this is the full URL 
#endif

const char* ssid = STASSID;
const char* password = STAPSK;
const char* unraidapiey = UNRAIDAPI;
const char* unraidapi = UNRAIDURL;
```
