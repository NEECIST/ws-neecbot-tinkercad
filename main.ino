#include<Servo.h>
Servo srv;
Servo srv1;
Servo control_servo;

const int distance_threshold = 100;
int motorSpeed;
int distance;
int left;
int right;

//Retorna a distância em centímetros ao  objeto
int measure(){
  digitalWrite(13, LOW);
  delay(100); 
  digitalWrite(13, HIGH);
  delay(100); 
  digitalWrite(13, LOW);
  int d=pulseIn(12,HIGH);
  d=d/29/2;
  return d;
}

void setup()
{
  //inicializar pins do sensor
  pinMode(13, OUTPUT);
  pinMode(12, INPUT);
  //inicializar pins dos servos
  srv.attach(7);
  srv1.attach(6);
  control_servo.attach(5);
}

void loop()
{
  control_servo.write(90);
  distance = measure();
  
  if(distance<=distance_threshold)
  {
    srv.write(93);
    srv1.write(93);
    control_servo.write(160);
    delay(3000);
    left = measure();

    control_servo.write(20);
    delay(3000);
    right = measure();

    if(right>=left){
      srv.write(120);
    }else{
      srv1.write(60);
    }
    delay(150);

  }else{
    motorSpeed = map(distance, distance_threshold, 334, 93,150 );
    srv.write(motorSpeed);
    srv1.write(180-motorSpeed);
  }
  delay(3000);
  delay(100);    
}
