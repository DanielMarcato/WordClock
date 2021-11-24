
void setup() {
  Serial.begin(115200);
  Serial.println("Hello from WordClock");
  _preferences.begin("wordclock", false); 
  _r = _preferences.getInt("r", 255);
  _g = _preferences.getInt("g", 255);
  _b = _preferences.getInt("b", 255);
  _brightness = _preferences.getInt("brightness", 10);
  pinMode(_clockPin, OUTPUT);
  pinMode(_dataPin, OUTPUT);
  InitTime();

  ClearLEDsArray();
  ShowLEDsArray();
  ShowAllLEDs();
  delay(1000);
  LoopLED(10);
}
