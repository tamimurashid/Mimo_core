/***************************************************************************************************************************
******************************************************************************************************************+*********
+          +             +             __      +                                           ___________                +                                             
+          /\            /\           (__)     +        /\            /\           {{  /              \    }}.       +
+         /+ \          /+ \                   +       /  \          /  \             /      _____      \           +
+        / +  \        / +  \         |  |     +      /    \        /    \           |     /       \     |          +
+       / + +  \      /  + + \        |  |     +     /   +  \      /   +  \          |    |         |    |          +
+      / +    + \    / +    + \       |  |          /        \    /        \         |    |    ^    |    |          +
+     / + /  \ + \  / + / \  + \      |  |     +   /   /  \   \  /   / \    \        |    |         |    |          +
+    / + /    \ + \/ + /   \  + \     |  |        /   /    \   \/   /   \    \       |     \ _____ /     |          +
+   / + /      \  / + /     \  + \    |  |     + /   /      \  /   /     \    \       \                 /           +
+  / + /         / + /       \  + \   |  |      /   /         /   /       \    \       \   __________  /            +
+===========================================================================================================================
+ PROJECTNAME: MIMO SECURITY ROBORT;
+ FILENAME:    CORE FILE;
+ DESIGNER: TAMIMU SAID RASHID;                                                                                                               +
+ LANGUAGEUSED: C/C++; 
+ BOARD_TYPE:  ESP8266, UNO, NANO, PICO, MEGA; The code will comapatible to the mentioned board;                                                                                                                +
+ EMAIL:   rashidytamimu@gmail.com;                                                                                                                +
+ COMPANY:  talianRobotics;                                                                                                                +                                                                                                               +
+*************************************************************************************************************************
*/
// Header file
//--------------------------------+
#include <SoftwareSerial.h> 
              
//--------------------------------+
// -->structure for all pins<-----+
//--------------------------------+
struct allpin{
 const char* port;
 const  int number;
};
//----------------------
const int outport = 8;
const int inport = 5;
const int analogport = 6;
const int delaytime = 1000;
//--------------------------+
//                          +
// --->array declaration<-- +
//--------------------------+
allpin port[outport]{
  {"motor1", 3},
  {"motor2", 12},
  {"led_charge", 13},
  {"trig", 5},
  {"alarm", 8},
  {"nightlight", 6},
  {"warnig_led", 9},
  {"Tx", 0}

};
//---------------------------
allpin port2[inport]{
  {"echo", 4},
  {"pir", 2},
  {"solarcharge", 7},
  {"Rx", 1}
};
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
allpin Analogport[analogport]{
   {"A1", A0},
   {"A2", A1},
   {"A3", A2},
   {"A4", A3},
   {"A5", A4},
   {"A6", A5}
};
SoftwareSerial sim800l(port[7].number, port2[3].number); 
const char* phoneNumbers[] = {
  "+255621351603", 
  "+255768857064" // add another numbers 
};
int numPhoneNumbers = sizeof(phoneNumbers) / sizeof(phoneNumbers[0]);

// Variable to hold the message content
char message[100];
//---------------------------+
//     Make it simple        +   
//.                          +
// ---->functions<-----------+ 
int  distance(){
  long duration, distance;

  // Clear the trigger pin
  digitalWrite(port[3].number, LOW);
  delayMicroseconds(2);

  // Send a 10 microsecond pulse to trigger the sensor
  digitalWrite(port[3].number, HIGH);
  delayMicroseconds(10);
  digitalWrite(port[3].number, LOW);

  // Read the echo pin, and calculate the duration of the pulse in microseconds
  duration = pulseIn(port2[0].number, HIGH);

  // Calculate the distance in centimeters
  distance = duration * 0.034 / 2;

  // Print the distance to the serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  Serial.println("-----------");
  delay(100);
   return distance;
}
//-------> End of distance function<--------  
int motor_control_F(int motor_delay){
    digitalWrite(port[0].number, HIGH);
    digitalWrite(port[1].number, LOW);
    delay(motor_delay);
}
int motor_control_B(int motor_delay){
    digitalWrite(port[1].number, HIGH);
    digitalWrite(port[0].number, LOW);
    delay(motor_delay);
}
int motor_control_S(int motor_delay){
    digitalWrite(port[1].number, LOW);
    digitalWrite(port[0].number, LOW);
    delay(motor_delay);
}


