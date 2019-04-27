
#include "oled.hpp"

#include "msp430f5529.hpp"


int main(void) {
  using namespace msp430f5529;

  system_init();

  gpio led1 = gpio(1, 0).direct(1);
  gpio led2 = gpio(4, 7).direct(1);

  gpio btn = gpio(1, 1).mode(gpio::mode_input_pullup);

  adc adc_input(2);

  oled<gpio> show(gpio(4, 2), gpio(4, 1));

  show.clear();

  show.cursor(0, 0) << "start";

  while (1) {
    led1.output(!led1.output());
    led2.output(!led2.output());

    show.cursor(0, 1) << "adc:" << adc_input.convert() << "   ";

    for (volatile uint16_t i = 0; i < 10000; i++)
      ;

    // while (btn.input())
    //   ;
    // while (!btn.input())
    //   ;
  }
}
