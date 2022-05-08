FINAL CODE:

//1 = TEMPERATURE SENSOR
//2 = PULSE SENSOR
//3 = SMOKE SENSOR

//2
#define USE_ARDUINO_INTERRUPTS true
#include <PulseSensorPlayground.h>


// 1 
int ThermistorPin = 0;              
int Vo;
float R1 = 10000;
float logR2, R2, T, Tc, Tf;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

//2
const int PulseWire = 0;
const int LED13 = 13;
int Threshold = 550;
PulseSensorPlayground pulseSensor;

//3
int smokeA0=A0;
int buzzer =11;
float sensorValue;

void setup() {
        //3
        pinMode(buzzer,OUTPUT);
        pinMode(smokeA0,INPUT);

        //1,2,3
        Serial.begin(9600);

        //2
        pulseSensor.analogInput(PulseWire);   
        pulseSensor.blinkOnPulse(LED13);
        pulseSensor.setThreshold(Threshold);
        if (pulseSensor.begin()) {
                Serial.println("We created a pulseSensor Object !"); 
        }

        //3
        Serial.println("Gas sensor warming up!");
        delay(20000);
}

void loop() {
        //1
        Vo = analogRead(ThermistorPin);
        R2 = R1 * (1023.0 / (float)Vo - 1.0);
        logR2 = log(R2);
        T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
        Tc = T - 273.15;
        Serial.print("Temperature: "); 
        Serial.print(Tc);
        Serial.println(" C");  

        //2
        int myBPM = pulseSensor.getBeatsPerMinute();
        if (pulseSensor.sawStartOfBeat()) {
                Serial.println("♥  A HeartBeat Happened ! ");
                Serial.print("BPM: ");                        // Print phrase "BPM: " 
                Serial.println(myBPM);
        delay(500);
        }

        //3
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
}