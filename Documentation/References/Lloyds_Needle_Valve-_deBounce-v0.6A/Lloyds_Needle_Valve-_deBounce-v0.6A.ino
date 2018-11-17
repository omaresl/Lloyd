// Lloyd's attempt at controlling a stepper motor: 10/10/2016
//Extended by Eucyblues 
//deBounce Version v0.4 modified 19/10/16 - deBounceWaitTime added

// THIS IS FULL STEP - MAXIMUM TORQUE, good speed at 1400 uS delay



#include <PinChangeInt.h> // Many Pins Interrupt library
 
#define dirPin  8 //  dir pin from Arduino to easydriver
#define stepPin 9 // step pin from Arduino to easydriver

#define OpenButton 14   // connected to push button -internal pullup
#define CloseButton 15  // connected to push button - internal pullup
#define Home_Stop 10  // Pin 10 connected to limit switch 'Home'- internal pull up resistor
#define Limit_Stop 11 // Pin 11 connected to limit switch 'full open' - internal pull up resistor
// Note - Pin 2 connected to INT0, Pin 3 to INT1, Pins 10 and 11 attach to PinChangeInterupts through
// the PintChangeInt Library


//initialse and declare variables  
unsigned long LastValve_Update; 
int LastButtonState=LOW; 
byte deBounceCount = 0;  // the last time the output pin was toggled
byte deBounceDelay = 50;    // the deBounce time; increase if necessary 
byte deBounceWaitTime = 20; // wait time after interrupt before sampling to lockout glitches

// Set Button/Switch state variables and do an initial read
        
volatile int OpenButtonState = digitalRead(OpenButton); // high if not pressed, low if pressed
volatile int CloseButtonState = digitalRead (CloseButton); // ditto
volatile int Home_StopState = digitalRead (Home_Stop);  // Home_Stop switch closed - tied to ground - pullup resistor pulls high 
                           // when limit switch opens
volatile int Limit_StopState = digitalRead (Limit_Stop);  // Limit_Stop switch closed - tied to ground - pullup resistor pulls high 
                           // when limit switch opens                           

//*********Asyncronous stuff***************
typedef void (*GeneralFunction) ();

GeneralFunction doIntervalFunction();

void doIntervalFunction(GeneralFunction callBackFunction, unsigned long*lastEvent, unsigned long Interval); // prototype
void doIntervalFunction(GeneralFunction callBackFunction, unsigned long*lastEvent, unsigned long Interval) {
  unsigned long Now = millis();
  if ((Now - *lastEvent) >= Interval) {
    *lastEvent = Now;
    callBackFunction();
  }

}

void setup() {
 // Serial.begin (9600);
  pinMode(dirPin, OUTPUT);  // define inputs and outputs
  pinMode(stepPin, OUTPUT);
  pinMode(OpenButton, INPUT_PULLUP);
  pinMode (CloseButton, INPUT_PULLUP);
  pinMode(Home_Stop, INPUT_PULLUP);// Home is normally high, low when tripped - engage internal pullup 
  pinMode(Limit_Stop, INPUT_PULLUP);// Limit is normally high, low when tripped - engage internal pullup
 
 digitalWrite(dirPin, LOW); // initilize the outputs and set Low
 digitalWrite(stepPin, LOW);
 // Startup test to avoid spikes from the simultaneous startup of the motor and driver board setting off the motor
 // causes a lockout until the toggle switches are confirmed to be HIGH
    OpenButtonState = digitalRead(OpenButton);
    CloseButtonState = digitalRead(CloseButton);//read the switches

    while(CloseButtonState==LOW ||OpenButtonState ==LOW){
    //  Serial.println ("Button LOW condition detected");
    OpenButtonState = digitalRead(OpenButton);
    CloseButtonState = digitalRead(CloseButton);//read the switches again and test
   }
 
 // attach interrup functions to the start and stop buttons
// Serial.println ("Attaching Interrupts");
 attachPinChangeInterrupt(14, OpenButtonISR, CHANGE);
 attachPinChangeInterrupt(15, CloseButtonISR, CHANGE);
 
// attach interrup functions to the Home and Limit limit switches
  attachPinChangeInterrupt(10, Home_StopISR, CHANGE);
  attachPinChangeInterrupt(11, Limit_StopISR, CHANGE);
  
//Serial.println ("Interrupts Attached");


// Do an intitial read of the switch/button states to check status
  OpenButtonState = digitalRead(OpenButton);
  CloseButtonState = digitalRead (CloseButton);
  Home_StopState = digitalRead (Home_Stop);
  Limit_StopState = digitalRead (Limit_Stop);

  
//************Autohome routine**********************
// so above, we've just tested to make sure the toggle switch is OFF
// now we'll autohome if necessary

 // Serial.print("Autohoming ");
  
  Home_StopState - digitalRead(Home_Stop);
   // If Home_StopState == HIGH, the limit switch is 
   //untripped so the valve has stopped away from home
  
  while (Home_StopState==HIGH){//loop until limit switch trips or button released
  digitalWrite(dirPin, LOW); // direction pin HIGH is OPEN the Valve, LOW is CLOSE Valve
  digitalWrite(stepPin, HIGH); // to move motor we drive the Step high and low
  delayMicroseconds(650); // with a delay to allow the motor to move before the next signal
  digitalWrite(stepPin, LOW); // 'other half of the needed call to make the step
  delayMicroseconds(650); // delay to allow the motor to move before the next signal
  }  
  
//  Serial.println("Home reached");

 //***************************************************  
}
void loop() {
doIntervalFunction(CheckValve, &LastValve_Update, 50); // Asynch 1: read the Clock every 50msecs
  
 // NB  take out thise print routines and the delay fn when you've tested the sketch
  
//  Serial.print ("OpenButton = ");
//  Serial.print (OpenButtonState);
//  Serial.print (" / Limit_Stop = ");
//  Serial.println (Limit_StopState);
//  Serial.print ("CloseButton = ");
//  Serial.print (CloseButtonState);
//  Serial.print ("  /  Home_Stop = ");
//  Serial.println (Home_StopState);
//Serial.println ("*************************************");
//
//delay(1000);

}

