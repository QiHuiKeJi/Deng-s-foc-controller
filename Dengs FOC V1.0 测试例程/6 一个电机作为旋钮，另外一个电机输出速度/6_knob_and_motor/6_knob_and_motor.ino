/**
Copyright Deng（灯哥） (ream_d@yeah.net)  Py-apple dog project
Github:https:#github.com/ToanTech/py-apple-quadruped-robot
Licensed under the Apache License, Version 2.0 (the "License")
you may not use this file except in compliance with the License.
You may obtain a copy of the License at:http:#www.apache.org/licenses/LICENSE-2.0
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
  
  // set motion control loop to be used
  motor.controller = ControlType::voltage;
  motor1.controller = ControlType::velocity;

  // contoller configuration 
  // default parameters in defaults.h


  // maximal voltage to be set to the motor
  motor.voltage_limit = 12.6;
  motor1.voltage_limit = 12.6;
  
  motor1.LPF_velocity.Tf = 0.02;
  motor1.PID_velocity.I = 40;

  // use monitoring with serial 
  Serial.begin(115200);
  // comment out if not needed
  motor.useMonitoring(Serial);
  motor1.useMonitoring(Serial);
  //记录无刷初始位置

  
  //初始化电机
  motor.init();
  motor1.init();
  motor.initFOC();
  motor1.initFOC();


  Serial.println("Motor ready.");
  _delay(1000);
  
}

void loop() {

  motor.loopFOC();
  motor1.loopFOC();

  motor.move(5*(motor1.shaft_velocity/10 - motor.shaft_angle));
  motor1.move(10*dead_zone(motor.shaft_angle));
}

float dead_zone(float x){
  return abs(x) < 0.2 ? 0 : x;
}
