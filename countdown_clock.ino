

const int stepsPerRevolution = 3200;
const int dirPin = 9; //direction of the motor
const int stepPin = 8; //speed 
const int limitSwitchPin = 2;
const int startButtonPin = 3;
const int resetButtonPin = 4;
const int buzzerPin = 5;




long currentStep = 0;
int state = 0; // 0 not started yet, 1  started, 3 finished
int second = 0;
int oldSecond =0;


const int CW = 1;
const int CCW = 0;

const int LED_1 = 20;  //Led second 1 
const int LED_2 = 21;  //Led second 2 
const int LED_3 = 22;  //Led second 3
const int LED_4 = 23;  //Led second 4
const int LED_5 = 24;  //Led second 5
const int LED_6 = 25;  //Led second 6
const int LED_7 = 26;  //Led second 7
const int LED_8 = 27;  //Led second 8
const int LED_9 = 28;  //Led second 9
const int LED_10 = 29;  //Led second 10
const int LED_11 = 30;  //Led second 11
const int LED_12 = 31;  //Led second 12
const int LED_13 = 32;  //Led second 13
const int LED_14 = 33;  //Led second 14
const int LED_15 = 34;  //Led second 15
const int LED_16 = 35;  //Led second 16
const int LED_17 = 36;  //Led second 17
const int LED_18 = 37;  //Led second 18
const int LED_19 = 38;  //Led second 19
const int LED_20 = 39;  //Led second 20
const int LED_21 = 40;  //Led second 21
const int LED_22 = 41;  //Led second 22
const int LED_23 = 42;  //Led second 23
const int LED_24 = 43;  //Led second 24
const int LED_25 = 44;  //Led second 25
const int LED_26 = 45;  //Led second 26
const int LED_27 = 46;  //Led second 27
const int LED_28 = 47;  //Led second 28
const int LED_29 = 48;  //Led second 29
const int LED_30 = 49;  //Led second 30

int lights[]  = { LED_1, LED_2, LED_3, LED_4, LED_5, LED_6, LED_7, LED_8, LED_9, LED_10, LED_11, LED_12, LED_13, LED_14, LED_15, LED_16, LED_17, LED_18, LED_19, LED_20, LED_21, LED_22, LED_23, LED_24, LED_25, LED_26, LED_27, LED_28, LED_29, LED_30};

void setup() {

  
  
  
  pinMode(limitSwitchPin, INPUT_PULLUP);
  pinMode(startButtonPin, INPUT_PULLUP);
  pinMode(resetButtonPin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);
  pinMode(LED_5, OUTPUT);
  pinMode(LED_6, OUTPUT);
  pinMode(LED_7, OUTPUT);
  pinMode(LED_8, OUTPUT);
  pinMode(LED_9, OUTPUT);
  pinMode(LED_10, OUTPUT);
  pinMode(LED_11, OUTPUT);
  pinMode(LED_12, OUTPUT);
  pinMode(LED_13, OUTPUT);
  pinMode(LED_14, OUTPUT);
  pinMode(LED_15, OUTPUT);
  pinMode(LED_16, OUTPUT);
  pinMode(LED_17, OUTPUT);
  pinMode(LED_18, OUTPUT);
  pinMode(LED_19, OUTPUT);
  pinMode(LED_20, OUTPUT);
  pinMode(LED_21, OUTPUT);
  pinMode(LED_22, OUTPUT);
  pinMode(LED_23, OUTPUT);
  pinMode(LED_24, OUTPUT);
  pinMode(LED_25, OUTPUT);
  pinMode(LED_26, OUTPUT);
  pinMode(LED_27, OUTPUT);
  pinMode(LED_28, OUTPUT);
  pinMode(LED_29, OUTPUT);
  pinMode(LED_30, OUTPUT);
  clearLights();
  digitalWrite(buzzerPin, LOW);
  Serial.begin(115200); // Initialize Serial communication
  

   Serial.println("Starting motor in reverse CCW...");
  // Start the motor in reverse CCW until it hits the limit switch
  while (digitalRead(resetButtonPin) == HIGH) {
   
  }

 
  while (digitalRead(limitSwitchPin) == HIGH) {
    delay(10);
    step(1, CCW, 1);
  }
  stopMotor();
  Serial.println("Limit switch hit.");

  // Stop the motor and wait for the start button
  Serial.println("Waiting for start button...");
 
}

  

int sec;

void loop() {
  //waiting for START
  
  if (state == 0) {
      if (digitalRead(startButtonPin) == LOW) {
          state=1;
          oldSecond=0;
          Serial.println("START!");     
      }
  }
  //running
  if (state == 1) {
      if (currentStep <= (stepsPerRevolution/2)) {
          
          step(1, CW, 1);
          delay(16);
          delayMicroseconds(600);
          second =  map(currentStep, 0, stepsPerRevolution/2, 0, 30);
          if (oldSecond != second ){
            oldSecond = second;
            
        
            Serial.print(" second: ");
            Serial.print(second);
            Serial.print(" curr step: ");
            Serial.print(currentStep);
            Serial.print(", milliseconds elapsed: ");
            Serial.println(millis());
            if (second){
              showLeds(second);
              shortBeep();
            }  
          }
          currentStep++;
          
      // the cycle has ended    
      } else {
          Serial.println("curr step 0");
          state =3;
          currentStep = 0;
          //longBeep();
          stopMotor();
          sos();
          
      } 
      
     
  }
  // waiting for reset
  if (state == 3) {
    if (digitalRead(resetButtonPin) == LOW) {
         
         Serial.println("RESET pressed!");
         currentStep = 0;
         clearLights();
         second=0;
         restart();
         state =0;
    }
    
  }   
}


void showLeds(int numLeds) {
  digitalWrite(lights[numLeds], LOW);
}

void restart(){
  Serial.print("Starting return: ");
  Serial.println(millis());
  step((stepsPerRevolution/2), CCW, 5);
  stopMotor();
  Serial.print("Returned: ");
  Serial.println(millis());
  longBeep();
}

void shortBeep(){
   digitalWrite(buzzerPin, HIGH);
   delay(1);
   digitalWrite(buzzerPin, LOW);
}
void longBeep(){
   digitalWrite(buzzerPin, HIGH);
   delay(100);
   digitalWrite(buzzerPin, LOW);
}
void longerBeep(){
   digitalWrite(buzzerPin, HIGH);
   delay(800);
   digitalWrite(buzzerPin, LOW);
}

void sos(){
  longBeep();
  delay(100);
  longBeep();
  delay(300);
  
  longBeep();
  delay(100);
  longBeep();
  delay(300);
//  
//  longBeep();
//  delay(50);
//  longBeep();
//  delay(50);
//  longBeep();
//  delay(100);
//  longBeep();
//  delay(400);
//  
//  longerBeep();
//  delay(100);
  
}

void stopMotor(){
  digitalWrite(stepPin, HIGH);
}

void step(int numStep, int dir, int addDelay){

      digitalWrite(dirPin, dir); // set direction attribute
      
      for (int x = 0; x < numStep; x++)
      {
        digitalWrite(stepPin, dir); 
        delay(addDelay);
        digitalWrite(stepPin,!dir); 
        delay(addDelay);
      }

}


void clearLights(){
  for (byte i = 0; i < 30; i = i + 1) { 
      digitalWrite(lights[i], HIGH);
  }
}
