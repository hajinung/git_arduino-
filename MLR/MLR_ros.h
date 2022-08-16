#ifndef MLR_ROS_H
#define MLR_ROS_H

#include <ros.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Int16.h>

void Callback_dxl_rotate(const std_msgs::Float32& dxl_move_msgs); // subscriber callback function

void Callback_encoder_motor_pwm(const std_msgs::Int16& ENC_pwm_msgs);

ros::NodeHandle nh;

ros::Subscriber<std_msgs::Float32> dxl_rotation("/steering_data", Callback_dxl_rotate);

ros::Subscriber<std_msgs::Int16> ENC_speed("/ENC_speed_data", Callback_encoder_motor_pwm);

float previous_dxl_move_msgs = 0;

#endif
