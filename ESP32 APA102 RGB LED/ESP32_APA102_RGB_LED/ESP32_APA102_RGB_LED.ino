#include <WiFi.h>
#include "time.h"
#include <WiFiManager.h>
#include <ESPmDNS.h>
#include <ESPAsyncWebServer.h>
#include <Preferences.h>

#define _clockPin 26     // GPIO-PIN
#define _dataPin 13     // GPIO-PIN
#define NUMBEROFLEDS 81  // Number of APA102 LEDs in String
Preferences _preferences;
const char* _ntpServer = "pool.ntp.org";
const long  _gmtOffset_sec = 3600;
const int   _daylightOffset_sec = 3600;
int _hour = -1, _min = -1, _sec = -1;
AsyncWebServer server(80); // Create an Asynchronous Webserver
int _brightness  = 10;
bool _doRefresh = false;
bool _turnLEDsOff = false;
int _r = 255, _g = 255, _b = 255;
String _creator = "Daniel";

typedef struct colorRGBB  {
    uint8_t red, green, blue, brightness;
} colorRGBB;

colorRGBB _LEDs[81];

void writeByte(uint8_t b) {
  uint8_t pos;
  for (pos=0;pos<=7;pos++) {
     digitalWrite(_dataPin, b >> (7-pos) & 1);
     digitalWrite(_clockPin, HIGH);
     digitalWrite(_clockPin, LOW);
   }
}

  /*
  T W E N T Y T E N
      H A L F I V E-
  Q U A R T E R H I
  P A S T O   S I X-
  E L E V E N I N E
  T H R E E I G H T-
  T W E L V E T E N
  S E V E N F I V E-
  F O U R T W O N E
  */ 
 #define FIVE 5, 1, 4
 #define TEN 6, 0, 3
 #define QUARTER 0, 2, 7
 #define TWENTY 0, 0, 6
 #define TEN2 6,0,3
 #define FIVE2 0,1,4
 #define HALF 3, 1, 4
 #define PAST 5,3,4
 #define TO 4,3,2
 #define ONE 6,8,3
 #define TWO 4,8,3
 #define THREE 4,5,5
 #define FOUR 0,8,4
 #define FIVE 0,7,4
 #define SIX 0,3,3
 #define SEVEN 4,7,5
 #define EIGHT 0,5,5
 #define NINE 5,4,4
 #define TEN 6,6,3
 #define ELEVEN 0,4,6
 #define TWELVE 0,6,6
