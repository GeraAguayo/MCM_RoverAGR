/*
Motion Control Module
Rover AGR
Gerardo Aguayo, 2025
*/
#include <SoftwareSerial.h>
#include <Servo.h>
#include "Motors.h"

//Motor maps
#define MAP_1 70
#define MAP_2 80
#define MAP_3 100
#define MAP_4 150
#define MAP_5 200
#define STOP 0
Motors motors;
int current_map = 0;
void forward(int MAP);
void reverse(int MAP);
void stop();
void test_all_motors();

//Servo steering 
#define L_SERVO_PIN 2
#define R_SERVO_PIN 3
Servo l_servo;
Servo r_servo;

void processCommand(char* msg);

void setup() {
  Serial.begin(9600); //Debug serial
  motors.start();
  Serial1.begin(2400); //HC12 Serial
  motors.stop();
  motors.current_map = STOP;
  l_servo.attach(L_SERVO_PIN);
  r_servo.attach(R_SERVO_PIN);
}

char buffer[5];
int index = 0;

void loop() {
  while (Serial1.available()){
    char c = Serial1.read();

    if (index == 0 && c != 'R' && c != 'L' &&
        c != 'M' && c != 'F' && c != 'B' &&
        c != 'S' && c != 'T' && c != 'K' && c != 'C'){
          //Skip if no valid command header
          continue;
    }

    buffer[index++] = c;

    if (index == 5){
      //validate a compleye message
      if (buffer[4] == '\n'){
        Serial.print("Command received: ");
        for (int i = 0; i < 5; i++) {
          Serial.print(buffer[i]);
        }
        Serial.println();
        
        processCommand(buffer);
      }
      index = 0;
    }
  }

}

void processCommand(char* buffer){
  char cmd = buffer[0];//option char
  char arg_1 = buffer[1];
  char arg_2 = buffer[2];
  char arg_3 = buffer[3];

  int val_1, val_2, val_3, angle {};

  switch (cmd){
    case 'M':
      //Motor map config
      Serial.print("Map config ");
      Serial.println(arg_1);
      switch (arg_1){
        case '1' : motors.current_map = MAP_1; break;
        case '2' : motors.current_map = MAP_2; break;
        case '3' : motors.current_map = MAP_3; break;
        case '4' : motors.current_map = MAP_4; break;
        case '5' : motors.current_map = MAP_5; break;
        case '0' : motors.current_map = STOP; break;
      }
      break;

    case 'F':
      Serial.println("Forward");
      motors.forward(motors.current_map);
      break;

    case 'B':
      Serial.println("Backwards");
      motors.reverse(motors.current_map);
      break;

    case 'T':
      Serial.println("Test all motors");
      motors.test_all_motors();
      break;

    case 'S':
      Serial.println("Stop");
      motors.stop();
      break;
    
    case 'R':
      val_1 = arg_1 - '0';
      val_2 = arg_2 - '0';
      val_3 = arg_3 - '0';
      angle = (val_1 * 100) + (val_2 * 10) + val_3;
      Serial.print("R - Angle: ");
      Serial.println(angle);
      r_servo.write(angle);
      break;

    case 'L':
      val_1 = arg_1 - '0';
      val_2 = arg_2 - '0';
      val_3 = arg_3 - '0';
      angle = (val_1 * 100) + (val_2 * 10) + val_3;
      Serial.print("L - Angle: ");
      Serial.println(angle);
      l_servo.write(angle);
      break;

    case 'K':
      Serial.println("Toggle light");
      break;

    case 'C':
      if (arg_1 == 'R'){
        Serial.println("Cam right");
      }
      else if (arg_1 == 'L'){
          Serial.println("Cam left");
      }
      break;
  }

}
