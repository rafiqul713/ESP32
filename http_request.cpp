#include<string>
#include "WiFi.h"
#include "HTTPClient.h"
#define PIN=13; //GPIO 13


const char* SSID = "here give your wifi ssid";
const char* pass =  "your wifi password";
const char* dev_ID="1234"
string url="http://your_url"; 
int status=0;
HTTPClient http;


//Interrupt handler 
//In this case, it sends http request
void ISR_handler() {

  //Device id and status is passed through the url
  //Here status is considered static value. 
  //But It depends on other factor. For example: battery is low. In that case status
  // may be change from 1 to 0  
  string update_msg=url+"?device_ID="+dev_ID+"&status="+to_string(status);
  http.begin(update_msg.c_str());
  int httpResponse = http.GET(); //http get request
  //Check response
  if(httpResponse>0){
    Serial.println(httpResponseCode);
    String data = http.getString();
    Serial.println(data);
  }
  
  else {
    Serial.print("Error.....!");
    Serial.println(httpResponseCode);
  }
  
  http.end();

}


void setup() {
  Serial.begin(115200);
  WiFi.begin(SSID, pass);
  while (WiFi.status() != WL_CONNECTED) { 
  delay(5000); 
  Serial.println("Connected to the wifi");
  //Attached interrupt handler. if pin change is occured ISR_handler function is called
  attachInterrupt(digitalPinToInterrupt(PIN), ISR_handler, CHANGE);
 }
   
}

void pin_change(){

    //PIN chaning is happened here. 
    // based on input or may be based on other events 
   // PIN status is changed HIGH to LOW or LOW to HIGH

}

void loop() {
  
  pin_change();  

}
