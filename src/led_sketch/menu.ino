#include <LiquidCrystal.h>
#include <LCDKeypad.h>

#define T_LOW_DIFFICULTY 0
#define T_HIGH_DIFFICULTY 5 

#define S_LOW_DIFFICULTY 0
#define S_HIGH_DIFFICULTY 2

byte c_up[8] = {
  0b00100,
  0b01110,
  0b10101,
  0b00100,
  0b00100,
  0b00100,
  0b00100,
  0b00100,
};

byte c_down[8] = {
  0b00100,
  0b00100,
  0b00100,
  0b00100,
  0b00100,
  0b10101,
  0b01110,
  0b00100,
};

byte c_select[8] = {
  0b00000,
  0b01110,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b01110,
  0b00000,
};

char* main_menu[] = {"Tetris",
                     "Snake",
                     "Music Visual",
                     "Color Chooser"
                    };

int num_main_menu_items = 4;


char* game_menu[] = {"Difficulty",
                     "Start",
                     "Quit"
                    };

int num_game_menu_items = 3;


char* mv_menu[] = {"Start",
                   "Quit"
                   };

int num_mv_menu_items = 2;


char* cc_menu[] = {"Red",
                   "Orange",
                   "Yellow",
                   "Green",
                   "Cyan",
                   "Blue",
                   "Purple",
                   "White",
                   "Rainbow",
                   "Rainbow Cycle",
                   "Quit"
                   };

int num_cc_menu_items = 11;



/** Initializes the special characters and sets the screen
*/
void menu_setup() {
  lcd.createChar(1, c_select);
  lcd.createChar(2, c_up);
  lcd.createChar(3, c_down);
  lcd.begin(16, 2);
  lcd.clear();
}

/**
MENU ITEMS:
  Tetris
  Snake
  Music Visualizer
  Choose Color (for solid board color)
  
Return true or false, doesn't matter.  
For sub menus, a return value of true means it should return to the top menu.
For false, it shouldn't
*/
bool handle_main_menu() {
  int curr_menu = 0;
  while (1) {
    lcd.noBlink();
    print_main_menu(curr_menu);
    int pressedButton = waitButton();
    waitReleaseButton();

    switch (pressedButton) {
      case KEYPAD_LEFT:
      case KEYPAD_RIGHT:
        //Do nothing
        break;
      case KEYPAD_DOWN:
        if (curr_menu < num_main_menu_items) {
          curr_menu++;
        }
        break;
      case KEYPAD_UP:
        if (curr_menu > 0) {
          curr_menu--;
        }
        break;
      case KEYPAD_SELECT:
        switch (curr_menu) {
          case 0: //The reason for 2 here is that "Main Menu" will appear at the top of the screen
          case 1:
            if(handle_tetris_menu()){
              return true;
            }
            break;
          case 2:
            if(handle_snake_menu()){
              return true;
            }
            break;
          case 3:
            if(handle_MV_menu()){
              return true;
            }
            break;
          case 4:
            if(handle_CC_menu()){
              return true;
            }
            break;

          default:
            break;
        }
        break;

      default:
        break;

    }
  }
}

/**
MENU ITEMS:
  Difficulty
  Start
  Quit

Same return value as explained in the main menu
*/
bool handle_tetris_menu() {
  int curr_menu = 0;
  int difficulty = 0; //difficulty ranges from 0-2, 0 easiest, 2 hardest
  
  
  while (1) {
    lcd.noBlink();
    print_tetris_menu(curr_menu, difficulty);
    int pressedButton = waitButton();
    waitReleaseButton();

    switch (pressedButton) {
      case KEYPAD_LEFT:
        
        if((curr_menu == 0 || curr_menu == 1) && difficulty > T_LOW_DIFFICULTY){
          difficulty--; 
        }
        break;
      case KEYPAD_RIGHT:
        if((curr_menu == 0 || curr_menu == 1) && difficulty < T_HIGH_DIFFICULTY){
          difficulty++; 
        }
        break;
      case KEYPAD_DOWN:
        if (curr_menu < num_game_menu_items) {
          curr_menu++;
        }
        break;
      case KEYPAD_UP:
        if (curr_menu > 0) {
          curr_menu--;
        }
        break;
      case KEYPAD_SELECT:
        switch (curr_menu) {
          case 0: //The reason for 2 here is that "Tetris Menu" will appear at the top of the screen
          case 1: //Difficulty
            //Do nothing
            break;
          case 2:  //Start
            //call the method to start the game here (can just take over the keypad)
            run_tetris(difficulty);
            return false;
            break;

          case 3:  //Quit
            return true;
            break;
          default:
            break;
        }
        break;

      default:
        break;

    }
  }
}

