int ENA = 5; //Enable Pin of the Right Motor (must be PWM)
int IN1 = 2; //Control Pin
int IN2 = 3;

int ENB = 6; //Enable Pin of the Left Motor (must be PWM)
int IN3 = 4;
int IN4 = 7;

//Speed of the Motors
#define ENASpeed 85
#define ENBSpeed 85

#define buzzer A1
#define bz A4


#define SENSOR1 7
#define SENSOR2 8
#define SENSOR3 9
#define SENSOR4 10
#define SENSORF 0
#define SENSORB 1
#define SENSORL 4
#define SENSORR 15

bool sensor1 = 0;
bool sensor2 = 0;
bool sensor3 = 0;
bool sensor4 = 0;
bool sensorL = 0;
bool sensorR = 0;
bool sensorF = 0;
bool sensorB = 0;
int pjcount=0;

void setup() {

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  pinMode(bz, 1);
  pinMode(buzzer, 1);

  //Use analogWrite to run motor at adjusted speed
  analogWrite(ENA, ENASpeed);
  analogWrite(ENB, ENBSpeed);

}

void sharp_right(){
    analogWrite(ENA, ENASpeed);
    analogWrite(ENB, ENBSpeed);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
}

void sharp_left(){
    analogWrite(ENA, ENASpeed);
    analogWrite(ENB, ENBSpeed);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}

void right(){
    analogWrite(ENA, ENASpeed);
    analogWrite(ENB, ENBSpeed / 2);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
}

void left(){
    analogWrite(ENA, ENASpeed / 2);
    analogWrite(ENB, ENBSpeed);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}

void straight(){
    analogWrite(ENA, ENASpeed);
    analogWrite(ENB, ENBSpeed);
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
int status = 1; // 1 for black 0 for white
int t_count = 0;
int plus_count = 0;
void loop() {
  sensor1 = digitalRead(8);
  sensor2 = digitalRead(9);
  sensor3 = digitalRead(10);
  sensor4 = digitalRead(11);
  sensorF = digitalRead(12);
  sensorB = digitalRead(13);
  sensorL = digitalRead(0);
  sensorR = digitalRead(1);

   if ((sensor1 == sensor4 && sensor4 == status && sensor2 == sensor3 && sensor3 == !status) ||
    (sensor1 == sensor4 && sensor4 == !status && sensor2 == sensor3 && sensor3 == status)){
     // Colors inverted
      status != status;
  }
  // if +_junction found
  else if (sensor1 == sensor2 && sensor2 == sensor3  && sensor3 == sensor4 && sensor4 == status && sensorF == sensorB && sensorB == status){
    // 3 is an arbitrary value
    if (plus_count == 0){
      straight();
    }
    plus_count++;
  }
  // if t_junction found
  else if (sensor1 == sensor2 && sensor2 == sensor3  && sensor3 == sensor4 && sensor4 == status && sensorF == !status){
    // 3 is an arbitrary value
    if (t_count == 0){
      sharp_left();
    }
    t_count++;
  }
  else if((sensor1 == sensor2 && sensor2 == sensor3 && sensor3 == status  && sensor4 == sensorF && sensorF == !status) ||
           (sensor1 == sensor2 && sensor2 == status && sensor3 == sensor4 && sensorF == sensor4 && sensor4 == !status)){
    
    sharp_right();
  }
  //left turn
  else if((sensor1==!status && sensor2==status && sensor3==!status && sensor4==status) || (sensor1 == sensor2 && sensor2 == !status && sensor3==sensor4 && sensor4 ==status)){
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
  else if(sensor2==status && sensor3==status && sensor1 == sensor4  && sensor4 == !status){
    straight();
  }

  //check_point notif
  else if(sensor1==sensor2 && sensor2 == sensor3 && sensor3 == sensor4 && sensor4 == sensorF && sensorF == status){
    signalCheckpointFound();
  }
}