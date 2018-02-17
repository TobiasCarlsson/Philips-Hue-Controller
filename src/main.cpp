#include <Arduino.h>
#include "config.h"
#include <ESP8266WiFi.h>


int dimPin = A0; // Pin for the dimmer
int buttonPin = D3; // Pin for the on/off button
int dim;
int button;


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
}

void loop() {

}

void Hue_Off(){


    Serial.println("Connecting to hue bridge");
    WiFiClient client; // Connection to Philips hue bridge

    String state = ("{\"on\":false}"); // What command to send to the hue bridge


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
}

void Hue_On() {
  Serial.println("Connecting to hue bridge");
  WiFiClient client; // Connection to Philips hue bridge

  String state = ("{\"on\":true}"); // What command to send to the hue bridge


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

}

void Hue_Dimmer(uint16_t dim) {

}
