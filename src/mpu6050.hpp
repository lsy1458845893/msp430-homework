#pragma once

template <class gpio>
class mpu6050 {
#include "hardware.hpp"
 private:
  class iicx {
   private:
   public:
    gpio sda, scl;
    iicx(gpio sda, gpio scl) : sda(sda), scl(scl) {
      sda.direct(1);
      scl.direct(1);
    }

    void start(void) {
      sda.direct(1);
      scl.output(1);
      sda.output(1);
      sda.output(0);
      scl.output(0);
    }

    void stop(void) {
      sda.direct(1);
      scl.output(0);
      sda.output(0);
      scl.output(1);
      sda.output(1);
    }

    void send(uint8_t data) {
      sda.direct(1);
      uint8_t t = 8;
      scl.output(0);
      while (t--) {
        if (data & (0x01 << t))
          sda.output(1);
        else
          sda.output(0);
        scl.output(1);
        scl.output(0);
      }
    }

    uint8_t read(bool ack) {
      uint8_t i, receive = 0;
      sda.direct(0);
      for (i = 0; i < 8; i++) {
        scl.output(0);
        scl.output(1);
        receive <<= 1;
        if (sda.input()) receive++;
      }
      if (!ack)
        send_nack();
      else
        send_ack();
      return receive;
    }

    bool wait_ack(void) {
      uint8_t err_time = 0;
      sda.direct(0);
      sda.output(1);
      scl.output(1);
      while (sda.input()) {
        err_time++;
        if (err_time > 100) {
          stop();
          return 1;
        }
      }
      scl.output(0);
      return 0;
    }

    void send_ack(void) {
      scl.output(0);
      sda.direct(1);
      sda.output(0);
      scl.output(1);
      scl.output(0);
    }

    void send_nack(void) {
      scl.output(0);
      sda.direct(1);
      sda.output(1);
      scl.output(1);
      scl.output(0);
    }
  };

  iicx iic;

  const uint8_t MPU_SELF_TESTX_REG   = 0X0D;
  const uint8_t MPU_SELF_TESTY_REG   = 0X0E;
  const uint8_t MPU_SELF_TESTZ_REG   = 0X0F;
  const uint8_t MPU_SELF_TESTA_REG   = 0X10;
  const uint8_t MPU_SAMPLE_RATE_REG  = 0X19;
  const uint8_t MPU_CFG_REG          = 0X1A;
  const uint8_t MPU_GYRO_CFG_REG     = 0X1B;
  const uint8_t MPU_ACCEL_CFG_REG    = 0X1C;
  const uint8_t MPU_MOTION_DET_REG   = 0X1F;
  const uint8_t MPU_FIFO_EN_REG      = 0X23;
  const uint8_t MPU_I2CMST_CTRL_REG  = 0X24;
  const uint8_t MPU_I2CSLV0_ADDR_REG = 0X25;
  const uint8_t MPU_I2CSLV0_REG      = 0X26;
  const uint8_t MPU_I2CSLV0_CTRL_REG = 0X27;
  const uint8_t MPU_I2CSLV1_ADDR_REG = 0X28;
  const uint8_t MPU_I2CSLV1_REG      = 0X29;
  const uint8_t MPU_I2CSLV1_CTRL_REG = 0X2A;
  const uint8_t MPU_I2CSLV2_ADDR_REG = 0X2B;
  const uint8_t MPU_I2CSLV2_REG      = 0X2C;
  const uint8_t MPU_I2CSLV2_CTRL_REG = 0X2D;
  const uint8_t MPU_I2CSLV3_ADDR_REG = 0X2E;
  const uint8_t MPU_I2CSLV3_REG      = 0X2F;
  const uint8_t MPU_I2CSLV3_CTRL_REG = 0X30;
  const uint8_t MPU_I2CSLV4_ADDR_REG = 0X31;
  const uint8_t MPU_I2CSLV4_REG      = 0X32;
  const uint8_t MPU_I2CSLV4_DO_REG   = 0X33;
  const uint8_t MPU_I2CSLV4_CTRL_REG = 0X34;
  const uint8_t MPU_I2CSLV4_DI_REG   = 0X35;

