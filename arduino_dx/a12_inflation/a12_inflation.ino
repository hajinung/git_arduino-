void setup() {
  // put your setup code here, to run once:
  Serial1.begin(1000000);
  pinMode(0, OUTPUT); // DIR HIGH로 맞춰 주었다 그래야 rs485통신이 가능하게 된다.
  pinMode(1, OUTPUT); // DIR HIGH로 맞춰 주었다 그래야 rs485통신이 가능하게 된다.
  digitalWrite(22, HIGH);
  //Serial1.begin(1000000);//보레이트 통신 맞춤
}

void loop() 
{
  // put your main code here, to run repeatedly:

    temp_write(300,500);
    delay(100);
  exit(0);
  

}




   void temp_write(int Want_Angle, int Want_Speed) // H1, H2, Packet_ID, Len, Inst,address, P1,P2, CKSM
  {

    digitalWrite(0, HIGH);
    digitalWrite(1, HIGH);
    
    
    int Header = 0xFF; //header매개변수

    int ID_Num = 0x02; //ID매개변수

    int Length; // Length = number of param +2 length 매개변수

    int Instruction = 0x03; //inst매개변수 = 0x03이므로 writ모드로 설정됨

    int Address = 0x20; // address매개변수 =  0x20이므로 프로토콜 32번 주소의 이동속도 모드 설정됨

    int Check_Sum; // Check_Sum = ~(ID + Length + Instruction + Param N)

    int Data_Length = 0x02; // Angle, Speed 2개  angle과 speed가 각각 두개로 나눠져 있어서 총 4개가 되므로 0x04이다

    int broadcastID = 0xFE;

    int Angle_MIN = 0, Angle_MAX = 1023; // 앵글 제한 AX-12A는 goal position이 0에서 1023 사이임
    int Speed_MIN = 1024, Speed_MAX = 2047; // Moving Speed에서 JoinMode는 0~1023으로 사용가능, 단위가 0.111rpm임
    //int Speed_MIN = 1024, Speed_MAX = 2020;
    int Angle;
    int Speed;

    //Angle = map(Want_Angle, 0,300, Angle_MIN, Angle_MAX);//map(원하는각도,0~300까지를,0~1023으로 나눈다 즉 150을 입력하면 약 512의 값이 나오는 원리이다. )
    Speed = map(Want_Speed, 0, 1000, Speed_MIN, Speed_MAX);
    //Speed1 = map(Want_Speed, 0, 1000, Speed_MIN, Speed_MAX);

    Length = Data_Length + 3 ; //프로토콜에서 length를 확인해보면 알수 있다.

    Serial1.write(Header);
    //Serial1.write(Header);
    
    Serial1.write(Header);
    //Serial1.write(Header);
    
    Serial1.write(ID_Num);
    //Serial1.write(ID_Num);
    
    Serial1.write(Length);
    //Serial1.write(Length);
    
    Serial1.write(Instruction);
    //Serial1.write(Instruction);
    
    Serial1.write(Address);
    //Serial1.write(Address);
    
    //Serial1.write(Angle); //low bit
    //Serial1.write(Angle>>8); //high bith
    Serial1.write(Speed);
    //Serial1.write(Speed);
    
    Serial1.write(Speed >> 8);
    //Serial1.write(Speed >> 8);
    
    Check_Sum = (ID_Num + Length + Instruction + Address  + Speed + (Speed >> 8));
    
    Serial1.write(~(Check_Sum));
    //Serial1.write(~(Check_Sum));


  }
