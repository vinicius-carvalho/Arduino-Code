#include <SoftwareSerial.h>
#include <TinyGPS.h>
 
float slat,slon; // Criando variaveis para Latitude e Longitude 
SoftwareSerial gpsSerial(8, 9); // Cria uma conexão com GPS
TinyGPS gps; // Cria um objeto para tratar os dados do GPS
 
void setup(){
  Serial.begin(9600); // Conecta a porta serial
  gpsSerial.begin(4800); // Conecta o GPS
}
 
void loop(){
  
  while(gpsSerial.available()){ // Verifica se existe dado doGPS
       if(gps.encode(gpsSerial.read())){ //  Codifica o dado
              unsigned long age;
             gps.f_get_position(&slat,&slon,&age); // Encontra a latitude e longitude
             
//Mostra a informação no Serial monitor
      Serial.println("Posição: ");
     Serial.print(slat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : slat, 6); Serial.print("  ");
    Serial.print(slon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : slon, 6);
   Serial.println(""); 
   }
  }
}
