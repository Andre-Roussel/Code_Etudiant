/*

Important - Add to git ignore

*/

/*
SSID du WIFI ainsi que le mot de passe
Modifier les paramètre WIFI pour le réseau auquels votre objets doit se brancher
*/


// Uncoment to use home network
/*
    #define WIFI_SECRET_SSID "LeCamping"
    #define WIFI_SECRET_USER ""
    #define WIFI_SECRET_PASS "Summer2019"
*/

//  Uncoment to use IDO open network
/*
    #define WIFI_SECRET_SSID "IOT_OBJECTS"
    #define WIFI_SECRET_USER ""
    #define WIFI_SECRET_PASS "42Bidules!"
*/

//  Uncoment to test other wifi  networks
/*
    #define WIFI_SECRET_SSID "CCNB-IOT-WRLS"
    #define WIFI_SECRET_USER ""
    #define WIFI_SECRET_PASS "iotwifi2020"

*/

//  Uncoment to use CCNB WPA2 Enterprise network
  
    #define WIFI_SECRET_SSID "CCNB-IOT-WRLS"
    #define WIFI_SECRET_USER "ba-ido-01"
    #define WIFI_SECRET_PASS "iotwifi2020"

/*
Information nécessaire pour le branchement a un Broker MQTT
Dans le cadre du cours AIIA1013, ne modifié pas cet information
*/

#define SECRET_MQTT_SERVER_IP "198.164.130.74"
#define SECRET_MQTT_SERVER_PORT 1883

/*
Détails sur l'indentification de l'objet
Cette information provient de l'objet virtuel créer sur le serveur Thingsbord
*/

#define SECRET_TOKEN  "ftM84kfIUO5kz2Bfq5GH"
#define SECRET_DEVICE_ID "13599980-8f1f-11ec-9235-d318ce92df6e"



