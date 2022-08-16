#include "MLR_Steer_Motor_Driver.h"
#include "MLR_Drive_Motor_Driver.h"
#include "MLR_ros.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  nh.initNode();
  nh.subscribe(dxl_rotation);
  nh.subscribe(ENC_speed);

  pinMode(L_ENC_A, INPUT);
  pinMode(L_ENC_B, INPUT);
  attachInterrupt(digitalPinToInterrupt(L_ENC_A),readEncoder,RISING);
  
  pinMode(L_PA, OUTPUT);
  pinMode(L_IN_A1, OUTPUT);
  pinMode(L_IN_A2, OUTPUT);

  pinMode(R_ENC_A, INPUT);
  pinMode(R_ENC_B, INPUT);
  attachInterrupt(digitalPinToInterrupt(R_ENC_A),readEncoder,RISING);
  
  pinMode(R_PA, OUTPUT);
  pinMode(R_IN_A1, OUTPUT);
  pinMode(R_IN_A2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  nh.spinOnce();
}

void Callback_dxl_rotate(const std_msgs::Float32& dxl_move_msgs)
{
  if(previous_dxl_move_msgs != dxl_move_msgs.data)
  {
    MLRSteerMotorDriver(dxl_move_msgs.data);
  }

  previous_dxl_move_msgs = dxl_move_msgs.data;
}

void Callback_encoder_motor_pwm(const std_msgs::Int16& ENC_pwm_msgs)
{
  int _PWM = abs(ENC_pwm_msgs.data);

  if(_PWM > 255)
  {
    _PWM = 255;
  }

  if(ENC_pwm_msgs.data >0)
  {
    L_setMotor(1,_PWM,L_PA,L_IN_A1,L_IN_A2);
    R_setMotor(1,_PWM,R_PA,R_IN_A1,R_IN_A2);
  }
  else if(ENC_pwm_msgs.data <0)
  {
    L_setMotor(-1,_PWM,L_PA,L_IN_A1,L_IN_A2);
    R_setMotor(-1,_PWM,R_PA,R_IN_A1,R_IN_A2);
  }
  else
  {
    L_setMotor(0,_PWM,L_PA,L_IN_A1,L_IN_A2);
    R_setMotor(0,_PWM,R_PA,R_IN_A1,R_IN_A2);
  }
}
