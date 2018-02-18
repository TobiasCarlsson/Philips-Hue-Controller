#include <Arduino.h>
#include "config.h"
#include <ESP8266WiFi.h>


int dimPin = A0; // Pin for the dimmer
int buttonPin = D3; // Pin for the on/off button
int dim;
int button;
int prevDim;

void Hue_Off(){


    //Serial.println("Connecting to hue bridge");
    WiFiClient client; // Connection to Philips hue bridge

    String state = ("{\"on\":false}"); // Turns of the light


    if(client.connect(HUE_IP, PORT)){


      client.print("PUT /api/" + String(HUE_USER_ID) + "/lights/" + String(LIGHT) + "/state");
      client.print(" HTTP/1.1");
      client.println("Cache-Control: no-cache");
      client.println("Content-Type: application/json");
      client.print("Content-Length: ");
      client.println(state.length());
      client.println();
      client.print(state);

    }
    client.stop();
}

void Hue_On() {
  //Serial.println("Connecting to hue bridge");
  WiFiClient client; // Connection to Philips hue bridge

  String state = ("{\"on\":true}"); // Turns on the ligth


  if(client.connect(HUE_IP, PORT)){


    client.print("PUT /api/" + String(HUE_USER_ID) + "/lights/" + String(LIGHT) + "/state");
    client.print(" HTTP/1.1");
    client.println("Cache-Control: no-cache");
    client.println("Content-Type: application/json");
    client.print("Content-Length: ");
    client.println(state.length());
    client.println();
    client.print(state);

  }
  client.stop();
}

void Hue_Dimmer(int dim) {
  Serial.println("Connecting to hue bridge");
  WiFiClient client; // Connection to Philips hue bridge

  String state = ("{\"on\":true,\"bri\":"+ String(dim) +"}"); // Turns on the ligth
  //Serial.println(state);


  if(client.connect(HUE_IP, PORT)){


    client.print("PUT /api/" + String(HUE_USER_ID) + "/lights/" + String(LIGHT) + "/state");
    client.print(" HTTP/1.1");
    client.println("Cache-Control: no-cache");
    client.println("Content-Type: application/json");
    client.print("Content-Length: ");
    client.println(state.length());
    client.println();
    client.print(state);

  }
  client.stop();
}

/*void on_off() {
  Hue_Off();
  return;
}*/


void setup(){

  Serial.begin(115200);
  pinMode(dimPin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFIF_PASS);

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected!");

  // attachInterrupt(digitalPinToInterrupt(buttonPin), on_off, CHANGE);


}


// Main loop
void loop() {

  button = digitalRead(buttonPin);
  if (button == 0){
    Hue_Off();
    }

    dim = analogRead(dimPin);
    dim = map(dim, 0, 1023, 0, 255);

    if(prevDim+20 < dim || prevDim-20 > dim){
      Hue_Dimmer(dim);
    }
    prevDim = dim;

}
