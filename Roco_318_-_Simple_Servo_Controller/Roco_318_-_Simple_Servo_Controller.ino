/*-----------------------------------------------------------------------------------------------------
  ----------------------------------------------------------------------------------------------------
  ---------------------------------------------------------------------------------------------------

            _____   ____   _____ ____ ____  __  ___
           |  __ \ / __ \ / ____/ __ \___ \/_ |/ _ \
           | |__) | |  | | |   | |  | |__) || | (_) |
           |  _  /| |  | | |   | |  | |__ < | |> _ <
           | | \ \| |__| | |___| |__| |__) || | (_) |
           |_|  \_\\____/ \_____\____/____/ |_|\___/
                    SIMPLE SERVO CONTROLLER

  This is some super simple code for controlling servos via id and angle values.
  This has been made for the Arduino Nano with a PCA9685 16 channel i2c PWM breakout board.

                         -:Wiring:-
                ARDUINO NANO --->    PCA9685
                     A5      --->      SCL
                     A4      --->      SDA
                    GND      --->      GND
                     5V      --->      VCC

  THIS CODE UTILISES THE ADAFRUIT PWM SERVO DRIVER LIBRARY, TO ADD IT TO YOUR ARDUINO IDE:
  - Click on; Sketch
  - Click on; Include Library
  - Click on; Manage Libraries...
  - In the search bar that appears, type in "Adafruit PWM Servo Driver" and click install on the one that appears with the same name.
  Now you have the neccessary libraries to run the following code.

                     -:USING THE CODE:-
                      ----------------
  When uploaded you can then send simple commands to the board to control your servos.
  It must be in the following format:
    ServoNumber,ServoAngle

    So for example:

    UpdateServo(6, 90);

    This will move servo number 6 to an angle of 90 degrees.

  That is everything you need to know to use the board

  Debugging:

  If you send your servo an angle value and it does not line up, then you may need to calibrate the servo minimum and maximum pulse lengths
  Currently they have been calibrated for a range of 0 to 180 degrees for the Towerpro MG996R
  #define SERVOMIN  135 // This is the 'minimum' pulse length count (out of 4096) For the MG996R this wants to be 135
  #define SERVOMAX  482 // this is the 'maximum' pulse length count (out of 4096) For the MG996R this wants to be 482

  ------------------------------------------------------------------------------------------------
  -------------------------------------------------------------------------------------------------
*/

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define SERVOMIN  150 // This is the 'minimum' pulse length count (out of 4096) For the MG996R this wants to be 135
#define SERVOMAX  600 // this is the 'maximum' pulse length count (out of 4096) For the MG996R this wants to be 482

Adafruit_PWMServoDriver PCA9685 = Adafruit_PWMServoDriver();

int ServoPositions[16][5]; //you can use this to make a 2D array of values for your 16 servos positions for each point of your walking gait
int HipL = 1;
int KneeL = 2;
int AnkleL = 3;
int HipR = 4;
int KneeR = 5;
int AnkleR = 6;

void setup() {
  Serial.begin(115200); //Nice faster speed
  PCA9685.begin();
  PCA9685.setPWMFreq(15); //Maximum speed this can be set to is 1600
  Wire.setClock(400000); // Fast 400khz I2C Mode
  Serial.println("PCA9685 Servo Controller Connected & Ready");
  
//  for (int ServoNumber = 1; ServoNumber <= 6; ServoNumber++) // reset all servos
//  {
//    UpdateServo(ServoNumber, 0);
//  }
//  while(1);
}

void loop() {

  delay(2500);

  for (int ServoNumber = 1; ServoNumber <= 16; ServoNumber++) // set all servos to 80 degrees
  {
    UpdateServo(ServoNumber, 0);
  }
  delay(1500);

  UpdateServo(HipL, -35);
  UpdateServo(KneeL, 35);
  delay(1500);

  UpdateServo(HipL, -12);
  UpdateServo(HipR, -12);
  UpdateServo(KneeL, 0);
  UpdateServo(KneeR, 0);
  UpdateServo(AnkleL, 20);
  UpdateServo(AnkleR, 20);
  delay(1500);

  for (int ServoNumber = 1; ServoNumber <= 3; ServoNumber++) // set all servos to 80 degrees
  {
    UpdateServo(ServoNumber, 0);
  }
  UpdateServo(KneeR, -30);
  delay(1500);

  UpdateServo(HipR, 35);
  UpdateServo(KneeR, -35);
  UpdateServo(AnkleR, 0);
  delay(1500);

  UpdateServo(HipL, -12);
  UpdateServo(HipR, -12);
  UpdateServo(KneeL, 0);
  UpdateServo(KneeR, 0);
  UpdateServo(AnkleL, 20);
  UpdateServo(AnkleR, 20);
  delay(1500);

  for (int ServoNumber = 1; ServoNumber <= 6; ServoNumber++) // set all servos to 80 degrees
  {
    UpdateServo(ServoNumber, 0);
  }
  UpdateServo(KneeR, -30);
  delay(1500);
//  while(1);

}

void UpdateServo (int Id, int Angle) {

  double pulselength = map(Angle, 0, 180, SERVOMIN, SERVOMAX); //map the degree value to pulselength value
  PCA9685.setPWM(Id, 0, pulselength); //Send the angle to the appropiate servo

}
