//COM4
#include <ArduinoBLE.h>
#include "WiFiNINA.h"



#define SW_BLACK_D11 11    // Switch Black Wire (COMMON)
#define SW_GREEN_A6 A6     // Switch Green Wire, Position 1
#define SW_RED_D13 13      // Switch Red Wire, Position 2
#define SW_WHITE_A7 A7     // Switch White Wire, Position 3

#define J1_P1_A0 A0       // Output for Buttons 1, 5, 10
#define J1_P2_A1 A1       // Output for Buttons 2, 6, 11
#define J1_P3_A2 A2       // Output for Buttons 3, 7, 12
#define J1_P4_A3 A3       // Output for Buttons 4, 8, 9, 13
#define J1_P5_D2 2         // Keypad Column for Button 9
#define J1_P6_D3 3         // Keypad Column for Buttons 10, 11, 12, 13
#define J1_P7_D4 4         // Keypad Column for Buttons 1, 2, 3, 4
#define J1_P8_D5 5         // Keypad Column for Buttons 5, 6, 7, 8
#define J2_P1_D6 6         // Keypad Row for Buttons 5, 6, 7, 8, 9
#define J2_P11_D10 10      // Keypad Row for Buttons 1,2,3,4,10,11,12,13

#define J2_P3_D7 7         // Button 1 LED GND   and    GREEN LED GND
#define J2_P5_D8 8         // Button 2 LED GND   and    YELLOW LED GND
#define J2_P7_D9 9         // Button 3 LED GND   and    RED LED GND
#define J2_LEDGND_D12 12   // All Other Buttons LED GND

byte inputArray[16] = {0};  //Switch Position 1,2,3 = G-A6,R-D13,W-A7

BLEService LEDService("19B10000-E8F2-537E-4F6C-D104768A1214"); // BLE LED Service
// BLE LED Switch Characteristic - custom 128-bit UUID, read and writable by central
BLECharacteristic LEDCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLENotify | BLEWrite, 16);

void setup() {

  Serial.begin(9600);

  // begin initialization
  if (!BLE.begin()) {
    Serial.println("starting BLE failed!");
  }
  // set advertised local name and service UUID:
  BLE.setLocalName("Button LED Device");
  BLE.setAdvertisedService(LEDService);
  // add the characteristic to the service
  LEDService.addCharacteristic(LEDCharacteristic);
  // add service
  BLE.addService(LEDService);
  // start advertising
  BLE.advertise();
  Serial.println("BLE LED Peripheral, waiting for connections....");

  pinMode(J1_P5_D2, OUTPUT);
  pinMode(J1_P6_D3, OUTPUT);
  pinMode(J1_P7_D4, OUTPUT);
  pinMode(J1_P8_D5, OUTPUT);
  pinMode(J2_P1_D6, OUTPUT);
  pinMode(J2_P11_D10, OUTPUT);
  digitalWrite(J1_P5_D2, LOW);
  digitalWrite(J1_P6_D3, LOW);
  digitalWrite(J1_P7_D4, LOW);
  digitalWrite(J1_P8_D5, LOW);
  digitalWrite(J2_P1_D6, LOW);
  digitalWrite(J2_P11_D10, LOW);

  pinMode(J2_P3_D7, OUTPUT);
  pinMode(J1_P5_D2, OUTPUT);
  pinMode(J1_P5_D2, OUTPUT);
  digitalWrite(J2_P3_D7, HIGH);
  digitalWrite(J1_P5_D2, HIGH);
  digitalWrite(J1_P5_D2, HIGH);

  pinMode(SW_BLACK_D11, OUTPUT);
  pinMode(J2_LEDGND_D12, OUTPUT);
  digitalWrite(SW_BLACK_D11, HIGH);
  digitalWrite(J2_LEDGND_D12, HIGH);

}






void loop() {
  // listen for BLE peripherals to connect:
  BLEDevice central = BLE.central();
  // if a central is connected to peripheral:
  if (central) {
    Serial.print("Connected to central: ");
    // print the central's MAC address:
    Serial.println(central.address());
    // while the central is still connected to peripheral:
    while (central.connected()) {
      readInputs();
      displayInputs();
      LEDCharacteristic.writeValue(inputArray, sizeof(inputArray));
    }
    // when the central disconnects, print it out:
    Serial.print(F("Disconnected from central: "));
    Serial.println(central.address());
  }
}



