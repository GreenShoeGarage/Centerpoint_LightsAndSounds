import sys
import time
from argparse import ArgumentParser

from bluepy import btle  # linux only (no mac)
#from colr import color as colr


# BLE IoT Sensor Demo
# Author: Gary Stafford
# Reference: https://elinux.org/RPi_Bluetooth_LE
# Requirements: python3 -m pip install --user -r requirements.txt
# To Run: python3 ./rasppi_ble_receiver.py d1:aa:89:0c:ee:82 <- MAC address - change me!

mac_address = "9c:9c:1f:e1:96:16"

def main():


    print("Connecting...")
    nano_sense = btle.Peripheral(mac_address, btle.ADDR_TYPE_PUBLIC, 0)

    print("Discovering Services...")
    _ = nano_sense.services
    keypad_service = nano_sense.getServiceByUUID("19b10000-e8f2-537e-4f6c-d104768a1214")

    print("Discovering Characteristics...")
    _ = keypad_service.getCharacteristics()

    while True:
        print("\n")
        #read_temperature(environmental_sensing_service)
        #read_humidity(environmental_sensing_service)
        #read_pressure(environmental_sensing_service)
        #read_color(environmental_sensing_service)
        read_keypad(keypad_service)

        # time.sleep(2) # transmission frequency set on IoT device


def byte_array_to_int(value):
    # Raw data is hexstring of int values, as a series of bytes, in little endian byte order
    # values are converted from bytes -> bytearray -> int
    # e.g., b'\xb8\x08\x00\x00' -> bytearray(b'\xb8\x08\x00\x00') -> 2232

    # print(f"{sys._getframe().f_code.co_name}: {value}")

    value = bytearray(value)
    value = int.from_bytes(value, byteorder="little")
    return value


def byte_array_to_char(value):
    # e.g., b'2660,2058,1787,4097\x00' -> 2659,2058,1785,4097
    value = value.decode("utf-8")
    return value


def decimal_exponent_two(value):
    # e.g., 2350 -> 23.5
    return value / 100


def decimal_exponent_one(value):
    # e.g., 988343 -> 98834.3
    return value / 10




def read_keypad(service):
    keypad_char = service.getCharacteristics("19b10001-e8f2-537e-4f6c-d104768a1214")[0]
    keypad_vals = keypad_char.read()
    keypad_vals = byte_array_to_int(keypad_vals)
    print(f"Keypad Values: {keypad_vals}")





if __name__ == "__main__":
    main()
