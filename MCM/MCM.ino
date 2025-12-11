/*
Motion Control Module
Rover AGR
Gerardo Aguayo, 2025
*/
#include <SoftwareSerial.h>

//DRV8871 Config
#define MOTOR_1_IN1 13
#define MOTOR_1_IN2 12

#define MOTOR_2_IN1 8
#define MOTOR_2_IN2 9

#define MOTOR_3_IN1 11
#define MOTOR_3_IN2 10

#define MOTOR_4_IN1 7
#define MOTOR_4_IN2 6

//HC12 Config
const uint32_t HC12_BAUD = 2400;
#define HC12_RX 18
#define HC12_TX 19
SoftwareSerial HC12(HC12_TX, HC12_RX);

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
int current_map = 0;

void forward(int MAP);
void reverse(int MAP);
void stop();
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
  Serial1.begin(2400);
  forward(STOP);
}

char buffer[5];
int index = 0;

void loop() {

  while (Serial1.available()) {

    char c = Serial1.read();
    if (c == '\n' || c == '\r' || c == ' '){
      continue;
    }

    buffer[index++] = c;

    if (index == 5) {
      //message complete
      buffer[2] = '\0';
      Serial.println(buffer);

      char cmd = buffer[0];//option char
      char arg_1 = buffer[1];
      char arg_2 = buffer[2];
      char arg_3 = buffer[3];

      index = 0; //reset buffer

      switch (cmd){
        case 'M':
          //Motor map config
          Serial.print("Map config ");
          Serial.println(arg_1);
          switch (arg_1){
            case '1' : current_map = MAP_1; break;
            case '2' : current_map = MAP_2; break;
            case '3' : current_map = MAP_3; break;
            case '4' : current_map = MAP_4; break;
            case '5' : current_map = MAP_5; break;
            case '0' : current_map = STOP; break;
          }
          break;
        case 'F':
          Serial.println("Forward");
          forward(current_map);
          break;
        case 'B':
          Serial.println("Backwards");
          reverse(current_map);
          break;
        case 'T':
          Serial.println("Test all motors");
          test_all_motors();
          break;
        case 'S':
          Serial.println("Stop");
          stop();
          break;
        case 'R':
          Serial.print("Right servo: ");
          Serial.print(arg_1);
          Serial.print(arg_2);
          Serial.println(arg_3);
          break;
        case 'L':
          Serial.print("Left servo: ");
          Serial.print(arg_1);
          Serial.print(arg_2);
          Serial.println(arg_3);
          break;
      }
    }
  }
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

void stop(){
  digitalWrite(MOTOR_1_IN1, LOW);
  analogWrite(MOTOR_1_IN2, LOW);

  digitalWrite(MOTOR_2_IN1, LOW);
  analogWrite(MOTOR_2_IN2, LOW);

  digitalWrite(MOTOR_3_IN1, LOW);
  analogWrite(MOTOR_3_IN2, LOW);

  digitalWrite(MOTOR_4_IN1, LOW);
  analogWrite(MOTOR_4_IN2, LOW);

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