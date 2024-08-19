//K1 blue LED=2 is blink --esp32-WROOM-DA-Module

/*************************************************************
  Blynk is a platform with iOS and Android apps to control
  ESP32, Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build mobile and web interfaces for any
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: https://www.blynk.io
    Sketch generator:           https://examples.blynk.cc
    Blynk community:            https://community.blynk.cc
    Follow us:                  https://www.fb.com/blynkapp
                                https://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example runs directly on ESP32 chip.

  NOTE: This requires ESP32 support package:
    https://github.com/espressif/arduino-esp32

  Please be sure to select the right ESP32 module
  in the Tools -> Board menu!

  Change WiFi ssid, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

/* Fill in information from Blynk Device Info here */
//#define BLYNK_TEMPLATE_ID           "TMPxxxxxx"
//#define BLYNK_TEMPLATE_NAME         "Device"
//#define BLYNK_AUTH_TOKEN            "YourAuthToken"

#define BLYNK_TEMPLATE_ID "TMPL_5Ml_CqT"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "sEIvE27Pw33C1sTZIoXOlNYOvNdAoKYd"


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <TimeLib.h>
#include <WidgetRTC.h>
#include <DHT.h>     //include DHT11 sensor library

// DHT Settings
#define DHTPIN 15         //D6 what digital pin we're connected to. If you are not using NodeMCU change D6 to real pin
#define DHTTYPE DHT11     // DHT 11
#define ledPin 4       //2 LED pin (GPIO2 - D4)

//void sendSensor();
//void clockDisplay(void);

const boolean IS_METRIC = true;
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "D-Link2570U";
char pass[] = "@k1_83727147k1";

// Initialize the temperat/ure/ humidity sensor
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
WidgetLED led0(V1);  //V0  //virtual pin 0 to control led display
WidgetRTC rtc;
//WidgetMap myMap(V6);  //virtual pin 6 for the device location

///////////////////////////////// Variable
int tempThresholds = 20;  // threshold temperature to trigger an email notification
boolean notification = true;
int counter =0;

//////////////////////////////////
void SendSensor()
{
  Serial.println("*****start*******");
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, t);  //V2
  Blynk.virtualWrite(V7, h);  //V3
  Serial.print("Current Temperature: " + String(t) + " °C, ");
  Serial.print("  Current Humidity: " + String(h) + " %");
  Serial.println("");
  /*
  if ((t > tempThresholds)&&(notification))
   {
     //Blynk.email("keivank1jan@yahoo.com", "Subject: Button Logger", "You just pushed the button..."); 
    // If you want to use the email specified in the App (like for App Export):
    Blynk.email("Subject: Warm to Hot weather - Alert", "Current temperature is "+String(t)+" °C");
    Blynk.tweet("Temperature is "+String(t)+" °C, "+"Humidity is "+String(h)+" %");
    notification = false;
    counter += 1;
  }
  else if (t <= tempThresholds) {
    notification = true;
    counter = 0;
  }
  else {
    if (counter > 99) {
      notification = true;
      counter = 0;
    }
    else
      counter += 1;  
  }
  */
}

////////////////////////////// Setup
void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  rtc.begin();
   //myMap.clear();
  //Device location - Sydney coordinate
  //int index = 1;
  //float lat = -33.772156;
  //float lon = 151.053815;
  //myMap.location(index, lat, lon, "IoT-DHT11");
  // Setup a function to check the sensor every 10 seconds
  timer.setInterval(1000L, SendSensor );  //10000L
  // Display digital clock every 10 seconds
  //timer.setInterval(10000L, clockDisplay);
   //SendSensor();

}

void loop()
{
  Blynk.run();
  timer.run();      // Initiates BlynkTimer
  //SendSensor();
}

//////////////////////////////////////////////////////////////////////
// This function will be called every time Button Widget at V1
// in Blynk app writes values to the Virtual Pin V1
BLYNK_WRITE(V1)
{
  int virtualPin1 = param.asInt(); // assigning incoming value from pin V0 to a variable
  // process received value
  if (virtualPin1 == 1){
    digitalWrite(ledPin, HIGH);
    led0.on();
  }
  else {
    digitalWrite(ledPin, LOW);
    led0.off();
  }
}
///////////////////////////
// Digital clock display of the time
/*
void clockDisplay()
{
  // You can call hour(), minute(), ... at any time
  // Please see Time library examples for details

  String currentTime = String(hour()) + ":" + minute() + ":" + second();
  String currentDate = String(day()) + " " + month() + " " + year();
  Serial.print("Current time: ");
  Serial.print(currentTime);
  Serial.print(" ");
  Serial.print(currentDate);
  Serial.println();

  // Send time to the App
  Blynk.virtualWrite(V4, currentTime);
  // Send date to the App
  Blynk.virtualWrite(V5, currentDate);
  //Device location - Sydney CBD coordinate
  //Get the latitude and longitude reading from Google Map)
  int index = 1;
  float lat = -33.8618;
  float lon = 151.2109;
  // Enter your IoT device name "**********"
  myMap.location(index, lat, lon, "**********");
}
*/
////////////////////////////////////////////////////