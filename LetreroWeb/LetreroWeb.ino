#include <WiFiManager.h> 
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "Index.h"
ESP8266WebServer server(80);
WiFiManager wifiManager;

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

String horaActual = "";
bool cadenaEstaticaMostrada = false;
const int pinCS = 15;
const int numberOfHorizontalDisplays = 8;
const int numberOfVerticalDisplays = 1;
const long utcOffsetInSeconds = 3600;

Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);


 
const int spacer = 1;
const int width = 5 + spacer; // Ancho de la fuente a 5 pixeles

unsigned long t = millis();
unsigned long t2 = millis();
unsigned long tesp = millis();
unsigned long tRefReloj = millis();
unsigned long TiempoTotalEncendido = 10000;
unsigned long TiempoTotalEspera = 0;
bool ModoIP = false;
bool ModoTiempo = true;
bool ModoTiempoBoton = true;
bool HoraCompleta = false;
bool YaEsperado = false;
bool ScrollText = true;
char daysOfTheWeek[7][12] = {"Domingo", "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado"};

//----------------------Variables estado Letrero--------------------------------------

//Duracion del Mensaje Si
int hMens = 0, mMens = 0, sMens = 10;
//Escribir Mensaje Si
String message = "";
//Velocidad Scroll Si
int wait = 25; 
//Intensidad Si
int Intensidad = 1;
//Tiempo de Espera Si
int hTEspera = 0, mTEspera = 0, sTEspera = 0;
//Mostrar / Ocultar Hora Si
bool MostrarHoraEspera = true;
//HoraScroll Si
bool HoraScroll = false;
//Scroll Texto Si
bool ScrollTexto = true;

//------------------------------------------------------------------------------------
// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

#include "arduino_secret.h"

void setup(){
  matrix.setIntensity(Intensidad); // Ajustar el brillo entre 0 y 15
  
  matrix.setPosition(0, 7, 0); // El primer display esta en <0, 0>
  matrix.setPosition(1, 6, 0); // El segundo display esta en <1, 0>
  matrix.setPosition(2, 5, 0); // El tercer display esta en <2, 0>
  matrix.setPosition(3, 4, 0); // El cuarto display esta en <3, 0>
  
  matrix.setPosition(4, 3, 0); // El primer display esta en <0, 0>
  matrix.setPosition(5, 2, 0); // El segundo display esta en <1, 0>
  matrix.setPosition(6, 1, 0); // El tercer display esta en <2, 0>
  matrix.setPosition(7, 0, 0); // El cuarto display esta en <3, 0>
  
  matrix.setRotation(0, 3);    // Posición del display
  matrix.setRotation(1, 3);    // Posición del display
  matrix.setRotation(2, 3);    // Posición del display
  matrix.setRotation(3, 3);    // Posición del display
  
  matrix.setRotation(4, 3);    // Posición del display
  matrix.setRotation(5, 3);    // Posición del display
  matrix.setRotation(6, 3);    // Posición del display
  matrix.setRotation(7, 3);    // Posición del display
  
  matrix.fillScreen(LOW);
  
  matrix.write();
  // wifiManager.resetSettings(); //Para resetear los valores de conexión WiFi
  wifiManager.autoConnect("Letrero_Web");
  message = "";
  Serial.begin(115200);
  Serial.println("");
  Serial.println("HTTP server started");
  Serial.println(WiFi.localIP());
  server.on("/", handleRoot);
  server.on("/Intensidad", ChangeIntensity); //Associate the handler function to the path
  server.on("/Tiempo", ChangeTime); //Associate the handler function to the path
  server.on("/Velocidad", ChangeSpeed); //Associate the handler function to the path
  server.on("/Escribir", CapturarTexto);   //Associate the handler function to the path
  server.on("/TiempoEspera", ChangeWaitTime);   //Associate the handler function to the path
  server.on("/MostrarHora", CambiarMostrarHora);   //Associate the handler function to the path
  server.on("/CambioTipoHora", CambiarTipoHora);   //Associate the handler function to the path
  server.on("/CambioScrollTexto", CambioScrollTexto);   //Associate the handler function to the path
  server.begin();
  timeClient.begin();
  t = millis();
  t2 = millis();
  tesp = millis();
  tRefReloj = millis();
}

void loop(){
  t2 = millis();
  server.handleClient();
  if(ModoIP){
    MostrarTexto(WiFi.localIP().toString());
  }
  else{
    if(YaEsperado){
      if(t2 > (t + TiempoTotalEncendido)){
        t = millis();
        message = "";
        horaActual = "";
      }
      if(message != "" && ScrollText)
        MostrarTexto(message);
      else if(!ScrollText && message != ""){
        if(!cadenaEstaticaMostrada){
          cadenaEstaticaMostrada = true;
          MostrarTextoEstatico(message);
        }
      }
      else if(!ModoTiempoBoton){
        matrix.fillScreen(LOW);
        matrix.write();
      }
    }
    else{
      if(t2 > (tesp + TiempoTotalEspera)){
        tesp = millis();
        YaEsperado = true;
        t = millis();
      }
      if(ModoTiempoBoton && HoraCompleta){
        MostrarHoraScroll();
      }
      else if(ModoTiempoBoton){
        MostrarHora();
      }
    }

    
    if(ModoTiempoBoton && HoraCompleta && message == ""){
      MostrarHoraScroll();
    }
    else if(ModoTiempoBoton && message == ""){
      MostrarHora();
    }
  }
}
