/*
* Author: David Park, Park Huck Gu Se)
* Application: AutoBin (a.k.a Smart Trashcan)
* No Licesense 
* Contact: rjtp5670@gmail.com

The Autobin Project is designed for my school project (July 2, 2015) 
All the code is hard-coded designed for beginner coder in Electronics major or hobbyist.

What Needed:
- Geared Motor: RB-35GM
- Motor Drive: L298
- 3cell, Li-Po battery
- Controller: Arduino Uno
- Water Pump (Rated Voltage: 9 to 15V)
- 7805 Regulator
- Diode for reverse current prevention. 
- Sonar Sensor 
- IR Sensors 
- LM-35
- Bluetooth Module: HC-05. 
*/


// Pins 
int en = 13;
int reverse = 12;
int sonic =5;
int sonic2;

// Config Motor 
const int motor1=9;
const int motor2=10;

// Forward Dir
int motor_speed1=127;
int motor_speed2=127;

int sct = 0;
int sums = 0;
int avg = 0;

// Reverse Dir
int reverse_motor_speed1=127;
int reverse_motor_speed2=127;

// Sonar 
int echo =3;
int trig =4;
int sensor_led[4] ;

// IR (To detect all directions obstacles)
int new_check[4] = {0,0,0,0};
const int led[4]= { 14,15,16,17};

char sh='b';