void CheckValve(){
  
//  Serial.print ("OpenButton = ");
//  Serial.print (OpenButtonState);
//  Serial.print (" / Limit_Stop = ");
//  Serial.println (Limit_StopState);
//  Serial.print ("CloseButton = ");
//  Serial.print (CloseButtonState);
//  Serial.print ("  /  Home_Stop = ");
//  Serial.println (Home_StopState);
//Serial.println ("*************************************");

  Valve_Open();
  Valve_Close();
}

void Read_SwitchesISR(){
  OpenButtonState = digitalRead(OpenButton);
  CloseButtonState = digitalRead (CloseButton);
  Home_StopState = digitalRead (Home_Stop);
  Limit_StopState = digitalRead (Limit_Stop);
 
}

void OpenButtonISR(){
   OpenButtonState = digitalRead(OpenButton);//read the switch
  deBounceOpenButton();
 }
 
void CloseButtonISR(){
   CloseButtonState = digitalRead(CloseButton);//read the switch
  deBounceCloseButton();
 }
 void Home_StopISR(){
   Home_StopState = digitalRead(Home_Stop);//read the switch
  deBounceHome_Stop();
 }

 void Limit_StopISR(){
   Limit_StopState = digitalRead(Limit_Stop);//read the switch
  deBounceLimit_Stop();
 }
void Valve_Open(){
  
  //Serial.println ("In Valve_Open Loop");
  while (Limit_StopState==HIGH&& OpenButtonState==LOW){ //loop until limit switch trips or button released
  digitalWrite(dirPin, HIGH); // direction pin HIGH is OPEN the Valve, LOW is CLOSE Valve
  digitalWrite(stepPin, HIGH); // to move motor we drive the Step high and low
  delayMicroseconds(650); // with a delay to allow the motor to move before the next signal
  digitalWrite(stepPin, LOW); // 'other half of the needed call to make the step
  delayMicroseconds(650); // delay to allow the motor to move before the next signal

//  digitalWrite(dirPin, HIGH);//1
//  digitalWrite(stepPin, HIGH);
//  delayMicroseconds(250);
//  
//  digitalWrite(dirPin, LOW);//2
//  digitalWrite(stepPin, HIGH);
//  delayMicroseconds(250);
//  
//  digitalWrite(dirPin, LOW);//3
//  digitalWrite(stepPin, LOW);
//  delayMicroseconds(250);
//  
//  digitalWrite(dirPin, HIGH);//4
//  digitalWrite(stepPin, LOW);
//  delayMicroseconds(250);



  
  }
}
void Valve_Close(){
  //Serial.println ("In Valve_Close Loop");
   while (Home_StopState==HIGH&&CloseButtonState==LOW){//loop until limit switch trips or button released
  digitalWrite(dirPin, LOW); // direction pin HIGH is OPEN the Valve, LOW is CLOSE Valve
  digitalWrite(stepPin, HIGH); // to move motor we drive the Step high and low
  delayMicroseconds(650); // with a delay to allow the motor to move before the next signal
  digitalWrite(stepPin, LOW); // 'other half of the needed call to make the step
  delayMicroseconds(650); // delay to allow the motor to move before the next signal

//    digitalWrite(dirPin, HIGH);//1
//  digitalWrite(stepPin, LOW);
//  delayMicroseconds(250);
//
//  digitalWrite(dirPin, LOW);//2
//  digitalWrite(stepPin, LOW);
//  delayMicroseconds(250);
//
//  digitalWrite(dirPin, LOW);//3
//  digitalWrite(stepPin, HIGH);
//  delayMicroseconds(250);
//  
//  digitalWrite(dirPin, HIGH);//4
//  digitalWrite(stepPin, HIGH);
//  delayMicroseconds(250);

  
  }
}

