#include <WiFi.h>
#include "FirebaseESP32.h"

#define FIREBASE_HOST "HOST" //Do not include https:// in FIREBASE_HOST
#define FIREBASE_AUTH "Secret"
#define WIFI_SSID "User_NAME"
#define WIFI_PASSWORD "password"

FirebaseData firebaseData;
int LED = 16;

void setup() {
 Serial.begin(115200);
 WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
 Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }

 Serial.println();
 Serial.print("Connected with IP: ");
 Serial.println(WiFi.localIP());
 Serial.println();

 Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
 Firebase.reconnectWiFi(true);
 Firebase.setReadTimeout(firebaseData, 1000 * 60);
 Firebase.setwriteSizeLimit(firebaseData, "tiny");
 pinMode(LED,OUTPUT);
}

 

void loop() {
  if(Firebase.getString(firebaseData,"/LED/status/status")){
  Serial.println(firebaseData.stringData());
  }
  if(firebaseData.stringData()=="ON"){
    digitalWrite(LED,HIGH);
  }
  else if(firebaseData.stringData()=="OFF"){
    digitalWrite(LED,LOW);
  }
}
