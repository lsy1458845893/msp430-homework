
#include "msp430f5529.hpp"
#include "oled.hpp"
#include "timer.hpp"

void interrupt_func(void *dat){
  using namespace msp430f5529;
  static uint16_t i = 0;
  if (i < 100) i++;
  else{
    i = 0;
    gpio *led = reinterpret_cast<gpio*>(dat);
    led->output(!led->output());
  }
}

int main(void) {
  using namespace msp430f5529;

  system_init();


  gpio led1 = gpio(1, 0).direct(1);
  gpio led2 = gpio(4, 7).direct(1);
  gpio btn  = gpio(1, 1).mode(gpio::mode_input_pullup);

  timer_A0::mode_interrupt(1e6, interrupt_func, &led2); // 1ms

  oled<gpio> show(gpio(4, 2), gpio(4, 1));

  show.clear();
  show.cursor(0, 0) << "counter:";

  uint32_t i = 0;

  while (1) {
    led1.output(!led1.output());
    // led2.output(!led2.output());

    show.cursor(60, 0) << i++ << "   ";
    // show.cursor(60, 1) << TA0R << "   ";
    // f /= 2;

    for (volatile uint32_t i = 0; i < 100000; i++)
      ;  // delay
  }
}
