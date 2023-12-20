// learn how to do multiplexing with LED ring light, MAX7219 chip and Arduino UNO
// since WOKWI does not support LED ring light, for simulation, the 8x8 LED Matrix Display is used instead

// created by upir, 2023
// youtube channel: https://www.youtube.com/upir_upir

// Youtube video: https://youtu.be/sE3LSYoCqLQ
// Source files: https://github.com/upiir/led_ring_light_with_max7219
// WOKWI sketch: https://wokwi.com/projects/384622406444001281

// Links from the video:
// LED ring light: https://s.click.aliexpress.com/e/_DmvHFpp
// MAX7219 module: https://s.click.aliexpress.com/e/_DkX1kNF
// Round hole pin header: https://s.click.aliexpress.com/e/_DkUOru9
// Arduino UNO: https://s.click.aliexpress.com/e/_AXDw1h
// Arduino prototyping shield: https://s.click.aliexpress.com/e/_ApbCwx
// Breadboard wires: https://s.click.aliexpress.com/e/_Dkbngin
// 8x8 LED Matrix Display connections: https://acoptex.com/project/160/basics-project-032a-8x8-dot-led-matrix-64-led-digital-display-common-anode-and-common-cathode-at-lex-c/
// LedControl library: https://github.com/wayoda/LedControl
// WOKWI Matrix Display documentation: https://docs.wokwi.com/parts/wokwi-max7219-matrix

// Other videos using 8x8 LED Matrix display and Multiplexing (MAX7219)
// Pimp my potentiometer (part 1): https://youtu.be/tHL4RYGSvg4
// Matrix display counter: https://youtu.be/jlhcDzS17vU
// Matrix display stencil overlays: https://youtu.be/oLgUtjyKO6Q
// Wood clock: https://youtu.be/50bVXHYW_9Q


#include "LedControl.h" // LedControl library is used to interface the MAX7219 chip (and the LED Ring Light)

LedControl lc=LedControl(/*DIN*/11,/*CLK*/13,/*CS*/10,/*number of displays*/1); // initialization of the display

void setup() {
  
  lc.shutdown(0,false); // The MAX72XX is in power-saving mode on startup, we have to do a wakeup call
  lc.setIntensity(0,8); // Set the brightness to a medium values
  lc.clearDisplay(0); // clear the display

  pinMode(A0, INPUT); // set pin A0 to be analog input for reading the potentiometer value
}

void loop() { // main loop

  int potentiometer_value = analogRead(A0); // read the potentiometer value from pin A0
  potentiometer_value = map(potentiometer_value, 0, 1023, 0, 32); // remap the value from 0-1023 to 0-32


  for(int row=0;row<4;row++) { // for every row
    for(int col=0;col<8;col++) { // for every column

      if ((col + (row * 8)) < potentiometer_value) { // if the current LED index is smaller than the potentiometer value...
        lc.setLed(0,row,col,true); // turn the LED on
      } else { // otherwise...
        lc.setLed(0,row,col,false); // turn the LED off
      }
    }
  }
}