void deBounceOpenButton(){
//  Serial.print ("  OpenButtonState = ");
//  Serial.print (OpenButtonState);
  delay(deBounceWaitTime); //wait some selectable msecs before sampling
  for ( deBounceCount=0; deBounceCount < deBounceDelay; deBounceCount++) {
  LastButtonState = digitalRead(OpenButton);//re-read the switch
 
//  Serial.print ("  / LastOpenButton = ");
//  Serial.print (LastButtonState);
//  Serial.print ("  / deBounce Count = ");
//  Serial.println (deBounceCount);
  
    if(LastButtonState != OpenButtonState){ // switch changed due to noise or pressing
      OpenButtonState=LastButtonState;  //swap readings
      deBounceCount = 0; // reset deBounce count - loops here until reading is stable
  }
  }
  // deBounce time has been exceeded so accept last stable value 
    OpenButtonState = LastButtonState;
    deBounceCount=0; //reset deBounce count
//  Serial.print ("Stable OpenButtonState = ");
//   Serial.println (OpenButtonState);
}
void deBounceCloseButton(){
//Serial.print ("  CloseButtonState = ");
//  Serial.print (CloseButtonState);
 // long start_time = micros();
  delay(deBounceWaitTime); //wait some selectable msecs before sampling
  for ( deBounceCount=0; deBounceCount < deBounceDelay; deBounceCount++) {
  LastButtonState = digitalRead(CloseButton);//re-read the switch
  
//  Serial.print ("  / LastCloseButton = ");
//  Serial.print (LastButtonState);
//  Serial.print ("  / deBounce Count = ");
//  Serial.println (deBounceCount);
  
    if(LastButtonState != CloseButtonState){ // switch changed due to noise or pressing
      CloseButtonState=LastButtonState;  //swap readings
    deBounceCount = 0; // reset deBounce count - loops here until reading is stable
  }
  }
  // deBounce time has been exceeded so accept last stable value 
    CloseButtonState = LastButtonState;
    deBounceCount=0; //reset deBounce count
 //   long duration = (micros()-start_time);
  //  Serial.println (duration);
 }
void deBounceLimit_Stop(){
//Serial.print ("  Limit_StopState = ");
//  Serial.print (Limit_StopState);
  delay(deBounceWaitTime); //wait some selectable msecs before sampling
  for ( deBounceCount=0; deBounceCount < deBounceDelay; deBounceCount++) {
  LastButtonState = digitalRead(Limit_Stop);//re-read the switch
  
//  Serial.print ("  / LastLimit_Stop = ");
//  Serial.print (LastButtonState);
//  Serial.print ("  / deBounce Count = ");
//  Serial.println (deBounceCount);
  
    if(LastButtonState != Limit_StopState){ // switch changed due to noise or pressing
      Limit_StopState = LastButtonState;  //swap readings
    deBounceCount = 0; // reset deBounce count - loops here until reading is stable
  }
  }
  // deBounce time has been exceeded so accept last stable value 
    Limit_StopState = LastButtonState;
    deBounceCount=0; //reset deBounce count
 }
void deBounceHome_Stop(){
//Serial.print ("  HomeStopState = ");
//  Serial.print (Home_StopState);
  delay(deBounceWaitTime); //wait some selectable msecs before sampling
  for ( deBounceCount=0; deBounceCount < deBounceDelay; deBounceCount++) {
  LastButtonState = digitalRead(Home_Stop);//re-read the switch
  
//  Serial.print ("  / LastButtonState = ");
//  Serial.print (LastButtonState);
//  Serial.print ("  / deBounce Count = ");
//  Serial.println (deBounceCount);
  
    if(LastButtonState != Home_StopState){ // switch changed due to noise or pressing
      Home_StopState=LastButtonState;  //swap readings
    deBounceCount = 0; // reset deBounce count - loops here until reading is stable
  }
  }
  // deBounce time has been exceeded so accept last stable value 
    Home_StopState = LastButtonState;
    deBounceCount=0; //reset deBounce count
  
}
