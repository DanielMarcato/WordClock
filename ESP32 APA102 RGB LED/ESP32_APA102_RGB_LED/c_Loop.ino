
void loop() {
  bool TimeIsNew = UpdateTime();
  if(TimeIsNew == true || _doRefresh == true)
  {  
    Serial.println("updating LEDs");
    TimeToLEDsArray(_hour, _min);
    ShowLEDsArray();
    _doRefresh= false;
  }
}
