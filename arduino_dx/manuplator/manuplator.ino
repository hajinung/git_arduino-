String myString = "";
void setup() {
  // put your setup code here, to run once:

  Serial3.begin(1000000);
  Serial1.begin(9600);
  pinMode(22, OUTPUT);
  digitalWrite(22, HIGH);

}



double cos(double x, int termCount)
{

    if (x < 0) return cos(-x, termCount);

    //while (x >= 2 * PI) x -= 2 * PI; // x가 2파이 이상일때, x=x-2파이 2파이 안에서만 계산되게끔

    double currentTerm = 1;
    double estimated = currentTerm;
    for (int n = 1; n < termCount; n++)
    {
        currentTerm = currentTerm * ( -x * x / (2 * n * (2 * n - 1))); //a*=b ->a=a*b //다음항을 만들어줌
                                                       //c=c*(-x * x / (2 * n * (2 * n - 1))
        estimated += currentTerm;  //e=e+c
    }
    return 50*(estimated+1); //sin함수의 결과값
}


void loop() 
{
  // put your main code here, to run repeatedly:

  Serial.println(Serial1.available()); // 블루투스의 신호를 받지 못하면 0 받으면 1
  while (Serial1.available()) //mySerial 값이 있으면
  {
    char myChar = (char)Serial1.read();  //mySerial int형식의 값을 char형식으로 변환
    myString += myChar; //수신되는 문자열을 myString에 모두 붙임 (1바이트씩 전송되는 것을 모두 붙임)
    delay(5);           //수신 문자열 끊김 방지
  }
  if (!myString.equals("")) //myString 값이 있다면
  {
    Serial.println("input value: " + myString); //시리얼모니터에 myString값 출력
    //Serial.println(myString); //시리얼모니터에 myString값 출력


    if (myString == "w") //앞으로 전진
    {
      Serial.println("1");
      for(double i = 3.15; i<4.7; i=i+0.01) //0~50
      {
        
        double result1 =( cos(i,15)+51); //오른쪽 보라색 1번 50~100
        double result = cos(i,15); //왼쪽 초록색 2번 0~50
       temp_write(result1, result);
       delay(10);
       Serial.println(result1);
       Serial.println(result);       
       
      }
      Serial.end();
      

     
    }
  


    else if (myString == "s") //뒤로 후진
    {
      for(double i = 3.15; i<4.7; i=i+0.01) //0~50
      {
        
        double result1 =( cos(i,15)+51); //오른쪽 보라색 1번 50~100
        double result = cos(i,15); //왼쪽 초록색 2번 0~50
       temp_write(result, result1);
       delay(10);
       Serial.println(result1);
       Serial.println(result);       
       
      }
      Serial.end();
      
       
        
    }

    else if (myString == "a") //왼쪽으로 회전
    {
      temp_write(75, 75);
      
      Serial.println("a");
       
      
        
    }
    
    else if (myString == "d") //오른쪽으로 회전
    {
      temp_write(25, 25);
      
      Serial.println("d");
       
        
    }

    else if (myString == "t") //오른쪽으로 회전
    {
      temp_write(0, 0);
      
      Serial.println("t");
    }

    else if (myString == "8") //매뉴플레이터 수직
    {
      mani(50,5 ,50,5, 50,5, 50,5, 50,5);
      
      Serial.println("매뉴플레이터 수직 모드");
      delay(1000);
       
    }
    
     else if (myString == "6") //매뉴플레이터 수직
    {
      mani(50,5 ,85,5, 85,5, 85,5, 50,5);
      
      Serial.println("매뉴플레이터 직선 모드");
      delay(1000);
       
    }

    else if (myString == "4") //매뉴플레이터 수직
    {
      mani(50,5 ,15,5, 15,5, 15,5, 50,5);
      
      Serial.println("매뉴플레이터 직선 모드");
      delay(1000);
       
    }

    else if (myString == "2") //매뉴플레이터 수직
    {
      mani(50,5 ,100,5, 100,5, 0,5, 50,5);
      
      Serial.println("매뉴플레이터 직선 모드");
      delay(1000);
       
    }
       
        
    
   

  }
  myString = ""; //myString 변수값 초기화

}


  


