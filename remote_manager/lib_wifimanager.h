#include <Ticker.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
//#include <WiFiClient.h>
#include <strings_en.h>
#include <WiFiManager.h>

#define indicador_wifi D0

Ticker ticker; // instancia que nos ayuda a saber si se conecto o no

//creo una funcion para que parpadee un led

void parpadeoLedwifi(){
  // cambiar el estado del led
  byte estado= digitalRead(indicador_wifi);
  //cambio el estado del led
  digitalWrite(indicador_wifi, !estado);
  }


void lib_conexionWifi(){

  Serial.begin(115200);

  pinMode(indicador_wifi, OUTPUT);

  //empezamos el parpadep
  ticker.attach(0.2, parpadeoLedwifi);

  //creo una instancia de wifimanager
  WiFiManager wifimanager;

  //reset de cualquier configuracion anterior
  //wifimanager.resetSettings();

  // creamos AP y portal cautivo guarda las contraseñas donde se conecto alguna dia
  //verificamos si la conexion se establecio
  
  if (!wifimanager.autoConnect("ESP8266Mario")){
    Serial.println("fallo la conexion");
    ESP.reset();
    delay(1000);
    }

  Serial.println("ya estas conectado");

  //eliminamos el temporizador o el parpadeo
  ticker.detach();

  //apagamos el led por si acaso quedo prendido
  digitalWrite(indicador_wifi, 1);

  
  }