void setup() {
  Serial.begin(9600);
  pinMode(motor1 , OUTPUT);
  pinMode(motor2 , OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(18,INPUT);
  pinMode(led[0],INPUT);
  pinMode(led[1],INPUT);
  pinMode(led[2],INPUT);
  pinMode(led[3],INPUT);
  pinMode(led[4],INPUT);
  pinMode(led[5],INPUT);
  pinMode(3,INPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  Serial.begin(9600);

}

void foward(){ 
  if(motor_speed2<=256 && motor_speed1<=256){
    motor_speed1 =150;
    motor_speed2 =150;
    delay(15);
    }
}
void left_1(){   
  if(motor_speed2<=255,motor_speed1<=255){
   motor_speed2 = 180;
   motor_speed1 = 100; 
   delay(15);
   } 
}

void left_2(){ 
  if(motor_speed2<=255,motor_speed1<=255){
    motor_speed2 = 180;
    motor_speed1 = 130; 
    delay(15);
    }
}

void left_3(){ 
  if(motor_speed2<=255,motor_speed1<=255){
    motor_speed2 = 255;
    motor_speed1 = 185; 
    delay(15);
    }
}

void left_4(){
 if(motor_speed2<=255,motor_speed1<=255){
    motor_speed2 = 200;
    motor_speed1 = 185; 
    delay(15);
    }
}

void right_1(){
  if(motor_speed2<=255,motor_speed1<=255){
    motor_speed1 = 180;
    motor_speed2 = 150; 
    delay(15);
    }
}

void right_2(){
  if(motor_speed2<=255,motor_speed1<=255){
    motor_speed1 = 200;
    motor_speed2 = 180; 
    delay(15);
    }
}

void right_3(){
  if(motor_speed2<=255,motor_speed1<=255){
    motor_speed1 = 255;
    motor_speed2 = 185;
    delay(15);
    }
}


void right_4(){
  if(motor_speed2<=255,motor_speed1<=255){ 
    motor_speed1 = 255; 
    motor_speed2 = 185; 
    delay(15);
    }
}


void right_5(){ 
  if(motor_speed2<=255,motor_speed1<=255){ 
    motor_speed1 = 255; //9
    motor_speed2 = 10;//10
    delay(15);
    }
}

void back(){
   analogWrite(reverse,150);
   digitalWrite(en,HIGH);
   digitalWrite(motor1,LOW);
   digitalWrite(motor2,LOW);
   Serial.println("back");
   Serial.println(motor_speed1);
   Serial.print("reverse : HIGH");
}

void turn(){
  motor_speed1=255;
  motor_speed2=10;
}

void STOP(){
  digitalWrite(en,LOW);
  motor_speed1= 0;
  motor_speed2= 0;
}

void blue_STOP( ){
  digitalWrite(en,LOW);
  Serial.println("given signal 'stop'");
  delay(5000);
  Serial.println( "go!"); 
}


void rando(){ 

  int rand = random(1,9);

  if(rand == 1){
    foward();
    Serial.println("forward");
    Serial.print(rand);
    Serial.println("");
    delay(500);
  }else if(rand == 2){
    left_1(); 
    Serial.println("left1");
    Serial.print(rand);
    Serial.println("");
    delay(300);
    }

  if(rand == 3){
    left_2();
    Serial.println("left2");
    Serial.print(rand);
    Serial.println("");
    delay(200);
  }

  if(rand == 4){
    foward();
    Serial.println("left3");
    Serial.print(rand);
    Serial.println("");
    delay(200);
  }

  if(rand == 5){
    right_1();
    Serial.println("right1");
    Serial.print(rand);
    Serial.println("");
    delay(200);
  }

  if(rand == 6){
    right_2();
    Serial.println("right2");
    Serial.print(rand);
    Serial.println("");
    delay(200);
  }

  if(rand == 7){
    foward(); 
    Serial.println("right3:");
    Serial.print(rand);
    Serial.println("");
    delay(200);
  }

  if(rand == 8){
    left_2(); 
    Serial.println("left2");
    Serial.print(rand);
    Serial.println("");
    delay(200);
  }

  if(rand == 9){
    right_1(); 
    Serial.println("right4");
    Serial.print(rand);
    Serial.println("");
    delay(200);
  }
}

void sensor_value(){
  digitalWrite(en,HIGH);
  digitalWrite(4,HIGH);
  delayMicroseconds(10);
  digitalWrite(4 ,LOW);

  int sonic_wave =  pulseIn(echo,HIGH)*17/1000;//sonic_speed = 340m/s therefore it is changed to 17*1000 because sonic sensor calculates the distance which is (340m/s) / 2 and trig have the microdelay
  int sums;
  int avg;
  int sct;
  
  if(sct <= 5){
    sums += sonic_wave;
    avg = sums/5;
    sct = 0;
    sums = 0;
  }else{
    sct++;
    sums += sonic_wave;
  }
  
  Serial.print("cm");
  Serial.println(sonic_wave);
  
  if(avg <=15){
    sonic2 = 1;
    Serial.println("AVG HIGH");
  }else{
    sonic2 = 0;
    Serial.println("AVG LOW");
  }

  if(sonic2 == 0  && new_check[1] == 0 && new_check[2] == 0 && new_check[3] == 0){
    foward();
    Serial.print ("0000");
    Serial.println("");
    delay(500);
    rando();
    Serial.println("random direction");
    delay(500);
  }else if(sonic2 == 0  && new_check[1] == 0 && new_check[2] == 0 && new_check[3] == 1){
    foward();
    Serial.print("foward 0001");
    Serial.println("");
    delay(400);
    left_2();
    delay(400);
    Serial.println("random direction after back"); 
  }else if(sonic2 == 0 && new_check[1] == 0 && new_check[2] == 1 && new_check[3] == 0){
    foward();
    delay(300);
    Serial.print ("foward0010");
    Serial.println("");
  }else if(sonic2 ==0 && new_check[1] == 0 && new_check[2] == 1 && new_check[3] == 1){
    foward();
    delay(300);
    Serial.println("random direction of 0011");
  }else if(sonic2 == 0 && new_check[1] == 1 && new_check[2] == 0 && new_check[3] == 0){
    foward();
    delay(400);
    right_2();
    Serial.println("0100 is right2 after foward");
    delay(200);
    rando();
    Serial.println("random direction of 0100");
  }else if(sonic2 == 0 && new_check[1] == 1 && new_check[2] == 0 && new_check[3] == 1){
    foward();
    delay(200);
    Serial.println("0101 and left2");
    delay(200); 
  }else if(sonic2 == 0 && new_check[1] == 1 && new_check[2] == 1 && new_check[3] == 0){
    foward();
    delay(300);
    Serial.println("0100 is foward");
  }else if(sonic2 == 0  && new_check[1] == 1 && new_check[2] == 1 && new_check[3] == 1){
    foward();
    Serial.println("0111 and foward");
    delay(300);
    rando();
    Serial.println("random direction of 0111");
  }else if(sonic2 == 1 && new_check[1] == 0 && new_check[2] == 0 && new_check[3] == 0){
    back();
    Serial.println("1000 ");
    delay(300);
    left_3();
    delay(300);  
    motor_speed2 = 200;
    motor_speed1 = 185; 
    Serial.println("random direction of 1000");
  }else if(  sonic2 == 1  && new_check[1] == 0 && new_check[2] == 0 && new_check[3] == 1){
    back();
    Serial.println("1001 and left2 ");
    delay(200);
    left_2();
    delay(200);
    rando();
    Serial.println("direction is rando after right3 ");
  }else if(  sonic2 == 1 && new_check[1] == 0 && new_check[2] == 1 && new_check[3] == 0){
    motor_speed1 = 255;
    motor_speed2= 20;
    delay(300);
    Serial.println("1010, right2 -> foward -> rando");
  }else if(  sonic2 ==1 && new_check[1] ==0 && new_check[2] == 1 && new_check[3] == 1){
    motor_speed1= 10;
    motor_speed2= 250;
    delay(200);
    Serial.println("1011 and left4 ->foward->rando ");
    rando();
  }else if(  sonic2 == 1 && new_check[1] == 1 && new_check[2] == 0 && new_check[3] == 0){
    turn();
    Serial.println("1100 turn ");
  }else if(  sonic2 == 1 && new_check[1] == 1 && new_check[2] == 0 && new_check[3] == 1){
    back();
    delay(400);
    turn();
    delay(300);
    left_3();
    Serial.println("1101 and right2->right3->rando");
  }else if(  sonic2 == 1  && new_check[1] == 1 && new_check[2] == 1 && new_check[3] == 0){
   motor_speed1 = 180;
   motor_speed2 = 100;
   delay(150);
   Serial.println("right->foward->left2->foward->rando 1110");
  }else if(  sonic2 == 1  && new_check[1] == 1 && new_check[2] == 1 && new_check[3] == 1){
   STOP();
   Serial.println("stop");
  }
  delay(1500);
}

void loop() { 
  Serial.println();
  digitalWrite(en,HIGH);
  digitalWrite(reverse,LOW);
  Serial.println("en:HIGH");
  
  if(reverse==LOW)
    Serial.print("reverse:LOW");
  
  Serial.println("");
  analogWrite(motor1,motor_speed1);
  analogWrite(motor2,motor_speed2);

  if(Serial.available()>0)
    sh=Serial.read();
 
  for(int i =0 ; i <=3 ; i++){
    sensor_led[i] = analogRead(led[i]);// sensor_led1 HIGH
    Serial.print("s");
    Serial.print(i + 1);
    Serial.print(" : ");
    analogWrite(motor1,motor_speed1);
    analogWrite(motor2,motor_speed2);
    
    if(sensor_led[i] > 200)
      new_check[i] = 0;
    else
      new_check[i] = 1;
  }

  Serial.println();
  
  if(sh == 'a'){
    blue_STOP();
    delay(500);
    sh='b';
    sensor_value();
  }

  if(sh=='c'){
    back();
    sh='b';
    delay(500);
  }

  if(new_check[0] ==HIGH){
  Serial.println("district out!! back  !! right now!");
  right_5();
  delay(100);
  }else
  sensor_value();
}
