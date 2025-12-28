#include "Motors.h"
#include <Arduino.h>

//DRV8871 Config
#define MOTOR_1_IN1 13
#define MOTOR_1_IN2 12

#define MOTOR_2_IN1 8
#define MOTOR_2_IN2 9

#define MOTOR_3_IN1 11
#define MOTOR_3_IN2 10

#define MOTOR_4_IN1 7
#define MOTOR_4_IN2 6

//Motor maps
#define MAP_1 70
#define MAP_2 80
#define MAP_3 100
#define MAP_4 150
#define MAP_5 200
#define STOP 0

Motors::Motors(){
  this->current_map = STOP;
}

void Motors::start(){
  pinMode(MOTOR_1_IN1, OUTPUT);
  pinMode(MOTOR_1_IN2, OUTPUT);
  pinMode(MOTOR_2_IN1, OUTPUT);
  pinMode(MOTOR_2_IN2, OUTPUT);
  pinMode(MOTOR_3_IN1, OUTPUT);
  pinMode(MOTOR_3_IN2, OUTPUT);
  pinMode(MOTOR_4_IN1, OUTPUT);
  pinMode(MOTOR_4_IN2, OUTPUT);
}

void Motors::forward(int MAP){
  digitalWrite(MOTOR_1_IN1, LOW);
  analogWrite(MOTOR_1_IN2, MAP);

  digitalWrite(MOTOR_2_IN1, LOW);
  analogWrite(MOTOR_2_IN2, MAP);

  digitalWrite(MOTOR_3_IN1, LOW);
  analogWrite(MOTOR_3_IN2, MAP);

  digitalWrite(MOTOR_4_IN1, LOW);
  analogWrite(MOTOR_4_IN2, MAP);
}

void Motors::reverse(int MAP){
  digitalWrite(MOTOR_1_IN2, LOW);
  analogWrite(MOTOR_1_IN1, MAP);

  digitalWrite(MOTOR_2_IN2, LOW);
  analogWrite(MOTOR_2_IN1, MAP);

  digitalWrite(MOTOR_3_IN2, LOW);
  analogWrite(MOTOR_3_IN1, MAP);

  digitalWrite(MOTOR_4_IN2, LOW);
  analogWrite(MOTOR_4_IN1, MAP);
}

void Motors::stop(){
  digitalWrite(MOTOR_1_IN1, LOW);
  analogWrite(MOTOR_1_IN2, LOW);

  digitalWrite(MOTOR_2_IN1, LOW);
  analogWrite(MOTOR_2_IN2, LOW);

  digitalWrite(MOTOR_3_IN1, LOW);
  analogWrite(MOTOR_3_IN2, LOW);

  digitalWrite(MOTOR_4_IN1, LOW);
  analogWrite(MOTOR_4_IN2, LOW);
}

void Motors::test_all_motors(){
  forward(MAP_1);
  delay(2000);
  reverse(MAP_1);
  delay(2000);

  forward(MAP_2);
  delay(2000);
  reverse(MAP_2);
  delay(2000);

  forward(MAP_3);
  delay(2000);
  reverse(MAP_3);
  delay(2000);

  forward(MAP_4);
  delay(2000);
  reverse(MAP_4);
  delay(2000);

  forward(MAP_5);
  delay(2000);
  reverse(MAP_5);
  delay(2000);
}


