
#include "oled.hpp"

#include "msp430f5529.hpp"
#include "timer.hpp"
#include "button.hpp"

typedef unsigned char uint8_t;

uint8_t period = 0;

const struct {
  uint8_t period;
  const char *str;
} period_tab[4] = {
  {40, "25Hz "}, // 25Hz
  {20, "50Hz "}, // 50Hz
  {13, "75Hz "}, // 75Hz
  {10, "100Hz"}, // 100Hz
};

void timer_handle(void *dat) {
  using namespace msp430f5529;
  gpio *wave = reinterpret_cast<gpio *>(dat);
  static uint8_t count = 0;
  if(count < period_tab[period].period) count ++;
  else {
    wave->output(!wave->output());// reverse wave output
    count = 0;
  }
}

int main(void) {
  using namespace msp430f5529;
  system_init();
  gpio led = gpio(4, 7).direct(1); // led gpio initial
  gpio wave = gpio(3, 2).direct(1); // wave gpio initial

  button<gpio> btn_inc(gpio(2, 1));  // increase button initial
  button<gpio> btn_dec(gpio(1, 1));  // decrease button initial

  // setting timer_A0 with interrupt mode
  timer_A0::mode_interrupt(1e6, timer_handle, reinterpret_cast<void*>(&wave));
  adc adc_input(1); // adc read fromo channl 1
  oled<gpio> show(gpio(4, 2), gpio(4, 1)); // oled initial
  show.clear(); // clear screen
  show.cursor(0, 0) << period_tab[period].str;
  while (1) {
    led.output(!led.output()); // reverse led output
    if (wave.output()) // check wave output is set
      show.cursor(0, 1) << float(adc_input.convert() * 0.0008058608058608059) << "V        ";
    if (btn_inc.check() && period < 3) // increase button press check
      show.cursor(0, 0) << period_tab[period++].str; // update screen
    if (btn_dec.check() && period > 0) // decrease button press check
      show.cursor(0, 0) << period_tab[period--].str; // update screen
  }
}

/**
 *   initial timer set periol 1ms
 *                V
 *   compute and show frequency <---------------------+
 *                V                                   |
 *     read ADC and update screen                     |
 *                V                                   |
 *   +---> check button press ---> change frequency --+
 *   |            V no      yes
 *   +------------+
 */    
