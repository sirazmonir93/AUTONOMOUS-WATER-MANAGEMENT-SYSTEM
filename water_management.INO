#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Arduino_JSON.h>
// GSM Module RX pin to Arduino 2
// GSM Module TX pin to Arduino 3
#define rxPin D5
#define txPin D0
const char* ssid = "ESP";
const char* password = "passpass1";
String openWeatherMapApiKey = "a95f7cec1f0a9fbf07dd3696b2222bb9";
SoftwareSerial sim800(txPin, rxPin);
String city = "Tongi";
String countryCode = "BD";
unsigned long lastTime = 0;
unsigned long timerDelay = 10000; // Timer delay set to 10 seconds
String jsonBuffer;
// Median filtering algorithm
// TDS sensor pin
#define tdsSensorPin A0
// Relay control pin
#define relayPin D7
bool already_sent = false;
int pos = HIGH;
int counter = 1;
// Ultrasonic sensor pins
int trigPin = D4; // TRIG pin
int echoPin = D8; // ECHO pin
float duration_us, distance_mm;
int cloudint;
int humm;
int tmp;
int wndspd;
int chap;
int feelslike;
int visib;
// I2C address for the LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup() {
Serial.begin(9600); // Initialize serial communication
sim800.begin(9600); // Initialize GSM module
Serial.println("GSM module initialized");
// Ultrasonic sensor setup
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
// Relay setup
pinMode(relayPin, OUTPUT);
pinMode(D6, INPUT);
// LCD setup
lcd.begin();
lcd.backlight();
delay(1000);
sim800.println("AT"); // Check if GSM module is ready
updateSerial();
// Connect to WiFi
WiFi.begin(ssid, password);
Serial.println("Connecting");
// Wait until the connection is established
while(WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
// Print the IP address of the board
Serial.println("");
Serial.print("Connected to WiFi network with IP Address: ");
Serial.println(WiFi.localIP());
// Print the timer interval
Serial.println("Timer set to 10 seconds (timerDelay variable), it will
take 10 seconds before publishing the first reading.");
}
void loop() {
// Send an HTTP GET request at the specified timer interval
if ((millis() - lastTime) > timerDelay) {
// Check WiFi connection status
if(WiFi.status()== WL_CONNECTED){
// Construct the URL for the OpenWeatherMap API
String serverPath =
"http://api.openweathermap.org/data/2.5/weather?q=" + city + "," +
countryCode + "&APPID=" + openWeatherMapApiKey;
// Send the HTTP GET request and store the response
jsonBuffer = httpGETRequest(serverPath.c_str());
// Print the response
Serial.println(jsonBuffer);
// Parse the response as a JSON object
JSONVar myObject = JSON.parse(jsonBuffer);
// Check if the parsing was successful
if (JSON.typeof(myObject) == "undefined") {
// If not, print an error message and return
Serial.println("Parsing input failed!");
return;
}
// Print the JSON object and its properties
Serial.print("JSON object = ");
Serial.println(myObject);
Serial.print("Temperature: ");
tmp = int(myObject["main"]["temp"]);
Serial.println(tmp);
// ... (other property prints)
cloudint = int(myObject["clouds"]["all"]);
}
else {
// If the WiFi connection is lost, print a message
Serial.println("WiFi Disconnected");
}
// Update the last time
lastTime = millis();
}

// TDS sensor reading
int tdsValue = analogRead(tdsSensorPin);
Serial.print("TDS Value: ");
Serial.println(tdsValue);
// Ultrasonic sensor reading
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration_us = pulseIn(echoPin, HIGH);
distance_mm = 0.173025 * duration_us;
// Relay control based on water level
int waterLevel = map(distance_mm, 0, 221, 100, 0);
// LCD display
if (digitalRead(D6) != pos) {
counter++;
lcd.clear();
pos = (digitalRead(D6));
if (counter > 3) {
counter = 1;
}
}
if (counter == 1) {
lcd.setCursor(0,0);
lcd.print("Rain:");
lcd.print(cloudint);
lcd.print("%");
lcd.setCursor(8,0);
lcd.print(",TDS:");
lcd.print(tdsValue);
lcd.setCursor(0, 1);
lcd.print("Waterlevel:");
lcd.print(waterLevel);
lcd.setCursor(13, 1);
lcd.print(" %");
} else if (counter == 2) {
// ... (other LCD displays)
} else if (counter == 3) {
// ... (other LCD displays)
}
// ... (pump control based on conditions)
// GSM Module - Send message if TDS value is above a limit
int tdsLimit = 300;
if (tdsValue > tdsLimit && !already_sent) {
sim800.println("AT+CMGF=1"); // Set SMS mode to text
updateSerial();
sim800.println("AT+CMGS=\"+8801615594236\"");
updateSerial();
sim800.print("Time to Clean up your tank!");
lcd.clear();
lcd.print("Change Water!!!"); // Your message here
updateSerial();
sim800.write(26); // ASCII code for CTRL+Z
delay(2000);
lcd.clear();
already_sent = true;
}
// Reset the already_sent flag if TDS value is below the limit
if (tdsValue < tdsLimit)
already_sent = false;
delay(500);
}
void updateSerial() {
delay(500);
while (Serial.available()) {
sim800.write(Serial.read()); // Forward what Serial received to
Software Serial Port
}
while (sim800.available()) {
Serial.write(sim800.read()); // Forward what Software Serial received
to Serial Port
}
}
// Define a function to send an HTTP GET request and return the response
String httpGETRequest(const char* serverName) {
// Create a WiFiClient object
WiFiClient client;
// Create an HTTPClient object
HTTPClient http;
// Begin the HTTP connection with the given server name
http.begin(client, serverName);
// Send the HTTP GET request
int httpResponseCode = http.GET();
// Declare a variable to store the response
String payload = "{}";
// Check the status code of the response
if (httpResponseCode > 0) {
// If successful, print the code and store the response
Serial.print("HTTP Response code: ");
Serial.println(httpResponseCode);
payload = http.getString();
} else {
// If failed, print the error code
Serial.print("Error code: ");
Serial.println(httpResponseCode);
}
// Free the resources
http.end();
// Return the response
return payload;
}
