
#include <msp430f5529.h>
#include "msp430f5529.hpp"
#include "oled.hpp"


#include "timer.hpp"

int main(void) {
  using namespace msp430f5529;

  system_init();


  gpio led1 = gpio(1, 0).direct(1);
  gpio led2 = gpio(4, 7).direct(1);
  gpio btn  = gpio(1, 1).mode(gpio::mode_input_pullup);

  P1DIR |= BIT2+BIT3;
  P1SEL |= BIT2+BIT3;
  
  P2DIR |= BIT0+BIT1;
  P2SEL |= BIT0+BIT1;

  timer_A1::mode_pwm(1e6); // 1ms

  oled<gpio> show(gpio(4, 2), gpio(4, 1));

  show.clear();
  show.cursor(0, 0) << "counter:";

  uint32_t duty = 0;

  while (1) {
    led1.output(!led1.output());
    led2.output(!led2.output());

    timer_A1::pwm_duty(1, duty % 1000000);
    duty += 10000;

    show.cursor(60, 0) << (float(duty % 1000000) / 1000000) << "   ";
    // show.cursor(60, 1) << TA0R << "   ";
    // f /= 2;

    // for (volatile uint32_t i = 0; i < 100000; i++)
    //   ;  // delay
  }
}