void solar_input(){
  int anasolarRead = analogRead(Analogport[0].number);
  
  float voltage = anasolarRead  * (5.0 / 1023.0);
  if(voltage >= 0.5){
     digitalWrite(port[2].number, HIGH); digitalWrite(port[5].number,LOW);
     Serial.println("STATUS: CHARGING");
     // other function here 
  }
  else if(voltage < 0.5){
    digitalWrite(port[2].number,LOW);
    digitalWrite(port[5].number,HIGH);
    Serial.println("STATUS: NOT CHARGING");
  }
  Serial.println("----------");
  Serial.print("Voltage: ");
  Serial.print(voltage);
  Serial.println(" V ");
  delay(1000);
}
int Solar_Control(){
  int anasolarRead = analogRead(Analogport[0].number);
  
  float voltage = anasolarRead  * (5.0 / 1023.0);

  // Print the voltage value to the serial monitor
  Serial.println("----------");
  Serial.print("Voltage: ");
  Serial.print(voltage);
  Serial.println(" V ");
  return voltage;

}
bool Rain_sensor(){
    // rain check 
  digitalWrite(port[2].number, HIGH);
  int outdata = analogRead(Analogport[2].number);
  float newdata = outdata * (5.0 / 1023.0);
  Serial.print(newdata);
  if(newdata >= 1 && newdata < 3){
    Serial.println("==========");
    Serial.println("-->Rain detected ");
    Serial.println("==========");
    smsSend("Hi it seems there is the precence of rain fall");
  }
  else if(newdata >= 3){
    Serial.println("==========");
    Serial.println("-->Rain detected ");
    Serial.println("==========");
    smsSend("It seems there is huge rain fall, to see sequence of value visit the app or website");
  }
  return newdata;
}
void weather_check(){
  int Voltage = Solar_Control();
  if(Voltage > 1.5/* this value to be changed*/){
    Serial.println("--> Sunny<-------");

  }
  else if(Voltage < 1.5/* this value to be changed*/){
     
     Serial.println("------>No sun<-------");
  }
  Rain_sensor();
}
int  power_system(){
   int AnasolarRead = analogRead(Analogport[1].number);
   int error_value = 0.15; 
   float b_voltage = AnasolarRead  * (5.0 / 1023.0) + error_value;
   if( b_voltage >= 4.0){
    Serial.println("------------>battery full.");
    alarmSound(1000, 1000);
   }
   else if( b_voltage < 4.0 &&   b_voltage > 3.0){
    Serial.println("------------>Medium charge.");
   }
   else if(b_voltage < 1.5){
    Serial.println("------------->Battery low .");
    digitalWrite(port[6].number, HIGH);
    delay(delaytime);
    digitalWrite(port[6].number, LOW);
    delay(delaytime);
    alarmSound(1000, 500);
    smsSend("Low battery to the robort ");
   }
   else{
    Serial.println("------------->There is an error with the battery or battery not connected .");
    alarmSound(1000, 100);
   }
   Serial.println("----------");
   Serial.print("--------------->Power Voltage: ");
   Serial.print(b_voltage);
   Serial.println(" V ");
   Serial.println("----------");
   return b_voltage;
}
int power_saver(){
  int powercheck = power_system();
  if(powercheck >= 1.5){
    // runs some 
    weather_check();
     solar_input();
   
  }
  else if(powercheck < 1.5){
   alarmSound(1000, 500);
    smsSend("Low battery to the robort ");
    smsSend("Automatic power saving mode enabled" );

  }
}
//-----------------------
int SerialController(){
  


}
//----------------------
bool motion(){
  int sensorValue = digitalRead(port2[1].number);
   if(sensorValue==LOW){
      Serial.println("no Object");
     delay(500);
     digitalWrite(port[2].number, HIGH);
    }
  else
     {
     Serial.println("Object Detected");
     delay(500);
     digitalWrite(port[2].number, LOW);
    }

  }
//---------------------------------------------------------
//-------------->do not touch this part<------------------- 
//---------------------------------------------------------
void sendSMS(const char* phoneNumber, const char* message) {
  sim800l.print("AT+CMGS=\"");
  sim800l.print(phoneNumber);
  sim800l.println("\"");
  delay(1000);
  sim800l.print(message);
  sim800l.write(26); // End the SMS with Ctrl+Z
  delay(1000);
  while (sim800l.available()) {
    Serial.write(sim800l.read());
  }
}

void smsSend(const char* customMessage ) {
  // Send SMS to each phone number in the array
  for (int i = 0; i < numPhoneNumbers; i++) {
    sendSMS(phoneNumbers[i], customMessage);
    delay(5000); // Delay between SMS messages
  }
}
void readSMS() {
  sim800l.println("AT+CMGR=1"); // Read the first SMS in the inbox
  delay(1000);
  while (sim800l.available()) {
    const char* readsms = sim800l.read();
    Serial.write(sim800l.read());
    return readsms;
  }
}
int alarmSound(int frequency, int  delay_time){
  // Generate a loud alarm tone
  tone(port[4].number, frequency); // Set the frequency to 1000 Hz
  delay(delay_time);            // Tone duration
  noTone(port[4].number);     // Turn off the tone
  delay(delay_time);            // Pause before the next tone
}
//------------------------------------
//------->default functions<----------
void setup(){
   for(int i= 0; i < outport; i++ ){
    pinMode(port[i].number, OUTPUT);

  }
  for(int j = 0; j < inport; j++){
    pinMode(port2[j].number, INPUT);
  }
  for(int c = 0; c < analogport; c++){
    pinMode(Analogport[c].number, INPUT);
  }
  Serial.begin(9600);
  sim800l.begin(9600);  // Start communication with the SIM800L module
  delay(1000);          // Wait for SIM800L to initialize
  Serial.println("Initializing...");

  // Set SMS mode to text
  sim800l.println("AT+CMGF=1");
  delay(1000);
  while (sim800l.available()) {
    Serial.write(sim800l.read());
  }
  // motion should run once
  
   if(motion()){
      motor_control_F(1000);
      motor_control_S(1000);
      motor_control_B(1000);
   }
  }
 
void loop(){
  //power_system();
  solar_input();
  
  //power_saver();
   
   
   // check if object is close and make alarm 
  //  int distances = distance();
  //  if(distance < 30){
  //   alarmSound(1000, 10);
  //  }
  //  else if( distances  < 50 && distance > 30 ){
  //    alarmSound(1000, 150);

  //  }
  //  else if(distances < 100 && distances > 50){
  //    alarmSound(1000, 250);

  //  }
  //  else{
     
  //  }
   

}
  
