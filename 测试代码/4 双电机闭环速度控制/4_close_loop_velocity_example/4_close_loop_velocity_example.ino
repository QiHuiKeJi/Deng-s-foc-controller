/**
Copyright Deng（灯哥） (ream_d@yeah.net)  Py-apple dog project
Github:https:#github.com/ToanTech/py-apple-quadruped-robot
Licensed under the Apache License, Version 2.0 (the "License")
you may not use this file except in compliance with the License.
You may obtain a copy of the License at:http:#www.apache.org/licenses/LICENSE-2.0
在串口中输入：电机1速度,电机2速度 即可实现对电机的闭环控制
在此例程中闭环采用的编码器是as5600
如让两个电机都以10rad/s的速度运行，你可以在串口中输入
10,10
然后回车，即可
 */
#include <SimpleFOC.h>
double init_p_sensor=0;
double init_p_sensor1=0;
int commaPosition;                //存储还没有分离出来的字符串 
double motor1_angle,motor2_angle;

MagneticSensorI2C sensor = MagneticSensorI2C(AS5600_I2C);
MagneticSensorI2C sensor1 = MagneticSensorI2C(AS5600_I2C);
TwoWire I2Cone = TwoWire(0);
TwoWire I2Ctwo = TwoWire(1);

// Motor instance
BLDCMotor motor = BLDCMotor(7);
BLDCDriver3PWM driver = BLDCDriver3PWM(32, 33, 25, 22);

BLDCMotor motor1 = BLDCMotor(7);
BLDCDriver3PWM driver1 = BLDCDriver3PWM(26, 27, 14, 12);

//HardwareSerial Serial2(2);
//定义 TROT 步态变量
void setup() {
  I2Cone.begin(18, 5, 400000); 
  I2Ctwo.begin(19, 23, 400000);
  sensor.init(&I2Cone);
  sensor1.init(&I2Ctwo);
  // link the motor to the sensor
  motor.linkSensor(&sensor);
  motor1.linkSensor(&sensor1);

  // driver config
  // power supply voltage [V]
  driver.voltage_power_supply = 12.6;
  driver.init();

  driver1.voltage_power_supply = 12.6;
  driver1.init();
  // link the motor and the driver
  motor.linkDriver(&driver);
  motor1.linkDriver(&driver1);
  
  // choose FOC modulation (optional)
  motor.foc_modulation = FOCModulationType::SpaceVectorPWM;
  motor1.foc_modulation = FOCModulationType::SpaceVectorPWM;
  // set motion control loop to be used
  motor.controller = ControlType::velocity;
  motor1.controller = ControlType::velocity;

  // contoller configuration 
  // default parameters in defaults.h

  // velocity PI controller parameters
  motor.PID_velocity.P = 0.2;
  motor1.PID_velocity.P = 0.2;
  motor.PID_velocity.I = 20;
  motor1.PID_velocity.I = 20;
  // maximal voltage to be set to the motor
  motor.voltage_limit = 16.8;
  motor1.voltage_limit = 16.8;
  
  // velocity low pass filtering time constant
  // the lower the less filtered
  motor.LPF_velocity.Tf = 0.01;
  motor1.LPF_velocity.Tf = 0.01;

  // maximal velocity of the position control
  motor.velocity_limit = 40;
  motor1.velocity_limit = 40;

  // use monitoring with serial 
  Serial.begin(115200);
  Serial2.begin(921600);
  // comment out if not needed
  motor.useMonitoring(Serial);
  motor1.useMonitoring(Serial);
  //记录无刷初始速度

  
  // initialize motor
  motor.init();
  motor1.init();
  // align sensor and start FOC
  motor.initFOC();
  motor1.initFOC();


  Serial.println("Motor ready.");
  init_p_sensor=sensor.getAngle();
  init_p_sensor1=sensor1.getAngle();
  Serial.println(init_p_sensor);
  Serial.println(init_p_sensor1);
  _delay(1000);
  
}


float target_velocity = 0;
void loop() {
  motor.loopFOC();
  motor1.loopFOC();

  motor.move(target_velocity);
  motor1.move(target_velocity);

  serialReceiveUserCommand();
}


void serialReceiveUserCommand() {
  
  // a string to hold incoming data
  static String received_chars;
  
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the string buffer:
    received_chars += inChar;
    // end of user input
    if (inChar == '\n') {
      
      // change the motor target
      target_velocity = received_chars.toFloat();
      Serial.print("Target velocity: ");
      Serial.println(target_velocity);
      
      // reset the command buffer 
      received_chars = "";
    }
  }
}
