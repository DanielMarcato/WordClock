 const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>WordClock</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="icon" href="data:,">
  <style>
    html {font-family: Arial; display: inline-block; text-align: center;}
    h2 {font-size: 3.0rem; margin-bottom: 0px;}
    p {font-size: 2.0rem;}
    h3 {margin:0; padding:0;}
    h4 {margin-bottom: 10px; padding:0;}
    body {max-width: 600px; margin:0px auto; padding-bottom: 25px; color: #FFFFFF; background-color: black}
    .switch {position: relative; display: inline-block; width: 120px; height: 68px} 
    .switch input {display: none}
    .slider {position: relative; display: inline-block; width: 240px; height: 34px} 
    .switchslider {position: absolute; top: 0; left: 0; right: 0; bottom: 0; background-color: #ccc; border-radius: 6px}
    .switchslider:before {position: absolute; content: ""; height: 52px; width: 52px; left: 8px; bottom: 8px; background-color: #fff; -webkit-transition: .4s; transition: .4s; border-radius: 3px}
    input:checked+.switchslider {background-color: #b30000}
    input:checked+.switchslider:before {-webkit-transform: translateX(52px); -ms-transform: translateX(52px); transform: translateX(52px)}
  </style>
</head>
<body onload="startTime()">
  <h2>Word<span id="clockWord">Clock</span></h2>
  <h3>by %CREATORPLACEHOLDER%</h3>
  <p id="clock">testclock</p>
  %SLIDERPLACEHOLDER%
  %PICKERPLACEHOLDER%
  %BUTTONPLACEHOLDER%
<script>
function toggleCheckbox(element) {
  var xhr = new XMLHttpRequest();
  if(element.checked){ 
    xhr.open("GET", "/LEDoff", true);
  }
  else { 
    xhr.open("GET", "/LEDon", true);
  }
  xhr.send();
}
function startTime() {
  const today = new Date();
  let h = today.getHours();
  let m = today.getMinutes();
  let s = today.getSeconds();
  m = checkTime(m);
  s = checkTime(s);
  document.getElementById('clock').innerHTML =  h + ":" + m + ":" + s;
  document.getElementById("clockWord").style.color = picker.value;
  setTimeout(startTime, 1000);
}
function checkTime(i) {
  if (i < 10) {i = "0" + i};  // add zero in front of numbers < 10
  return i;
}
function sendColor(element){
  var xhr = new XMLHttpRequest();
  var colorcode = element.value.replace("#", "");
  xhr.open("GET", "/update?color=" + colorcode, true);
  xhr.send();
  document.getElementById("clockWord").style.color = picker.value;
}

function sendBrightness(element){
  var xhr = new XMLHttpRequest();
  xhr.open("GET", "/update?brightness=" + slider.value, true);
  xhr.send();
  offButton.checked = false;
}

picker.addEventListener('input', function() {
  sendColor(picker);
});

slider.addEventListener('input', function() {
  sendBrightness(slider);
});
</script>
</body>
</html>
)rawliteral";

// Replaces placeholder with button section in your web page
String processor(const String& var){
  //Serial.println(var);
  if(var == "BUTTONPLACEHOLDER"){
    String buttons = "";
    buttons += "<h4>Turn LEDs off</h4>";
    buttons += "<label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"offButton\" " + checkedFromBrightness(_brightness) + "><span class=\"switchslider\"></span></label>";
    return buttons;
  }
  if(var == "PICKERPLACEHOLDER"){
    String picker = "";
    picker += "<h4>Change Color</h4>";
    picker += "<input class=\"switch\" type=\"color\" onchange=\"sendColor(this)\" id=\"picker\" name=\"picker\" value=\"#"+ HexColorFromRGB(_r, _g, _b) +"\" style=\"background-color: #ccc;border-radius:6px\">";
    return picker;
  }
  if(var == "SLIDERPLACEHOLDER"){
    String slider = "";
    slider += "<h4>Change Brightness</h4>";
    slider += "<input class=\"slider\" id=\"slider\" name=\"slider\" type=\"range\" min=\"1\" max=\"10\" step=\"1\" value=\"" + String(_brightness) + "\">";
    return slider;
  }
  if(var == "CREATORPLACEHOLDER"){
    return _creator;
  }
  return String();
}

String HexColorFromRGB(int r, int g, int b){
  char hex[7] = {0};
  sprintf(hex,"%02X%02X%02X",r,g,b); //convert to an hexadecimal string. Lookup sprintf for what %02X means.
  Serial.println(hex); //Print the string.
  return hex;
}

String checkedFromBrightness(int brightness){
  if(brightness == 0){
    return "checked";
  }
  else {
    return "";
  }
}
