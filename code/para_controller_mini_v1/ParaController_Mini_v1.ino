/*ParaController Mini v1

By Andre Bandarra https://andrebandarra.com/

Hardware
Uses the Para Controller Mini V1 PCB based on the Arduino Pro Micro

Software
Uses Joystick library V1  https://github.com/MHeironimus/ArduinoJoystickLibrary/tree/version-1.0

Setup
- Defines switches and potentiometer input pins
- Starts Joystick entity
Loop
- Checks button states and updates
- Checks pot values and updates

*/

#include <Joystick.h>

#define MAX_SWITCHES 4                            //number of switches
byte switch_pin[MAX_SWITCHES] = {A6, A1, A2, A3}; // digital input pins for switches
#define DEBOUNCE_TIME 5                           // ms delay before the push button changes state
#define MAX_ANALOG 4                              //number of analog potentiometers
byte analog_pin[MAX_ANALOG] = {A10, A9, A8, A7};  //array of input pins for potentiometers
int readvalues[8];                                //array of input read values

byte reading, switch_state[MAX_SWITCHES], switch_state_old[MAX_SWITCHES];
int analog_value[MAX_ANALOG];
unsigned long debounce_time[MAX_SWITCHES];


void setup() {

// Serial.begin(9600);    use serial for debugging

  for (int i = 0; i < MAX_SWITCHES; i++){
      pinMode(switch_pin[i], INPUT_PULLUP);
      }

  Joystick.begin();                       
}

void loop() {


  for (byte i=0; i<MAX_SWITCHES; i++) {                                                         // read the switches
    reading = !digitalRead(switch_pin[i]);
    if (reading == switch_state[i]) debounce_time[i] = millis() + (unsigned long)DEBOUNCE_TIME;
    else if (millis() > debounce_time[i]) switch_state[i] = reading;
    if (switch_state[i] != switch_state_old[i]) {                                               // debounced button has changed state
      // this code is executed once after change of state
      digitalWrite(13,switch_state[i]);
      if (switch_state[i]) Joystick.pressButton(i); else Joystick.releaseButton(i);
        switch_state_old[i] = switch_state[i];                                                  // store new state such that the above gets done only once
    }
  } //END read switches


  for (byte i=0; i<MAX_ANALOG; i++) {                                                           // read analog inputs in sequence
    analog_value[i] = analogRead(analog_pin[i]);

    switch(i) {
      case 0:
        Joystick.setXAxis(map(analog_value[0], 0, 1023, -127, 127));                            // Sets this joystick axis to variable and rescales it using a map (value, min input, max input, min output, max output)
      break;
      case 1:
        Joystick.setYAxis(map(analog_value[1], 0, 1023, -127, 127));
      break;
      case 2:
        Joystick.setZAxis(map(analog_value[2], 0, 1023, -127, 127));
      break;
      case 3:
        Joystick.setXAxisRotation(map(analog_value[3], 0, 1023, 0, 359));
      break;
    }
   } //END read analogues

/*
  //Use serial prints for debugging
  
  Serial.print(analog_value[0]);
  Serial.print("\t");
  Serial.print(analog_value[1]);
  Serial.print("\t");
  Serial.print(analog_value[2]);
  Serial.print("\t");
  Serial.println(analog_value[3]);
*/

   
}