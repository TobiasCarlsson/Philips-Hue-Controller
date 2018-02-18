#include <Arduino.h>
#include "config.h"
#include <ESP8266WiFi.h>


int dimPin = A0; // Pin for the dimmer
int buttonPin = D3; // Pin for the on/off button
int dim;
int button;
int prevDim;
int buttonState;

void Hue_Off(){


    Serial.println("Turning light off");
    WiFiClient client; // Connection to Philips hue bridge

    String state = ("{\"on\":false}"); // Turns off the light


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
  Serial.println("Turning light on");
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

    delay(100);

  }
  client.stop();
}

void Hue_Dimmer(int dim) {
  Serial.println("Diming");
  WiFiClient client; // Connection to Philips hue bridge

  String state = ("{\"on\":true,\"bri\":"+ String(dim) +"}"); // Sets the brightness for the light
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

    delay(100);

  }
  client.stop();
}

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


// Main loop
void loop() {

  button = digitalRead(buttonPin);
  if (button == 0){ // Looks for if the button is pressed/connected to ground
    buttonState = buttonState + 1;
    if (buttonState%2 == 0){
      Hue_Off();
      delay(100);
    }
    else{
      Hue_On();
      delay(100);
    }
    }

    dim = analogRead(dimPin); // Reding the dimPin
    dim = map(dim, 0, 1023, 0, 255); // Maping the analog value 10 bit value to 8 bit value for the pwm

    if(prevDim+10 < dim || prevDim-10 > dim){ // Lokking what the previues value was and compars it to the newer value is
      Hue_Dimmer(dim);
      prevDim = dim;

    }
    delay(100);

}
