
//before running any program, this will initialize the program by detaching any interrupts
//and turning off the LEDS
void new_mode_init(){
  //if any timers left over, detach them now
  Timer1.detachInterrupt();
  colorSet(strip.Color(0,0,0));
}
