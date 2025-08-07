#include <Arduino.h>
#include <IRremote.h>
#include <Servo.h>

#define SCL_Pin  A5
#define SDA_Pin  A4

unsigned char start01[] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};
unsigned char front[] = {0x00,0x00,0x00,0x00,0x00,0x24,0x12,0x09,0x12,0x24,0x00,0x00,0x00,0x00,0x00,0x00};
unsigned char back[] = {0x00,0x00,0x00,0x00,0x00,0x24,0x48,0x90,0x48,0x24,0x00,0x00,0x00,0x00,0x00,0x00};
unsigned char left[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x44,0x28,0x10,0x44,0x28,0x10,0x44,0x28,0x10,0x00};
unsigned char right[] = {0x00,0x10,0x28,0x44,0x10,0x28,0x44,0x10,0x28,0x44,0x00,0x00,0x00,0x00,0x00,0x00};
unsigned char STOP01[] = {0x2E,0x2A,0x3A,0x00,0x02,0x3E,0x02,0x00,0x3E,0x22,0x3E,0x00,0x3E,0x0A,0x0E,0x00};
unsigned char clear[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

int left_ctrl = 2;
int left_pwm = 5;
int right_ctrl = 4;
int right_pwm = 6;

Servo servo_A3;

void setup() {
  Serial.begin(9600);
  Serial.println("Starting IR receiver");
  IrReceiver.begin(3, ENABLE_LED_FEEDBACK); // Pin 3 IR receiver
  
  pinMode(left_ctrl, OUTPUT);
  pinMode(left_pwm, OUTPUT);
  pinMode(right_ctrl, OUTPUT);
  pinMode(right_pwm, OUTPUT);

  servo_A3.attach(A3);
  servo_A3.write(90);
  
  delay(300);
  
  pinMode(SCL_Pin, OUTPUT);
  pinMode(SDA_Pin, OUTPUT);
  matrix_display(clear);
  matrix_display(start01);
}

void loop() {
  if (IrReceiver.decode()) {
    unsigned long irr_val = IrReceiver.decodedIRData.command; // usa .command o .value según el protocolo
    Serial.print("IR code: 0x");
    Serial.println(irr_val, HEX);

    switch (irr_val) {
      case 0x46: // adelante (El cambio esta en el codigo case 0xFF629D)
        car_front();
        matrix_display(clear);
        matrix_display(front);
        break;
      case 0x15: // atrás (El cambio esta en el codigo case 0xFFA857)
        car_back();
        matrix_display(clear);
        matrix_display(back);
        break;
      case 0x44: // izquierda (El cambio esta en el codigo case 0xFF22DD)
        car_left();
        matrix_display(clear);
        matrix_display(left);
        break;
      case 0x43: // derecha (El cambio esta en el codigo case 0xFFC23D)
        car_right();
        matrix_display(clear);
        matrix_display(right);
        break;
      case 0x40: // stop (El cambio esta en el codigo case 0xFF02FD)
        car_Stop();
        matrix_display(clear);
        matrix_display(STOP01);
        break;
    }
    IrReceiver.resume();
  }
}

void car_front() {
  digitalWrite(left_ctrl, HIGH);
  analogWrite(left_pwm, 105);
  digitalWrite(right_ctrl, HIGH);
  analogWrite(right_pwm, 105);
}

void car_back() {
  digitalWrite(left_ctrl, LOW);
  analogWrite(left_pwm, 150);
  digitalWrite(right_ctrl, LOW);
  analogWrite(right_pwm, 150);
}

void car_left() {
  digitalWrite(left_ctrl, LOW);
  analogWrite(left_pwm, 100);
  digitalWrite(right_ctrl, HIGH);
  analogWrite(right_pwm, 155);
}

void car_right() {
  digitalWrite(left_ctrl, HIGH);
  analogWrite(left_pwm, 155);
  digitalWrite(right_ctrl, LOW);
  analogWrite(right_pwm, 100);
}

void car_Stop() {
  digitalWrite(left_ctrl, LOW);
  analogWrite(left_pwm, 0);
  digitalWrite(right_ctrl, LOW);
  analogWrite(right_pwm, 0);
}

// Matriz LED funciones originales (sin cambios)

void matrix_display(unsigned char matrix_value[]) {
  IIC_start();
  IIC_send(0xc0);
  for (int i = 0; i < 16; i++) {
    IIC_send(matrix_value[i]);
  }
  IIC_end();
  IIC_start();
  IIC_send(0x8A);
  IIC_end();
}

void IIC_start() {
  digitalWrite(SDA_Pin, HIGH);
  digitalWrite(SCL_Pin, HIGH);
  delayMicroseconds(3);
  digitalWrite(SDA_Pin, LOW);
  delayMicroseconds(3);
  digitalWrite(SCL_Pin, LOW);
}

void IIC_end() {
  digitalWrite(SCL_Pin, LOW);
  digitalWrite(SDA_Pin, LOW);
  delayMicroseconds(3);
  digitalWrite(SCL_Pin, HIGH);
  delayMicroseconds(3);
  digitalWrite(SDA_Pin, HIGH);
  delayMicroseconds(3);
}

void IIC_send(unsigned char send_data) {
  for (byte mask = 0x01; mask != 0; mask <<= 1) {
    digitalWrite(SDA_Pin, (send_data & mask) ? HIGH : LOW);
    delayMicroseconds(3);
    digitalWrite(SCL_Pin, HIGH);
    delayMicroseconds(3);
    digitalWrite(SCL_Pin, LOW);
  }
}
