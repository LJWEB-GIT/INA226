/*******************************************************************************************************************
** Program to demonstrate the INA226 library for the Arduino IDE. A simple infinite loop of measurments will      **
** display the bus voltage and current running through the INA226.                                                **
**                                                                                                                **
** Detailed documentation can be found on the GitHub Wiki pages at https://github.com/SV-Zanshin/INA226/wiki      **
**                                                                                                                **
** This example is for a INA226 set up to measure a 5-Volt load with a 0.1 Ohm resistor in place, this is the same**
** setup that can be found in the Adafruit INA219 breakout board.  The complex calibration options are done at    **
** runtime using the 2 parameters specified in the "begin()" call and the library has gone to great lengths to    **
** avoid the use of floating point to conserve space and minimize runtime.  This demo program uses floating point **
** only to convert and display the data conveniently. The INA226 uses 15 bits of precision, and even though the   **
** current and watt information is returned using 32-bit integers the precision remains the same.                 **
**                                                                                                                **
** The datasheet for the INA226 can be found at http://www.ti.com/lit/ds/symlink/ina226.pdf and it contains the   **
** information required in order to hook up the device. Unfortunately it comes as a VSSOP package but it can be   **
** soldered onto a breakout board for breadboard use. The INA226 is quite similar to the INA219 mentioned above,  **
** but it can take bus voltages of up to 36V (which I needed in order to monitor a 24V battery system which goes  **
** above 28V while charging and which is above the absolute limits of the INA219). It is also significantly more  **
** accurate than the INA219.                                                                                      **
**                                                                                                                **
** This program is free software: you can redistribute it and/or modify it under the terms of the GNU General     **
** Public License as published by the Free Software Foundation, either version 3 of the License, or (at your      **
** option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY     **
** WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the   **
** GNU General Public License for more details. You should have received a copy of the GNU General Public License **
** along with this program.  If not, see <http://www.gnu.org/licenses/>.                                          **
**                                                                                                                **
** Vers.  Date       Developer                     Comments                                                       **
** ====== ========== ============================= ============================================================== **
** 1.0.2   2017-08-09 https://github.com/SV-Zanshin Cosmetic changes                                              **
** 1.0.1   2017-01-12 https://github.com/SV-Zanshin Minor code cleanup and added more comments                    **
** 1.0.0   2017-01-09 https://github.com/SV-Zanshin Cloned example from test program suite                        **
**                                                                                                                **
*******************************************************************************************************************/
#include <INA226.h>                                                           // INA226 Library                   //
/*******************************************************************************************************************
** Declare program Constants                                                                                      **
*******************************************************************************************************************/
const uint32_t SERIAL_SPEED          = 115200;                                // Use fast serial speed            //
/*******************************************************************************************************************
** Declare global variables and instantiate classes                                                               **
*******************************************************************************************************************/
INA226_Class INA226;                                                          // INA class instantiation          //
uint8_t devicesFound = 0;                                                     // Number of INA226s found          //
/*******************************************************************************************************************
** Declare prototypes for all functions used                                                                      **
*******************************************************************************************************************/
void    setup();                                                              // Called once on power-up/restart  //
void    loop();                                                               // Called repeatedly after setup()  //
/*******************************************************************************************************************
** Method Setup(). This is an Arduino IDE method which is called first upon initial boot or restart. It is only   **
** called one time and all of the variables and other initialization calls are done here prior to entering the    **
** main loop for data measurement and storage.                                                                    **
*******************************************************************************************************************/
void setup() {                                                                //                                  //
  Serial.begin(SERIAL_SPEED);                                                 // Start serial communications      //
  #ifdef  __AVR_ATmega32U4__                                                  // If we are a 32U4 processor, then //
    delay(2000);                                                              // wait 2 seconds for the serial    //
  #endif                                                                      // interface to initialize          //
  Serial.print(F("\n\nDisplay INA226 Readings V1.0.1\n"));                    // Display program information      //
  // The begin initialized the calibration for an expected �1 Amps maximum current and for a 0.1Ohm resistor      //
  devicesFound = INA226.begin(1,100000);                                      // All devices set to same values   //
  Serial.print(F("Detected "));                                               //                                  //
  Serial.print(devicesFound);                                                 //                                  //
  Serial.println(F(" INA226 devices on I2C bus"));                            //                                  //
  INA226.setAveraging(4);                                                     // Average each reading n-times     //
  INA226.setBusConversion(7);                                                 // Maximum conversion time 8.244ms  //
  INA226.setShuntConversion(7);                                               // Maximum conversion time 8.244ms  //
  INA226.setMode(INA_MODE_CONTINUOUS_BOTH);                                   // Bus/shunt measured continuously  //
} // of method setup()                                                        //                                  //
/*******************************************************************************************************************
** This is the main program for the Arduino IDE, it is called in an infinite loop. The INA226 measurements are    **
** run in a simple infinite loop                                                                                  **
*******************************************************************************************************************/
void loop() {                                                                 // Main program loop                //
  Serial.print(F("Bus voltage:   "));                                         //                                  //
  Serial.print((float)INA226.getBusMilliVolts()/1000.0,4);                    // Convert to millivolts            //
  Serial.println(F("V"));                                                     //                                  //
  Serial.print(F("Shunt voltage: "));                                         //                                  //
  Serial.print((float)INA226.getShuntMicroVolts()/1000.0,3);                  // Convert to millivolts            //
  Serial.println(F("mV"));                                                    //                                  //
  Serial.print(F("Bus amperage:  "));                                         //                                  //
  Serial.print((float)INA226.getBusMicroAmps()/1000.0,3);                     // Convert to milliamp              //
  Serial.println(F("mA"));                                                    //                                  //
  Serial.print(F("Bus wattage:   "));                                         //                                  //
  Serial.print((float)INA226.getBusMicroWatts()/1000.0,3);                    // Convert to milliwatts            //
  Serial.println(F("mW"));                                                    //                                  //
  Serial.println();                                                           //                                  //
  delay(5000);                                                                //                                  //
} // of method loop                                                           //----------------------------------//
