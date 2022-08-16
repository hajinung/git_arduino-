void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  double x,y,x2,y2,B,L,c,a,a1,a2,z,z1,SinB,CosB,SinA2,CosA2;
  x=14;
  y=12;
  y2=y;
  x2=x-7;
  L=sqrt((x2*x2)+(y2*y2));
  Serial.println(L);
  //B=acos((49+121-L*L)/(2*7*11));
  //B = 180/PI * B;
  CosB=(49+121-L*L)/(2*7*11);
  SinB=sqrt(abs(1-(CosB*CosB)));;
  B=atan2(SinB,CosB);
  B = 180/PI * B;
  Serial.println(B);

  //a2=acos((121+L*L-49)/(2*L*11));
  CosA2=(121+L*L-49)/(2*L*11);
  SinA2=sqrt(abs(1-(CosA2*CosA2)));
  a2=atan2(SinA2,CosA2);
  a2 = 180/PI * a2;
  Serial.println(a2);
  a1=acos(y/L);
  a1 = 180/PI * a1;
  Serial.println(a1);
  a=a1+a2;
  Serial.println(a);
  c=270-a-B;
  Serial.println(c);


  
  

  



  delay(5000);
  
  
}
