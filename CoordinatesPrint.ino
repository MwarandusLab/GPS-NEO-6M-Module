#include <SoftwareSerial.h>

// Define the GPS module's serial pins
#define GPS_TX_PIN 14
#define GPS_RX_PIN 13

SoftwareSerial gpsSerial(GPS_TX_PIN, GPS_RX_PIN); // Create a SoftwareSerial instance

void setup() {
  Serial.begin(9600);  // Start the serial communication with the computer
  gpsSerial.begin(9600); // Start the serial communication with the GPS module
}

void loop() {
  if (gpsSerial.available()) {
    String sentence = gpsSerial.readStringUntil('\n'); // Read a line from GPS module

    // Check if the sentence contains latitude and longitude
    if (sentence.startsWith("$GPGGA")) {
      // Split the sentence into individual parts
      char data[100];
      sentence.toCharArray(data, 100);

      // Extract latitude and longitude
      char *token = strtok(data, ",");
      for (int i = 0; i < 6; i++) {
        token = strtok(NULL, ",");
      }
      if (token != NULL) {
        float latitude = atof(token);
        token = strtok(NULL, ",");
        if (token != NULL) {
          float longitude = atof(token);
          Serial.print("Latitude: ");
          Serial.print(latitude, 6); // Print latitude with 6 decimal places
          Serial.print(", Longitude: ");
          Serial.println(longitude, 6); // Print longitude with 6 decimal places
        }
      }
    }
  }
}
