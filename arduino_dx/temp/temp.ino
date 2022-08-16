void setup() {
  // put your setup code here, to run once:
  

}

void loop() {
  // put your main code here, to run repeatedly:
int seta1,seta2,Sin2,Cos2,K1,K2;


Cos2 = (((-14)*(-14))+(20*20)-(7*7)-(11*11))/(2*7*11);
Sin2 = sqrt(1-(Cos2*Cos2));

K1=7+(11*Cos2)*(20-(7))



seta2=atan2(Cos2,Sin2);
seta1 = atan2

Serial.println(seta2);
delay(5000);

  
 
}
