#pragma once

namespace software {
#include "hardware.hpp"

template <class gpio>
class iic {
 private:
  gpio sda, scl;

 public:
  uint32_t delay;
  uint32_t wait;

  iic(gpio sda, gpio scl) : sda(sda), scl(scl) {

  }
  
};
}  // namespace software