/**
MENU ITEMS:
  Difficulty
  Start
  Quit
  
Same return value as above
*/
bool handle_snake_menu() {
  int curr_menu = 0;
  int difficulty = 0; //difficulty ranges from 0-2, 0 easiest, 2 hardest
  
  while (1) {
    lcd.noBlink();
    print_snake_menu(curr_menu, difficulty);
    int pressedButton = waitButton();
    waitReleaseButton();

    switch (pressedButton) {
      case KEYPAD_LEFT:
        
        if((curr_menu == 0 || curr_menu == 1) && difficulty > S_LOW_DIFFICULTY){
          difficulty--; 
        }
        break;
      case KEYPAD_RIGHT:
        if((curr_menu == 0 || curr_menu == 1) && difficulty < S_HIGH_DIFFICULTY){
          difficulty++; 
        }
        break;
      case KEYPAD_DOWN:
        if (curr_menu < num_game_menu_items) {
          curr_menu++;
        }
        break;
      case KEYPAD_UP:
        if (curr_menu > 0) {
          curr_menu--;
        }
        break;
      case KEYPAD_SELECT:
        switch (curr_menu) {
          case 0: //The reason for 2 here is that "Tetris Menu" will appear at the top of the screen
          case 1: //Difficulty
            //Do nothing
            break;
          case 2: //Start
            run_snake(difficulty);
            return false;
            break;

          case 3: //Quit
            return true;
            break;
          default:
            break;
        }
        break;

      default:
        break;

    }
  }
}

/**
MENU ITEMS:
  Start
  Quit
*/
bool handle_MV_menu() {
  int curr_menu = 0;
  
  
  while (1) {
    lcd.noBlink();
    print_mv_menu(curr_menu);
    int pressedButton = waitButton();
    waitReleaseButton();

    switch (pressedButton) {
      case KEYPAD_LEFT:
      case KEYPAD_RIGHT:
        //Do nothing
        break;
      case KEYPAD_DOWN:
        if (curr_menu < num_mv_menu_items) {
          curr_menu++;
        }
        break;
      case KEYPAD_UP:
        if (curr_menu > 0) {
          curr_menu--;
        }
        break;
      case KEYPAD_SELECT:
        switch (curr_menu) {
          case 0: //The reason for 2 here is that "Tetris Menu" will appear at the top of the screen
          case 1: //Start
            //Do visualizer work here, take over the keypad if needed
            if(start_visualizer()){
              return false; 
            }
            break;
          case 2: //Quit
            //quit
            return true;
          default:
            break;
        }
        break;

      default:
        break;

    }
  }
}

/**
MENU ITEMS:
  Red
  Orange
  Yellow
  Green
  Cyan
  Blue
  Purple
  White
  Rainbow
  Rotating Rainbow (Rainbow shuffles)
  Quit
*/
bool handle_CC_menu() {
  int curr_menu = 0;
  
  while (1) {
    lcd.noBlink();
    print_cc_menu(curr_menu);
    int pressedButton = waitButton();
    waitReleaseButton();

    switch (pressedButton) {
      case KEYPAD_LEFT:
      case KEYPAD_RIGHT:
        //Do nothing
        break;
      case KEYPAD_DOWN:
        if (curr_menu < num_cc_menu_items) {
          curr_menu++;
        }
        break;
      case KEYPAD_UP:
        if (curr_menu > 0) {
          curr_menu--;
        }
        break;
      case KEYPAD_SELECT:
        switch (curr_menu) {
          case 0: //The reason for 2 here is that "Tetris Menu" will appear at the top of the screen
          case 1:
            //Red
            if(start_board_with_color(0)){
              return false;
            }
            break;
          case 2:
            //Orange
          case 3:
          //Yellow
          case 4:
            //Green
          case 5:
            //cyan
          case 6:
            //Blue
          case 7:
            //Purple
          case 8:
            //White
          case 9:
            //Rainbow
          case 10: 
            //Rainbow Cycle
            if(start_board_with_color(curr_menu-1)){
              return false;
            }
            break;
          case 11:
            return true;
          default:
            break;
        }
        break;

      default:
        break;

    }
  }
}

/**
Prints out the main menu depending on the current selection
*/
void print_tetris_menu(int curr_menu, int difficulty) {
  lcd.clear();
  switch (curr_menu) {
    case 0:
      lcd.setCursor(0, 0);
      lcd.print("--Tetris Menu---");
      //supposed to fall through to continue printing
    case 1:
    case 2:
    case 3:
    default:
      print_game_menu(curr_menu, difficulty);
  }
}

/**
Prints out the main menu depending on the current selection
*/
void print_snake_menu(int curr_menu, int difficulty) {
  lcd.clear();
  switch (curr_menu) {
    case 0:
      lcd.setCursor(0, 0);
      lcd.print("---Snake Menu---");
      //supposed to fall through to continue printing
    case 1:
    case 2:
    case 3:
    default:
      print_game_menu(curr_menu, difficulty);
  }
}


