int buzzer =11;

int ThermistorPin = 5;
int Vo;
float R1 = 10000;
float logR2, R2, T, Tc, Tf;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

int smokeA0=A0;
float sensorValue;

const int trigPin = 9;
const int echoPin = 10;
long duration;
int distance;
int safetyDistance;

int PulseSensorPurplePin = 3;
int Signal;               
int Threshold = 500;

void setup() {
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  pinMode(buzzer,OUTPUT);
  pinMode(smokeA0,INPUT);
  Serial.begin(9600); 
  Serial.println("Gas sensor warming up!");
  //delay(20000); // allow the MQ-6 to warm up
  noTone(buzzer); 
}

void loop() {
  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  Tc = T - 278.15;
  Serial.print("Temperature: "); 
  Serial.print(Tc);
  Serial.println(" C");   
  if(Tc > 30){
    tone(buzzer,1000,200);
  }
  else{
    noTone(buzzer);
  }
  delay(500);

  sensorValue=analogRead(smokeA0);
  if(sensorValue > 100){
    Serial.print(" | Smoke detected!");
    tone(buzzer,1000,200);
  }
  else{
    Serial.print(" | Smoke  not detected!");
    noTone(buzzer);
   
  }
  delay(2000);

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance= duration*0.034/2;
  safetyDistance = distance;
  if (safetyDistance >= 25){
    digitalWrite(buzzer, HIGH);
  }
  else{
    digitalWrite(buzzer, LOW);
  }
  //Serial.print("Distance: ");
  //Serial.println(distance);
  delay(1000);

  Signal = analogRead(PulseSensorPurplePin);
  Serial.println(Signal);
  if(Signal > Threshold){                          
    noTone(buzzer);
  } 
  else{
    tone(buzzer,1000,200);       
  }
  delay(800);
  
}
