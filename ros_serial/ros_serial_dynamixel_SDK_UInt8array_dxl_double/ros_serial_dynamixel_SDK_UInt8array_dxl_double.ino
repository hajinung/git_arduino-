
#include <DynamixelSDK.h>
#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/UInt16MultiArray.h>
#include <std_msgs/Float32.h>

// Control table address
#define ADDR_MX_MOVING                  30

// Protocol version
#define PROTOCOL_VERSION                1.0                 // See which protocol version is used in the Dynamixel

// Default setting
#define DXL_ID1                          1
#define DXL_ID2                          2                   // Dynamixel ID: 1
#define BAUDRATE                        1000000
#define DEVICENAME                      "OpenCR_DXL_Port"   // This definition only has a symbolic meaning and does not affect to any functionality

//goal position 각도  입력
#define DXL_MINIMUM_MOVING              500                 // Dynamixel will rotate between this value              
#define ESC_ASCII_VALUE                 0x1b

#define CMD_SERIAL                      Serial


std_msgs::Float32 value_me;                       //publish의 자료형 선
ros::Publisher view("view_val", &value_me);       //rostopic echo /view_val 을 사용해서 토픽의 데이터를 확인하기 위해서 publish해

ros::NodeHandle  nh;

void messageCb( const std_msgs::UInt16MultiArray& cmd_val)
{

  if(cmd_val.data[0] == 1)
  {
    int DXL_VALUE_ID1 = cmd_val.data[1];
    dynamixel_dx1(DXL_VALUE_ID1);
    
  }
  
  else if(cmd_val.data[0] == 2)
  {
    int DXL_VALUE_ID2 = cmd_val.data[1];
    dynamixel_dx2(DXL_VALUE_ID2);
  }

  for(int i; i<2; i++)
  {
    int DXL_VALUE1 = cmd_val.data[i];
  value_me.data = DXL_VALUE1;
  view.publish(&value_me);
  }
  
  
  

}

void dynamixel_dx1(int DXL_VALUE_ID1)
{
  
 
//다이나믹셀 핸들러
  dynamixel::PortHandler *portHandler = dynamixel::PortHandler::getPortHandler(DEVICENAME);
  dynamixel::PacketHandler *packetHandler = dynamixel::PacketHandler::getPacketHandler(PROTOCOL_VERSION);


  int dxl_moving1 = DXL_VALUE_ID1;         // Goal position -> 다이나믹셀 DXL_MINIMUM_POSITION_VALUE 값을 받아서 dxl_goal_position에 저장
  uint8_t dxl_error = 0;                                      // Dynamixel error



  // Open port
  portHandler->openPort();
  
  // Set port baudrate
  portHandler->setBaudRate(BAUDRATE);

  // Write goal position
   packetHandler->write2ByteTxRx(portHandler, DXL_ID1, ADDR_MX_MOVING, dxl_moving1, &dxl_error);

   
    
  // Close port
  portHandler->closePort();
  
}

void dynamixel_dx2(int DXL_VALUE_ID2)
{
  
 
//다이나믹셀 핸들러
  dynamixel::PortHandler *portHandler = dynamixel::PortHandler::getPortHandler(DEVICENAME);
  dynamixel::PacketHandler *packetHandler = dynamixel::PacketHandler::getPacketHandler(PROTOCOL_VERSION);


  int dxl_moving2 = DXL_VALUE_ID2;         // Goal position -> 다이나믹셀 DXL_MINIMUM_POSITION_VALUE 값을 받아서 dxl_goal_position에 저장
  uint8_t dxl_error = 0;                                      // Dynamixel error



  // Open port
  portHandler->openPort();
  
  // Set port baudrate
  portHandler->setBaudRate(BAUDRATE);

  // Write goal position
   packetHandler->write2ByteTxRx(portHandler, DXL_ID2, ADDR_MX_MOVING, dxl_moving2, &dxl_error);
   
    
  // Close port
  portHandler->closePort();
  
}


ros::Subscriber<std_msgs::UInt16MultiArray> sub("cmd_val", messageCb );


void setup() {
  Serial.begin(57600);
  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(view);
}

void loop() {
  nh.spinOnce();
}
