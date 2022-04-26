int ENA = 6; //Enable Pin of the Right Motor (must be PWM)
int IN1 = 0; //Control Pin
int IN2 = 1;

int ENB = 5; //Enable Pin of the Left Motor (must be PWM)
int IN3 = 2;
int IN4 = 3;

//Speed of the Motors
#define ENASpeed 90 
#define ENBSpeed 90

#define buzzer A1
#define bz A4



bool sensor1 = 0;
bool sensor2 = 0;
bool sensor3 = 0;
bool sensor4 = 0;
bool sensor5 = 0;

int pjcount=0;

void setup() {

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  pinMode(bz, 1);
  pinMode(gl, 1);

  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  pinMode(12, INPUT);

  //Use analogWrite to run motor at adjusted speed
  analogWrite(ENA, ENASpeed);
  analogWrite(ENB, ENBSpeed);

}

void sharp_right(){
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
}

void sharp_left(){
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}

void right(){
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
}

void left(){
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}

void straight(){
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    
}
void halt(){
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
}
void signalCheckpointFound(){
    pjcount++;
    digitalWrite(buzzer,1);
    delay(1000);
    digitalWrite(buzzer,0);
}
int status = 1;
int t_count = 0;

void loop() {
  sensor1 = digitalRead(7);
  sensor2 = digitalRead(8);
  sensor3 = digitalRead(9);
  sensor4 = digitalRead(10);
  sensorF = digitalRead(11);
  sensorB = digitalRead(13);
  sensorL = digitalRead(14);
  sensorR = digitalRead(15);

   if ((sensor1 == sensor4 == status && sensor2 == sensor3 == !status) ||
    (sensor1 == sensor4 == !status && sensor2 == sensor3 == status)){
     // Colors inverted
      status != status;
  }
  // if t_junction found
  else if (sensor1 == sensor2 == sensor3 == sensor4 == !status && sensor5 == status){
    // 3 is an arbitrary value
    // if (t_count == 3){
    //   sharp_right();
    // }
    t_count++;
  }
  else if((sensor1 == sensor2 == sensor3 == status  && sensor4==!status) || (sensor1 == sensor2==status && sensor3 == sensor4==!status)){
    
    sharp_right();
  }
  //left turn
  else if((sensor1==!status && sensor2==status && sensor3==!status && sensor4==status) || (sensor1 == sensor2 == !status && sensor3==sensor4==status)){
    sharp_left();
    } 
  
  //adjust right
  else if(sensor2==status && sensor3==!status){
    right();
  }
  //adjust left
  else if(sensor2==!status && sensor3==status){
    left();
  }
  //move straight
  else if(sensor2==status && sensor3==status){
    straight();
  }

  //check_point notif
  if(sensor1==sensor2==sensor3==sensor4==sensor5==status){
    signalCheckpointFound();
  }
}