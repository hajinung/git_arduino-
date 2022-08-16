void setup() {
  // put your setup code here, to run once:

  Serial1.begin(1000000);
  pinMode(1,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned char Check_Sum,Header=0xFF;
  digitalWrite(1,Header);
  digitalWrite(1,Header);
  digitalWrite(1,0x02);      //id
  digitalWrite(1,0x05);      //length
  digitalWrite(1,0x03);      //instruction (write)
  digitalWrite(1,0x20);    //address
  digitalWrite(1,0x02);    //parameter
  digitalWrite(1,0x08);    //parameter
  Check_Sum = ~(0x02+0x05+0x03+0x20+0x02+0x08);
  digitalWrite(1,Check_Sum);    //cksm

}

/*void packet(unsigned int Angle1, unsigned int Angle2)
{
  unsigned char Check_Sum,Header=0xFF;
  digitalWrite(1,Header);
  digitalWrite(1,Header);
  digitalWrite(1,0x02);      //id
  digitalWrite(1,0x05);      //length
  digitalWrite(1,0x03);      //instruction (write)
  digitalWrite(1,0x20);    //address
  digitalWrite(1,Angle1);    //parameter
  digitalWrite(1,Angle2);    //parameter
  Check_Sum = ~(0x02+0x05+0x03+0x20+Angle1+Angle2);
  digitalWrite(1,Check_Sum);    //cksm
  
}*/
