# Centerpoint Lights and Sounds

| RP2040 Pin | Keypad PCB Header Row (J) | Keypad PCB Header Pin (P) | Pin Function                                                    |
|------------|---------------------------|---------------------------|-----------------------------------------------------------------|
| D2         | J1                        | 5                         | Keypad Column for Button 9                                      |
| D3         | J1                        | 6                         | Keypad Column for Buttons 10, 11, 12, 13                        |
| D4         | J1                        | 7                         | Keypad Column for Buttons 1,2,3,4                               |
| D5         | J1                        | 8                         | Keypad Column for Buttons 5, 6, 7, 8                            |
| D6         | J2                        | 1                         | Keypad Row for Buttons 5, 6, 7, 8, 9                            |
| D7         | J2                        | 3                         |  Button 1 LED GND   AND GREEN LED GROUND                        |
| D8         | J2                        | 5                         |  Button 2 LED GND   AND YELLOW LED GROUND                       |
| D9         | J2                        | 7                         |  GND for RED LED         AND MAYBE  Button 3 LED GND****        |
| D10        | J2                        | 11                        | Keypad Row for Buttons 1,2,3,4,10,11,12,13                      |
| D11        | SW                        | BLACK                     | VCC for Switch                                                  |
| D12        | J2                        | 4                         | Buttons 8 and 13 LED GND                                        |
| D12        | J2                        | 6                         | Buttons 5 and 10 LED GND                                        |
| D12        | J2                        | 8                         | Buttons 6 and 11 LED GND                                        |
| D12        | J2                        | 9                         | Buttons 4 and 9 LED GND                                         |
| D12        | J2                        | 10                        | Buttons 7 and 12 LED GND                                        |
| D13        | SW                        | RED                       | Switch Position 2                                               |
| VCC        | J2                        | 2                         | Top Row of Rubber Buttons (1-8) LED Vcc                         |
| VCC        | J2                        | 13                        | Bottom Row of Rubber Buttons (9-13) LED Vcc   AND  GYR LEDs Vcc |
| A0         | J1                        | 1                         | Buttons 1 and 5 and 10                                          |
| A1         | J1                        | 2                         | Buttons 2 and 6 and 11                                          |
| A2         | J1                        | 3                         |  Buttons 3 and 7 and 12                                         |
| A3         | J1                        | 4                         |  Buttons 4 and 8 and 9 and 13                                   |
| A4         | unassigned                | unassigned                | Reserved for I2C                                                |
| A5         | unassigned                | unassigned                | Reserved for I2C                                                |
| A6         | SW                        | GREEN                     | Switch Position 1                                               |
| A7         | SW                        | WHITE                     | Switch Position 3                                               |
