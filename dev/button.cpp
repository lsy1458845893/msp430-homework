
#include "msp430f5529.hpp"
#include "oled.hpp"

int main(void) {
  using namespace msp430f5529;

  WDTCTL = WDTPW + WDTHOLD;

  gpio led1 = gpio(1, 0).direct(1);
  gpio led2 = gpio(4, 7).direct(1);
  gpio btn  = gpio(1, 1).mode(gpio::mode_input_pullup);

  oled<gpio> show(gpio(4, 2), gpio(4, 1));

  show.clear();
  show.cursor(0, 0) << "counter:";
  show.cursor(0, 1) << "divider:";

  int i = 0;
  float f = -1;

  while (1) {
    led1.output(!led1.output());
    led2.output(!led2.output());

    show.cursor(60, 0) << i++;
    show.cursor(60, 1) << f;
    f /= 2;

    while (btn.input())
      ;
    while (!btn.input())
      ;

    // for (volatile int i = 0; i < 10000; i++)
    //   ;  // delay
  }
}