void readInputs() {

  digitalWrite(J2_P11_D10, HIGH);             // Keypad Row for Buttons 1,2,3,4,10,11,12,13
  digitalWrite(J2_P1_D6, LOW);                // Keypad Row for Buttons 5, 6, 7, 8, 9
  digitalWrite(J1_P7_D4, HIGH);               //Col for buttons 1-4
  digitalWrite(J1_P8_D5, LOW);                //Col for buttons 5-8
  digitalWrite(J1_P5_D2, LOW);                //Col for Button 9
  digitalWrite(J1_P6_D3, LOW);                //Col for Buttons 10-13
  delay(100);
  inputArray[0] = analogRead(J1_P1_A0);     //Output for Buttons 1, 5, 10
  inputArray[1] = analogRead(J1_P2_A1);     //Output for Buttons 2, 6, 11
  inputArray[2] = analogRead(J1_P3_A2);     //Output for Buttons 3, 7, 12
  inputArray[3] = analogRead(J1_P4_A3);     //Output for Buttons 4, 8, 9, 13


  digitalWrite(J2_P11_D10, LOW);              // Keypad Row for Buttons 1,2,3,4,10,11,12,13
  digitalWrite(J2_P1_D6, HIGH);               // Keypad Row for Buttons 5, 6, 7, 8, 9
  digitalWrite(J1_P7_D4, LOW);                //Col for buttons 1-4
  digitalWrite(J1_P8_D5, HIGH);               //Col for buttons 5-8
  digitalWrite(J1_P5_D2, LOW);                //Col for Button 9
  digitalWrite(J1_P6_D3, LOW);                //Col for Buttons 10-13
  delay(100);
  inputArray[4] = analogRead(J1_P1_A0);     //Output for Buttons 1, 5, 10
  inputArray[5] = analogRead(J1_P2_A1);     //Output for Buttons 2, 6, 11
  inputArray[6] = analogRead(J1_P3_A2);     //Output for Buttons 3, 7, 12
  inputArray[7] = analogRead(J1_P4_A3);     //Output for Buttons 4, 8, 9, 13


  digitalWrite(J2_P11_D10, LOW);              // Keypad Row for Buttons 1,2,3,4,10,11,12,13
  digitalWrite(J2_P1_D6, HIGH);               // Keypad Row for Buttons 5, 6, 7, 8, 9
  digitalWrite(J1_P7_D4, LOW);                //Col for buttons 1-4
  digitalWrite(J1_P8_D5, LOW);                //Col for buttons 5-8
  digitalWrite(J1_P5_D2, HIGH);               //Col for Button 9
  digitalWrite(J1_P6_D3, LOW);                //Col for Buttons 10-13
  delay(100);
  inputArray[8] = analogRead(J1_P4_A3);     //Output for Buttons 4, 8, 9, 13


  digitalWrite(J2_P11_D10, HIGH);             // Keypad Row for Buttons 1,2,3,4,10,11,12,13
  digitalWrite(J2_P1_D6, LOW);                // Keypad Row for Buttons 5, 6, 7, 8, 9
  digitalWrite(J1_P7_D4, LOW);                //Col for buttons 1-4
  digitalWrite(J1_P8_D5, LOW);                //Col for buttons 5-8
  digitalWrite(J1_P5_D2, LOW);                //Col for Button 9
  digitalWrite(J1_P6_D3, HIGH);               //Col for Buttons 10-13
  delay(100);
  inputArray[9] = analogRead(J1_P1_A0);     //Output for Buttons 1, 5, 10
  inputArray[10] = analogRead(J1_P2_A1);    //Output for Buttons 2, 6, 11
  inputArray[11] = analogRead(J1_P3_A2);    //Output for Buttons 3, 7, 12
  inputArray[12] = analogRead(J1_P4_A3);    //Output for Buttons 4, 8, 9, 13


  inputArray[13] = 0; //analogRead(A6);
  inputArray[14] = digitalRead(13);
  inputArray[15] = 0; //analogRead(A7);

}



void displayInputs() {

  Serial.print("Button status: ");
  for (int x = 0; x < 13; x++) {
    Serial.print(inputArray[x]); Serial.print(",");
  }
  Serial.println();


  Serial.print("Switch status: ");
  for (int x = 13; x < 16; x++) {
    Serial.print(inputArray[x]); Serial.print(",");
  }
  Serial.println();
}
