
bool UpdateTime() {
  struct tm timeinfo;
  bool isNew = false;
  if (!getLocalTime(&timeinfo)) {
    InitTime();
    return UpdateTime();
  }
  if (_hour != timeinfo.tm_hour) {
    isNew = true;
    _hour = timeinfo.tm_hour;
  }
  if (_min != timeinfo.tm_min) {
    _min = timeinfo.tm_min;
    isNew = true;
  }
  _sec = timeinfo.tm_sec;

  if (isNew == true)
  {
    Serial.println("updating time");
    Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
  }
  return isNew;
}

void InitTime() {
  ConnectWIFI();
  //init and get the time
  configTime(_gmtOffset_sec, _daylightOffset_sec, _ntpServer);
}

void DisconnectWIFI() {
  //disconnect WiFi as it's no longer needed
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}

void ConnectWIFI() {
  //connect to WiFi
  WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
  WiFiManager wifiManager;
  wifiManager.autoConnect("WordClock");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" CONNECTED");
  if (!MDNS.begin("wordclock")) {
    Serial.println("Error starting mDNS");
    return;
  }
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", index_html, processor);
  });

  server.on("/LEDoff", HTTP_GET, [] (AsyncWebServerRequest * request) {
    _turnLEDsOff = true;
    _doRefresh = true;
    request->send(200, "text/plain", "OK");
  });

  server.on("/LEDon", HTTP_GET, [] (AsyncWebServerRequest * request) {
    _turnLEDsOff = false;
    _doRefresh = true;
    request->send(200, "text/plain", "OK");
  });

  server.on("/update", HTTP_GET, [] (AsyncWebServerRequest * request) {
    if(request->hasParam("color") == true)
    {
      String hexColorString = request->getParam("color")->value();
      long number = (long) strtol( &hexColorString[0], NULL, 16);
      _r = number >> 16;
      _g = number >> 8 & 0xFF;
      _b = number & 0xFF;
      _preferences.putInt("r", _r);
      _preferences.putInt("g", _g);
      _preferences.putInt("b", _b);
      _doRefresh = true;
      Serial.print("Color changed to ");
      Serial.print(_r); Serial.print(" ");
      Serial.print(_g); Serial.print(" ");
      Serial.println(_b);
    }
    if(request->hasParam("brightness") == true)
    {
      String brightnessString = request->getParam("brightness")->value();
      _brightness = brightnessString.toInt();
      _preferences.putInt("brightness", _brightness);
      _doRefresh = true;
      if(_brightness > 0)
        _turnLEDsOff = false;
      else
        _turnLEDsOff = true;
      Serial.print("Brightness changed to ");
      Serial.println(_brightness);
    }
    request->send(200, "text/plain", "OK");
  });

  server.begin();
  MDNS.addService("http", "tcp", 80);
}
