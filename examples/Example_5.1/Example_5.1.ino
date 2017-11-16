/*
  5.1 BLE control

  This example shows how to receive data in 101. When you tap the buttons in CTC app Custom
  Control interface, the values associated with the buttons will be received by 101 in the form of a
  one char sized array. The value is displayed to serial monitor afterwards.

*/

#include <EducationShield.h>
#include <LCR.h>

BLEuart ble = BLEuart();
LCR robot;

unsigned char data;
int numero = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // Curie BLE setup
  // set advertised local name
  ble.setName("CustomC");
  ble.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (ble.searchCentral()) {
    Serial.println("Connected to central ");
    while (ble.connected()) {

      //If data is sent through BLE to 101 board
      if (ble.dataReceived()) {
        //Fetch all data from BLE
        ble.fetchData();

        //Read the 1 byte data received
        data = ble.getValueAt(0);

        switch (data)
        {
          case 1:
            robot.LCR_MotorL(FORWARDS,50);
            robot.LCR_MotorR(FORWARDS,50);
            break;

          case 2:
            robot.LCR_MotorL(BACKWARDS,50);
            robot.LCR_MotorR(FORWARDS,50);
            break;

          case 3:
            robot.LCR_MotorL(BACKWARDS,50);
            robot.LCR_MotorR(BACKWARDS,50);
            break;

          case 4:
            robot.LCR_MotorL(FORWARDS,50);
            robot.LCR_MotorR(BACKWARDS,50);
            break;

         case 5:
            robot.LCR_Sound(FS,500);
            robot.LCR_Delay(0.5);
            
          case 6:
            robot.LCR_MotorL(STOP);
            robot.LCR_MotorR(STOP);
            break;
        }
      }
    }
  }
}
