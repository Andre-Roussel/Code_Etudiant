/*
  Titre      : Démonstration DHT22
  Auteur     : André Roussel
  Date       : 14/04/2022
  Description: Démonstration de l'utilisation d'un capteur DHT22 ainsi qu'une méthode de rebrachement au WIFI en cas de perte de signal
  Droits     : Reproduction permise pour usage pédagogique
  Version    : 0.0.1
*/



#include <Arduino.h>

// DHT Temperature & Humidity Sensor
// Unified Sensor Library Example
// Written by Tony DiCola for Adafruit Industries
// Released under an MIT license.

// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor


//Libraire DHT22 emprunté de Tony DiCola
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>


//Librairire de branchement WIFI et MQTT
#include "WIFI_NINA_Connector.h"
#include "MQTTConnector.h"

#define DHTPIN 2     // Digital pin connected to the DHT sensor 
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

#define DHTTYPE    DHT22     // DHT 22 (AM2302)


DHT_Unified dht(DHTPIN, DHTTYPE); //Création d'une objet de type DHT


//Définition des variables pour l'utilisation de la fonction millis()
unsigned long LastMillis=0;
unsigned long PresentMillis =0;
uint32_t delayMS = 60000;  //délais de 1 minutes pour la capture de données


/*
  Changement important

  La variable reconnected permet de capturé le nombre de fois que le uC a été obligé de se 
  rebranché au WIFI du a une changement de canal ou perte de signal

*/

unsigned long reconnected =0;


void setup() {
  Serial.begin(9600);
  wifiConnect();                            //  Branchement au réseau WIFI
  MQTTConnect();                            //  Branchement au broker MQTT

  dht.begin();                              //  Mise en fonction de l'objet dht
  sensor_t sensor;                          //  Définition d'un capteur pour l'acquisition des données
  dht.temperature().getSensor(&sensor);     //  Capture des capteurs
  
}

void loop() {

  //Voici un autre changement...  ClientWIFI.connected() retourne TRUE si le signal est correct, FALSE sinon
  if(ClientWIFI.connected() && ClientMQTT.connected())
  {
  
    ClientMQTT.loop(); 

    PresentMillis=millis();
    
    if(PresentMillis-LastMillis > delayMS)
    {
      LastMillis=PresentMillis;
      sensors_event_t event;
      dht.temperature().getEvent(&event);
      if (isnan(event.temperature)) {
        Serial.println(F("Error reading temperature!"));
      }
      else {
        appendPayload("Temperature", event.temperature);  //Ajout de la donnée humidité au message MQTT
      }
      
      dht.humidity().getEvent(&event);
      if (isnan(event.relative_humidity)) {
        Serial.println(F("Error reading humidity!"));
      }
      else {
        appendPayload("Humidity", event.relative_humidity);  //Ajout de la donnée humidité au message MQTT
      }
      //Ajout de la valeur reconnected a la chaine MQTT de facon a suivre le nombre de rebranchement
      appendPayload("Reconnected", reconnected);
      sendPayload();  
    }
  }

  else //Si et seulement si ClientWIFI.connected() == False ou ClientMQTT.connected() == False
    {

        status=WL_IDLE_STATUS;
        WiFi.end();
        wifiConnect();
        MQTTConnect();
        reconnected++;  //  Incrémente la valeur
    }
}