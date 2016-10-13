
/**
This will now take control of the keypad if needed and start lightup of the board 
with the passed in color.
The return value is the same as the others
*/
bool start_board_with_color(int color){
  new_mode_init();
  switch(color){
    case 0: //red
       colorSet(strip.Color(255, 0, 0));
       break;
    case 1: //orange
       colorSet(strip.Color(255, 64, 0)); 
       break;
    case 2: //yellow
       colorSet(strip.Color(255, 175, 0));
       break;
    case 3: //green
       colorSet(strip.Color(0, 255, 0));
       break;
    case 4: //cyan
       colorSet(strip.Color(0, 255, 255));
       break;
    case 5: //blue
       colorSet(strip.Color(0, 0, 255));
       break;
    case 6: //Purple
       colorSet(strip.Color(127, 0, 255));
       break;
    case 7: //white
       colorSet(strip.Color(255, 255, 255));
       break;
    case 8: //rainbow
       rainbow();
       break;
    case 9: //rotating rainbow
       rainbowCycle();
    default:
       colorSet(strip.Color(0, 0, 0));
       break;
       
  }
  
  return true;
}

// Fill the dots one after the other with a color
void colorSet(uint32_t c) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
  }
  strip.show();
}


void rainbow() {
  uint16_t i;
  int pix = strip.numPixels();
  float div = (float) 255/pix; 
  for(i=0; i<pix; i++) {
    int val = (int) i * div; 
    strip.setPixelColor(i, Wheel(val & 255));
  }
  strip.show();
}



// Slightly different, this makes the rainbow equally distributed throughout
//Need to modify to use a timer to change
void rainbowCycle() {
  Timer1.initialize(2000000);
  Timer1.attachInterrupt(rainbowISR);
  //wait for any button press.  Doesn't matter what it is, to return 
  //waitButton(); 
  //waitReleaseButton();
}

void rainbowISR(){
  static int lastInt = 0;
  
  uint16_t i;
  int pix = strip.numPixels();
  float div = (float) 255/pix; 
  for(i=0; i<pix; i++) {
    int val = (int) i * div; 
    strip.setPixelColor((i+lastInt) % pix, Wheel(val & 255));
  }
  
  lastInt++;
  strip.show();
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}
