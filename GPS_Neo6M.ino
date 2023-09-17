#include <TinyGPS++.h>
#include <SoftwareSerial.h>

// Define the GPS module's serial connection
SoftwareSerial gpsSerial(10, 11); // RX, TX

// Create a TinyGPS++ object
TinyGPSPlus gps;

void setup() {
  // Start the serial communication
  Serial.begin(9600);
  gpsSerial.begin(9600); // GPS module operates at 9600 baud rate

  // Wait for GPS module to initialize (you can adjust this delay)
  delay(2000);
  Serial.println("GPS Module Check");
}

void loop() {
  // Check if there is data available from the GPS module
  if (gpsSerial.available() > 0) {
    // Read the GPS data
    while (gpsSerial.available() > 0) {
      gps.encode(gpsSerial.read());
    }

    // Check if we have a valid GPS fix
    if (gps.location.isValid()) {
      // Print GPS data to the serial monitor
      Serial.print("Latitude: ");
      Serial.println(gps.location.lat(), 6);
      Serial.print("Longitude: ");
      Serial.println(gps.location.lng(), 6);
      Serial.print("Altitude: ");
      Serial.println(gps.altitude.meters());
      Serial.print("Speed (km/h): ");
      Serial.println(gps.speed.kmph());

      // Check if the GPS has a valid date and time
      if (gps.date.isValid()) {
        Serial.print("Date: ");
        Serial.print(gps.date.month());
        Serial.print("/");
        Serial.print(gps.date.day());
        Serial.print("/");
        Serial.print(gps.date.year());
        Serial.print(" Time: ");
        Serial.print(gps.time.hour());
        Serial.print(":");
        Serial.print(gps.time.minute());
        Serial.print(":");
        Serial.println(gps.time.second());
      } else {
        Serial.println("Waiting for valid date and time...");
      }
    } else {
      Serial.println("Waiting for GPS fix...");
    }
  }
}
