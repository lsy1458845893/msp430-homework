#pragma once

template<class gpio>
class button {
  private:
    bool last;
    gpio btn;
  public:
    button(gpio btn):btn(btn),last(true) {
      btn.mode(gpio::mode_input_pullup);
    }

    bool check(void) {
      bool ret = false;
      bool input = btn.input();
      if (last == true && input == false) ret = true;
      last = input;
      return ret;
    }
};
