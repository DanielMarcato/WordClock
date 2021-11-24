
void startFrame() {
  //Serial.println("startFrame");
  writeByte(0);
  writeByte(0);
  writeByte(0);
  writeByte(0);
}

void endFrame(uint16_t count) {
  //Serial.println("endFrame");
  writeByte(0xFF);
  writeByte(0xFF);
  writeByte(0xFF);
  writeByte(0xFF);
}

void writeRGB(uint8_t red, uint8_t green, uint8_t blue, uint8_t brightness) {
  writeByte(0b11100000 | brightness);
  writeByte(blue);
  writeByte(green);
  writeByte(red);
}

void writeColor(colorRGBB color) {
  writeRGB(color.red, color.green, color.blue, color.brightness);
}

void writeColors(colorRGBB * colors, uint16_t count) {
  //Serial.println("writeColors");
  startFrame();
  for(int i = 0; i < count; i++) {
    writeColor(colors[i]);
  }
  endFrame(count);
} 

void ShowLEDsArray(){
  writeColors(_LEDs, NUMBEROFLEDS+1);
}

void AddWordToLEDsArray(int x, int y, int l) {
  int start = y * 9 + x;
    for(int i = start; i < start+l; i++)
    {
        _LEDs[i].red=_r;
        _LEDs[i].green=_g;
        _LEDs[i].blue=_b;
        if(_turnLEDsOff == false)
          _LEDs[i].brightness=_brightness;
        else
          _LEDs[i].brightness=0;
    }
}

void ClearLEDsArray(){
    for(int i = 0; i < NUMBEROFLEDS; i++) {
       _LEDs[i].red=0;
       _LEDs[i].green=0;
       _LEDs[i].blue=0;
       _LEDs[i].brightness=0;
     }
}

void ShowAllLEDs(){
  for(int i = 0; i < NUMBEROFLEDS; i++) {
       _LEDs[i].red=_r;
       _LEDs[i].green=_g;
       _LEDs[i].blue=_b;
       if(_turnLEDsOff == false)
          _LEDs[i].brightness=_brightness;
        else
          _LEDs[i].brightness=0;
  }
  ShowLEDsArray();
}

void TimeToLEDsArray(int hour, int minute){
  
  ClearLEDsArray();

  int leftover = minute % 5;
  minute = minute - leftover;

  if (minute >= 35)
    hour = (hour + 1) % 24; // Switch to "TO" minutes the next hour

  /*
  switch (leftover)
  {
  case 4:
    AddWordToLEDsArray(DIGITFOUR);
  case 3: // fall through
    AddWordToLEDsArray(DIGITTHREE);
  case 2: // fall through
    AddWordToLEDsArray(DIGITTWO);
  case 1: // fall through
    AddWordToLEDsArray(DIGITONE);
  case 0: // fall through
    break;
  }  
  */ 

  switch (minute)
  {
  case 5:
    AddWordToLEDsArray(FIVE2);
    AddWordToLEDsArray(PAST);
    break;
  case 10:
    AddWordToLEDsArray(TEN2);
    AddWordToLEDsArray(PAST);
    break;
  case 15:
    AddWordToLEDsArray(QUARTER);
    AddWordToLEDsArray(PAST);
    break;
  case 20:
    AddWordToLEDsArray(TWENTY);
    AddWordToLEDsArray(PAST);
    break;
  case 25:
    AddWordToLEDsArray(TWENTY);
    AddWordToLEDsArray(FIVE2);
    AddWordToLEDsArray(PAST);
    break;
  case 30:
    AddWordToLEDsArray(HALF);
    AddWordToLEDsArray(PAST);
    break;
  case 35:
    AddWordToLEDsArray(TWENTY);
    AddWordToLEDsArray(FIVE2);
    AddWordToLEDsArray(TO);
    break;
  case 40:
    AddWordToLEDsArray(TWENTY);
    AddWordToLEDsArray(TO);
    break;
  case 45:
    AddWordToLEDsArray(QUARTER);
    AddWordToLEDsArray(TO);
    break;
  case 50:
    AddWordToLEDsArray(TEN2);
    AddWordToLEDsArray(TO);
    break;
  case 55:
    AddWordToLEDsArray(FIVE2);
    AddWordToLEDsArray(TO);
    break;
  default:
    Serial.print("Invalid minute ");
    Serial.println(minute);
  }

  switch (hour)
  {
  case 0:
  case 12:
    AddWordToLEDsArray(TWELVE);
    break;
  case 1:
  case 13:
    AddWordToLEDsArray(ONE);
    break;
  case 2:
  case 14:
    AddWordToLEDsArray(TWO);
    break;
  case 3:
  case 15:
    AddWordToLEDsArray(THREE);
    break;
  case 4:
  case 16:
    AddWordToLEDsArray(FOUR);
    break;
  case 5:
  case 17:
    AddWordToLEDsArray(FIVE);
    break;
  case 6:
  case 18:
    AddWordToLEDsArray(SIX);
    break;
  case 7:
  case 19:
    AddWordToLEDsArray(SEVEN);
    break;
  case 8:
  case 20:
    AddWordToLEDsArray(EIGHT);
    break;
  case 9:
  case 21:
    AddWordToLEDsArray(NINE);
    break;
  case 10:
  case 22:
    AddWordToLEDsArray(TEN);
    break;
  case 11:
  case 23:
    AddWordToLEDsArray(ELEVEN);
    break;
  default:
    Serial.print("Invalid hour ");
    Serial.println(hour);
  }
}

void LoopLED(int ms){
  Serial.println("Looping LED");
  for(int i = 0; i < NUMBEROFLEDS; i++){
    ClearLEDsArray();
    _LEDs[i].red=_r;
    _LEDs[i].green=_g;
    _LEDs[i].blue=_b;
    if(_turnLEDsOff == false)
          _LEDs[i].brightness=_brightness;
        else
          _LEDs[i].brightness=0;
    ShowLEDsArray();
    delay(ms);
  }
  for(int i = NUMBEROFLEDS-1; i >= 0; i--){
    ClearLEDsArray();
    _LEDs[i].red=_r;
    _LEDs[i].green=_g;
    _LEDs[i].blue=_b;
    if(_turnLEDsOff == false)
          _LEDs[i].brightness=_brightness;
        else
          _LEDs[i].brightness=0;
    ShowLEDsArray();
    delay(ms);
  }
}
