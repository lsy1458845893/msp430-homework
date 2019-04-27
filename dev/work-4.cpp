
#include "oled.hpp"

#include "msp430f5529.hpp"
#include "timer.hpp"
#include "button.hpp"

static unsigned int counter;
static unsigned int prev_counter;

msp430f5529::gpio led1 = msp430f5529::gpio(1, 0).direct(1);

void handle_func(void *dat) {
  using namespace msp430f5529;
  led1.output(!led1.output());
  prev_counter = counter;
  counter = TA0CCR1;
  uint32_t *udat = (uint32_t *)dat;
  *udat = (prev_counter - counter) * 40;
  TA0CCTL1 &= ~CCIFG;
}

int main(void) {
  using namespace msp430f5529;
  system_init();
  gpio led = gpio(4, 7).direct(1); // led gpio initial

  P1DIR |= BIT2+BIT3;
  P1SEL |= BIT2+BIT3;
  
  P2DIR |= BIT0;
  P2SEL |= BIT0;
  
  P1SEL |= BIT1;

  button<gpio> btn_inc(gpio(2, 1));  // increase button initial
  button<gpio> btn_dec(gpio(1, 1));  // decrease button initial

  oled<gpio> show(gpio(4, 2), gpio(4, 1)); 
  show.clear(); 
  show.cursor(0, 0) << "output:";
  show.cursor(0, 1) << "capture:";
  show.cursor(50, 0) << "10%";

  uint32_t duty = 1e6;
  uint32_t test_duty = 0;
  timer_A0::mode_capture(1e7, handle_func, (void *)&test_duty);
  timer_A1::mode_pwm(1e7);

  while (1) {
    led.output(!led.output());
    timer_A1::pwm_duty(1, duty);
    show.cursor(50, 1) << uint8_t(float(test_duty) / 1e5) << "%  ";
    if (btn_inc.check() && duty + 500000 <= 1e7 - 1e6) {// increase button press check
      duty += 500000;
      show.cursor(50,0) << uint8_t(float(duty) / 1e5) << "%  "; // update screen
    }
    if (btn_dec.check() && duty - 500000 >= 1e6) {// decrease button press check
      duty -= 500000;
      show.cursor(50,0) << uint8_t(float(duty) / 1e5) << "%  "; // update screen
    }
  }
}

