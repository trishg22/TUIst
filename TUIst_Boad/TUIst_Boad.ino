//Packages 
#include <CircularBuffer.h>
#include <Entropy.h>
#include <Adafruit_NeoPixel.h>
//NeoPixels pins
#define PIN 9
#define PIN2 10
#include <SoftwareSerial.h>
SoftwareSerial BTserial(0, 1);
CircularBuffer<int, 100> playerList;
//Variables
 bool currentPlayerMoved = false;//current player checker
\\Sensors
const int PIEZO_1 = A0; // Piezo output
const int PIEZO_2 = A1;
const int PIEZO_3 = A2;
const int PIEZO_4 = A3;
const int PIEZO_5 = A4;
const int PIEZO_6 = A5;
const int PIEZO_7 = A6;
const int PIEZO_8 = A7;
const int PIEZO_9 = A8;
const int PIEZO_10 = A9;
const int PIEZO_11 = A10;
const int PIEZO_12 = A11;
bool colorChanged;//Color change checker
int finalColor;//Sets the final color to be matched
char winner = false;//Checks if the player has won the game
int colors[] = {1, 2, 3, 4};//Array for colors 1=red, ect..
int spot[12];//Creates a spot array
//char array that contains all the sensors
char sensor[] = {PIEZO_1, PIEZO_2, PIEZO_3, PIEZO_4, PIEZO_5, PIEZO_6,
                 PIEZO_7, PIEZO_8, PIEZO_9, PIEZO_10, PIEZO_11, PIEZO_12
                };
