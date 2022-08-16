
#include <DynamixelSDK.h>
#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Int16.h>


// Control table address
#define ADDR_MX_GOAL_POSITION           30

// Protocol version
#define PROTOCOL_VERSION                1.0                 // See which protocol version is used in the Dynamixel

// Default setting
#define DXL_ID                          2                   // Dynamixel ID: 1
#define BAUDRATE                        1000000
#define DEVICENAME                      "OpenCR_DXL_Port"   // This definition only has a symbolic meaning and does not affect to any functionality

//goal position 각도  입력
#define DXL_MINIMUM_POSITION_VALUE      500                 // Dynamixel will rotate between this value              
#define ESC_ASCII_VALUE                 0x1b

#define CMD_SERIAL                      Serial


ros::NodeHandle  nh;

void messageCb( const std_msgs::Int16& led_msg)
{
  int DXL_VALUE = led_msg.data;
  
  dynamixel_dx(DXL_VALUE);

}

void dynamixel_dx(int DXL_VALUE)
{
  
 
//다이나믹셀 핸들러
  dynamixel::PortHandler *portHandler = dynamixel::PortHandler::getPortHandler(DEVICENAME);
  dynamixel::PacketHandler *packetHandler = dynamixel::PacketHandler::getPacketHandler(PROTOCOL_VERSION);


  int dxl_goal_position = DXL_VALUE;         // Goal position -> 다이나믹셀 DXL_MINIMUM_POSITION_VALUE 값을 받아서 dxl_goal_position에 저장

  uint8_t dxl_error = 0;                                      // Dynamixel error



  // Open port
  portHandler->openPort();
  
  // Set port baudrate
  portHandler->setBaudRate(BAUDRATE);

  // Write goal position
   packetHandler->write2ByteTxRx(portHandler, DXL_ID, ADDR_MX_GOAL_POSITION, dxl_goal_position, &dxl_error);
    
  // Close port
  portHandler->closePort();
  
}


ros::Subscriber<std_msgs::Int16> sub("led_out", messageCb );


void setup() {

  nh.initNode();
  nh.subscribe(sub);
}

void loop() {
  nh.spinOnce();
}
