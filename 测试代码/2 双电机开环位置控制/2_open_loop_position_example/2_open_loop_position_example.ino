/**
Copyright Deng（灯哥） (ream_d@yeah.net)  Py-apple dog project
Github:https:#github.com/ToanTech/py-apple-quadruped-robot
Licensed under the Apache License, Version 2.0 (the "License")
you may not use this file except in compliance with the License.
You may obtain a copy of the License at:http:#www.apache.org/licenses/LICENSE-2.0
 */
#include <SimpleFOC.h>

//电机加载
//加载电机1
BLDCMotor motor = BLDCMotor(7);
BLDCDriver3PWM driver = BLDCDriver3PWM(32, 33, 25, 22);
//加载电机2
BLDCMotor motor1 = BLDCMotor(7);
BLDCDriver3PWM driver1 = BLDCDriver3PWM(26, 27, 14, 12);

void setup() {


  //设置电机1供电电压
  driver.voltage_power_supply = 12.6;
  driver.init();
  //设置电机2供电电压
  driver1.voltage_power_supply = 12.6;
  driver1.init();
  // link the motor and the driver
  motor.linkDriver(&driver);
  motor1.linkDriver(&driver1);

  //设置电机1,2工作模式为开环速度模式
  motor.controller = ControlType::angle_openloop;
  motor1.controller = ControlType::angle_openloop;


  //设置串口波特率
  Serial.begin(115200);

  //初始化电机
  motor.init();
  motor1.init();

  Serial.println("Motor ready.");
  _delay(1000);
  
}

float target_position = 0; // [rad/s]


//串口输入数字，即可使电机运行到指定位置
void loop() {
  motor.move(target_position);
  motor1.move(target_position);

  //接收串口进入的数据的函数
  serialReceiveUserCommand();
}

//此函数用来接收电机需求的目标角度
void serialReceiveUserCommand() {

  static String received_chars;

  while (Serial.available()) {
    //接收一个新byte:
    char inChar = (char)Serial.read();
    // add it to the string buffer:
    received_chars += inChar;
    // 用户输入一般以回车结束
    if (inChar == '\n') {

      // change the motor target
      target_position = received_chars.toFloat();
      Serial.print("Target position: ");
      Serial.println(target_position);


      received_chars = "";
    }
  }
}
