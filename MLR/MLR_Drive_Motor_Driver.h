#ifndef MLR_DRIVE_MOTOR_DRIVER_H
#define MLR_DRIVE_MOTOR_DRIVER_H

int L_pos = 0;
int target = 360;
int R_pos = 0;

// left wheel param

#define L_ENC_A 2 // White
#define L_ENC_B 3 // Green
#define L_PA    5 // Orange PWM
#define L_IN_A1 4 // Brown motor drive A1
#define L_IN_A2 7 // Gray motor drive A2

// Right wheel param

//#define R_ENC_A 7 // White
//#define R_ENC_B 8 // Green
//#define R_PA    9 // Orange PWM
//#define R_IN_A1 10// Brown motor drive A1
//#define R_IN_A2 11 // Gray motor drive A2

#define R_ENC_A 8 // White
#define R_ENC_B 9 // Green
#define R_PA    11 // Orange PWM
#define R_IN_A1 10// Brown motor drive A1
#define R_IN_A2 12 // Gray motor drive A2


// right wheel param 

void L_setMotor(int dir, int pwmVal, int pwm, int in1, int in2){
  
  analogWrite(pwm, pwmVal);

  //CW
  if(dir == 1){
    digitalWrite(in2, LOW);
    digitalWrite(in1, HIGH);
    
  }
//CCW
  else if(dir == -1){
    digitalWrite(in2, HIGH);
    digitalWrite(in1, LOW);
  }

  else{
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
  }
}

void R_setMotor(int dir, int pwmVal, int pwm, int in1, int in2){
  
  analogWrite(pwm, pwmVal);

  //CW
  if(dir == 1){
    digitalWrite(in2, LOW);
    digitalWrite(in1, HIGH);
    
  }
//CCW
  else if(dir == -1){
    digitalWrite(in2, HIGH);
    digitalWrite(in1, LOW);
  }

  else{
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
  }
}

void readEncoder(){

  if(digitalRead(L_ENC_B) == LOW)
  {
    L_pos ++;
  }
  
  else{
    L_pos--;
  }
  
  if(digitalRead(R_ENC_B) == LOW)
  {
    R_pos ++;
  }
  
  else{
    R_pos--;
  }
}
#endif
