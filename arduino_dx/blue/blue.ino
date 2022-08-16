
String myString = ""; //받는 문자열

void setup() {

  Serial3.begin(1000000);
  Serial1.begin(9600);
  pinMode(22, OUTPUT); // DIR HIGH로 맞춰 주었다 그래야 rs485통신이 가능하게 된다.
  digitalWrite(22, HIGH);
}


void loop()
{
  Serial.println(Serial1.available());
  while (Serial1.available()) //mySerial 값이 있으면
  {
    char myChar = (char)Serial1.read();  //mySerial int형식의 값을 char형식으로 변환
    myString += myChar; //수신되는 문자열을 myString에 모두 붙임 (1바이트씩 전송되는 것을 모두 붙임)
    delay(5);           //수신 문자열 끊김 방지
  }

    if (!myString.equals("")) //myString 값이 있다면
    {
      Serial.print("input value: "); //시리얼모니터에 myString값 출력
      Serial.println(myString); //시리얼모니터에 myString값 출력
    }
    
    if (myString == "on") //myString 값이 'on' 이라면
    {
      Serial.println("1");
      
      for (int i = 0; i <= 810; i = i + 10)
      {

        if (i <= 790) //790
        {
          temp_write(300, i);
          delay(100);
          temp_write1(300, i);
          delay(100);
        }

        else if (790 < i && i <= 800) //800
        {
          temp_write(300, 1000);
          delay(5000);
          temp_write1(300, 1000);
          delay(5000);
        }



        else if (i > 800) //810
        {
          for (int j = 1000; j > -1; j = j - 10)
          {
            temp_write(300, j);
            delay(100);
            temp_write1(300, j);
            delay(100);

          }
        }
      }
//      exit(0);
    myString="";
    }



    else
    {
      temp_write(300, 0);
            delay(100);
            temp_write1(300, 0);
            delay(100);
            myString="";
    }
  
}
//myString = ""; //myString 변수값 초기화





void temp_write(int Want_Angle, int Want_Speed) // H1, H2, Packet_ID, Len, Inst,address, P1,P2, CKSM
{

  digitalWrite(22, HIGH);

  int Header = 0xFF; //header매개변수

  int ID_Num = 0x02; //ID매개변수

  int Length; // Length = number of param +2 length 매개변수

  int Instruction = 0x03; //inst매개변수 = 0x03이므로 writ모드로 설정됨

  int Address = 0x20; // address매개변수 =  0x20이므로 프로토콜 32번 주소의 이동속도 모드 설정됨

  int Check_Sum; // Check_Sum = ~(ID + Length + Instruction + Param N)

  int Data_Length = 0x02; // Angle, Speed 2개  angle과 speed가 각각 두개로 나눠져 있어서 총 4개가 되므로 0x04이다

  int broadcastID = 0xFE;

  int Angle_MIN = 0, Angle_MAX = 1023; // 앵글 제한 AX-12A는 goal position이 0에서 1023 사이임
  int Speed_MIN = 0, Speed_MAX = 1023; // Moving Speed에서 JoinMode는 0~1023으로 사용가능, 단위가 0.111rpm임
  //int Speed_MIN = 1024, Speed_MAX = 2020;
  int Angle;
  int Speed;

  //Angle = map(Want_Angle, 0,300, Angle_MIN, Angle_MAX);//map(원하는각도,0~300까지를,0~1023으로 나눈다 즉 150을 입력하면 약 512의 값이 나오는 원리이다. )
  Speed = map(Want_Speed, 0, 1000, Speed_MIN, Speed_MAX);
  //Speed1 = map(Want_Speed, 0, 1000, Speed_MIN, Speed_MAX);

  Length = Data_Length + 3 ; //프로토콜에서 length를 확인해보면 알수 있다.

  Serial3.write(Header);
  //Serial1.write(Header);

  Serial3.write(Header);
  //Serial1.write(Header);

  Serial3.write(ID_Num);
  //Serial1.write(ID_Num);

  Serial3.write(Length);
  //Serial1.write(Length);

  Serial3.write(Instruction);
  //Serial1.write(Instruction);

  Serial3.write(Address);
  //Serial1.write(Address);

  //Serial1.write(Angle); //low bit
  //Serial1.write(Angle>>8); //high bit
  Serial3.write(Speed);
  //Serial1.write(Speed);

  Serial3.write(Speed >> 8);
  //Serial1.write(Speed >> 8);

  Check_Sum = (ID_Num + Length + Instruction + Address  + Speed + (Speed >> 8));

  Serial3.write(~(Check_Sum));
  //Serial1.write(~(Check_Sum));
}


void temp_write1(int Want_Angle, int Want_Speed) // H1, H2, Packet_ID, Len, Inst,address, P1,P2, CKSM
{

  digitalWrite(22, HIGH);

  int Header = 0xFF; //header매개변수

  int ID_Num = 0x01; //ID매개변수

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

  Serial3.write(Header);
  //Serial1.write(Header);

  Serial3.write(Header);
  //Serial1.write(Header);

  Serial3.write(ID_Num);
  //Serial1.write(ID_Num);

  Serial3.write(Length);
  //Serial1.write(Length);

  Serial3.write(Instruction);
  //Serial1.write(Instruction);

  Serial3.write(Address);
  //Serial1.write(Address);

  //Serial1.write(Angle); //low bit
  //Serial1.write(Angle>>8); //high bith
  Serial3.write(Speed);
  //Serial1.write(Speed);

  Serial3.write(Speed >> 8);
  //Serial1.write(Speed >> 8);

  Check_Sum = (ID_Num + Length + Instruction + Address  + Speed + (Speed >> 8));

  Serial3.write(~(Check_Sum));
  //Serial1.write(~(Check_Sum));


}
