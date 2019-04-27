
#include "msp430f5529.hpp"

int main(void) {
  using namespace msp430f5529;

  gpio led1 = gpio(1, 0).direct(1);
  gpio led2 = gpio(4, 7).direct(1);

  while (1) {
    led1.output(!led1.output());
    led2.output(!led2.output());

    for (volatile unsigned int i = 10000; i > 0; i--)
      ;  // delay
  }
}
