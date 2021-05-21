#include <Arduino.h>
#include "WiFi.h"

#include "DropboxManager.h"

#define WIFI_SSID "YOUR_SSID"
#define WIFI_PASSWORD "YOUR_PASSWORD"

#define FILENAME "/test_file.txt"
#define DROPBOX_PATH "/name_dropbox.txt"

#define TOKEN "YOUR_TOKEN"

// instance of DropboxMAnager
DropboxManager db;

void setup(){
    Serial.begin(9600);
    
    // Initialize wifi and wait for conection
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    
    while(WiFi.status() != WL_CONNECTED){
        Serial.print(".");    
        delay(500);
    }
   
   // Initialize dropbox manager with token
    db.begin(TOKEN);
    
    // Upload file in dropboc
    if(db.upload(FILENAME, DROPBOX_PATH))
        Serial.println("Sucessfull upload");
}

void loop(){

}