  const uint8_t MPU_I2CMST_STA_REG = 0X36;
  const uint8_t MPU_INTBP_CFG_REG  = 0X37;
  const uint8_t MPU_INT_EN_REG     = 0X38;
  const uint8_t MPU_INT_STA_REG    = 0X3A;

  const uint8_t MPU_ACCEL_XOUTH_REG = 0X3B;
  const uint8_t MPU_ACCEL_XOUTL_REG = 0X3C;
  const uint8_t MPU_ACCEL_YOUTH_REG = 0X3D;
  const uint8_t MPU_ACCEL_YOUTL_REG = 0X3E;
  const uint8_t MPU_ACCEL_ZOUTH_REG = 0X3F;
  const uint8_t MPU_ACCEL_ZOUTL_REG = 0X40;

  const uint8_t MPU_TEMP_OUTH_REG = 0X41;
  const uint8_t MPU_TEMP_OUTL_REG = 0X42;

  const uint8_t MPU_GYRO_XOUTH_REG = 0X43;
  const uint8_t MPU_GYRO_XOUTL_REG = 0X44;
  const uint8_t MPU_GYRO_YOUTH_REG = 0X45;
  const uint8_t MPU_GYRO_YOUTL_REG = 0X46;
  const uint8_t MPU_GYRO_ZOUTH_REG = 0X47;
  const uint8_t MPU_GYRO_ZOUTL_REG = 0X48;

  const uint8_t MPU_I2CSLV0_DO_REG = 0X63;
  const uint8_t MPU_I2CSLV1_DO_REG = 0X64;
  const uint8_t MPU_I2CSLV2_DO_REG = 0X65;
  const uint8_t MPU_I2CSLV3_DO_REG = 0X66;

  const uint8_t MPU_I2CMST_DELAY_REG = 0X67;
  const uint8_t MPU_SIGPATH_RST_REG  = 0X68;
  const uint8_t MPU_MDETECT_CTRL_REG = 0X69;
  const uint8_t MPU_USER_CTRL_REG    = 0X6A;
  const uint8_t MPU_PWR_MGMT1_REG    = 0X6B;
  const uint8_t MPU_PWR_MGMT2_REG    = 0X6C;
  const uint8_t MPU_FIFO_CNTH_REG    = 0X72;
  const uint8_t MPU_FIFO_CNTL_REG    = 0X73;
  const uint8_t MPU_FIFO_RW_REG      = 0X74;
  const uint8_t MPU_DEVICE_ID_REG    = 0X75;

  const uint8_t MPU_ADDR = 0x68;

  uint8_t write(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf) {
    uint8_t i;
    iic.start();
    iic.send((addr << 1) | 0);
    if (iic.wait_ack()) {
      iic.stop();
      return 1;
    }
    iic.send(reg);
    iic.wait_ack();
    for (i = 0; i < len; i++) {
      iic.send(buf[i]);
      if (iic.wait_ack()) {
        iic.stop();
        return 1;
      }
    }
    iic.stop();
    return 0;
  }

  uint8_t write(uint8_t reg, uint8_t data) {
    iic.start();
    iic.send((MPU_ADDR << 1) | 0);
    if (iic.wait_ack()) {
      iic.stop();
      return 1;
    }
    iic.send(reg);
    if (iic.wait_ack()) {
      iic.stop();
      return 1;
    }
    iic.send(data);
    if (iic.wait_ack()) {
      iic.stop();
      return 1;
    }
    iic.stop();
    return 0;
  }

  uint8_t read(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf) {
    iic.start();
    iic.send((addr << 1) | 0);
    if (iic.wait_ack()) {
      iic.stop();
      return 1;
    }
    iic.send(reg);
    iic.wait_ack();
    iic.start();
    iic.send((addr << 1) | 1);
    iic.wait_ack();
    while (len) {
      if (len == 1)
        *buf = iic.read(0);
      else
        *buf = iic.read(1);
      len--;
      buf++;
    }
    iic.stop();
    return 0;
  }