void temp_write(double want1_speed, double want2_speed)
{
    digitalWrite(22, HIGH);
  
    int Header = 0xFF; //header매개변수

    int packitID = 0xFE;

    int Length; // Length = number of param +2 length 매개변수

    int Instruction = 0x83; //inst매개변수 = 0x03이므로 writ모드로 설정됨

    int Address = 0x20; // address매개변수 =  0x20이므로 프로토콜 32번 주소의 이동속도 모드 설정됨

    int Check_Sum; // Check_Sum = ~(ID + Length + Instruction + Param N)

    int Data_Length = 0x02; // Angle, Speed 2개  angle과 speed가 각각 두개로 나눠져 있어서 총 4개가 되므로 0x04이다

    int Motor1_ID = 0x01;

    int Motor2_ID = 0x02;

    int Xel_Nums = 2;

    int broadcastID = 0xFE;

    int Speed1_MIN = 0, Speed1_MAX = 2047;

    int Speed1;

    Speed1 = map(want1_speed, 0, 100, Speed1_MIN, Speed1_MAX );
    
    int Speed2_MIN = 0, Speed2_MAX = 2047;

    int Speed2;
    
    Speed2 = map(want2_speed, 0, 100, Speed2_MIN, Speed2_MAX); 

    Serial3.write(Header);
 
    Serial3.write(Header);

    Serial3.write(packitID);

    Length = ((Data_Length+1)*Xel_Nums)+4; 
    
    
    Serial3.write(Length);

    Serial3.write(Instruction);

    Serial3.write(Address); // P1

    Serial3.write(Data_Length); //P2

    Serial3.write(Motor1_ID); //P3

    Serial3.write(Speed1); //P4

    Serial3.write(Speed1 >> 8); //P5

    Serial3.write(Motor2_ID); //P6

    Serial3.write(Speed2); //P7

    Serial3.write(Speed2 >> 8); //P8

    Check_Sum = (packitID + Length + Instruction + Address  + Data_Length + Motor1_ID + Speed1 + (Speed1 >> 8)+ Motor2_ID + Speed2 + (Speed2 >> 8) );

    Serial3.write(~(Check_Sum));
  }

 //----------------------------------------------------------------------------------------------------------------------------------------------------------

  void mani(int ID3_angle, int ID3_speed , int ID4_angle, int ID4_speed ,int ID5_angle, int ID5_speed ,int ID6_angle, int ID6_speed ,int ID7_angle, int ID7_speed )
{
    digitalWrite(22, HIGH);
  
    int Header = 0xFF; //header매개변수

    int packitID = 0xFE;

    int Length; // Length = number of param +2 length 매개변수

    int Instruction = 0x83; //inst매개변수 = 0x03이므로 writ모드로 설정됨

    int Address = 0x1E; // address매개변수 =  0x20이므로 프로토콜 32번 주소의 이동속도 모드 설정됨

    int Check_Sum; // Check_Sum = ~(ID + Length + Instruction + Param N)

    int Data_Length = 0x04; // Angle, Speed 2개  angle과 speed가 각각 두개로 나눠져 있어서 총 4개가 되므로 0x04이다

    int Motor3_ID = 0x03;
    int Motor4_ID = 0x04;
    int Motor5_ID = 0x05;
    int Motor6_ID = 0x06;
    int Motor7_ID = 0x07;

    int Xel_Nums = 5;

    int broadcastID = 0xFE;

    int angle_MIN = 327, angle_MAX = 3921;
    int Speed2_MIN = 0, Speed2_MAX = 1023;

    int angle3,Speed3,angle4,Speed4,angle5,Speed5,angle6,Speed6,angle7,Speed7;
    
    
    angle3 = map(ID3_angle, 0, 100, angle_MIN, angle_MAX );
    Speed3 = map(ID3_speed, 0, 100, Speed2_MIN, Speed2_MAX); 

    angle4 = map(ID4_angle, 0, 100, angle_MIN, angle_MAX );
    Speed4 = map(ID4_speed, 0, 100, Speed2_MIN, Speed2_MAX); 

    angle5 = map(ID5_angle, 0, 100, angle_MIN, angle_MAX );
    Speed5 = map(ID5_speed, 0, 100, Speed2_MIN, Speed2_MAX); 

    angle6 = map(ID6_angle, 0, 100, angle_MIN, angle_MAX );
    Speed6 = map(ID6_speed, 0, 100, Speed2_MIN, Speed2_MAX); 

    angle7 = map(ID7_angle, 0, 100, angle_MIN, angle_MAX );
    Speed7 = map(ID7_speed, 0, 100, Speed2_MIN, Speed2_MAX); 

    

    Serial3.write(Header);
 
    Serial3.write(Header);

    Serial3.write(packitID);

    Length = ((Data_Length+1)*Xel_Nums)+4; 
    
    
    Serial3.write(Length);

    Serial3.write(Instruction);

    Serial3.write(Address); // P1

    Serial3.write(Data_Length); //P2

    Serial3.write(Motor3_ID); //P3
    Serial3.write(angle3); //P4
    Serial3.write(angle3 >> 8); //P5
    Serial3.write(Speed3); //P6
    Serial3.write(Speed3 >> 8); //P7
    


    Serial3.write(Motor4_ID); //P8
    Serial3.write(angle4); //P9
    Serial3.write(angle4 >> 8); //P10
    Serial3.write(Speed4); //P11
    Serial3.write(Speed4 >> 8); //P12
    

    Serial3.write(Motor5_ID); //P13
    Serial3.write(angle5); //P14
    Serial3.write(angle5 >> 8); //P15
    Serial3.write(Speed5); //P16
    Serial3.write(Speed5 >> 8); //P17


    Serial3.write(Motor6_ID); //P18
    Serial3.write(angle6); //P19
    Serial3.write(angle6 >> 8); //P20
    Serial3.write(Speed6); //P21
    Serial3.write(Speed6 >> 8); //P22


    Serial3.write(Motor7_ID); //P23
    Serial3.write(angle7); //P24
    Serial3.write(angle7 >> 8); //P25
    Serial3.write(Speed7); //P26
    Serial3.write(Speed7 >> 8); //P27

    Check_Sum = (packitID + Length + Instruction + Address  + Data_Length + Motor3_ID + angle3 + (angle3 >> 8) + Speed3 + (Speed3 >> 8)+ Motor4_ID + angle4 + (angle4 >> 8) + Speed4 + (Speed4 >> 8)+Motor5_ID + angle5 + (angle5 >> 8) + Speed5+ (Speed5 >> 8)+Motor6_ID + angle6 + (angle6 >> 8) + Speed6 + (Speed6 >> 8)+Motor7_ID + angle7 + (angle7 >> 8) + Speed7 + (Speed7 >> 8) );

    Serial3.write(~(Check_Sum));
    
    return ;
  }