//Sets up neopixels strips
Adafruit_NeoPixel strip = Adafruit_NeoPixel(4, PIN, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(2, PIN2, NEO_RGB + NEO_KHZ800);
////***************
// Setup function 
//****************
void setup() {
//Begins Serial at 9600 Baudrate and a bluetooth serial at 384000
  Serial.begin(9600);
  BTserial.begin(38400);  
  Entropy.initialize();//Initialiazes Entropy for random class

  strip.begin();//sets up strips
  strip.show(); // Initialize all pixels to 'off'

  strip2.begin();
  strip2.show(); 

  rainbow(20);//Flashes rainbow patterns, we will add a loop that calls this function until game starts

  //Setp us a random color to all he spots
  for (int i = 0; i < 12; i = i + 1) {
    spot[i] = Entropy.random(1, 5);q

//Sets the color based off the randomly assigned number, and 
//prints to the serial the color
    if (spot[i] == 1) {
      Serial.println("red");
      delay(500);
      setRed(i);
    } if (spot[i] == 2) {
      Serial.println("green");
      delay(500);
      setGreen(i);
    } if (spot[i] == 3) {
      setBlue(i);
      delay(500);
      Serial.println("blue");
    } if (spot[i] == 4) {
      setYellow(i);
      delay(500);
      Serial.println("yellow");
    }
  }
int players;//creat the ariable players
int i = 0;
 BTserial.write(i);//Passes a variable to controller bluetooth that tells it to search for number of players
 
 delay(1000);//delays for 1 second
   if (BTserial.available() > 0){//if it is available
  players = BTserial.parseInt();//obtain the number of players and print to Serial
    Serial.print(" there are ");
    Serial.print(players);
    Serial.print(" players ");
  }

  //Creates a list of players
  for(int i = players; i<players +1; i++){
  playerList.push(i);
  }
}



void loop() {
//***Code looks for an interference(WIP)***
// int i = 1;
// BTserial.write(i);
// delay(1000);
//   if (BTserial.available() > 0){
//    colorChanged = true;
//    finalColor = BTserial.parseInt();
//    //Talk about interference
//    Serial.print(" there was an interference, know match ");
//    Serial.print(finalColor);
//  }
  playGame();//calls play game
 }

  
void playGame(){
  //makes move if they have not won
  if(winner == false) {
    //***This is code for the game to assign what body part(WIP - need audio)
//    callPlayer();
//    pickLimb();
    makeMove();
      } 
  }

void callPlayer(){
  
  //Call player code(WIP- needs audio)
  
  
  }

 ////*********************
// pickLimb function 
//Will assign a limb 
//to the current player
//***********************
void pickLimb(){
  int limb = Entropy.random(1, 5); //random number
  //Based on random number the board will use audio to tell which limb
  switch (limb) {
  case 1:
    // speak l hand
        Serial.println("Left Hand");
    break;
  case 2:
    // speak r hand
        Serial.println("Right Hand");
    break;
  case 3:
    // speak l foot
        Serial.println("Left Foot");
    break;
  case 4:
    // speak r foot
    Serial.println("Right Foot");
    break;
}
  
  }


////**********************
// makeMove function 
//Function that registers
//if a player has made a 
//move
//***********************
void makeMove(){
  
currentPlayerMoved = false;//if current player hasn't moved
  while(currentPlayerMoved == false){
 //For loop that checks every sensor   
 for(int i=2 ; i<3 ; i++){
  //Serial.println(analogRead(sensor[i]));//prints to serial the sensor reading(TESTING)
    if (analogRead(sensor[i]) > 900){//if it registers high
      delay(50);//pauses for a 1/5th of a sec
      if (analogRead(sensor[i]) < 800){//and registers low
        //(TESTING)
        //Serial.println(analogRead(sensor[i]));
       // Serial.println("in reading");
        nextColor(i);//call the next color
         currentPlayerMoved = true;//and set variable that the player has made a move
   }
   }
 }
  
  }
  }
   
 
  

////*****************
// setRed function 
//sets color to red
//*******************
void setRed(int num) {
  
  //Block of if stateents that check the 
  //spot number and sets the correct led to red 
  if (0 <= num && num <= 3) {
    strip.setPixelColor(num, 255, 0, 0);
    strip.show();
  }
  else if (4 <= num && num  <= 7) {
    num = num - 4;
    strip2.setPixelColor(num, 255, 0, 0);
    strip2.show();
  }
  else if (8 <= num && num  <= 11) {
       strip3.setPixelColor(num - 8,255, 0, 0);
        strip3.show();

  }
}

////*****************
// setGreen function 
//sets color to green
//Code similar to above
//*******************
void setGreen(int num) {
  if (0 <= num && num <= 3) {
    strip.setPixelColor(num, 0, 255, 0);
    strip.show();
 
  }
  else if (4 <= num && num <= 7) {
    num = num - 4;
    strip2.setPixelColor(num, 0, 255, 0);
    strip2.show();

  }
  else if (8 <= num && num <= 11) {
    //     strip3.setPixelColor(num - 8,0,255, 0);
    //     strip3.show();

  }
}

////*****************
// setBlue function 
//sets color to blue
//Code similar to above
//*******************
void setBlue(int num) {
  if (0 <= num && num  <= 3) {
    strip.setPixelColor(num, 0, 0, 255);
    strip.show();
  }
  else if (4 <= num && num <= 7) {
    num = num - 4;
    strip2.setPixelColor(num, 0, 0, 255);
    strip2.show();
  }
  else if (8 <= num && num <= 11) {
    //     strip3.setPixelColor(num - 8,0,0,255);
    //     strip3.show();

  }
}

////*****************
// setYellow function 
//sets color to yellow
//Code similar to above
//*******************
void setYellow(int num) {
  if (0 <= num && num <= 3) {
    strip.setPixelColor(num, 255, 125, 0);
    strip.show();

  }
  else if (4 <= num && num < 8) {
    num = num - 4;
    strip2.setPixelColor(num, 255, 125, 0);
    strip2.show();

  }
  else if (8 <= num && num  <= 11) {
    //     strip3.setPixelColor(num - 8,255,125,12);
    //     strip3.show();

  }
}


////********************
// nextColor function 
//sets color to green
//Code similar to above
//**********************
void nextColor(int num) {

//Block of IF statements that checks the current spot assigned number(color),
// calls the set[color] function and assigns the next color 
  if (spot[num] == 1) {
    setBlue(num);
    spot[num] = 2;
  }
  else if (spot[num] == 2) {
    setGreen(num);
    spot[num] = 3;
  } else if (spot[num] == 3) {
    setYellow(num);
    spot[num] = 4;
  } else if (spot[num] == 4) {
    setRed(num);
    spot[num] = 1;
  }
  win();//Calls Win to check to see if player has won
}

////*****************
// win function 
//checks if the game 
//has been won
//*******************
void win() {
  winner = true;//sets winner to true every round
  
 if(colorChanged == false){//if there hasn't been an interference
  finalColor = spot[0];//assign the final color to sppot one's color
     }
//IF statement that checks to make sure all spots have the same color(number)
  for (int i = 1; i < 6; i++) {
    if (spot[i] != finalColor) {
      winner = false;//If it doesn't than they have not won
    }
  }

  if (winner == true) {//if there has been a winner, call rainbow function
    rainbow(50);
  }

(TESTING)
 // Serial.println("Next Level");
 //// for (int i = 0; i < 12; i = i + 4) {
   // Serial.print(spot[i]);   Serial.print("\t"); Serial.print(spot[i + 1]);  Serial.print("\t");
  //  Serial.print(spot[i + 2]);   Serial.print("\t"); Serial.println(spot[i + 3]);  Serial.print("\n");
  }
}

//*****************************************************************************************************
NEOPixel Library code for a rainbow pattern
void rainbow(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i + j) & 255));
      strip2.setPixelColor(i, Wheel2((i + j) & 255));
    }
    strip.show();
    strip2.show();
    delay(wait);

 
  }
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

uint32_t Wheel2(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip2.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip2.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip2.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

//*****************************************************************************************************

