//#include <Servo.h>
//Global variables
#define SMA_PIN   9     //Pin # for SMA PWM on P2
#define LED_PIN   13    //Pin # for on-board Teensy LED
#define IR_PIN A0
#define TIME_ON   1.5   //In Seconds (Less than 2s)
#define TIME_OFF  20    //In Seconds (At least 30s)

void setup() {
  // Declarations for Sensor and Actuator Pins
  pinMode(SMA_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT); // On-Board Indicator LED
  pinMode(IR_PIN, INPUT);

  //Intialize Serial Communication
  Serial.begin(19200);
}

// int型のデータを送信する関数
void sendIntData(int value) {
  Serial.write('H'); // ヘッダの送信
  Serial.write(highByte(value)); // 上位バイトの送信
  Serial.write(lowByte(value)); // 下位バイトの送信
}

//グローバル変数の宣言
int i = 0;
int ir_val = 0;
int distance = 0;

// メインループ
void loop() {
  ir_val = 0;
  for (i=0 ; i < 100 ; i++) {
    ir_val  = ir_val + analogRead(IR_PIN) ;   // 指定のアナログピン(0番端子)から読取ります
  }
  ir_val = ir_val/100.0;
  distance = 6762/(ir_val-9)-4;

  sendIntData(distance);
  //Serial.println(distance);
}
