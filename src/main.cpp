#include <ESP8266WiFi.h>       //Librari ESP8266
#include <FirebaseArduino.h>   // Librari Arduino
#include <ESP8266HTTPClient.h> //Librari ESP8266 Sebagai Wifi Client
#include <DNSServer.h>         // Server DNS bagi ESP8266
#include <ESP8266WebServer.h>  // Web Server Saat ESP8266 sebagai AP
#include <WiFiManager.h>       // Manager AP ESP8266

//Autentikasi Firebase
#define FIREBASE_HOST "raw-esp12e.firebaseio.com"
#define FIREBASE_AUTH "kRwTxpSFQFA9SvU33gBW79vi6rRZMnJdpKpavvRh"

// Deklarasi Variabel
const int sensorMin = 0;    // sensor minimum
const int sensorMax = 1024; // sensor maximum
String myString;            // Kondisi Sensor

void setup()
{

  //Setting bagi Wifi menggunakan librari WifiManager
  Serial.begin(9600);
  Serial.println("\n Starting");
  WiFiManager wifiManager;
  wifiManager.resetSettings();
  wifiManager.setBreakAfterConfig(true);

  if (!wifiManager.autoConnect("RainSensor"))
  {
    Serial.println("Gagal Terkoneksi, akan dicoba dihubungkan kembali");
    delay(3000);
    ESP.reset();
    delay(5000);
  }
  Serial.println("Terkoneksi :)");

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); // Autentikasi Firebase
}
void loop()
{
  //Membaca masukan analog sensor
  int sensorReading = analogRead(A0);
  // Membuat map pembacaan sensor

  // Create dan Update data pada Firebase
  int range = map(sensorReading, sensorMin, sensorMax, 0, 3);

  // Kondisi Sensor
  if (range == 0)
  {
    myString = "HUJAN";
  }
  else if (range == 3)
  {
    myString = "CERAH";
  }
  else
  {
    myString = "LEMBAB";
  };

  Firebase.setString("Cuaca", myString);
  Serial.println(myString);

  delay(500); //Delay setiap transfer kondisi
}
