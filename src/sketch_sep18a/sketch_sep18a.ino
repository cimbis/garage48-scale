#include <SoftwareSerial.h>

#define ROBOT_NAME "RandomBot"

// If you haven't configured your device before use this
#define BLUETOOTH_SPEED 57600 //9600


#include <SoftwareSerial.h>

// Swap RX/TX connections on bluetooth chip
//   Pin 10 --> Bluetooth TX
//   Pin 11 --> Bluetooth RX
SoftwareSerial bluetooth(10, 11); // RX, TX

int incomingByte = 0;


void setup()
{
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  Serial.println("Starting config");
  bluetooth.begin(BLUETOOTH_SPEED);
  delay(1000);

  // Should respond with OK
  bluetooth.print("AT");
  waitForResponse();

  // Should respond with its version
  bluetooth.print("AT+VERSION");
  waitForResponse();

  // Set pin to 0000
  bluetooth.print("AT+PIN0000");
  waitForResponse();

  // Set the name to ROBOT_NAME
  bluetooth.print("AT+NAME");
  bluetooth.print(ROBOT_NAME);
  waitForResponse();

  // Set baudrate to 57600
  bluetooth.print("AT+BAUD7");
  waitForResponse();
 
  Serial.println("SETUP COMPLETE!");
}

void waitForResponse() {
    delay(1000);
    while (bluetooth.available()) {
      Serial.write(bluetooth.read());
    }
    Serial.write("\n");
}



void loop() {
  delay(1000);

  if (Serial.available() > 0) {
      // read the incoming byte:
      incomingByte = Serial.read();
  
      // say what you got:
      Serial.print("I received: ");
      Serial.print(incomingByte, HEX);
  
//      bluetooth.write(incomingByte);
  }

//  if (bluetooth.available()){
//    char[] = bluetooth.read();
//  }
}
