//COM3
#include <ArduinoBLE.h>


void setup() {
  Serial.begin(9600);
  while (!Serial);
  // initialize the BLE hardware
  BLE.begin();
  Serial.println("BLE Central - LED control");
  // start scanning for LED BLE peripherals
  BLE.scanForUuid("19b10000-e8f2-537e-4f6c-d104768a1214");
}
void loop() {
  // check if a peripheral has been discovered
  BLEDevice peripheral = BLE.available();
  if (peripheral) {
    // discovered a peripheral, print out address, local name, and advertised service
    Serial.print("Found ");
    Serial.print(peripheral.address());
    Serial.print(" '");
    Serial.print(peripheral.localName());
    Serial.print("' ");
    Serial.print(peripheral.advertisedServiceUuid());
    Serial.println();
    if (peripheral.localName().indexOf("LED") < 0) {
      Serial.println("No 'LED' in name");
      return;  // If the name doeshn't have "LED" in it then ignore it
    }
    // stop scanning
    BLE.stopScan();

    controlLed(peripheral);
    // peripheral disconnected, start scanning again
    BLE.scanForUuid("19b10000-e8f2-537e-4f6c-d104768a1214");
  }
}
void controlLed(BLEDevice peripheral) {
  // connect to the peripheral
  Serial.println("Connecting ...");
  if (peripheral.connect()) {
    Serial.println("Connected");
  } else {
    Serial.println("Failed to connect!");
    return;
  }
  // discover peripheral attributes
  Serial.println("Discovering attributes ...");
  if (peripheral.discoverAttributes()) {
    Serial.println("Attributes discovered");
  } else {
    Serial.println("Attribute discovery failed!");
    peripheral.disconnect();
    return;
  }
  // retrieve the LED characteristic
  BLECharacteristic LEDCharacteristic = peripheral.characteristic("19b10001-e8f2-537e-4f6c-d104768a1214");
  if (!LEDCharacteristic) {
    Serial.println("Peripheral does not have LED characteristic!");
    peripheral.disconnect();
    return;
  }


  while (peripheral.connected()) {
    // while the peripheral is connected
    if (LEDCharacteristic.canRead()) {
      byte value[16] = {0};
      //value = LEDCharacteristic.read();
      LEDCharacteristic.readValue(value, 16);

      for (int x = 0; x < 16; x++) {
        Serial.print(value[x]); Serial.print(",");
        switch (x) {
          case 0:
            if ( value[x] > 250) {
              digitalWrite(13, HIGH);
            }
            break;
          case 1:
            if ( value[x] > 250) {
              digitalWrite(13, LOW);
            }
            break;
          case 13:
            if ( value[x] > 250) {
            }
            break;
          case 14:
            if ( value[x] == 1) {
            }
            break;
          case 15:
            if ( value[x] > 250) {
            }
            break;
          default:
            break;

        }
      }
    }
    Serial.println();
  }

  Serial.println("Peripheral disconnected");
}
