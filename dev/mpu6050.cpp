
#include "msp430f5529.hpp"
#include "oled.hpp"

int mpu_err = 0;

#include "mpu6050.hpp"

// #include <math.h>

int main(void) {
  using namespace msp430f5529;

  system_init();

  gpio led1 = gpio(1, 0).direct(1);
  gpio led2 = gpio(4, 7).direct(1);
  gpio btn  = gpio(1, 1).mode(gpio::mode_input_pullup);

  oled<gpio> show(gpio(4, 2), gpio(4, 1));

  show.clear();

  // mpu6050<gpio> sensor(gpio(3, 5), gpio(3, 6));

  mpu6050::inner::initial(gpio(3, 5), gpio(3, 6));
  
    int16_t ax, ay, az, gx, gy, gz;
    mpu6050::inner::get_accelerometer(ax, ay, az);
    mpu6050::inner::get_gyroscope(gx, gy, gz);

  // show.cursor(0, 3) << "size:" << sizeof(long double);

  // mpu6050::inner::mpu_dmp_init(gpio(3, 5), gpio(3, 6));

  int32_t err;
  while((err = mpu6050::inner::mpu_dmp_init(gpio(3, 5), gpio(3, 6))) != 0){
    show.cursor(0, 0) << "mpu6050 init err:" << err;
    show.cursor(0, 4) << mpu_err;
  }


  // uint8_t err;
  // while ((err = sensor.initial()) != 0)
  //   show.cursor(0, 0) << "mpu6050 init failed:" << err;

  show.cursor(0, 0) << "temp:";

  const char *blank = "   ";

  while (1) {
    led1.output(!led1.output());
    led2.output(!led2.output());

    // show.cursor(30, 0) << float(asin(100));

    show.cursor(30, 0) << mpu6050::inner::get_temperature() << blank;

    // int16_t ax, ay, az, gx, gy, gz;
    // mpu6050::inner::get_accelerometer(ax, ay, az);
    // mpu6050::inner::get_gyroscope(gx, gy, gz);
    
    int16_t ax, ay, az;
    float gx, gy, gz;
    mpu6050::inner::mpu_dmp_get_data(&gx,&gy,&gz,&ax,&ay,&az);

    show.cursor(0, 1) << ax << ' ' << gx << blank;
    show.cursor(0, 2) << ay << ' ' << gy << blank;
    show.cursor(0, 3) << az << ' ' << gz << blank;
  }
}
