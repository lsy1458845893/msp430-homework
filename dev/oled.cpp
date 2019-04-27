
#include "oled.hpp"
#include "msp430f5529.hpp"

int main(void) {
  using namespace msp430f5529;

  WDTCTL = WDTPW + WDTHOLD;

  gpio led1 = gpio(1, 0).direct(1);
  gpio led2 = gpio(4, 7).direct(1);

  oled<gpio> show(gpio(4, 2), gpio(4, 1));

  show.clear();
  show.cursor(0, 0) << "hello world";
  show.cursor(0, 1) << "counter:";

  int i = 0;

  while (1) {
    led1.output(!led1.output());
    led2.output(!led2.output());

    show.cursor(60, 1) << i++;

    for (volatile int i = 0; i < 10000; i++)
      ;  // delay
  }
}
