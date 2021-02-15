/*
  KeyboardController For Arduino DUE
  Pre-optimized for HFSBOX keys using a standard arcade 2 players with x6 buttons panel :
  WARNING ! Keys are QWERTY Keyboard based !
    
  Created in 2021 by Aetios
  Based on Keyboard and Mouse Control code by Tom Igoe
*/

//#include "Keyboard.h"

#include "HID-Project.h"

unsigned long Index = 0;
// set pin numbers for each player controls:
int TabPinPlayer1[16] = {13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 14, 15};
int TabPinPlayer2[16] = {16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31};
//int TabPinPlayer3[16] = {32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 47, 46, 45, 44, 43};
//int TabPinPlayer4[16] = {A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, 48, 49, 53, 52, 51, 50};

// set keys for each player controls:
char TabKeysPlayer1[16] = {KEY_UP_ARROW, KEY_DOWN_ARROW, KEY_LEFT_ARROW, KEY_RIGHT_ARROW, '1', '5', KEY_LEFT_CTRL, 
                           KEY_LEFT_ALT, ' ', KEY_LEFT_SHIFT, 'Z', 'X', 'C', 'V', 'P', KEY_RETURN};
char TabKeysPlayer2[16] = {'R', 'F', 'D', 'G', '2', '6', 'A', 'S', 'Q', 'W', 'I', 'K', 'J', 'L', KEY_TAB, KEY_ESC};
//char TabKeysPlayer3[16] = {'I', 'K', 'J', 'L', 3, 7, KEY_RIGHT_CTRL, KEY_RIGHT_SHIFT, KEY_RETURN, 'O', NULL, NULL, NULL, NULL, NULL, NULL};
//char TabKeysPlayer4[16] = {'Y', 'N', 'V', 'U', 4, 8, 'B', 'E', 'H', 'M', NULL, NULL, NULL, NULL, NULL, NULL};

// set Hotkey and shifted Keys
int Hotkey = TabPinPlayer1[4];
char TabShiftedKeysP1[16] = {NULL, 'P', KEY_RETURN, KEY_TAB, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
char TabShiftedKeysP2[16] = {NULL, NULL, NULL, NULL, KEY_ESC, '5', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};

// Initialize CurrentState as "NORMAL". Other state is "SHIFTED" when Hotkey is ON.
enum States
{
  NORMAL,
  SHIFTED
};

int CurrentState = NORMAL;
bool KeyPressedState1[16] = {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false};
bool KeyPressedState2[16] = {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false};
//bool KeyPressedState3[16] = {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false};
//bool KeyPressedState4[16] = {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false};

void setup() { // initialize the buttons' inputs:
  for (int n=0 ; n < 16 ; n++) 
    {
      pinMode(TabPinPlayer1[n], INPUT_PULLUP);
      pinMode(TabPinPlayer2[n], INPUT_PULLUP);
   //   pinMode(TabPinPlayer3[n], INPUT_PULLUP);
   //   pinMode(TabPinPlayer4[n], INPUT_PULLUP);
    }
  Serial.begin(9600);
  // initialize keyboard control:
  Keyboard.begin();
}

void loop() {

  switch (CurrentState) {
    
    case NORMAL:
      for (int n=0 ; n < 16 ; n++) {
        
        if ((digitalRead(TabPinPlayer1[n]) == LOW) && (TabKeysPlayer1[n] != NULL) && (!KeyPressedState1[n])) {
            KeyPressedState1[n] = true;
            Keyboard.press(TabKeysPlayer1[n]);
        }
        if ((digitalRead(TabPinPlayer1[n]) == HIGH) && (TabKeysPlayer1[n] != NULL) && (KeyPressedState1[n])) {
            KeyPressedState1[n] = false;
            Keyboard.release(TabKeysPlayer1[n]);
        }

        if ((digitalRead(TabPinPlayer2[n]) == LOW) && (TabKeysPlayer2[n] != NULL) && (!KeyPressedState2[n])) {
            KeyPressedState2[n] = true;
            Keyboard.press(TabKeysPlayer2[n]);
        }
        if ((digitalRead(TabPinPlayer2[n]) == HIGH) && (TabKeysPlayer2[n] != NULL) && (KeyPressedState2[n])) {
            KeyPressedState2[n] = false;
            Keyboard.release(TabKeysPlayer2[n]);
        }  

    /*    if ((digitalRead(TabPinPlayer3[n]) == LOW) && (TabKeysPlayer3[n] != NULL) && (!KeyPressedState3[n])) {
            KeyPressedState3[n] = true;
            Keyboard.press(TabKeysPlayer3[n]);
        }
        if ((digitalRead(TabPinPlayer3[n]) == HIGH) && (TabKeysPlayer3[n] != NULL) && (KeyPressedState3[n])) {
            KeyPressedState3[n] = false;
            Keyboard.release(TabKeysPlayer3[n]);
        }          

        if ((digitalRead(TabPinPlayer4[n]) == LOW) && (TabKeysPlayer4[n] != NULL) && (!KeyPressedState4[n])) {
            KeyPressedState4[n] = true;
            Keyboard.press(TabKeysPlayer4[n]);
        }
        if ((digitalRead(TabPinPlayer4[n]) == HIGH) && (TabKeysPlayer4[n] != NULL) && (KeyPressedState4[n])) {
            KeyPressedState4[n] = false;
            Keyboard.release(TabKeysPlayer4[n]);
        }                */
        if (digitalRead(Hotkey) == LOW) {
          CurrentState = SHIFTED;
        }
      }
      break;

         
    case SHIFTED :
      for (int n=0 ; n < 16 ; n++) {
        
        if ((digitalRead(TabPinPlayer1[n]) == LOW) && (TabShiftedKeysP1[n] != NULL) && (!KeyPressedState1[n])) {
            KeyPressedState1[n] = true;
            Keyboard.press(TabShiftedKeysP1[n]);
        }
        if ((digitalRead(TabPinPlayer1[n]) == HIGH) && (TabShiftedKeysP1[n] != NULL) && (KeyPressedState1[n])) {
            KeyPressedState1[n] = false;
            Keyboard.release(TabShiftedKeysP1[n]);
        }

        if ((digitalRead(TabPinPlayer2[n]) == LOW) && (KeyPressedState2[n] != NULL) && (!KeyPressedState2[n])) {
            KeyPressedState2[n] = true;
            Keyboard.press(KeyPressedState2[n]);
        }
        if ((digitalRead(TabPinPlayer2[n]) == HIGH) && (KeyPressedState2[n] != NULL) && (KeyPressedState2[n])) {
            KeyPressedState2[n] = false;
            Keyboard.release(KeyPressedState2[n]);
        }  

        if (digitalRead(Hotkey) == HIGH) {
          CurrentState = NORMAL;
        }
     break;

    }
  }
}  
