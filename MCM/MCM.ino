/*
Motion Control Module
Rover AGR
Gerardo Aguayo, 2025
*/
#include <SoftwareSerial.h>

// IN1 pins are for direction
// IN2 pins are for speed
#define MOTOR_1_IN1 13
#define MOTOR_1_IN2 12

#define MOTOR_2_IN1 8
#define MOTOR_2_IN2 9

#define MOTOR_3_IN1 11
#define MOTOR_3_IN2 10

#define MOTOR_4_IN1 7
#define MOTOR_4_IN2 6

/*
ENGINE MAPS
Will dictate how much power si set to the motors
*/
#define MAP_1 70
#define MAP_2 80
#define MAP_3 100
#define MAP_4 150
#define MAP_5 200
#define STOP 0

void forward(int MAP);
void reverse(int MAP);
void test_all_motors();

void setup() {
  Serial.begin(9600);
  pinMode(MOTOR_1_IN1, OUTPUT);
  pinMode(MOTOR_1_IN2, OUTPUT);
  pinMode(MOTOR_2_IN1, OUTPUT);
  pinMode(MOTOR_2_IN2, OUTPUT);
  pinMode(MOTOR_3_IN1, OUTPUT);
  pinMode(MOTOR_3_IN2, OUTPUT);
  pinMode(MOTOR_4_IN1, OUTPUT);
  pinMode(MOTOR_4_IN2, OUTPUT);
}

void loop() {

  test_all_motors();
}

void forward(int MAP){
  digitalWrite(MOTOR_1_IN1, LOW);
  analogWrite(MOTOR_1_IN2, MAP);

  digitalWrite(MOTOR_2_IN1, LOW);
  analogWrite(MOTOR_2_IN2, MAP);

  digitalWrite(MOTOR_3_IN1, LOW);
  analogWrite(MOTOR_3_IN2, MAP);

  digitalWrite(MOTOR_4_IN1, LOW);
  analogWrite(MOTOR_4_IN2, MAP);
}

void reverse(int MAP){
  digitalWrite(MOTOR_1_IN2, LOW);
  analogWrite(MOTOR_1_IN1, MAP);

  digitalWrite(MOTOR_2_IN2, LOW);
  analogWrite(MOTOR_2_IN1, MAP);

  digitalWrite(MOTOR_3_IN2, LOW);
  analogWrite(MOTOR_3_IN1, MAP);

  digitalWrite(MOTOR_4_IN2, LOW);
  analogWrite(MOTOR_4_IN1, MAP);
}

void test_all_motors(){
  Serial.println("Forward  - MAP 1");
  forward(MAP_1);
  delay(2000);
  Serial.println("Reverse - MAP 1");
  reverse(MAP_1);
  delay(2000);

  Serial.println("Forward - MAP 2");
  forward(MAP_2);
  delay(2000);
  Serial.println("Reverse - MAP 2");
  reverse(MAP_2);
  delay(2000);

  Serial.println("Forward - MAP 3");
  forward(MAP_3);
  delay(2000);
  Serial.println("Reverse - MAP 3");
  reverse(MAP_3);
  delay(2000);

  Serial.println("Forward - MAP 4");
  forward(MAP_4);
  delay(2000);
  Serial.println("Reverse - MAP 4");
  reverse(MAP_4);
  delay(2000);

  Serial.println("Forward - MAP 5");
  forward(MAP_5);
  delay(2000);
  Serial.println("Reverse - MAP 5");
  reverse(MAP_5);
  delay(2000);
}