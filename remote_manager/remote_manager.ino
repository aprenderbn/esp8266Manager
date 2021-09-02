//DESARROLLADOR MARIO ALBERTO BEGAMBRE GOMEZ

#include <ArduinoJson.h>

#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include "lib_wifimanager.h"

#define prueba D4 //led de placa azul
#define pin_in1 D1
#define led D0 //led de placa rojo

//String url = "https://conelecap.com.co/tesis/pages/webservice/sincronizacion.php";

int pin = 1;
int estado = 0;
int logica = 100; //variable que me sirve para poder controlar el envio (metodo1()) de la informacion en el void loop
int consultar = 0;

String protocolo="http://";
String host = "192.168.1.7";
String resourse = "/api_remote_manager/php/consulta.php";
int puerto = 80;

String url = protocolo + host + resourse;
//String url2 = "http://192.168.1.7/api_remote_manager/php/consulta.php";
void setup() {

  lib_conexionWifi();
  pinMode(prueba,OUTPUT);
  pinMode(pin_in1,INPUT);
  pinMode(led,OUTPUT);
  
}

void loop() {
  verifica();

  int valor1 = digitalRead(pin_in1); //verifico el estado de el pin 1
  
  if(valor1 == 1 && logica == 1){ //aqui miro el ultimo estado y doy la ccion y si el estado estaba en alto lo cambia a bajo. valor1 actua siempre que mande un 1 logico en ambos casos
   
    digitalWrite(led,1);
    digitalWrite(prueba,1);
    pin = 1;
    estado= 0;
    metodo1();
    Serial.println(valor1);
  }else if(valor1 == 1 && logica == 0){ //aqui miro el ultimo estado y doy la accion y si el estado estaba en bajo lo cambia a alto. valor1 actua siempre que mande un 1 logico en ambos casos
    
    digitalWrite(led,0);
    pin = 1;
    estado= 1;
    metodo1();
    Serial.println(valor1);
  }
  //metodo1();
 /* WiFiClient client;
   char buf [100];
   snprintf(buf, sizeof(buf),"[{\"procedimiento\":%d, \"valores\"{ \"1\":%d, \"2\":%d, \"3\":%d}}]","procedimiento","1","1","0"); 
   //String postData="?procedimiento="+ procedimiento + "&1=" + String(primero) + "&2=" + String(segundo) + "&3=" + String(tercero);
   //String postData="{procedimiento:WS_RECIBE,valores:{1:1,2:1,3:1}}";

  if(!client.connect(host, puerto)){
    Serial.println("fallo al conectar");
    client.stop();
    return;
  }

  client.print(String("POST")+ url + "HTTP/1.0\r\n" +
          "Host:" + host + "\r\n" +
          "Accept: *" + "/" + "*\r\n" +
           "\r\n" +
          "Content-Type: application/x-www-form-urlencoded\r\n"+
          "\r\n" + buf);

  Serial.println(buf); //("procedimiento="+ procedimiento + "&1=" + String(primero) + "&2=" + String(segundo) + "&3=" + String(tercero));  
  Serial.println("***********datos enviados**********");

  /*int nl= 0;
  int codigo = -1;
  String respuesta = "";     

  while (client.connected()){
    if(client.available()){
      String line= client.readStringUntil('\n');
      Serial.println(line);         
    }
  }
 Serial.println("********fin******");
 client.stop();*/
}

void verifica(){
  WiFiClient cliente; 
  HTTPClient http; // declaro un objeto HTTPCLIENTE
  http.begin(cliente,url);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded"); //si o si esto hay que ponerlo tal cual

  //String postData= "pin = 1";
  String postData= "pin=" + String(pin) + "&opcion= 1" ;
 

  int httcode = http.POST(postData); //envio la peticion
  String respuesta = http.getString(); //recupero la respuesta del servidor

  Serial.println(httcode);
  Serial.println(respuesta);

  //verificamos en que estado esta el dispositivo
  if(respuesta == "0"){
      digitalWrite(prueba,1);
      logica=0;
      //consultar = 1;
      digitalWrite(prueba,1);
    }else if(respuesta == "1"){
      digitalWrite(prueba,0);
      logica=1;
      //consultar = 0;
      digitalWrite(led,0);
    }else{
      //este problema de que cuando se apague el servidor se prenda todo o se apaga todo hay que corregirlo ojo
      digitalWrite(prueba,1);
      digitalWrite(prueba,1);
    }
    
  http.end(); //cerramos la coneccion
  delay(1000);
}

//el metodo para la actualizacion del pin 1
void metodo1(){
  WiFiClient cliente; 
  HTTPClient http; // declaro un objeto HTTPCLIENTE
  http.begin(cliente,url);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded"); //si o si esto hay que ponerlo tal cual

  String postData= "pin=" + String(pin) + "&estado=" + String(estado) + "&opcion= 2&nombre=ventilador";

  int httcode = http.POST(postData); //almacena el valor que nos regresa en tipo entero
  String respuesta = http.getString(); //postData;

  Serial.println(httcode);
  Serial.println(respuesta);
  

  delay(1000);
  http.end(); //cerramos la conexion
  
  
  }