/**
Generic printing method for both Tetris and Snake (They have the same menu)
*/
void print_game_menu(int curr_menu, int difficulty){
  switch (curr_menu) {
    case 0:
      lcd.setCursor(0, 1);
      lcd.write(1);
      lcd.setCursor(2, 1);
      lcd.print(game_menu[0]);
      lcd.write('<');
      lcd.write('0' + difficulty);
      lcd.write('>');
      break;
    case 1:
      lcd.setCursor(0, 0);
      lcd.write(1);
      lcd.setCursor(2, 0);
      lcd.print(game_menu[curr_menu - 1]);
      lcd.write('<');
      lcd.write('0' + difficulty);
      lcd.write('>');
      lcd.setCursor(2, 1);
      lcd.print(game_menu[curr_menu]);
      break;
    case 2:
      lcd.setCursor(0, 0);
      lcd.write(1);
      lcd.setCursor(2, 0);
      lcd.print(game_menu[curr_menu - 1]);
      lcd.setCursor(2, 1);
      lcd.print(game_menu[curr_menu]);
      break;
    case 3:
      lcd.setCursor(2, 0);
      lcd.print(game_menu[curr_menu - 2]);
      lcd.setCursor(0, 1);
      lcd.write(1);
      lcd.setCursor(2, 1);
      lcd.print(game_menu[curr_menu - 1]);
      break;
    default:
      break;
  }
}

void print_mv_menu(int curr_menu){
  lcd.clear();
  switch (curr_menu) {
    case 0:
      lcd.setCursor(0, 0);
      lcd.print("-----MV Menu----");
      lcd.setCursor(0, 1);
      lcd.write(1);
      lcd.setCursor(2, 1);
      lcd.print(mv_menu[0]);
      break;
    case 1:
      lcd.setCursor(0, 0);
      lcd.write(1);
      lcd.setCursor(2, 0);
      lcd.print(mv_menu[curr_menu - 1]);
      lcd.setCursor(2, 1);
      lcd.print(mv_menu[curr_menu]);
      break;
      break;
    case 2:
      lcd.setCursor(2, 0);
      lcd.print(mv_menu[curr_menu - 2]);
      lcd.setCursor(0, 1);
      lcd.write(1);
      lcd.setCursor(2, 1);
      lcd.print(mv_menu[curr_menu - 1]);
      break;
    default:
      break;
  }
}


void print_cc_menu(int curr_menu){
  lcd.clear();
  switch (curr_menu) {
    case 0:
      lcd.setCursor(0, 0);
      lcd.print("-----CC Menu----");
      lcd.setCursor(0, 1);
      lcd.write(1);
      lcd.setCursor(2, 1);
      lcd.print(cc_menu[0]);
      break;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6: 
    case 7: 
    case 8:
    case 9:
    case 10:
      lcd.setCursor(0, 0);
      lcd.write(1);
      lcd.setCursor(2, 0);
      lcd.print(cc_menu[curr_menu - 1]);
      lcd.setCursor(2, 1);
      lcd.print(cc_menu[curr_menu]);
      break;
    case 11:
      lcd.setCursor(2, 0);
      lcd.print(cc_menu[curr_menu - 2]);
      lcd.setCursor(0, 1);
      lcd.write(1);
      lcd.setCursor(2, 1);
      lcd.print(cc_menu[curr_menu - 1]);
      break;
    default:
      break;
  }
}


/**
Prints out the main menu depending on the current selection
*/
void print_main_menu(int curr_menu) {
  lcd.clear();
  switch (curr_menu) {
    case 0:
      lcd.setCursor(0, 0);
      lcd.print("----Main Menu---");
      lcd.setCursor(0, 1);
      lcd.write(1);
      lcd.setCursor(2, 1);
      lcd.print(main_menu[0]);
      break;
    case 1:
    case 2:
    case 3:
      lcd.setCursor(0, 0);
      lcd.write(1);
      lcd.setCursor(2, 0);
      lcd.print(main_menu[curr_menu - 1]);
      lcd.setCursor(2, 1);
      lcd.print(main_menu[curr_menu]);
      break;
    case 4:
      lcd.setCursor(2, 0);
      lcd.print(main_menu[curr_menu - 2]);
      lcd.setCursor(0, 1);
      lcd.write(1);
      lcd.setCursor(2, 1);
      lcd.print(main_menu[curr_menu - 1]);
      break;
    default:
      break;
  }
}

int waitButton()
{
  int buttonPressed;
  waitReleaseButton;
  //lcd.blink();
  while ((buttonPressed = lcd.button()) == KEYPAD_NONE)
  {
  }
  delay(50);
  //lcd.noBlink();
  return buttonPressed;
}

void waitReleaseButton()
{
  delay(50);
  while (lcd.button() != KEYPAD_NONE)
  {
  }
  delay(50);
}