  uint8_t read(uint8_t reg) {
    uint8_t res = 0;
    iic.start();
    iic.send((MPU_ADDR << 1) | 0);
    iic.wait_ack();
    iic.send(reg);
    iic.wait_ack();
    iic.start();
    iic.send((MPU_ADDR << 1) | 1);
    iic.wait_ack();
    res = iic.read(0);
    iic.stop();
    return res;
  }

  uint8_t set_gyro_fsr(uint8_t fsr) { return write(MPU_GYRO_CFG_REG, fsr << 3); }

  uint8_t set_accel_fsr(uint8_t fsr) { return write(MPU_ACCEL_CFG_REG, fsr << 3); }

  uint8_t set_LPF(uint16_t lpf) {
    uint8_t data = 0;
    if (lpf >= 188)
      data = 1;
    else if (lpf >= 98)
      data = 2;
    else if (lpf >= 42)
      data = 3;
    else if (lpf >= 20)
      data = 4;
    else if (lpf >= 10)
      data = 5;
    else
      data = 6;
    return write(MPU_CFG_REG, data);
  }

  uint8_t set_rate(uint16_t rate) {
    uint8_t data;
    if (rate > 1000) rate = 1000;
    if (rate < 4) rate = 4;
    data = 1000 / rate - 1;
    data = write(MPU_SAMPLE_RATE_REG, data);
    return set_LPF(rate / 2);
  }

 public:
  mpu6050(gpio sda, gpio scl) : iic(sda, scl) {}

  uint8_t initial(void) {
    if (write(MPU_PWR_MGMT1_REG, 0X80)) return 2;
    for (volatile uint16_t i = 0; i < 1000; i++)
      ;
    if (write(MPU_PWR_MGMT1_REG, 0X00)) return 3;
    if (set_gyro_fsr(3)) return 4;
    if (set_accel_fsr(0)) return 5;
    if (set_rate(50)) return 6;
    if (write(MPU_INT_EN_REG, 0X00)) return 7;
    if (write(MPU_USER_CTRL_REG, 0X00)) return 8;
    if (write(MPU_FIFO_EN_REG, 0X00)) return 9;
    if (write(MPU_INTBP_CFG_REG, 0X80)) return 10;

    uint8_t res = read(MPU_DEVICE_ID_REG);
    if (res == MPU_ADDR) {
      write(MPU_PWR_MGMT1_REG, 0X01);
      write(MPU_PWR_MGMT2_REG, 0X00);
      set_rate(50);
    } else
      return res;

    return 0;
  }

  float get_temperature(void) {
    uint8_t buf[2];
    int16_t raw;
    float   temp;
    read(MPU_ADDR, MPU_TEMP_OUTH_REG, 2, buf);
    raw  = ((uint16_t)buf[0] << 8) | buf[1];
    temp = 36.53 + ((float)raw) / 340;
    return temp * 100;
  }

  uint8_t get_gyroscope(int16_t &gx, int16_t &gy, int16_t &gz) {
    uint8_t buf[6], res;
    res = read(MPU_ADDR, MPU_GYRO_XOUTH_REG, 6, buf);
    if (res == 0) {
      gx = ((uint16_t)buf[0] << 8) | buf[1];
      gy = ((uint16_t)buf[2] << 8) | buf[3];
      gz = ((uint16_t)buf[4] << 8) | buf[5];
    }
    return res;
  }

  uint8_t get_accelerometer(int16_t &ax, int16_t &ay, int16_t &az) {
    uint8_t buf[6], res;
    res = read(MPU_ADDR, MPU_ACCEL_XOUTH_REG, 6, buf);
    if (res == 0) {
      ax = ((uint16_t)buf[0] << 8) | buf[1];
      ay = ((uint16_t)buf[2] << 8) | buf[3];
      az = ((uint16_t)buf[4] << 8) | buf[5];
    }
    return res;
  }
};
