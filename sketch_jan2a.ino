
#include <AFMotor.h>
struct allpin{
 const char* port;
 const  int number;
};
//----------------------
// Global variables 
const int outport = 8;
const int inport = 5;
const int analogport = 6;
const int delaytime = 1000;
int max_speed = 255;
int baudrate = 9600;
//--------------------------+
//                          +
// --->array declaration<-- +
//--------------------------+
allpin port[outport]{
  {"empty", 5}, //0
  {"empty", 12},//1
  {"warning_led", 13},//2
  {"trig", 3},//3
  {"alarm", 8},//4
  {"beem", 6},//5
  {"beem2", 9},//6
  {"Tx", 0}//7

};
//---------------------------
allpin port2[inport]{
  {"echo", 4},//0
  {"pir", 2},//1
  {"solarcharge", 7},//2
  {"Rx", 1}//3
};

allpin Analogport[analogport]{
   {"A1", A0},
   {"A2", A1},
   {"A3", A2},
   {"A4", A3},
   {"A5", A4},
   {"A6", A5}
};


AF_DCMotor left_forward(1);
AF_DCMotor left_backward(4);
AF_DCMotor right_forward(3);
AF_DCMotor right_backward(2);

void setup() {
  Serial.begin(9600);
  // Set the speed of both motors
  left_forward.setSpeed(max_speed);
  left_backward.setSpeed(max_speed);
  right_forward.setSpeed(max_speed);
  right_backward.setSpeed(max_speed);

  // Initialize the motors
  left_forward.run(RELEASE);
  left_backward.run(RELEASE);
  right_forward.run(RELEASE);
  right_backward.run(RELEASE);

  for(int i = 0; i <= outport; i++){
    pinMode(port[i].number, OUTPUT);
  }
  for(int j = 0; j <= inport; j++){
    pinMode(port2[j].number, INPUT);
  }
  
  // put your setup code here, to run once:

}

class Control{
  public:
  void forward(){
     left_forward.run(FORWARD);
     left_backward.run(FORWARD);
     right_forward.run(FORWARD);
     right_backward.run(FORWARD);
  }
  public:
  void backward(){
    left_forward.run(BACKWARD);
    left_backward.run(BACKWARD);
    right_forward.run(BACKWARD);
    right_backward.run(BACKWARD);
  }
  public:
  void right(){
     left_forward.run(FORWARD);
     left_backward.run(FORWARD);
     right_forward.run(BACKWARD);
     right_backward.run(BACKWARD);
  }
  public:
  void left(){
    left_forward.run(BACKWARD);
    left_backward.run(BACKWARD);
    right_forward.run(FORWARD);
    right_backward.run(FORWARD);
  }
  public:
  void stop(){
    left_forward.run(RELEASE);
    left_backward.run(RELEASE);
    right_forward.run(RELEASE);
    right_backward.run(RELEASE);
  }


};
//Control control;
class Robort: public  Control{
    public:
    void Serial_Com(){
       while (Serial.available() > 0) {
       // Read the incoming byte
       char incomingByte = Serial.read();
      // Check the value of the incoming byte
       switch (incomingByte) {
         case '0':
           forward();
          break;
        case '1':
           backward();
          break;
        case '2':
           stop();
          break;
        case '3':
           left();
          break;
        case '4':
           right();
          break;
        default:
          break;
     }
   }
 }  
};
Robort robort;
void loop() {
 
   
    
}
