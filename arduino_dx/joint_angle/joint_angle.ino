void setup() {
  // put your setup code here, to run once:
  Serial1.begin(1000000);
}

void loop() {
  // put your main code here, to run repeatedly:
  temp_write(300, 20);
  delay(3000);
  temp_write(0,20);
  delay(3000);

  exit(0);
}
void temp_read(int)
{
  
}

void temp_write(int Want_Angle, int Want_Speed) // H1, H2, Packet_ID, Len, Inst, P1,P2, CKSM
{
  int Header = 0xFF;
  
  int ID_Num = 0x01;
  
  int Length; // Length = number of param +2
  
  int Instruction = 0x03; //쓰기
  
  int Address = 0x1E; // 
  int Check_Sum; // Check_Sum = ~(ID + Length + Instruction + Param N)

  int Data_Length = 0x04; // Angle, Speed 2개  

  int broadcastID = 0xFE;

  int Angle_MIN=0, Angle_MAX=1023; // 앵글 제한 AX-12A는 goal position이 0에서 1023 사이임
  int Speed_MIN=0, Speed_MAX=1023; // Moving Speed에서 JoinMode는 0~1023으로 사용가능, 단위가 0.111rpm임
  int Angle;
  int Speed;

  Angle = map(Want_Angle, 0,300, Angle_MIN, Angle_MAX);
  Speed = map(Want_Speed,0,100,Speed_MIN, Speed_MAX);

  Length = Data_Length + 3 ;  
  
  Serial1.write(Header);
  Serial1.write(Header);
  Serial1.write(ID_Num);
  Serial1.write(Length);
  Serial1.write(Instruction);
  Serial1.write(Address);
  Serial1.write(Angle); //low bit 
  Serial1.write(Angle>>8); //high bit
  Serial1.write(Speed);
  Serial1.write(Speed>>8);
  Check_Sum = (ID_Num + Length + Instruction + Address + Angle + (Angle>>8) + Speed + (Speed >>8));
  Serial1.write(~(Check_Sum));

  
}
