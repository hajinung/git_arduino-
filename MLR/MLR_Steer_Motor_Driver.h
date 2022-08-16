#ifndef MLR_STEER_MOTOR_DRIVER_H
#define MLR_STEER_MOTOR_DRIVER_H

#include <DynamixelSDK.h>

// ****************************************************
// ************ control table ex106+ ******************
// ****************************************************

#define EX_106_TORQUE_ENABLE            24
#define EX_106_GOAL_POSITION            30         
#define EX_106_PRESENT_POSITION         36

// ****************************************************
// ************* Data Byte Length ********************
// ****************************************************

#define LEN_EX_GOAL_POSITION           2
#define LEN_EX_PRESENT_POSITION        2

// ****************************************************
// *************Protocol version***********************
// ****************************************************

#define PROTOCOL_VERSION                1.0

// ****************************************************
// *************Default setting************************
// ****************************************************

#define DXL1_ID                         1                   // Dynamixel#1 ID: 1 RIGHT
#define DXL2_ID                         2                   // Dynamixel#2 ID: 2 LEFT
#define BAUDRATE                        1000000
#define DEVICENAME                      "OpenCR_DXL_Port"   // This definition only has a symbolic meaning and does not affect to any functionality

#define TORQUE_ENABLE                   1                   // Value for enabling the torque
#define TORQUE_DISABLE                  0                   // Value for disabling the torque

#define CMD_SERIAL                      Serial
#define DXL_MOVING_STATUS_THRESHOLD     10                  // Dynamixel moving status threshold

#define Angle_MIN  0
#define Angle_MAX  4095

int _dxl_angle = 0;

float Calc_DXL_Angle(int DXL_ID, float dxl_angle)
{
  int _dxl_angle;
  
  if(DXL_ID == 1) //RIGHT
  {
    _dxl_angle = dxl_angle+35.46;

//    if(_dxl_angle >360)
//    {
//      _dxl_angle = _dxl_angle - 360;
//    }

//    if(_dxl_angle > 250.92 && _dxl_angle < 360)
//    {
//      _dxl_angle = _dxl_angle - 180;
//    }
  }
  else if(DXL_ID==2) //LEFT
  {
    _dxl_angle = dxl_angle+35.46;

//    if(_dxl_angle > 360)
//    {
//      _dxl_angle = _dxl_angle - 360;
//    }

//    if(_dxl_angle > 250.92 && _dxl_angle < 360)
//    {
//      _dxl_angle = _dxl_angle - 180;
//    }
  }
  return _dxl_angle;
}

void MLRSteerMotorDriver(float dxl_angle)
{
  //*****************************************************************************************************
  // Initialize PortHandler instance ********************************************************************
  // Set the port path **********************************************************************************
  // Get methods and members of PortHandlerLinux or PortHandlerWindows **********************************
  //*****************************************************************************************************
  
  dynamixel::PortHandler *portHandler = dynamixel::PortHandler::getPortHandler(DEVICENAME);
  
  //*****************************************************************************************************
  // Initialize PacketHandler instance ******************************************************************
  // Set the protocol version ***************************************************************************
  // Get methods and members of Protocol1PacketHandler or Protocol2PacketHandler ************************
  //*****************************************************************************************************
  
  dynamixel::PacketHandler *packetHandler = dynamixel::PacketHandler::getPacketHandler(PROTOCOL_VERSION);

  // ****************************************************************************************************
  // Initialize GroupSyncWrite instance *****************************************************************
  // ****************************************************************************************************
  

  int dxl_comm_result = COMM_TX_FAIL;             // Communication result
  bool dxl_addparam_result = false;               // addParam result

  uint8_t dxl_error = 0;                          // Dynamixel error
  uint16_t dxl1_present_position = 0, dxl2_present_position = 0;                        // Present position

  // Open port
  portHandler->openPort();

  // Set port baudrate
  portHandler->setBaudRate(BAUDRATE);

  // **************************************************************************************************
  // setTorque **************************************************************************************** 
  // **************************************************************************************************
  dynamixel::GroupSyncWrite groupSyncWrite(portHandler, packetHandler, EX_106_GOAL_POSITION , LEN_EX_GOAL_POSITION);
  
  // Enable Dynamixel#1 Torque
  dxl_comm_result = packetHandler->write1ByteTxRx(portHandler, DXL1_ID, EX_106_TORQUE_ENABLE, TORQUE_ENABLE, &dxl_error);

  // Enable Dynamixel#2 Torque
  dxl_comm_result = packetHandler->write1ByteTxRx(portHandler, DXL2_ID, EX_106_TORQUE_ENABLE, TORQUE_ENABLE, &dxl_error);
  
  // **************************************************************************************************

  int DXL1_goal_position; 
  int DXL2_goal_position;
  
  DXL1_goal_position = Calc_DXL_Angle(DXL1_ID,dxl_angle) * (4096 / 250.92);
  DXL2_goal_position = Calc_DXL_Angle(DXL2_ID,dxl_angle) * (4096 / 250.92);
  
  uint8_t DXL1_param_goal_position[2];
  uint8_t DXL2_param_goal_position[2];

  DXL1_param_goal_position[0] = DXL_LOBYTE(DXL1_goal_position);
  DXL1_param_goal_position[1] = DXL_HIBYTE(DXL1_goal_position);
   
  DXL2_param_goal_position[0] = DXL_LOBYTE(DXL2_goal_position);
  DXL2_param_goal_position[1] = DXL_HIBYTE(DXL2_goal_position);
  
  while(1)
  {
    
    // Add Dynamixel#1 moving_speed value to the Syncwrite storage
    dxl_addparam_result = groupSyncWrite.addParam(DXL1_ID, DXL1_param_goal_position);
  
    // Add Dynamixel#2 moving_speed value to the Syncwrite parameter storage
    dxl_addparam_result = groupSyncWrite.addParam(DXL2_ID, DXL2_param_goal_position);

    // Syncwrite goal position
    dxl_comm_result = groupSyncWrite.txPacket();
  
    // Clear syncwrite parameter storage
    groupSyncWrite.clearParam();

    do
    {
      // Read Dynamixel#1 present position
      dxl_comm_result = packetHandler->read2ByteTxRx(portHandler, DXL1_ID, EX_106_PRESENT_POSITION, &dxl1_present_position, &dxl_error);

      // Read Dynamixel#2 present position
      dxl_comm_result = packetHandler->read2ByteTxRx(portHandler, DXL2_ID, EX_106_PRESENT_POSITION, &dxl2_present_position, &dxl_error);     

    }while((abs(DXL1_goal_position - dxl1_present_position) > DXL_MOVING_STATUS_THRESHOLD) || (abs(DXL2_goal_position - dxl2_present_position) > DXL_MOVING_STATUS_THRESHOLD));

    break;
  }

//  // Disable Dynamixel#1 Torque
//  dxl_comm_result = packetHandler->write1ByteTxRx(portHandler, DXL1_ID, EX_106_TORQUE_ENABLE, TORQUE_DISABLE, &dxl_error);
//
//  // Disable Dynamixel#2 Torque
//  dxl_comm_result = packetHandler->write1ByteTxRx(portHandler, DXL2_ID, EX_106_TORQUE_ENABLE, TORQUE_DISABLE, &dxl_error);

  // Close port
//  portHandler->closePort();
}
 

#endif
