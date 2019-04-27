
#include "msp430f5529.hpp"
#include "oled.hpp"

int main(void) {
  using namespace msp430f5529;

  system_init();  // stop watch dog, set cpu freq 25MHz

  gpio led1 = gpio(1, 0).direct(1);  // setting led
  gpio led2 = gpio(4, 7).direct(1);  // setting led

  gpio btn_inc = gpio(2, 1).mode(gpio::mode_input_pullup);  // setting button
  gpio btn_dec = gpio(1, 1).mode(gpio::mode_input_pullup);  // setting button

  oled<gpio> show(gpio(4, 2), gpio(4, 1));  // setting oled
  show.clear();                             // clear oled

  int32_t i = 2019;

  while (true) {
    show.cursor(60, 1) << i << "     ";  // show number
    led1.output(i % 2 == 1);             // change led1
    led2.output(i % 2 == 0);             // change led2

    while (true) {  // check button press
      if (!btn_inc.input()) {
        while (!btn_inc.input())
          ;
        if (i < 65535) i++;  // increase number
        break;
      }
      if (!btn_dec.input()) {
        while (!btn_dec.input())
          ;
        if (i > -65535) i--;  // decrease number
        break;
      }
    }
  }
}