import sys
import time
from argparse import ArgumentParser

from bluepy import btle

mac_address = "9c:9c:1f:e1:96:16"

threshold_value = 250




def main():


    print("Connecting...")
    nano_sense = btle.Peripheral(mac_address, btle.ADDR_TYPE_PUBLIC)

    print("Discovering Services...")
    _ = nano_sense.services
    keypad_service = nano_sense.getServiceByUUID("19b10000-e8f2-537e-4f6c-d104768a1214")

    print("Discovering Characteristics...")
    _ = keypad_service.getCharacteristics()

    while True:
        print("\n")
        read_keypad(keypad_service)




def button_press_react(index, value):
    print(index, end=":")
    print(value)

    if (index==0 and value > threshold_value):
        print("Button 1 Pressed.")
    elif(index==1 and value > threshold_value):
        print("Button 2 Pressed.")
    elif(index==2 and value > threshold_value):
        print("Button 3 Pressed.")
    elif(index==13 and value > threshold_value):
        print("Switch is in Position 1")
    elif(index==14 and value==1):
        print("Switch is in Position 2")
    elif(index==15 and value > threshold_value):
        print("Switch is in Position 3")



def process_keypad_vals(values):
    i = 0
    while i < len(values):
        button_press_react(i, values[i])
        i += 1




def read_keypad(service):
    keypad_char = service.getCharacteristics("19b10001-e8f2-537e-4f6c-d104768a1214")[0]
    keypad_vals = keypad_char.read()
    print(keypad_vals)
    process_keypad_vals(keypad_vals)




if __name__ == "__main__":
    main()