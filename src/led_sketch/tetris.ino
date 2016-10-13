#include "T_Board.h"
#include "T_Shape.h"

int curr_difficulty = 0;
Board* board;
/**
  Starts tetris with the provided difficulty.
*/
bool run_tetris(int difficulty) {
  new_mode_init();
  
  board = new Board();
  
  lcd.clear();
  curr_difficulty = difficulty;

  //The initialize function defines how long the isr will be called
  Timer1.initialize(2000000);
  Timer1.attachInterrupt(tetris_isr);

  while (1) {
    int pressedButton = waitButton();
    Shape* s = new Shape(0,3);
    waitReleaseButton();
    delete s;
  }
  delete board;
  return false;
}

//used to drop the place the piece
void tetris_isr() {
  static int stopTimer = 0;
  stopTimer++;
  Serial.println("Hello");
  lcd.setCursor(0, 0);
  lcd.print("Hello! ");
  lcd.write('0' + stopTimer);
  if (stopTimer == 10) {
    Timer1.detachInterrupt();
  }
}



