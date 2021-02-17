/**
 * ESP32 position motion control example with magnetic sensor
 */
#include <SimpleFOC.h>

// SPI Magnetic sensor instance (AS5047U example)
// MISO 12
// MOSI 9
// SCK 14
//MagneticSensorSPI sensor = MagneticSensorSPI(10, 14, 0x3FFF);

// I2C Magnetic sensor instance (AS5600 example)
// make sure to use the pull-ups!!
// SDA 21
// SCL 22
//MagneticSensorI2C sensor = MagneticSensorI2C(0x36, 12, 0x0E, 4);

// Analog output Magnetic sensor instance (AS5600)
// MagneticSensorAnalog sensor = MagneticSensorAnalog(A1, 14, 1020);
MagneticSensorAnalog sensor = MagneticSensorAnalog(4, 14, 4096);

// Motor instance
BLDCMotor motor = BLDCMotor(32, 33, 25, 7, 18);

void setup() {
  // monitoring port
  Serial.begin(115200);
  //sensor 1
  //sensor.sda_pin = 4;
  //sensor.scl_pin =0;
  sensor.init();

  Serial.println("Sensor ready");
  _delay(1000);
  // link the motor to the sensor
  motor.linkSensor(&sensor);

  // power supply voltage
  // default 12V
  motor.voltage_power_supply = 12;
  
  // choose FOC modulation (optional)
  motor.foc_modulation = FOCModulationType::SpaceVectorPWM;

  // set motion control loop to be used
  motor.controller = ControlType::angle;

  // contoller configuration 
  // default parameters in defaults.h

  // velocity PI controller parameters
  motor.PID_velocity.P = 0.1;
  motor.PID_velocity.I = 0.5;
  // maximal voltage to be set to the motor
  motor.voltage_limit = 10;
  
  // velocity low pass filtering time constant
  // the lower the less filtered
  motor.LPF_velocity.Tf = 0.05;

  // angle P controller 
  motor.P_angle.P = 20;
  // maximal velocity of the position control
  motor.velocity_limit = 40;

  // use monitoring with serial 
  Serial.begin(115200);
  // comment out if not needed
  motor.useMonitoring(Serial);

  
  // initialize motor
  motor.init();
  // align sensor and start FOC
  motor.initFOC();


  Serial.println("Motor ready.");
  Serial.println("Set the target angle using serial terminal:");
  _delay(1000);
}

// angle set point variable
float target_angle = 0;

void loop() {

  // main FOC algorithm function
  // the faster you run this function the better
  // Arduino UNO loop  ~1kHz
  // Bluepill loop ~10kHz 
  motor.loopFOC();

  // Motion control function
  // velocity, position or voltage (defined in motor.controller)
  // this function can be run at much lower frequency than loopFOC() function
  // You can also use motor.move() and set the motor.target in the code
  Serial.println(sensor.getAngle());
  motor.move(target_angle);


  // function intended to be used with serial plotter to monitor motor variables
  // significantly slowing the execution down!!!!
  // motor.monitor();
  
  // user communication
  serialReceiveUserCommand();
}

// utility function enabling serial communication with the user to set the target values
// this function can be implemented in serialEvent function as well
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
      target_angle = received_chars.toFloat();
      Serial.print("Target angle: ");
      Serial.println(target_angle);
      
      // reset the command buffer 
      received_chars = "";
    }
  }
}
