 void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

 

}

void loop() {
  // put your main code here, to run repeatedly:
  
  double x,y;
   x=(7*cos(radians(125)))+(11*cos(radians(125)))+(7*cos(radians(125)));
   y=(7*sin(radians(125)))+(11*sin(radians(125)))+(7*sin(radians(125)));

   

   Serial.println(x);
   Serial.println(y);
   delay(5000);
}
