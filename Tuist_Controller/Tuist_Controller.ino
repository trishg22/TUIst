//Packages
#include <Keypad.h>
#include <SoftwareSerial.h>
SoftwareSerial BTserial(0, 1);

//Variables
const byte ROWS = 4; // Four rows
const byte COLS = 3; // Three columns
//button pins & buttons that correspond to R,G,B, Y
const int buttonPin1 = 5; 
const int buttonPin2 = 4; 
const int buttonPin3 = 3; 
const int buttonPin4 = 2; 
int button1 = digitalRead(buttonPin1);
int button2 = digitalRead(buttonPin2);
int button3 = digitalRead(buttonPin3);
int button4 = digitalRead(buttonPin4);

int button[4]={button1,button2,button3,button4};//button array
int buttonPin[4]={buttonPin1,buttonPin2,buttonPin3,buttonPin4};
// Define the Keymap
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'#','0','*'}};
// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte rowPins[ROWS] = { 9, 8, 7, 6 };
// Connect keypad COL0, COL1 and COL2 to these Arduino pins.
byte colPins[COLS] = { 12, 11, 10 }; 

// Create the Keypad
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

#define ledpin 13

////***************
// Setup function 
//****************
void setup()
{
   pinMode(buttonPin, INPUT);//Creates a pin mode
   Serial.begin(9600);//Begins serial
   BTserial.begin(38400); //Begins bluetooth serial 
}


////***************
// loop function 
//****************
void loop(){
  
int state;//creates a variable that will determine what state the TUIst board is in

//IF statement that obtains a int, and passes the corresponding information to the board
 if (BTserial.available() > 0){//if Serial/data is available
  state = BTserial.parseInt();//state equals what was written to the serial
    Serial.println(state);//print that number
  if(state == 0){//if it is 0, get player number 
    getPlayerNumber();
      }
    if(state == 1) {//if state = 1, than get color from audience
        getColor();
        }

  }
}

 ////***********************
// getplayerNumber function 
//**************************
void getPlayerNumber(){
  int key = kpd.getKey();//gets the key that was pressed
  if(key)  // Check for a valid key.
  {
        Serial.println(key);//prints it to serial
         BTserial.write(key);//writes it to bluetooth seria;
    }
  
  }

////******************
// getColor function 
//******************
 void getColor(){

  //FOR loop that checks all the buttons
  for(int i = 0; i<4; i++){
  if((button[i]) == 1 && digitalRead(buttonPin[i]) == 0){//checks for a change in reading
    delay(500);//delays a half a second
    Serial.println(i+1);//than prints to the serial the correct button
    BTserial.write(i+1);//than prints to the bluetooth serial the correct button
    button[i] = 0;//sets the button number to 0
      }

 //Block of code similar to above except checks for change of button from 0 to 1     
   if((button[i]) == 0 && digitalRead(buttonPin[i]) == 1){
    delay(500);
    Serial.println(i+1);
    BTserial.write(i+1);
    button[i] = 1;
      }
    else{
      break;
    }
    }
  
  }

