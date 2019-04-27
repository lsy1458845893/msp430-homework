#pragma once 
#include "msp430f5529.hpp"

// #include <stdlib.h>
#include <string.h>
#include <math.h>
namespace mpu6050 {

  namespace dev = msp430f5529;

  namespace inner {

    #include "hardware.hpp"
  class iicx {
   private:
    dev::gpio  sda, scl;
   public:
    iicx():sda(dev::gpio(3, 5)), scl(dev::gpio(3, 6)){
      sda.direct(1);
      scl.direct(1);
    }
    iicx(dev::gpio sda, dev::gpio scl) : sda(sda), scl(scl) {
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



  uint8_t initial(dev::gpio sda, dev::gpio scl) {
    iic = iicx(sda, scl);
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

void delay_ms(uint32_t t){
    while(t--) __delay_cycles(25000);
}

#define LOGI(...)
#define LOGE(...)
#define TAG

#define DMP_PTAT    0
#define DMP_XGYR    2
#define DMP_YGYR    4
#define DMP_ZGYR    6
#define DMP_XACC    8
#define DMP_YACC    10
#define DMP_ZACC    12
#define DMP_ADC1    14
#define DMP_ADC2    16
#define DMP_ADC3    18
#define DMP_BIASUNC    20
#define DMP_FIFORT    22
#define DMP_INVGSFH    24
#define DMP_INVGSFL    26
#define DMP_1H    28
#define DMP_1L    30
#define DMP_BLPFSTCH    32
#define DMP_BLPFSTCL    34
#define DMP_BLPFSXH    36
#define DMP_BLPFSXL    38
#define DMP_BLPFSYH    40
#define DMP_BLPFSYL    42
#define DMP_BLPFSZH    44
#define DMP_BLPFSZL    46
#define DMP_BLPFMTC    48
#define DMP_SMC    50
#define DMP_BLPFMXH    52
#define DMP_BLPFMXL    54
#define DMP_BLPFMYH    56
#define DMP_BLPFMYL    58
#define DMP_BLPFMZH    60
#define DMP_BLPFMZL    62
#define DMP_BLPFC    64
#define DMP_SMCTH    66
#define DMP_0H2    68
#define DMP_0L2    70
#define DMP_BERR2H    72
#define DMP_BERR2L    74
#define DMP_BERR2NH    76
#define DMP_SMCINC    78
#define DMP_ANGVBXH    80
#define DMP_ANGVBXL    82
#define DMP_ANGVBYH    84
#define DMP_ANGVBYL    86
#define DMP_ANGVBZH    88
#define DMP_ANGVBZL    90
#define DMP_BERR1H    92
#define DMP_BERR1L    94
#define DMP_ATCH    96
#define DMP_BIASUNCSF    98
#define DMP_ACT2H    100
#define DMP_ACT2L    102
#define DMP_GSFH    104
#define DMP_GSFL    106
#define DMP_GH    108
#define DMP_GL    110
#define DMP_0_5H    112
#define DMP_0_5L    114
#define DMP_0_0H    116
#define DMP_0_0L    118
#define DMP_1_0H    120
#define DMP_1_0L    122
#define DMP_1_5H    124
#define DMP_1_5L    126
#define DMP_TMP1AH    128
#define DMP_TMP1AL    130
#define DMP_TMP2AH    132
#define DMP_TMP2AL    134
#define DMP_TMP3AH    136
#define DMP_TMP3AL    138
#define DMP_TMP4AH    140
#define DMP_TMP4AL    142
#define DMP_XACCW    144
#define DMP_TMP5    146
#define DMP_XACCB    148
#define DMP_TMP8    150
#define DMP_YACCB    152
#define DMP_TMP9    154
#define DMP_ZACCB    156
#define DMP_TMP10    158
#define DMP_DZH    160
#define DMP_DZL    162
#define DMP_XGCH    164
#define DMP_XGCL    166
#define DMP_YGCH    168
#define DMP_YGCL    170
#define DMP_ZGCH    172
#define DMP_ZGCL    174
#define DMP_YACCW    176
#define DMP_TMP7    178
#define DMP_AFB1H    180
#define DMP_AFB1L    182
#define DMP_AFB2H    184
#define DMP_AFB2L    186
#define DMP_MAGFBH    188
#define DMP_MAGFBL    190
#define DMP_QT1H    192
#define DMP_QT1L    194
#define DMP_QT2H    196
#define DMP_QT2L    198
#define DMP_QT3H    200
#define DMP_QT3L    202
#define DMP_QT4H    204
#define DMP_QT4L    206
#define DMP_CTRL1H    208
#define DMP_CTRL1L    210
#define DMP_CTRL2H    212
#define DMP_CTRL2L    214
#define DMP_CTRL3H    216
#define DMP_CTRL3L    218
#define DMP_CTRL4H    220
#define DMP_CTRL4L    222
#define DMP_CTRLS1    224
#define DMP_CTRLSF1    226
#define DMP_CTRLS2    228
#define DMP_CTRLSF2    230
#define DMP_CTRLS3    232
#define DMP_CTRLSFNLL    234
#define DMP_CTRLS4    236
#define DMP_CTRLSFNL2    238
#define DMP_CTRLSFNL    240
#define DMP_TMP30    242
#define DMP_CTRLSFJT    244
#define DMP_TMP31    246
#define DMP_TMP11    248
#define DMP_CTRLSF2_2    250
#define DMP_TMP12    252
#define DMP_CTRLSF1_2    254
#define DMP_PREVPTAT    256
#define DMP_ACCZB    258
#define DMP_ACCXB    264
#define DMP_ACCYB    266
#define DMP_1HB    272
#define DMP_1LB    274
#define DMP_0H    276
#define DMP_0L    278
#define DMP_ASR22H    280
#define DMP_ASR22L    282
#define DMP_ASR6H    284
#define DMP_ASR6L    286
#define DMP_TMP13    288
#define DMP_TMP14    290
#define DMP_FINTXH    292
#define DMP_FINTXL    294
#define DMP_FINTYH    296
#define DMP_FINTYL    298
#define DMP_FINTZH    300
#define DMP_FINTZL    302
#define DMP_TMP1BH    304
#define DMP_TMP1BL    306
#define DMP_TMP2BH    308
#define DMP_TMP2BL    310
#define DMP_TMP3BH    312
#define DMP_TMP3BL    314
#define DMP_TMP4BH    316
#define DMP_TMP4BL    318
#define DMP_STXG    320
#define DMP_ZCTXG    322
#define DMP_STYG    324
#define DMP_ZCTYG    326
#define DMP_STZG    328
#define DMP_ZCTZG    330
#define DMP_CTRLSFJT2    332
#define DMP_CTRLSFJTCNT    334
#define DMP_PVXG    336
#define DMP_TMP15    338
#define DMP_PVYG    340
#define DMP_TMP16    342
#define DMP_PVZG    344
#define DMP_TMP17    346
#define DMP_MNMFLAGH    352
#define DMP_MNMFLAGL    354
#define DMP_MNMTMH    356
#define DMP_MNMTML    358
#define DMP_MNMTMTHRH    360
#define DMP_MNMTMTHRL    362
#define DMP_MNMTHRH    364
#define DMP_MNMTHRL    366
#define DMP_ACCQD4H    368
#define DMP_ACCQD4L    370
#define DMP_ACCQD5H    372
#define DMP_ACCQD5L    374
#define DMP_ACCQD6H    376
#define DMP_ACCQD6L    378
#define DMP_ACCQD7H    380
#define DMP_ACCQD7L    382
#define DMP_ACCQD0H    384
#define DMP_ACCQD0L    386
#define DMP_ACCQD1H    388
#define DMP_ACCQD1L    390
#define DMP_ACCQD2H    392
#define DMP_ACCQD2L    394
#define DMP_ACCQD3H    396
#define DMP_ACCQD3L    398
#define DMP_XN2H    400
#define DMP_XN2L    402
#define DMP_XN1H    404
#define DMP_XN1L    406
#define DMP_YN2H    408
#define DMP_YN2L    410
#define DMP_YN1H    412
#define DMP_YN1L    414
#define DMP_YH    416
#define DMP_YL    418
#define DMP_B0H    420
#define DMP_B0L    422
#define DMP_A1H    424
#define DMP_A1L    426
#define DMP_A2H    428
#define DMP_A2L    430
#define DMP_SEM1    432
#define DMP_FIFOCNT    434
#define DMP_SH_TH_X    436
#define DMP_PACKET    438
#define DMP_SH_TH_Y    440
#define DMP_FOOTER    442
#define DMP_SH_TH_Z    444
#define DMP_TEMP29    448
#define DMP_TEMP30    450
#define DMP_XACCB_PRE    452
#define DMP_XACCB_PREL    454
#define DMP_YACCB_PRE    456
#define DMP_YACCB_PREL    458
#define DMP_ZACCB_PRE    460
#define DMP_ZACCB_PREL    462
#define DMP_TMP22    464
#define DMP_TAP_TIMER    466
#define DMP_TAP_THX    468
#define DMP_TAP_THY    472
#define DMP_TAP_THZ    476
#define DMP_TAPW_MIN    478
#define DMP_TMP25    480
#define DMP_TMP26    482
#define DMP_TMP27    484
#define DMP_TMP28    486
#define DMP_ORIENT    488
#define DMP_THRSH    490
#define DMP_ENDIANH    492
#define DMP_ENDIANL    494
#define DMP_BLPFNMTCH    496
#define DMP_BLPFNMTCL    498
#define DMP_BLPFNMXH    500
#define DMP_BLPFNMXL    502
#define DMP_BLPFNMYH    504
#define DMP_BLPFNMYL    506
#define DMP_BLPFNMZH    508
#define DMP_BLPFNMZL    510
#define INV_Z_GYRO      (0x10)
#define INV_XYZ_GYRO    (INV_X_GYRO | INV_Y_GYRO | INV_Z_GYRO)
#define INV_XYZ_ACCEL   (0x08)
#define INV_XYZ_COMPASS (0x01)

#define DEFAULT_MPU_HZ  (10)		//100Hz

#define INV_X_GYRO      (0x40)
#define INV_Y_GYRO      (0x20)
#define INV_Z_GYRO      (0x10)
#define INV_XYZ_GYRO    (INV_X_GYRO | INV_Y_GYRO | INV_Z_GYRO)
#define INV_XYZ_ACCEL   (0x08)
#define INV_XYZ_COMPASS (0x01)


#define KEY_CFG_25                  (0)
#define KEY_CFG_24                  (KEY_CFG_25 + 1)
#define KEY_CFG_26                  (KEY_CFG_24 + 1)
#define KEY_CFG_27                  (KEY_CFG_26 + 1)
#define KEY_CFG_21                  (KEY_CFG_27 + 1)
#define KEY_CFG_20                  (KEY_CFG_21 + 1)
#define KEY_CFG_TAP4                (KEY_CFG_20 + 1)
#define KEY_CFG_TAP5                (KEY_CFG_TAP4 + 1)
#define KEY_CFG_TAP6                (KEY_CFG_TAP5 + 1)
#define KEY_CFG_TAP7                (KEY_CFG_TAP6 + 1)
#define KEY_CFG_TAP0                (KEY_CFG_TAP7 + 1)
#define KEY_CFG_TAP1                (KEY_CFG_TAP0 + 1)
#define KEY_CFG_TAP2                (KEY_CFG_TAP1 + 1)
#define KEY_CFG_TAP3                (KEY_CFG_TAP2 + 1)
#define KEY_CFG_TAP_QUANTIZE        (KEY_CFG_TAP3 + 1)
#define KEY_CFG_TAP_JERK            (KEY_CFG_TAP_QUANTIZE + 1)
#define KEY_CFG_DR_INT              (KEY_CFG_TAP_JERK + 1)
#define KEY_CFG_AUTH                (KEY_CFG_DR_INT + 1)
#define KEY_CFG_TAP_SAVE_ACCB       (KEY_CFG_AUTH + 1)
#define KEY_CFG_TAP_CLEAR_STICKY    (KEY_CFG_TAP_SAVE_ACCB + 1)
#define KEY_CFG_FIFO_ON_EVENT       (KEY_CFG_TAP_CLEAR_STICKY + 1)
#define KEY_FCFG_ACCEL_INPUT        (KEY_CFG_FIFO_ON_EVENT + 1)
#define KEY_FCFG_ACCEL_INIT         (KEY_FCFG_ACCEL_INPUT + 1)
#define KEY_CFG_23                  (KEY_FCFG_ACCEL_INIT + 1)
#define KEY_FCFG_1                  (KEY_CFG_23 + 1)
#define KEY_FCFG_3                  (KEY_FCFG_1 + 1)
#define KEY_FCFG_2                  (KEY_FCFG_3 + 1)
#define KEY_CFG_3D                  (KEY_FCFG_2 + 1)
#define KEY_CFG_3B                  (KEY_CFG_3D + 1)
#define KEY_CFG_3C                  (KEY_CFG_3B + 1)
#define KEY_FCFG_5                  (KEY_CFG_3C + 1)
#define KEY_FCFG_4                  (KEY_FCFG_5 + 1)
#define KEY_FCFG_7                  (KEY_FCFG_4 + 1)
#define KEY_FCFG_FSCALE             (KEY_FCFG_7 + 1)
#define KEY_FCFG_AZ                 (KEY_FCFG_FSCALE + 1)
#define KEY_FCFG_6                  (KEY_FCFG_AZ + 1)
#define KEY_FCFG_LSB4               (KEY_FCFG_6 + 1)
#define KEY_CFG_12                  (KEY_FCFG_LSB4 + 1)
#define KEY_CFG_14                  (KEY_CFG_12 + 1)
#define KEY_CFG_15                  (KEY_CFG_14 + 1)
#define KEY_CFG_16                  (KEY_CFG_15 + 1)
#define KEY_CFG_18                  (KEY_CFG_16 + 1)
#define KEY_CFG_6                   (KEY_CFG_18 + 1)
#define KEY_CFG_7                   (KEY_CFG_6 + 1)
#define KEY_CFG_4                   (KEY_CFG_7 + 1)
#define KEY_CFG_5                   (KEY_CFG_4 + 1)
#define KEY_CFG_2                   (KEY_CFG_5 + 1)
#define KEY_CFG_3                   (KEY_CFG_2 + 1)
#define KEY_CFG_1                   (KEY_CFG_3 + 1)
#define KEY_CFG_EXTERNAL            (KEY_CFG_1 + 1)
#define KEY_CFG_8                   (KEY_CFG_EXTERNAL + 1)
#define KEY_CFG_9                   (KEY_CFG_8 + 1)
#define KEY_CFG_ORIENT_3            (KEY_CFG_9 + 1)
#define KEY_CFG_ORIENT_2            (KEY_CFG_ORIENT_3 + 1)
#define KEY_CFG_ORIENT_1            (KEY_CFG_ORIENT_2 + 1)
#define KEY_CFG_GYRO_SOURCE         (KEY_CFG_ORIENT_1 + 1)
#define KEY_CFG_ORIENT_IRQ_1        (KEY_CFG_GYRO_SOURCE + 1)
#define KEY_CFG_ORIENT_IRQ_2        (KEY_CFG_ORIENT_IRQ_1 + 1)
#define KEY_CFG_ORIENT_IRQ_3        (KEY_CFG_ORIENT_IRQ_2 + 1)
#define KEY_FCFG_MAG_VAL            (KEY_CFG_ORIENT_IRQ_3 + 1)
#define KEY_FCFG_MAG_MOV            (KEY_FCFG_MAG_VAL + 1)
#define KEY_CFG_LP_QUAT             (KEY_FCFG_MAG_MOV + 1)

/* MPU6050 keys */
#define KEY_CFG_ACCEL_FILTER        (KEY_CFG_LP_QUAT + 1)
#define KEY_CFG_MOTION_BIAS         (KEY_CFG_ACCEL_FILTER + 1)
#define KEY_TEMPLABEL               (KEY_CFG_MOTION_BIAS + 1)

#define KEY_D_0_22                  (KEY_TEMPLABEL + 1)
#define KEY_D_0_24                  (KEY_D_0_22 + 1)
#define KEY_D_0_36                  (KEY_D_0_24 + 1)
#define KEY_D_0_52                  (KEY_D_0_36 + 1)
#define KEY_D_0_96                  (KEY_D_0_52 + 1)
#define KEY_D_0_104                 (KEY_D_0_96 + 1)
#define KEY_D_0_108                 (KEY_D_0_104 + 1)
#define KEY_D_0_163                 (KEY_D_0_108 + 1)
#define KEY_D_0_188                 (KEY_D_0_163 + 1)
#define KEY_D_0_192                 (KEY_D_0_188 + 1)
#define KEY_D_0_224                 (KEY_D_0_192 + 1)
#define KEY_D_0_228                 (KEY_D_0_224 + 1)
#define KEY_D_0_232                 (KEY_D_0_228 + 1)
#define KEY_D_0_236                 (KEY_D_0_232 + 1)

#define KEY_DMP_PREVPTAT            (KEY_D_0_236 + 1)
#define KEY_D_1_2                   (KEY_DMP_PREVPTAT + 1)
#define KEY_D_1_4                   (KEY_D_1_2 + 1)
#define KEY_D_1_8                   (KEY_D_1_4 + 1)
#define KEY_D_1_10                  (KEY_D_1_8 + 1)
#define KEY_D_1_24                  (KEY_D_1_10 + 1)
#define KEY_D_1_28                  (KEY_D_1_24 + 1)
#define KEY_D_1_36                  (KEY_D_1_28 + 1)
#define KEY_D_1_40                  (KEY_D_1_36 + 1)
#define KEY_D_1_44                  (KEY_D_1_40 + 1)
#define KEY_D_1_72                  (KEY_D_1_44 + 1)
#define KEY_D_1_74                  (KEY_D_1_72 + 1)
#define KEY_D_1_79                  (KEY_D_1_74 + 1)
#define KEY_D_1_88                  (KEY_D_1_79 + 1)
#define KEY_D_1_90                  (KEY_D_1_88 + 1)
#define KEY_D_1_92                  (KEY_D_1_90 + 1)
#define KEY_D_1_96                  (KEY_D_1_92 + 1)
#define KEY_D_1_98                  (KEY_D_1_96 + 1)
#define KEY_D_1_100                 (KEY_D_1_98 + 1)
#define KEY_D_1_106                 (KEY_D_1_100 + 1)
#define KEY_D_1_108                 (KEY_D_1_106 + 1)
#define KEY_D_1_112                 (KEY_D_1_108 + 1)
#define KEY_D_1_128                 (KEY_D_1_112 + 1)
#define KEY_D_1_152                 (KEY_D_1_128 + 1)
#define KEY_D_1_160                 (KEY_D_1_152 + 1)
#define KEY_D_1_168                 (KEY_D_1_160 + 1)
#define KEY_D_1_175                 (KEY_D_1_168 + 1)
#define KEY_D_1_176                 (KEY_D_1_175 + 1)
#define KEY_D_1_178                 (KEY_D_1_176 + 1)
#define KEY_D_1_179                 (KEY_D_1_178 + 1)
#define KEY_D_1_218                 (KEY_D_1_179 + 1)
#define KEY_D_1_232                 (KEY_D_1_218 + 1)
#define KEY_D_1_236                 (KEY_D_1_232 + 1)
#define KEY_D_1_240                 (KEY_D_1_236 + 1)
#define KEY_D_1_244                 (KEY_D_1_240 + 1)
#define KEY_D_1_250                 (KEY_D_1_244 + 1)
#define KEY_D_1_252                 (KEY_D_1_250 + 1)
#define KEY_D_2_12                  (KEY_D_1_252 + 1)
#define KEY_D_2_96                  (KEY_D_2_12 + 1)
#define KEY_D_2_108                 (KEY_D_2_96 + 1)
#define KEY_D_2_208                 (KEY_D_2_108 + 1)
#define KEY_FLICK_MSG               (KEY_D_2_208 + 1)
#define KEY_FLICK_COUNTER           (KEY_FLICK_MSG + 1)
#define KEY_FLICK_LOWER             (KEY_FLICK_COUNTER + 1)
#define KEY_CFG_FLICK_IN            (KEY_FLICK_LOWER + 1)
#define KEY_FLICK_UPPER             (KEY_CFG_FLICK_IN + 1)
#define KEY_CGNOTICE_INTR           (KEY_FLICK_UPPER + 1)
#define KEY_D_2_224                 (KEY_CGNOTICE_INTR + 1)
#define KEY_D_2_244                 (KEY_D_2_224 + 1)
#define KEY_D_2_248                 (KEY_D_2_244 + 1)
#define KEY_D_2_252                 (KEY_D_2_248 + 1)

#define KEY_D_GYRO_BIAS_X               (KEY_D_2_252 + 1)
#define KEY_D_GYRO_BIAS_Y               (KEY_D_GYRO_BIAS_X + 1)
#define KEY_D_GYRO_BIAS_Z               (KEY_D_GYRO_BIAS_Y + 1)
#define KEY_D_ACC_BIAS_X                (KEY_D_GYRO_BIAS_Z + 1)
#define KEY_D_ACC_BIAS_Y                (KEY_D_ACC_BIAS_X + 1)
#define KEY_D_ACC_BIAS_Z                (KEY_D_ACC_BIAS_Y + 1)
#define KEY_D_GYRO_ENABLE               (KEY_D_ACC_BIAS_Z + 1)
#define KEY_D_ACCEL_ENABLE              (KEY_D_GYRO_ENABLE + 1)
#define KEY_D_QUAT_ENABLE               (KEY_D_ACCEL_ENABLE +1)
#define KEY_D_OUTPUT_ENABLE             (KEY_D_QUAT_ENABLE + 1)
#define KEY_D_CR_TIME_G                 (KEY_D_OUTPUT_ENABLE + 1)
#define KEY_D_CR_TIME_A                 (KEY_D_CR_TIME_G + 1)
#define KEY_D_CR_TIME_Q                 (KEY_D_CR_TIME_A + 1)
#define KEY_D_CS_TAX                    (KEY_D_CR_TIME_Q + 1)
#define KEY_D_CS_TAY                    (KEY_D_CS_TAX + 1)
#define KEY_D_CS_TAZ                    (KEY_D_CS_TAY + 1)
#define KEY_D_CS_TGX                    (KEY_D_CS_TAZ + 1)
#define KEY_D_CS_TGY                    (KEY_D_CS_TGX + 1)
#define KEY_D_CS_TGZ                    (KEY_D_CS_TGY + 1)
#define KEY_D_CS_TQ0                    (KEY_D_CS_TGZ + 1)
#define KEY_D_CS_TQ1                    (KEY_D_CS_TQ0 + 1)
#define KEY_D_CS_TQ2                    (KEY_D_CS_TQ1 + 1)
#define KEY_D_CS_TQ3                    (KEY_D_CS_TQ2 + 1)

/* Compass keys */
#define KEY_CPASS_BIAS_X            (KEY_D_CS_TQ3 + 1)
#define KEY_CPASS_BIAS_Y            (KEY_CPASS_BIAS_X + 1)
#define KEY_CPASS_BIAS_Z            (KEY_CPASS_BIAS_Y + 1)
#define KEY_CPASS_MTX_00            (KEY_CPASS_BIAS_Z + 1)
#define KEY_CPASS_MTX_01            (KEY_CPASS_MTX_00 + 1)
#define KEY_CPASS_MTX_02            (KEY_CPASS_MTX_01 + 1)
#define KEY_CPASS_MTX_10            (KEY_CPASS_MTX_02 + 1)
#define KEY_CPASS_MTX_11            (KEY_CPASS_MTX_10 + 1)
#define KEY_CPASS_MTX_12            (KEY_CPASS_MTX_11 + 1)
#define KEY_CPASS_MTX_20            (KEY_CPASS_MTX_12 + 1)
#define KEY_CPASS_MTX_21            (KEY_CPASS_MTX_20 + 1)
#define KEY_CPASS_MTX_22            (KEY_CPASS_MTX_21 + 1)

/* Gesture Keys */
#define KEY_DMP_TAPW_MIN            (KEY_CPASS_MTX_22 + 1)
#define KEY_DMP_TAP_THR_X           (KEY_DMP_TAPW_MIN + 1)
#define KEY_DMP_TAP_THR_Y           (KEY_DMP_TAP_THR_X + 1)
#define KEY_DMP_TAP_THR_Z           (KEY_DMP_TAP_THR_Y + 1)
#define KEY_DMP_SH_TH_Y             (KEY_DMP_TAP_THR_Z + 1)
#define KEY_DMP_SH_TH_X             (KEY_DMP_SH_TH_Y + 1)
#define KEY_DMP_SH_TH_Z             (KEY_DMP_SH_TH_X + 1)
#define KEY_DMP_ORIENT              (KEY_DMP_SH_TH_Z + 1)
#define KEY_D_ACT0                  (KEY_DMP_ORIENT + 1)
#define KEY_D_ACSX                  (KEY_D_ACT0 + 1)
#define KEY_D_ACSY                  (KEY_D_ACSX + 1)
#define KEY_D_ACSZ                  (KEY_D_ACSY + 1)

#define KEY_X_GRT_Y_TMP             (KEY_D_ACSZ + 1)
#define KEY_SKIP_X_GRT_Y_TMP        (KEY_X_GRT_Y_TMP + 1)
#define KEY_SKIP_END_COMPARE        (KEY_SKIP_X_GRT_Y_TMP + 1)
#define KEY_END_COMPARE_Y_X_TMP2    (KEY_SKIP_END_COMPARE + 1)       
#define KEY_CFG_ANDROID_ORIENT_INT  (KEY_END_COMPARE_Y_X_TMP2 + 1)
#define KEY_NO_ORIENT_INTERRUPT     (KEY_CFG_ANDROID_ORIENT_INT + 1)
#define KEY_END_COMPARE_Y_X_TMP     (KEY_NO_ORIENT_INTERRUPT + 1)
#define KEY_END_ORIENT_1            (KEY_END_COMPARE_Y_X_TMP + 1)
#define KEY_END_COMPARE_Y_X         (KEY_END_ORIENT_1 + 1) 
#define KEY_END_ORIENT              (KEY_END_COMPARE_Y_X + 1)
#define KEY_X_GRT_Y                 (KEY_END_ORIENT + 1)
#define KEY_NOT_TIME_MINUS_1        (KEY_X_GRT_Y + 1)       
#define KEY_END_COMPARE_Y_X_TMP3    (KEY_NOT_TIME_MINUS_1 + 1) 
#define KEY_X_GRT_Y_TMP2            (KEY_END_COMPARE_Y_X_TMP3 + 1)

/* Authenticate Keys */
#define KEY_D_AUTH_OUT              (KEY_X_GRT_Y_TMP2 + 1)
#define KEY_D_AUTH_IN               (KEY_D_AUTH_OUT + 1)
#define KEY_D_AUTH_A                (KEY_D_AUTH_IN + 1)
#define KEY_D_AUTH_B                (KEY_D_AUTH_A + 1)

/* Pedometer standalone only keys */
#define KEY_D_PEDSTD_BP_B           (KEY_D_AUTH_B + 1)
#define KEY_D_PEDSTD_HP_A           (KEY_D_PEDSTD_BP_B + 1)
#define KEY_D_PEDSTD_HP_B           (KEY_D_PEDSTD_HP_A + 1)
#define KEY_D_PEDSTD_BP_A4          (KEY_D_PEDSTD_HP_B + 1)
#define KEY_D_PEDSTD_BP_A3          (KEY_D_PEDSTD_BP_A4 + 1)
#define KEY_D_PEDSTD_BP_A2          (KEY_D_PEDSTD_BP_A3 + 1)
#define KEY_D_PEDSTD_BP_A1          (KEY_D_PEDSTD_BP_A2 + 1)
#define KEY_D_PEDSTD_INT_THRSH      (KEY_D_PEDSTD_BP_A1 + 1)
#define KEY_D_PEDSTD_CLIP           (KEY_D_PEDSTD_INT_THRSH + 1)
#define KEY_D_PEDSTD_SB             (KEY_D_PEDSTD_CLIP + 1)
#define KEY_D_PEDSTD_SB_TIME        (KEY_D_PEDSTD_SB + 1)
#define KEY_D_PEDSTD_PEAKTHRSH      (KEY_D_PEDSTD_SB_TIME + 1)
#define KEY_D_PEDSTD_TIML           (KEY_D_PEDSTD_PEAKTHRSH + 1)
#define KEY_D_PEDSTD_TIMH           (KEY_D_PEDSTD_TIML + 1)
#define KEY_D_PEDSTD_PEAK           (KEY_D_PEDSTD_TIMH + 1)
#define KEY_D_PEDSTD_TIMECTR        (KEY_D_PEDSTD_PEAK + 1)
#define KEY_D_PEDSTD_STEPCTR        (KEY_D_PEDSTD_TIMECTR + 1)
#define KEY_D_PEDSTD_WALKTIME       (KEY_D_PEDSTD_STEPCTR + 1)
#define KEY_D_PEDSTD_DECI           (KEY_D_PEDSTD_WALKTIME + 1)

/*Host Based No Motion*/
#define KEY_D_HOST_NO_MOT           (KEY_D_PEDSTD_DECI + 1)

/* EIS keys */
#define KEY_P_EIS_FIFO_FOOTER       (KEY_D_HOST_NO_MOT + 1)
#define KEY_P_EIS_FIFO_YSHIFT       (KEY_P_EIS_FIFO_FOOTER + 1)
#define KEY_P_EIS_DATA_RATE         (KEY_P_EIS_FIFO_YSHIFT + 1)
#define KEY_P_EIS_FIFO_XSHIFT       (KEY_P_EIS_DATA_RATE + 1)
#define KEY_P_EIS_FIFO_SYNC         (KEY_P_EIS_FIFO_XSHIFT + 1)
#define KEY_P_EIS_FIFO_ZSHIFT       (KEY_P_EIS_FIFO_SYNC + 1)
#define KEY_P_EIS_FIFO_READY        (KEY_P_EIS_FIFO_ZSHIFT + 1)
#define KEY_DMP_FOOTER              (KEY_P_EIS_FIFO_READY + 1)
#define KEY_DMP_INTX_HC             (KEY_DMP_FOOTER + 1)
#define KEY_DMP_INTX_PH             (KEY_DMP_INTX_HC + 1)
#define KEY_DMP_INTX_SH             (KEY_DMP_INTX_PH + 1)
#define KEY_DMP_AINV_SH             (KEY_DMP_INTX_SH + 1)
#define KEY_DMP_A_INV_XH            (KEY_DMP_AINV_SH + 1)
#define KEY_DMP_AINV_PH             (KEY_DMP_A_INV_XH + 1)
#define KEY_DMP_CTHX_H              (KEY_DMP_AINV_PH + 1)
#define KEY_DMP_CTHY_H              (KEY_DMP_CTHX_H + 1)
#define KEY_DMP_CTHZ_H              (KEY_DMP_CTHY_H + 1)
#define KEY_DMP_NCTHX_H             (KEY_DMP_CTHZ_H + 1)
#define KEY_DMP_NCTHY_H             (KEY_DMP_NCTHX_H + 1)
#define KEY_DMP_NCTHZ_H             (KEY_DMP_NCTHY_H + 1)
#define KEY_DMP_CTSQ_XH             (KEY_DMP_NCTHZ_H + 1)
#define KEY_DMP_CTSQ_YH             (KEY_DMP_CTSQ_XH + 1)
#define KEY_DMP_CTSQ_ZH             (KEY_DMP_CTSQ_YH + 1)
#define KEY_DMP_INTX_H              (KEY_DMP_CTSQ_ZH + 1)
#define KEY_DMP_INTY_H              (KEY_DMP_INTX_H + 1)
#define KEY_DMP_INTZ_H              (KEY_DMP_INTY_H + 1)
//#define KEY_DMP_HPX_H               (KEY_DMP_INTZ_H + 1)
//#define KEY_DMP_HPY_H               (KEY_DMP_HPX_H + 1)
//#define KEY_DMP_HPZ_H               (KEY_DMP_HPY_H + 1)

/* Stream keys */
#define KEY_STREAM_P_GYRO_Z         (KEY_DMP_INTZ_H + 1)
#define KEY_STREAM_P_GYRO_Y         (KEY_STREAM_P_GYRO_Z + 1)
#define KEY_STREAM_P_GYRO_X         (KEY_STREAM_P_GYRO_Y + 1)
#define KEY_STREAM_P_TEMP           (KEY_STREAM_P_GYRO_X + 1)
#define KEY_STREAM_P_AUX_Y          (KEY_STREAM_P_TEMP + 1)
#define KEY_STREAM_P_AUX_X          (KEY_STREAM_P_AUX_Y + 1)
#define KEY_STREAM_P_AUX_Z          (KEY_STREAM_P_AUX_X + 1)
#define KEY_STREAM_P_ACCEL_Y        (KEY_STREAM_P_AUX_Z + 1)
#define KEY_STREAM_P_ACCEL_X        (KEY_STREAM_P_ACCEL_Y + 1)
#define KEY_STREAM_P_FOOTER         (KEY_STREAM_P_ACCEL_X + 1)
#define KEY_STREAM_P_ACCEL_Z        (KEY_STREAM_P_FOOTER + 1)

#define NUM_KEYS                    (KEY_STREAM_P_ACCEL_Z + 1)

typedef struct {
    uint16_t key;
    uint16_t addr;
} tKeyLabel;

#define DINA0A 0x0a
#define DINA22 0x22
#define DINA42 0x42
#define DINA5A 0x5a

#define DINA06 0x06
#define DINA0E 0x0e
#define DINA16 0x16
#define DINA1E 0x1e
#define DINA26 0x26
#define DINA2E 0x2e
#define DINA36 0x36
#define DINA3E 0x3e
#define DINA46 0x46
#define DINA4E 0x4e
#define DINA56 0x56
#define DINA5E 0x5e
#define DINA66 0x66
#define DINA6E 0x6e
#define DINA76 0x76
#define DINA7E 0x7e

#define DINA00 0x00
#define DINA08 0x08
#define DINA10 0x10
#define DINA18 0x18
#define DINA20 0x20
#define DINA28 0x28
#define DINA30 0x30
#define DINA38 0x38
#define DINA40 0x40
#define DINA48 0x48
#define DINA50 0x50
#define DINA58 0x58
#define DINA60 0x60
#define DINA68 0x68
#define DINA70 0x70
#define DINA78 0x78

#define DINA04 0x04
#define DINA0C 0x0c
#define DINA14 0x14
#define DINA1C 0x1C
#define DINA24 0x24
#define DINA2C 0x2c
#define DINA34 0x34
#define DINA3C 0x3c
#define DINA44 0x44
#define DINA4C 0x4c
#define DINA54 0x54
#define DINA5C 0x5c
#define DINA64 0x64
#define DINA6C 0x6c
#define DINA74 0x74
#define DINA7C 0x7c

#define DINA01 0x01
#define DINA09 0x09
#define DINA11 0x11
#define DINA19 0x19
#define DINA21 0x21
#define DINA29 0x29
#define DINA31 0x31
#define DINA39 0x39
#define DINA41 0x41
#define DINA49 0x49
#define DINA51 0x51
#define DINA59 0x59
#define DINA61 0x61
#define DINA69 0x69
#define DINA71 0x71
#define DINA79 0x79

#define DINA25 0x25
#define DINA2D 0x2d
#define DINA35 0x35
#define DINA3D 0x3d
#define DINA4D 0x4d
#define DINA55 0x55
#define DINA5D 0x5D
#define DINA6D 0x6d
#define DINA75 0x75
#define DINA7D 0x7d

#define DINADC 0xdc
#define DINAF2 0xf2
#define DINAAB 0xab
#define DINAAA 0xaa
#define DINAF1 0xf1
#define DINADF 0xdf
#define DINADA 0xda
#define DINAB1 0xb1
#define DINAB9 0xb9
#define DINAF3 0xf3
#define DINA8B 0x8b
#define DINAA3 0xa3
#define DINA91 0x91
#define DINAB6 0xb6
#define DINAB4 0xb4


#define DINC00 0x00
#define DINC01 0x01
#define DINC02 0x02
#define DINC03 0x03
#define DINC08 0x08
#define DINC09 0x09
#define DINC0A 0x0a
#define DINC0B 0x0b
#define DINC10 0x10
#define DINC11 0x11
#define DINC12 0x12
#define DINC13 0x13
#define DINC18 0x18
#define DINC19 0x19
#define DINC1A 0x1a
#define DINC1B 0x1b

#define DINC20 0x20
#define DINC21 0x21
#define DINC22 0x22
#define DINC23 0x23
#define DINC28 0x28
#define DINC29 0x29
#define DINC2A 0x2a
#define DINC2B 0x2b
#define DINC30 0x30
#define DINC31 0x31
#define DINC32 0x32
#define DINC33 0x33
#define DINC38 0x38
#define DINC39 0x39
#define DINC3A 0x3a
#define DINC3B 0x3b

#define DINC40 0x40
#define DINC41 0x41
#define DINC42 0x42
#define DINC43 0x43
#define DINC48 0x48
#define DINC49 0x49
#define DINC4A 0x4a
#define DINC4B 0x4b
#define DINC50 0x50
#define DINC51 0x51
#define DINC52 0x52
#define DINC53 0x53
#define DINC58 0x58
#define DINC59 0x59
#define DINC5A 0x5a
#define DINC5B 0x5b

#define DINC60 0x60
#define DINC61 0x61
#define DINC62 0x62
#define DINC63 0x63
#define DINC68 0x68
#define DINC69 0x69
#define DINC6A 0x6a
#define DINC6B 0x6b
#define DINC70 0x70
#define DINC71 0x71
#define DINC72 0x72
#define DINC73 0x73
#define DINC78 0x78
#define DINC79 0x79
#define DINC7A 0x7a
#define DINC7B 0x7b

#define DIND40 0x40


#define DINA80 0x80
#define DINA90 0x90
#define DINAA0 0xa0
#define DINAC9 0xc9
#define DINACB 0xcb
#define DINACD 0xcd
#define DINACF 0xcf
#define DINAC8 0xc8
#define DINACA 0xca
#define DINACC 0xcc
#define DINACE 0xce
#define DINAD8 0xd8
#define DINADD 0xdd
#define DINAF8 0xf0
#define DINAFE 0xfe

#define DINBF8 0xf8
#define DINAC0 0xb0
#define DINAC1 0xb1
#define DINAC2 0xb4
#define DINAC3 0xb5
#define DINAC4 0xb8
#define DINAC5 0xb9
#define DINBC0 0xc0
#define DINBC2 0xc2
#define DINBC4 0xc4
#define DINBC6 0xc6

  // mpu_motionxxx.h
#define TAP_X               (0x01)
#define TAP_Y               (0x02)
#define TAP_Z               (0x04)
#define TAP_XYZ             (0x07)

#define TAP_X_UP            (0x01)
#define TAP_X_DOWN          (0x02)
#define TAP_Y_UP            (0x03)
#define TAP_Y_DOWN          (0x04)
#define TAP_Z_UP            (0x05)
#define TAP_Z_DOWN          (0x06)

#define ANDROID_ORIENT_PORTRAIT             (0x00)
#define ANDROID_ORIENT_LANDSCAPE            (0x01)
#define ANDROID_ORIENT_REVERSE_PORTRAIT     (0x02)
#define ANDROID_ORIENT_REVERSE_LANDSCAPE    (0x03)

#define DMP_INT_GESTURE     (0x01)
#define DMP_INT_CONTINUOUS  (0x02)

#define DMP_FEATURE_TAP             (0x001)
#define DMP_FEATURE_ANDROID_ORIENT  (0x002)
#define DMP_FEATURE_LP_QUAT         (0x004)
#define DMP_FEATURE_PEDOMETER       (0x008)
#define DMP_FEATURE_6X_LP_QUAT      (0x010)
#define DMP_FEATURE_GYRO_CAL        (0x020)
#define DMP_FEATURE_SEND_RAW_ACCEL  (0x040)
#define DMP_FEATURE_SEND_RAW_GYRO   (0x080)
#define DMP_FEATURE_SEND_CAL_GYRO   (0x100)

#define INV_WXYZ_QUAT       (0x100)

// typedef uint32_t size_t;

// void *
// memcpy (void *dest, const void *src, size_t len)
// {
//   char *d = dest;
//   const char *s = src;
//   while (len--)
//     *d++ = *s++;
//   return dest;
// }
// int32_t memcmp(const void *vl, const void *vr, size_t n)
// {
//     const uint8_t *l=vl, *r=vr;
//     for (; n && *l == *r; n--, l++, r++);
//     return n ? *l-*r : 0;
// }

// void *memset(void * dest, int32_t c, size_t n)
// {
//     uint8_t *s = dest;
//     size_t k;

//     /* Fill head and tail with minimal branching. Each
//      * conditional ensures that all the subsequently used
//      * offsets are well-defined and in the dest region. */

//     if (!n) return dest;
//     s[0] = s[n-1] = c;
//     if (n <= 2) return dest;
//     s[1] = s[n-2] = c;
//     s[2] = s[n-3] = c;
//     if (n <= 6) return dest;
//     s[3] = s[n-4] = c;
//     if (n <= 8) return dest;

//     /* Advance pointer to align it at a 4-byte boundary,
//      * and truncate n to a multiple of 4. The previous code
//      * already took care of any head/tail that get cut off
//      * by the alignment. */

//     k = -(uint32_t)s & 3;
//     s += k;
//     n -= k;
//     n &= -4;
//     n /= 4;

//     uint32_t *ws = (uint32_t *)s;
//     uint32_t wc = c & 0xFF;
//     wc |= ((wc << 8) | (wc << 16) | (wc << 24));

//     /* Pure C fallback with no aliasing violations. */
//     for (; n; n--, ws++) *ws = wc;

//     return dest;
// }

/* Set up functions. */
int32_t dmp_load_motion_driver_firmware(void);
int32_t dmp_set_fifo_rate(uint16_t rate);
int32_t dmp_get_fifo_rate(uint16_t *rate);
int32_t dmp_enable_feature(uint16_t mask);
int32_t dmp_get_enabled_features(uint16_t *mask);
int32_t dmp_set_interrupt_mode(uint8_t mode);
int32_t dmp_set_orientation(uint16_t orient);
int32_t dmp_set_gyro_bias(int64_t *bias);
int32_t dmp_set_accel_bias(int64_t *bias);

/* Tap functions. */
int32_t dmp_register_tap_cb(void (*func)(uint8_t, uint8_t));
int32_t dmp_set_tap_thresh(uint8_t axis, uint16_t thresh);
int32_t dmp_set_tap_axes(uint8_t axis);
int32_t dmp_set_tap_count(uint8_t min_taps);
int32_t dmp_set_tap_time(uint16_t time);
int32_t dmp_set_tap_time_multi(uint16_t time);
int32_t dmp_set_shake_reject_thresh(int64_t sf, uint16_t thresh);
int32_t dmp_set_shake_reject_time(uint16_t time);
int32_t dmp_set_shake_reject_timeout(uint16_t time);

/* Android orientation functions. */
int32_t dmp_register_android_orient_cb(void (*func)(uint8_t));

/* LP quaternion functions. */
int32_t dmp_enable_lp_quat(uint8_t enable);
int32_t dmp_enable_6x_lp_quat(uint8_t enable);

/* Pedometer functions. */
int32_t dmp_get_pedometer_step_count(uint64_t *count);
int32_t dmp_set_pedometer_step_count(uint64_t count);
int32_t dmp_get_pedometer_walk_time(uint64_t *time);
int32_t dmp_set_pedometer_walk_time(uint64_t time);

/* DMP gyro calibration functions. */
int32_t dmp_enable_gyro_cal(uint8_t enable);

/* Read function. This function should be called whenever the MPU interrupt is
 * detected.
 */
int32_t dmp_read_fifo(short *gyro, short *accel, int64_t *quat,
    uint64_t *timestamp, short *sensors, uint8_t *more);
/* Set up APIs */
int32_t mpu_init(void);
int32_t mpu_init_slave(void);
int32_t mpu_set_bypass(uint8_t bypass_on);

/* Configuration APIs */
int32_t mpu_lp_accel_mode(uint8_t rate);
int32_t mpu_lp_motion_interrupt(uint16_t thresh, uint8_t time,
    uint8_t lpa_freq);
int32_t mpu_set_int_level(uint8_t active_low);
int32_t mpu_set_int_latched(uint8_t enable);

int32_t mpu_set_dmp_state(uint8_t enable);
int32_t mpu_get_dmp_state(uint8_t *enabled);

int32_t mpu_get_lpf(uint16_t *lpf);
int32_t mpu_set_lpf(uint16_t lpf);

int32_t mpu_get_gyro_fsr(uint16_t *fsr);
int32_t mpu_set_gyro_fsr(uint16_t fsr);

int32_t mpu_get_accel_fsr(uint8_t *fsr);
int32_t mpu_set_accel_fsr(uint8_t fsr);

int32_t mpu_get_compass_fsr(uint16_t *fsr);

int32_t mpu_get_gyro_sens(float *sens);
int32_t mpu_get_accel_sens(uint16_t *sens);

int32_t mpu_get_sample_rate(uint16_t *rate);
int32_t mpu_set_sample_rate(uint16_t rate);
int32_t mpu_get_compass_sample_rate(uint16_t *rate);
int32_t mpu_set_compass_sample_rate(uint16_t rate);

int32_t mpu_get_fifo_config(uint8_t *sensors);
int32_t mpu_configure_fifo(uint8_t sensors);

int32_t mpu_get_power_state(uint8_t *power_on);
int32_t mpu_set_sensors(uint8_t sensors);

int32_t mpu_set_accel_bias(const int64_t *accel_bias);

/* Data getter/setter APIs */
int32_t mpu_get_gyro_reg(short *data, uint64_t *timestamp);
int32_t mpu_get_accel_reg(short *data, uint64_t *timestamp);
int32_t mpu_get_compass_reg(short *data, uint64_t *timestamp);
int32_t mpu_get_temperature(int64_t *data, uint64_t *timestamp);

int32_t mpu_get_int_status(short *status);
int32_t mpu_read_fifo(short *gyro, short *accel, uint64_t *timestamp,
    uint8_t *sensors, uint8_t *more);
int32_t mpu_read_fifo_stream(uint16_t length, uint8_t *data,
    uint8_t *more);
int32_t mpu_reset_fifo(void);

int32_t mpu_write_mem(uint16_t mem_addr, uint16_t length,
    uint8_t *data);
int32_t mpu_read_mem(uint16_t mem_addr, uint16_t length,
    uint8_t *data);
int32_t mpu_load_firmware(uint16_t length, const uint8_t *firmware,
    uint16_t start_addr, uint16_t sample_rate);

int32_t mpu_reg_dump(void);
int32_t mpu_read_reg(uint8_t reg, uint8_t *data);
int32_t mpu_run_self_test(int64_t *gyro, int64_t *accel);
int32_t mpu_register_tap_cb(void (*func)(uint8_t, uint8_t));

void mget_ms(uint64_t *time);
uint16_t inv_row_2_scale(const signed char *row);
uint16_t inv_orientation_matrix_to_scalar(const signed char *mtx);

int32_t mpu_dmp_init(dev::gpio sda, dev::gpio scl);
int32_t mpu_dmp_get_data(float *gx,float *gy,float *gz,int16_t* ax, int16_t* ay,int16_t* az);

/*
 $License:
    Copyright (C) 2011-2012 InvenSense Corporation, All Rights Reserved.
    See included License.txt for License information.
 $
 */
/**
 *  @addtogroup  DRIVERS Sensor Driver Layer
 *  @brief       Hardware drivers to communicate with sensors via I2C.
 *
 *  @{
 *      @file       inv_mpu_dmp_motion_driver.c
 *      @brief      DMP image and interface functions.
 *      @details    All functions are preceded by the dmp_ prefix to
 *                  differentiate among MPL and general driver function calls.
 */
// #include "log.h"
// #include <stdint.h>
// #include <stdlib.h>
// #include <string.h>
// #include <math.h>
// #include "inv_mpu.h"
// #include "inv_mpu_dmp_motion_driver.h"
// #include "dmpKey.h"
// #include "dmpmap.h"

// #define TAG "inv_mpu_dmp_motion_driver"


#define  MOTION_DRIVER_TARGET_MSP430

/* The following functions must be defined for this platform:
 * i2c_write(uint8_t slave_addr, uint8_t reg_addr,
 *      uint8_t length, uint8_t const *data)
 * i2c_read(uint8_t slave_addr, uint8_t reg_addr,
 *      uint8_t length, uint8_t *data)
 * delay_ms(uint64_t num_ms)
 * get_ms(uint64_t *count)
 */
#if defined MOTION_DRIVER_TARGET_MSP430
//#include "msp430.h"
//#include "msp430_clock.h"
#define delay_ms(...)    //delay_ms
#define get_ms(...)      //mget_ms
// #define log_i 		//printf
// #define log_e  		//printf

#elif defined EMPL_TARGET_MSP430
#include "msp430.h"
#include "msp430_clock.h"
#include "log.h"
#define delay_ms    msp430_delay_ms
#define get_ms      msp430_get_clock_ms
#define log_i       MPL_LOGI
#define log_e       MPL_LOGE

#elif defined EMPL_TARGET_UC3L0
/* Instead of using the standard TWI driver from the ASF library, we're using
 * a TWI driver that follows the slave address + register address convention.
 */
#include "delay.h"
#include "sysclk.h"
#include "log.h"
#include "uc3l0_clock.h"
/* delay_ms is a function already defined in ASF. */
#define get_ms  uc3l0_get_clock_ms
#define log_i       MPL_LOGI
#define log_e       MPL_LOGE

#else
#error  Gyro driver is missing the system layer implementations.
#endif

/* These defines are copied from dmpDefaultMPU6050.c in the general MPL
 * releases. These defines may change for each DMP image, so be sure to modify
 * these values when switching to a new image.
 */
#define CFG_LP_QUAT             (2712)
#define END_ORIENT_TEMP         (1866)
#define CFG_27                  (2742)
#define CFG_20                  (2224)
#define CFG_23                  (2745)
#define CFG_FIFO_ON_EVENT       (2690)
#define END_PREDICTION_UPDATE   (1761)
#define CGNOTICE_INTR           (2620)
#define X_GRT_Y_TMP             (1358)
#define CFG_DR_INT              (1029)
#define CFG_AUTH                (1035)
#define UPDATE_PROP_ROT         (1835)
#define END_COMPARE_Y_X_TMP2    (1455)
#define SKIP_X_GRT_Y_TMP        (1359)
#define SKIP_END_COMPARE        (1435)
#define FCFG_3                  (1088)
#define FCFG_2                  (1066)
#define FCFG_1                  (1062)
#define END_COMPARE_Y_X_TMP3    (1434)
#define FCFG_7                  (1073)
#define FCFG_6                  (1106)
#define FLAT_STATE_END          (1713)
#define SWING_END_4             (1616)
#define SWING_END_2             (1565)
#define SWING_END_3             (1587)
#define SWING_END_1             (1550)
#define CFG_8                   (2718)
#define CFG_15                  (2727)
#define CFG_16                  (2746)
#define CFG_EXT_GYRO_BIAS       (1189)
#define END_COMPARE_Y_X_TMP     (1407)
#define DO_NOT_UPDATE_PROP_ROT  (1839)
#define CFG_7                   (1205)
#define FLAT_STATE_END_TEMP     (1683)
#define END_COMPARE_Y_X         (1484)
#define SKIP_SWING_END_1        (1551)
#define SKIP_SWING_END_3        (1588)
#define SKIP_SWING_END_2        (1566)
#define TILTG75_START           (1672)
#define CFG_6                   (2753)
#define TILTL75_END             (1669)
#define END_ORIENT              (1884)
#define CFG_FLICK_IN            (2573)
#define TILTL75_START           (1643)
#define CFG_MOTION_BIAS         (1208)
#define X_GRT_Y                 (1408)
#define TEMPLABEL               (2324)
#define CFG_ANDROID_ORIENT_INT  (1853)
#define CFG_GYRO_RAW_DATA       (2722)
#define X_GRT_Y_TMP2            (1379)

#define D_0_22                  (22+512)
#define D_0_24                  (24+512)

#define D_0_36                  (36)
#define D_0_52                  (52)
#define D_0_96                  (96)
#define D_0_104                 (104)
#define D_0_108                 (108)
#define D_0_163                 (163)
#define D_0_188                 (188)
#define D_0_192                 (192)
#define D_0_224                 (224)
#define D_0_228                 (228)
#define D_0_232                 (232)
#define D_0_236                 (236)

#define D_1_2                   (256 + 2)
#define D_1_4                   (256 + 4)
#define D_1_8                   (256 + 8)
#define D_1_10                  (256 + 10)
#define D_1_24                  (256 + 24)
#define D_1_28                  (256 + 28)
#define D_1_36                  (256 + 36)
#define D_1_40                  (256 + 40)
#define D_1_44                  (256 + 44)
#define D_1_72                  (256 + 72)
#define D_1_74                  (256 + 74)
#define D_1_79                  (256 + 79)
#define D_1_88                  (256 + 88)
#define D_1_90                  (256 + 90)
#define D_1_92                  (256 + 92)
#define D_1_96                  (256 + 96)
#define D_1_98                  (256 + 98)
#define D_1_106                 (256 + 106)
#define D_1_108                 (256 + 108)
#define D_1_112                 (256 + 112)
#define D_1_128                 (256 + 144)
#define D_1_152                 (256 + 12)
#define D_1_160                 (256 + 160)
#define D_1_176                 (256 + 176)
#define D_1_178                 (256 + 178)
#define D_1_218                 (256 + 218)
#define D_1_232                 (256 + 232)
#define D_1_236                 (256 + 236)
#define D_1_240                 (256 + 240)
#define D_1_244                 (256 + 244)
#define D_1_250                 (256 + 250)
#define D_1_252                 (256 + 252)
#define D_2_12                  (512 + 12)
#define D_2_96                  (512 + 96)
#define D_2_108                 (512 + 108)
#define D_2_208                 (512 + 208)
#define D_2_224                 (512 + 224)
#define D_2_236                 (512 + 236)
#define D_2_244                 (512 + 244)
#define D_2_248                 (512 + 248)
#define D_2_252                 (512 + 252)

#define CPASS_BIAS_X            (35 * 16 + 4)
#define CPASS_BIAS_Y            (35 * 16 + 8)
#define CPASS_BIAS_Z            (35 * 16 + 12)
#define CPASS_MTX_00            (36 * 16)
#define CPASS_MTX_01            (36 * 16 + 4)
#define CPASS_MTX_02            (36 * 16 + 8)
#define CPASS_MTX_10            (36 * 16 + 12)
#define CPASS_MTX_11            (37 * 16)
#define CPASS_MTX_12            (37 * 16 + 4)
#define CPASS_MTX_20            (37 * 16 + 8)
#define CPASS_MTX_21            (37 * 16 + 12)
#define CPASS_MTX_22            (43 * 16 + 12)
#define D_EXT_GYRO_BIAS_X       (61 * 16)
#define D_EXT_GYRO_BIAS_Y       (61 * 16) + 4
#define D_EXT_GYRO_BIAS_Z       (61 * 16) + 8
#define D_ACT0                  (40 * 16)
#define D_ACSX                  (40 * 16 + 4)
#define D_ACSY                  (40 * 16 + 8)
#define D_ACSZ                  (40 * 16 + 12)

#define FLICK_MSG               (45 * 16 + 4)
#define FLICK_COUNTER           (45 * 16 + 8)
#define FLICK_LOWER             (45 * 16 + 12)
#define FLICK_UPPER             (46 * 16 + 12)

#define D_AUTH_OUT              (992)
#define D_AUTH_IN               (996)
#define D_AUTH_A                (1000)
#define D_AUTH_B                (1004)

#define D_PEDSTD_BP_B           (768 + 0x1C)
#define D_PEDSTD_HP_A           (768 + 0x78)
#define D_PEDSTD_HP_B           (768 + 0x7C)
#define D_PEDSTD_BP_A4          (768 + 0x40)
#define D_PEDSTD_BP_A3          (768 + 0x44)
#define D_PEDSTD_BP_A2          (768 + 0x48)
#define D_PEDSTD_BP_A1          (768 + 0x4C)
#define D_PEDSTD_INT_THRSH      (768 + 0x68)
#define D_PEDSTD_CLIP           (768 + 0x6C)
#define D_PEDSTD_SB             (768 + 0x28)
#define D_PEDSTD_SB_TIME        (768 + 0x2C)
#define D_PEDSTD_PEAKTHRSH      (768 + 0x98)
#define D_PEDSTD_TIML           (768 + 0x2A)
#define D_PEDSTD_TIMH           (768 + 0x2E)
#define D_PEDSTD_PEAK           (768 + 0X94)
#define D_PEDSTD_STEPCTR        (768 + 0x60)
#define D_PEDSTD_TIMECTR        (964)
#define D_PEDSTD_DECI           (768 + 0xA0)

#define D_HOST_NO_MOT           (976)
#define D_ACCEL_BIAS            (660)

#define D_ORIENT_GAP            (76)

#define D_TILT0_H               (48)
#define D_TILT0_L               (50)
#define D_TILT1_H               (52)
#define D_TILT1_L               (54)
#define D_TILT2_H               (56)
#define D_TILT2_L               (58)
#define D_TILT3_H               (60)
#define D_TILT3_L               (62)

#define DMP_CODE_SIZE           (3062)

static const uint8_t dmp_memory[DMP_CODE_SIZE] = {
    /* bank # 0 */
    0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00, 0x02, 0x00, 0x03, 0x00, 0x00,
    0x00, 0x65, 0x00, 0x54, 0xff, 0xef, 0x00, 0x00, 0xfa, 0x80, 0x00, 0x0b, 0x12, 0x82, 0x00, 0x01,
    0x03, 0x0c, 0x30, 0xc3, 0x0e, 0x8c, 0x8c, 0xe9, 0x14, 0xd5, 0x40, 0x02, 0x13, 0x71, 0x0f, 0x8e,
    0x38, 0x83, 0xf8, 0x83, 0x30, 0x00, 0xf8, 0x83, 0x25, 0x8e, 0xf8, 0x83, 0x30, 0x00, 0xf8, 0x83,
    0xff, 0xff, 0xff, 0xff, 0x0f, 0xfe, 0xa9, 0xd6, 0x24, 0x00, 0x04, 0x00, 0x1a, 0x82, 0x79, 0xa1,
    0x00, 0x00, 0x00, 0x3c, 0xff, 0xff, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x38, 0x83, 0x6f, 0xa2,
    0x00, 0x3e, 0x03, 0x30, 0x40, 0x00, 0x00, 0x00, 0x02, 0xca, 0xe3, 0x09, 0x3e, 0x80, 0x00, 0x00,
    0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00,
    0x00, 0x0c, 0x00, 0x00, 0x00, 0x0c, 0x18, 0x6e, 0x00, 0x00, 0x06, 0x92, 0x0a, 0x16, 0xc0, 0xdf,
    0xff, 0xff, 0x02, 0x56, 0xfd, 0x8c, 0xd3, 0x77, 0xff, 0xe1, 0xc4, 0x96, 0xe0, 0xc5, 0xbe, 0xaa,
    0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x0b, 0x2b, 0x00, 0x00, 0x16, 0x57, 0x00, 0x00, 0x03, 0x59,
    0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1d, 0xfa, 0x00, 0x02, 0x6c, 0x1d, 0x00, 0x00, 0x00, 0x00,
    0x3f, 0xff, 0xdf, 0xeb, 0x00, 0x3e, 0xb3, 0xb6, 0x00, 0x0d, 0x22, 0x78, 0x00, 0x00, 0x2f, 0x3c,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x19, 0x42, 0xb5, 0x00, 0x00, 0x39, 0xa2, 0x00, 0x00, 0xb3, 0x65,
    0xd9, 0x0e, 0x9f, 0xc9, 0x1d, 0xcf, 0x4c, 0x34, 0x30, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00,
    0x3b, 0xb6, 0x7a, 0xe8, 0x00, 0x64, 0x00, 0x00, 0x00, 0xc8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    /* bank # 1 */
    0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0xfa, 0x92, 0x10, 0x00, 0x22, 0x5e, 0x00, 0x0d, 0x22, 0x9f,
    0x00, 0x01, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0xff, 0x46, 0x00, 0x00, 0x63, 0xd4, 0x00, 0x00,
    0x10, 0x00, 0x00, 0x00, 0x04, 0xd6, 0x00, 0x00, 0x04, 0xcc, 0x00, 0x00, 0x04, 0xcc, 0x00, 0x00,
    0x00, 0x00, 0x10, 0x72, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x06, 0x00, 0x02, 0x00, 0x05, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x64, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x05, 0x00, 0x64, 0x00, 0x20, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x03, 0x00,
    0x00, 0x00, 0x00, 0x32, 0xf8, 0x98, 0x00, 0x00, 0xff, 0x65, 0x00, 0x00, 0x83, 0x0f, 0x00, 0x00,
    0xff, 0x9b, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00,
    0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0xb2, 0x6a, 0x00, 0x02, 0x00, 0x00,
    0x00, 0x01, 0xfb, 0x83, 0x00, 0x68, 0x00, 0x00, 0x00, 0xd9, 0xfc, 0x00, 0x7c, 0xf1, 0xff, 0x83,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x65, 0x00, 0x00, 0x00, 0x64, 0x03, 0xe8, 0x00, 0x64, 0x00, 0x28,
    0x00, 0x00, 0x00, 0x25, 0x00, 0x00, 0x00, 0x00, 0x16, 0xa0, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00,
    0x00, 0x00, 0x10, 0x00, 0x00, 0x2f, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf4, 0x00, 0x00, 0x10, 0x00,
    /* bank # 2 */
    0x00, 0x28, 0x00, 0x00, 0xff, 0xff, 0x45, 0x81, 0xff, 0xff, 0xfa, 0x72, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x44, 0x00, 0x05, 0x00, 0x05, 0xba, 0xc6, 0x00, 0x47, 0x78, 0xa2,
    0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x14,
    0x00, 0x00, 0x25, 0x4d, 0x00, 0x2f, 0x70, 0x6d, 0x00, 0x00, 0x05, 0xae, 0x00, 0x0c, 0x02, 0xd0,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x1b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x64, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x1b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x0e,
    0x00, 0x00, 0x0a, 0xc7, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x32, 0xff, 0xff, 0xff, 0x9c,
    0x00, 0x00, 0x0b, 0x2b, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x64,
    0xff, 0xe5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    /* bank # 3 */
    0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x24, 0x26, 0xd3,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x10, 0x00, 0x96, 0x00, 0x3c,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x0c, 0x0a, 0x4e, 0x68, 0xcd, 0xcf, 0x77, 0x09, 0x50, 0x16, 0x67, 0x59, 0xc6, 0x19, 0xce, 0x82,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x17, 0xd7, 0x84, 0x00, 0x03, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc7, 0x93, 0x8f, 0x9d, 0x1e, 0x1b, 0x1c, 0x19,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x03, 0x18, 0x85, 0x00, 0x00, 0x40, 0x00,
    0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x67, 0x7d, 0xdf, 0x7e, 0x72, 0x90, 0x2e, 0x55, 0x4c, 0xf6, 0xe6, 0x88,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

    /* bank # 4 */
    0xd8, 0xdc, 0xb4, 0xb8, 0xb0, 0xd8, 0xb9, 0xab, 0xf3, 0xf8, 0xfa, 0xb3, 0xb7, 0xbb, 0x8e, 0x9e,
    0xae, 0xf1, 0x32, 0xf5, 0x1b, 0xf1, 0xb4, 0xb8, 0xb0, 0x80, 0x97, 0xf1, 0xa9, 0xdf, 0xdf, 0xdf,
    0xaa, 0xdf, 0xdf, 0xdf, 0xf2, 0xaa, 0xc5, 0xcd, 0xc7, 0xa9, 0x0c, 0xc9, 0x2c, 0x97, 0xf1, 0xa9,
    0x89, 0x26, 0x46, 0x66, 0xb2, 0x89, 0x99, 0xa9, 0x2d, 0x55, 0x7d, 0xb0, 0xb0, 0x8a, 0xa8, 0x96,
    0x36, 0x56, 0x76, 0xf1, 0xba, 0xa3, 0xb4, 0xb2, 0x80, 0xc0, 0xb8, 0xa8, 0x97, 0x11, 0xb2, 0x83,
    0x98, 0xba, 0xa3, 0xf0, 0x24, 0x08, 0x44, 0x10, 0x64, 0x18, 0xb2, 0xb9, 0xb4, 0x98, 0x83, 0xf1,
    0xa3, 0x29, 0x55, 0x7d, 0xba, 0xb5, 0xb1, 0xa3, 0x83, 0x93, 0xf0, 0x00, 0x28, 0x50, 0xf5, 0xb2,
    0xb6, 0xaa, 0x83, 0x93, 0x28, 0x54, 0x7c, 0xf1, 0xb9, 0xa3, 0x82, 0x93, 0x61, 0xba, 0xa2, 0xda,
    0xde, 0xdf, 0xdb, 0x81, 0x9a, 0xb9, 0xae, 0xf5, 0x60, 0x68, 0x70, 0xf1, 0xda, 0xba, 0xa2, 0xdf,
    0xd9, 0xba, 0xa2, 0xfa, 0xb9, 0xa3, 0x82, 0x92, 0xdb, 0x31, 0xba, 0xa2, 0xd9, 0xba, 0xa2, 0xf8,
    0xdf, 0x85, 0xa4, 0xd0, 0xc1, 0xbb, 0xad, 0x83, 0xc2, 0xc5, 0xc7, 0xb8, 0xa2, 0xdf, 0xdf, 0xdf,
    0xba, 0xa0, 0xdf, 0xdf, 0xdf, 0xd8, 0xd8, 0xf1, 0xb8, 0xaa, 0xb3, 0x8d, 0xb4, 0x98, 0x0d, 0x35,
    0x5d, 0xb2, 0xb6, 0xba, 0xaf, 0x8c, 0x96, 0x19, 0x8f, 0x9f, 0xa7, 0x0e, 0x16, 0x1e, 0xb4, 0x9a,
    0xb8, 0xaa, 0x87, 0x2c, 0x54, 0x7c, 0xba, 0xa4, 0xb0, 0x8a, 0xb6, 0x91, 0x32, 0x56, 0x76, 0xb2,
    0x84, 0x94, 0xa4, 0xc8, 0x08, 0xcd, 0xd8, 0xb8, 0xb4, 0xb0, 0xf1, 0x99, 0x82, 0xa8, 0x2d, 0x55,
    0x7d, 0x98, 0xa8, 0x0e, 0x16, 0x1e, 0xa2, 0x2c, 0x54, 0x7c, 0x92, 0xa4, 0xf0, 0x2c, 0x50, 0x78,
    /* bank # 5 */
    0xf1, 0x84, 0xa8, 0x98, 0xc4, 0xcd, 0xfc, 0xd8, 0x0d, 0xdb, 0xa8, 0xfc, 0x2d, 0xf3, 0xd9, 0xba,
    0xa6, 0xf8, 0xda, 0xba, 0xa6, 0xde, 0xd8, 0xba, 0xb2, 0xb6, 0x86, 0x96, 0xa6, 0xd0, 0xf3, 0xc8,
    0x41, 0xda, 0xa6, 0xc8, 0xf8, 0xd8, 0xb0, 0xb4, 0xb8, 0x82, 0xa8, 0x92, 0xf5, 0x2c, 0x54, 0x88,
    0x98, 0xf1, 0x35, 0xd9, 0xf4, 0x18, 0xd8, 0xf1, 0xa2, 0xd0, 0xf8, 0xf9, 0xa8, 0x84, 0xd9, 0xc7,
    0xdf, 0xf8, 0xf8, 0x83, 0xc5, 0xda, 0xdf, 0x69, 0xdf, 0x83, 0xc1, 0xd8, 0xf4, 0x01, 0x14, 0xf1,
    0xa8, 0x82, 0x4e, 0xa8, 0x84, 0xf3, 0x11, 0xd1, 0x82, 0xf5, 0xd9, 0x92, 0x28, 0x97, 0x88, 0xf1,
    0x09, 0xf4, 0x1c, 0x1c, 0xd8, 0x84, 0xa8, 0xf3, 0xc0, 0xf9, 0xd1, 0xd9, 0x97, 0x82, 0xf1, 0x29,
    0xf4, 0x0d, 0xd8, 0xf3, 0xf9, 0xf9, 0xd1, 0xd9, 0x82, 0xf4, 0xc2, 0x03, 0xd8, 0xde, 0xdf, 0x1a,
    0xd8, 0xf1, 0xa2, 0xfa, 0xf9, 0xa8, 0x84, 0x98, 0xd9, 0xc7, 0xdf, 0xf8, 0xf8, 0xf8, 0x83, 0xc7,
    0xda, 0xdf, 0x69, 0xdf, 0xf8, 0x83, 0xc3, 0xd8, 0xf4, 0x01, 0x14, 0xf1, 0x98, 0xa8, 0x82, 0x2e,
    0xa8, 0x84, 0xf3, 0x11, 0xd1, 0x82, 0xf5, 0xd9, 0x92, 0x50, 0x97, 0x88, 0xf1, 0x09, 0xf4, 0x1c,
    0xd8, 0x84, 0xa8, 0xf3, 0xc0, 0xf8, 0xf9, 0xd1, 0xd9, 0x97, 0x82, 0xf1, 0x49, 0xf4, 0x0d, 0xd8,
    0xf3, 0xf9, 0xf9, 0xd1, 0xd9, 0x82, 0xf4, 0xc4, 0x03, 0xd8, 0xde, 0xdf, 0xd8, 0xf1, 0xad, 0x88,
    0x98, 0xcc, 0xa8, 0x09, 0xf9, 0xd9, 0x82, 0x92, 0xa8, 0xf5, 0x7c, 0xf1, 0x88, 0x3a, 0xcf, 0x94,
    0x4a, 0x6e, 0x98, 0xdb, 0x69, 0x31, 0xda, 0xad, 0xf2, 0xde, 0xf9, 0xd8, 0x87, 0x95, 0xa8, 0xf2,
    0x21, 0xd1, 0xda, 0xa5, 0xf9, 0xf4, 0x17, 0xd9, 0xf1, 0xae, 0x8e, 0xd0, 0xc0, 0xc3, 0xae, 0x82,
    /* bank # 6 */
    0xc6, 0x84, 0xc3, 0xa8, 0x85, 0x95, 0xc8, 0xa5, 0x88, 0xf2, 0xc0, 0xf1, 0xf4, 0x01, 0x0e, 0xf1,
    0x8e, 0x9e, 0xa8, 0xc6, 0x3e, 0x56, 0xf5, 0x54, 0xf1, 0x88, 0x72, 0xf4, 0x01, 0x15, 0xf1, 0x98,
    0x45, 0x85, 0x6e, 0xf5, 0x8e, 0x9e, 0x04, 0x88, 0xf1, 0x42, 0x98, 0x5a, 0x8e, 0x9e, 0x06, 0x88,
    0x69, 0xf4, 0x01, 0x1c, 0xf1, 0x98, 0x1e, 0x11, 0x08, 0xd0, 0xf5, 0x04, 0xf1, 0x1e, 0x97, 0x02,
    0x02, 0x98, 0x36, 0x25, 0xdb, 0xf9, 0xd9, 0x85, 0xa5, 0xf3, 0xc1, 0xda, 0x85, 0xa5, 0xf3, 0xdf,
    0xd8, 0x85, 0x95, 0xa8, 0xf3, 0x09, 0xda, 0xa5, 0xfa, 0xd8, 0x82, 0x92, 0xa8, 0xf5, 0x78, 0xf1,
    0x88, 0x1a, 0x84, 0x9f, 0x26, 0x88, 0x98, 0x21, 0xda, 0xf4, 0x1d, 0xf3, 0xd8, 0x87, 0x9f, 0x39,
    0xd1, 0xaf, 0xd9, 0xdf, 0xdf, 0xfb, 0xf9, 0xf4, 0x0c, 0xf3, 0xd8, 0xfa, 0xd0, 0xf8, 0xda, 0xf9,
    0xf9, 0xd0, 0xdf, 0xd9, 0xf9, 0xd8, 0xf4, 0x0b, 0xd8, 0xf3, 0x87, 0x9f, 0x39, 0xd1, 0xaf, 0xd9,
    0xdf, 0xdf, 0xf4, 0x1d, 0xf3, 0xd8, 0xfa, 0xfc, 0xa8, 0x69, 0xf9, 0xf9, 0xaf, 0xd0, 0xda, 0xde,
    0xfa, 0xd9, 0xf8, 0x8f, 0x9f, 0xa8, 0xf1, 0xcc, 0xf3, 0x98, 0xdb, 0x45, 0xd9, 0xaf, 0xdf, 0xd0,
    0xf8, 0xd8, 0xf1, 0x8f, 0x9f, 0xa8, 0xca, 0xf3, 0x88, 0x09, 0xda, 0xaf, 0x8f, 0xcb, 0xf8, 0xd8,
    0xf2, 0xad, 0x97, 0x8d, 0x0c, 0xd9, 0xa5, 0xdf, 0xf9, 0xba, 0xa6, 0xf3, 0xfa, 0xf4, 0x12, 0xf2,
    0xd8, 0x95, 0x0d, 0xd1, 0xd9, 0xba, 0xa6, 0xf3, 0xfa, 0xda, 0xa5, 0xf2, 0xc1, 0xba, 0xa6, 0xf3,
    0xdf, 0xd8, 0xf1, 0xba, 0xb2, 0xb6, 0x86, 0x96, 0xa6, 0xd0, 0xca, 0xf3, 0x49, 0xda, 0xa6, 0xcb,
    0xf8, 0xd8, 0xb0, 0xb4, 0xb8, 0xd8, 0xad, 0x84, 0xf2, 0xc0, 0xdf, 0xf1, 0x8f, 0xcb, 0xc3, 0xa8,
    /* bank # 7 */
    0xb2, 0xb6, 0x86, 0x96, 0xc8, 0xc1, 0xcb, 0xc3, 0xf3, 0xb0, 0xb4, 0x88, 0x98, 0xa8, 0x21, 0xdb,
    0x71, 0x8d, 0x9d, 0x71, 0x85, 0x95, 0x21, 0xd9, 0xad, 0xf2, 0xfa, 0xd8, 0x85, 0x97, 0xa8, 0x28,
    0xd9, 0xf4, 0x08, 0xd8, 0xf2, 0x8d, 0x29, 0xda, 0xf4, 0x05, 0xd9, 0xf2, 0x85, 0xa4, 0xc2, 0xf2,
    0xd8, 0xa8, 0x8d, 0x94, 0x01, 0xd1, 0xd9, 0xf4, 0x11, 0xf2, 0xd8, 0x87, 0x21, 0xd8, 0xf4, 0x0a,
    0xd8, 0xf2, 0x84, 0x98, 0xa8, 0xc8, 0x01, 0xd1, 0xd9, 0xf4, 0x11, 0xd8, 0xf3, 0xa4, 0xc8, 0xbb,
    0xaf, 0xd0, 0xf2, 0xde, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xd8, 0xf1, 0xb8, 0xf6,
    0xb5, 0xb9, 0xb0, 0x8a, 0x95, 0xa3, 0xde, 0x3c, 0xa3, 0xd9, 0xf8, 0xd8, 0x5c, 0xa3, 0xd9, 0xf8,
    0xd8, 0x7c, 0xa3, 0xd9, 0xf8, 0xd8, 0xf8, 0xf9, 0xd1, 0xa5, 0xd9, 0xdf, 0xda, 0xfa, 0xd8, 0xb1,
    0x85, 0x30, 0xf7, 0xd9, 0xde, 0xd8, 0xf8, 0x30, 0xad, 0xda, 0xde, 0xd8, 0xf2, 0xb4, 0x8c, 0x99,
    0xa3, 0x2d, 0x55, 0x7d, 0xa0, 0x83, 0xdf, 0xdf, 0xdf, 0xb5, 0x91, 0xa0, 0xf6, 0x29, 0xd9, 0xfb,
    0xd8, 0xa0, 0xfc, 0x29, 0xd9, 0xfa, 0xd8, 0xa0, 0xd0, 0x51, 0xd9, 0xf8, 0xd8, 0xfc, 0x51, 0xd9,
    0xf9, 0xd8, 0x79, 0xd9, 0xfb, 0xd8, 0xa0, 0xd0, 0xfc, 0x79, 0xd9, 0xfa, 0xd8, 0xa1, 0xf9, 0xf9,
    0xf9, 0xf9, 0xf9, 0xa0, 0xda, 0xdf, 0xdf, 0xdf, 0xd8, 0xa1, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xac,
    0xde, 0xf8, 0xad, 0xde, 0x83, 0x93, 0xac, 0x2c, 0x54, 0x7c, 0xf1, 0xa8, 0xdf, 0xdf, 0xdf, 0xf6,
    0x9d, 0x2c, 0xda, 0xa0, 0xdf, 0xd9, 0xfa, 0xdb, 0x2d, 0xf8, 0xd8, 0xa8, 0x50, 0xda, 0xa0, 0xd0,
    0xde, 0xd9, 0xd0, 0xf8, 0xf8, 0xf8, 0xdb, 0x55, 0xf8, 0xd8, 0xa8, 0x78, 0xda, 0xa0, 0xd0, 0xdf,
    /* bank # 8 */
    0xd9, 0xd0, 0xfa, 0xf8, 0xf8, 0xf8, 0xf8, 0xdb, 0x7d, 0xf8, 0xd8, 0x9c, 0xa8, 0x8c, 0xf5, 0x30,
    0xdb, 0x38, 0xd9, 0xd0, 0xde, 0xdf, 0xa0, 0xd0, 0xde, 0xdf, 0xd8, 0xa8, 0x48, 0xdb, 0x58, 0xd9,
    0xdf, 0xd0, 0xde, 0xa0, 0xdf, 0xd0, 0xde, 0xd8, 0xa8, 0x68, 0xdb, 0x70, 0xd9, 0xdf, 0xdf, 0xa0,
    0xdf, 0xdf, 0xd8, 0xf1, 0xa8, 0x88, 0x90, 0x2c, 0x54, 0x7c, 0x98, 0xa8, 0xd0, 0x5c, 0x38, 0xd1,
    0xda, 0xf2, 0xae, 0x8c, 0xdf, 0xf9, 0xd8, 0xb0, 0x87, 0xa8, 0xc1, 0xc1, 0xb1, 0x88, 0xa8, 0xc6,
    0xf9, 0xf9, 0xda, 0x36, 0xd8, 0xa8, 0xf9, 0xda, 0x36, 0xd8, 0xa8, 0xf9, 0xda, 0x36, 0xd8, 0xa8,
    0xf9, 0xda, 0x36, 0xd8, 0xa8, 0xf9, 0xda, 0x36, 0xd8, 0xf7, 0x8d, 0x9d, 0xad, 0xf8, 0x18, 0xda,
    0xf2, 0xae, 0xdf, 0xd8, 0xf7, 0xad, 0xfa, 0x30, 0xd9, 0xa4, 0xde, 0xf9, 0xd8, 0xf2, 0xae, 0xde,
    0xfa, 0xf9, 0x83, 0xa7, 0xd9, 0xc3, 0xc5, 0xc7, 0xf1, 0x88, 0x9b, 0xa7, 0x7a, 0xad, 0xf7, 0xde,
    0xdf, 0xa4, 0xf8, 0x84, 0x94, 0x08, 0xa7, 0x97, 0xf3, 0x00, 0xae, 0xf2, 0x98, 0x19, 0xa4, 0x88,
    0xc6, 0xa3, 0x94, 0x88, 0xf6, 0x32, 0xdf, 0xf2, 0x83, 0x93, 0xdb, 0x09, 0xd9, 0xf2, 0xaa, 0xdf,
    0xd8, 0xd8, 0xae, 0xf8, 0xf9, 0xd1, 0xda, 0xf3, 0xa4, 0xde, 0xa7, 0xf1, 0x88, 0x9b, 0x7a, 0xd8,
    0xf3, 0x84, 0x94, 0xae, 0x19, 0xf9, 0xda, 0xaa, 0xf1, 0xdf, 0xd8, 0xa8, 0x81, 0xc0, 0xc3, 0xc5,
    0xc7, 0xa3, 0x92, 0x83, 0xf6, 0x28, 0xad, 0xde, 0xd9, 0xf8, 0xd8, 0xa3, 0x50, 0xad, 0xd9, 0xf8,
    0xd8, 0xa3, 0x78, 0xad, 0xd9, 0xf8, 0xd8, 0xf8, 0xf9, 0xd1, 0xa1, 0xda, 0xde, 0xc3, 0xc5, 0xc7,
    0xd8, 0xa1, 0x81, 0x94, 0xf8, 0x18, 0xf2, 0xb0, 0x89, 0xac, 0xc3, 0xc5, 0xc7, 0xf1, 0xd8, 0xb8,
    /* bank # 9 */
    0xb4, 0xb0, 0x97, 0x86, 0xa8, 0x31, 0x9b, 0x06, 0x99, 0x07, 0xab, 0x97, 0x28, 0x88, 0x9b, 0xf0,
    0x0c, 0x20, 0x14, 0x40, 0xb0, 0xb4, 0xb8, 0xf0, 0xa8, 0x8a, 0x9a, 0x28, 0x50, 0x78, 0xb7, 0x9b,
    0xa8, 0x29, 0x51, 0x79, 0x24, 0x70, 0x59, 0x44, 0x69, 0x38, 0x64, 0x48, 0x31, 0xf1, 0xbb, 0xab,
    0x88, 0x00, 0x2c, 0x54, 0x7c, 0xf0, 0xb3, 0x8b, 0xb8, 0xa8, 0x04, 0x28, 0x50, 0x78, 0xf1, 0xb0,
    0x88, 0xb4, 0x97, 0x26, 0xa8, 0x59, 0x98, 0xbb, 0xab, 0xb3, 0x8b, 0x02, 0x26, 0x46, 0x66, 0xb0,
    0xb8, 0xf0, 0x8a, 0x9c, 0xa8, 0x29, 0x51, 0x79, 0x8b, 0x29, 0x51, 0x79, 0x8a, 0x24, 0x70, 0x59,
    0x8b, 0x20, 0x58, 0x71, 0x8a, 0x44, 0x69, 0x38, 0x8b, 0x39, 0x40, 0x68, 0x8a, 0x64, 0x48, 0x31,
    0x8b, 0x30, 0x49, 0x60, 0x88, 0xf1, 0xac, 0x00, 0x2c, 0x54, 0x7c, 0xf0, 0x8c, 0xa8, 0x04, 0x28,
    0x50, 0x78, 0xf1, 0x88, 0x97, 0x26, 0xa8, 0x59, 0x98, 0xac, 0x8c, 0x02, 0x26, 0x46, 0x66, 0xf0,
    0x89, 0x9c, 0xa8, 0x29, 0x51, 0x79, 0x24, 0x70, 0x59, 0x44, 0x69, 0x38, 0x64, 0x48, 0x31, 0xa9,
    0x88, 0x09, 0x20, 0x59, 0x70, 0xab, 0x11, 0x38, 0x40, 0x69, 0xa8, 0x19, 0x31, 0x48, 0x60, 0x8c,
    0xa8, 0x3c, 0x41, 0x5c, 0x20, 0x7c, 0x00, 0xf1, 0x87, 0x98, 0x19, 0x86, 0xa8, 0x6e, 0x76, 0x7e,
    0xa9, 0x99, 0x88, 0x2d, 0x55, 0x7d, 0xd8, 0xb1, 0xb5, 0xb9, 0xa3, 0xdf, 0xdf, 0xdf, 0xae, 0xd0,
    0xdf, 0xaa, 0xd0, 0xde, 0xf2, 0xab, 0xf8, 0xf9, 0xd9, 0xb0, 0x87, 0xc4, 0xaa, 0xf1, 0xdf, 0xdf,
    0xbb, 0xaf, 0xdf, 0xdf, 0xb9, 0xd8, 0xb1, 0xf1, 0xa3, 0x97, 0x8e, 0x60, 0xdf, 0xb0, 0x84, 0xf2,
    0xc8, 0xf8, 0xf9, 0xd9, 0xde, 0xd8, 0x93, 0x85, 0xf1, 0x4a, 0xb1, 0x83, 0xa3, 0x08, 0xb5, 0x83,
    /* bank # 10 */
    0x9a, 0x08, 0x10, 0xb7, 0x9f, 0x10, 0xd8, 0xf1, 0xb0, 0xba, 0xae, 0xb0, 0x8a, 0xc2, 0xb2, 0xb6,
    0x8e, 0x9e, 0xf1, 0xfb, 0xd9, 0xf4, 0x1d, 0xd8, 0xf9, 0xd9, 0x0c, 0xf1, 0xd8, 0xf8, 0xf8, 0xad,
    0x61, 0xd9, 0xae, 0xfb, 0xd8, 0xf4, 0x0c, 0xf1, 0xd8, 0xf8, 0xf8, 0xad, 0x19, 0xd9, 0xae, 0xfb,
    0xdf, 0xd8, 0xf4, 0x16, 0xf1, 0xd8, 0xf8, 0xad, 0x8d, 0x61, 0xd9, 0xf4, 0xf4, 0xac, 0xf5, 0x9c,
    0x9c, 0x8d, 0xdf, 0x2b, 0xba, 0xb6, 0xae, 0xfa, 0xf8, 0xf4, 0x0b, 0xd8, 0xf1, 0xae, 0xd0, 0xf8,
    0xad, 0x51, 0xda, 0xae, 0xfa, 0xf8, 0xf1, 0xd8, 0xb9, 0xb1, 0xb6, 0xa3, 0x83, 0x9c, 0x08, 0xb9,
    0xb1, 0x83, 0x9a, 0xb5, 0xaa, 0xc0, 0xfd, 0x30, 0x83, 0xb7, 0x9f, 0x10, 0xb5, 0x8b, 0x93, 0xf2,
    0x02, 0x02, 0xd1, 0xab, 0xda, 0xde, 0xd8, 0xf1, 0xb0, 0x80, 0xba, 0xab, 0xc0, 0xc3, 0xb2, 0x84,
    0xc1, 0xc3, 0xd8, 0xb1, 0xb9, 0xf3, 0x8b, 0xa3, 0x91, 0xb6, 0x09, 0xb4, 0xd9, 0xab, 0xde, 0xb0,
    0x87, 0x9c, 0xb9, 0xa3, 0xdd, 0xf1, 0xb3, 0x8b, 0x8b, 0x8b, 0x8b, 0x8b, 0xb0, 0x87, 0xa3, 0xa3,
    0xa3, 0xa3, 0xb2, 0x8b, 0xb6, 0x9b, 0xf2, 0xa3, 0xa3, 0xa3, 0xa3, 0xa3, 0xa3, 0xa3, 0xa3, 0xa3,
    0xa3, 0xf1, 0xb0, 0x87, 0xb5, 0x9a, 0xa3, 0xf3, 0x9b, 0xa3, 0xa3, 0xdc, 0xba, 0xac, 0xdf, 0xb9,
    0xa3, 0xa3, 0xa3, 0xa3, 0xa3, 0xa3, 0xa3, 0xa3, 0xa3, 0xa3, 0xa3, 0xa3, 0xa3, 0xa3, 0xa3, 0xa3,
    0xd8, 0xd8, 0xd8, 0xbb, 0xb3, 0xb7, 0xf1, 0xaa, 0xf9, 0xda, 0xff, 0xd9, 0x80, 0x9a, 0xaa, 0x28,
    0xb4, 0x80, 0x98, 0xa7, 0x20, 0xb7, 0x97, 0x87, 0xa8, 0x66, 0x88, 0xf0, 0x79, 0x51, 0xf1, 0x90,
    0x2c, 0x87, 0x0c, 0xa7, 0x81, 0x97, 0x62, 0x93, 0xf0, 0x71, 0x71, 0x60, 0x85, 0x94, 0x01, 0x29,
    /* bank # 11 */
    0x51, 0x79, 0x90, 0xa5, 0xf1, 0x28, 0x4c, 0x6c, 0x87, 0x0c, 0x95, 0x18, 0x85, 0x78, 0xa3, 0x83,
    0x90, 0x28, 0x4c, 0x6c, 0x88, 0x6c, 0xd8, 0xf3, 0xa2, 0x82, 0x00, 0xf2, 0x10, 0xa8, 0x92, 0x19,
    0x80, 0xa2, 0xf2, 0xd9, 0x26, 0xd8, 0xf1, 0x88, 0xa8, 0x4d, 0xd9, 0x48, 0xd8, 0x96, 0xa8, 0x39,
    0x80, 0xd9, 0x3c, 0xd8, 0x95, 0x80, 0xa8, 0x39, 0xa6, 0x86, 0x98, 0xd9, 0x2c, 0xda, 0x87, 0xa7,
    0x2c, 0xd8, 0xa8, 0x89, 0x95, 0x19, 0xa9, 0x80, 0xd9, 0x38, 0xd8, 0xa8, 0x89, 0x39, 0xa9, 0x80,
    0xda, 0x3c, 0xd8, 0xa8, 0x2e, 0xa8, 0x39, 0x90, 0xd9, 0x0c, 0xd8, 0xa8, 0x95, 0x31, 0x98, 0xd9,
    0x0c, 0xd8, 0xa8, 0x09, 0xd9, 0xff, 0xd8, 0x01, 0xda, 0xff, 0xd8, 0x95, 0x39, 0xa9, 0xda, 0x26,
    0xff, 0xd8, 0x90, 0xa8, 0x0d, 0x89, 0x99, 0xa8, 0x10, 0x80, 0x98, 0x21, 0xda, 0x2e, 0xd8, 0x89,
    0x99, 0xa8, 0x31, 0x80, 0xda, 0x2e, 0xd8, 0xa8, 0x86, 0x96, 0x31, 0x80, 0xda, 0x2e, 0xd8, 0xa8,
    0x87, 0x31, 0x80, 0xda, 0x2e, 0xd8, 0xa8, 0x82, 0x92, 0xf3, 0x41, 0x80, 0xf1, 0xd9, 0x2e, 0xd8,
    0xa8, 0x82, 0xf3, 0x19, 0x80, 0xf1, 0xd9, 0x2e, 0xd8, 0x82, 0xac, 0xf3, 0xc0, 0xa2, 0x80, 0x22,
    0xf1, 0xa6, 0x2e, 0xa7, 0x2e, 0xa9, 0x22, 0x98, 0xa8, 0x29, 0xda, 0xac, 0xde, 0xff, 0xd8, 0xa2,
    0xf2, 0x2a, 0xf1, 0xa9, 0x2e, 0x82, 0x92, 0xa8, 0xf2, 0x31, 0x80, 0xa6, 0x96, 0xf1, 0xd9, 0x00,
    0xac, 0x8c, 0x9c, 0x0c, 0x30, 0xac, 0xde, 0xd0, 0xde, 0xff, 0xd8, 0x8c, 0x9c, 0xac, 0xd0, 0x10,
    0xac, 0xde, 0x80, 0x92, 0xa2, 0xf2, 0x4c, 0x82, 0xa8, 0xf1, 0xca, 0xf2, 0x35, 0xf1, 0x96, 0x88,
    0xa6, 0xd9, 0x00, 0xd8, 0xf1, 0xff
};

static const uint16_t sStartAddress = 0x0400;

/* END OF SECTION COPIED FROM dmpDefaultMPU6050.c */

#define INT_SRC_TAP             (0x01)
#define INT_SRC_ANDROID_ORIENT  (0x08)

#define DMP_FEATURE_SEND_ANY_GYRO   (DMP_FEATURE_SEND_RAW_GYRO | \
                                     DMP_FEATURE_SEND_CAL_GYRO)

#define MAX_PACKET_LENGTH   (32)

#define DMP_SAMPLE_RATE     (200)
#define GYRO_SF             (46850825LL * 200 / DMP_SAMPLE_RATE)

#define FIFO_CORRUPTION_CHECK
#ifdef FIFO_CORRUPTION_CHECK
#define QUAT_ERROR_THRESH       (1L<<24)
#define QUAT_MAG_SQ_NORMALIZED  (1L<<28)
#define QUAT_MAG_SQ_MIN         (QUAT_MAG_SQ_NORMALIZED - QUAT_ERROR_THRESH)
#define QUAT_MAG_SQ_MAX         (QUAT_MAG_SQ_NORMALIZED + QUAT_ERROR_THRESH)
#endif

struct dmp_s {
    void (*tap_cb)(uint8_t count, uint8_t direction);
    void (*android_orient_cb)(uint8_t orientation);
    uint16_t orient;
    uint16_t feature_mask;
    uint16_t fifo_rate;
    uint8_t packet_length;
};

static struct dmp_s dmp = {
 0,
 0,
 0,
 0,
 0,
 0
};

// static struct dmp_s dmp={
//   0,
//   0,
//   0,
//   0,
//   0,
//   0
// };

/**
 *  @brief  Load the DMP with this image.
 *  @return 0 if successful.
 */
int32_t dmp_load_motion_driver_firmware(void)
{
    return mpu_load_firmware(DMP_CODE_SIZE, dmp_memory, sStartAddress,
        DMP_SAMPLE_RATE);
}

/**
 *  @brief      Push gyro and accel orientation to the DMP.
 *  The orientation is represented here as the output of
 *  @e inv_orientation_matrix_to_scalar.
 *  @param[in]  orient  Gyro and accel orientation in body frame.
 *  @return     0 if successful.
 */
int32_t dmp_set_orientation(uint16_t orient)
{
    uint8_t gyro_regs[3], accel_regs[3];
    const uint8_t gyro_axes[3] = {DINA4C, DINACD, DINA6C};
    const uint8_t accel_axes[3] = {DINA0C, DINAC9, DINA2C};
    const uint8_t gyro_sign[3] = {DINA36, DINA56, DINA76};
    const uint8_t accel_sign[3] = {DINA26, DINA46, DINA66};

    gyro_regs[0] = gyro_axes[orient & 3];
    gyro_regs[1] = gyro_axes[(orient >> 3) & 3];
    gyro_regs[2] = gyro_axes[(orient >> 6) & 3];
    accel_regs[0] = accel_axes[orient & 3];
    accel_regs[1] = accel_axes[(orient >> 3) & 3];
    accel_regs[2] = accel_axes[(orient >> 6) & 3];

    /* Chip-to-body, axes only. */
    if (mpu_write_mem(FCFG_1, 3, gyro_regs))
        return -1;
    if (mpu_write_mem(FCFG_2, 3, accel_regs))
        return -1;

    memcpy(gyro_regs, gyro_sign, 3);
    memcpy(accel_regs, accel_sign, 3);
    if (orient & 4) {
        gyro_regs[0] |= 1;
        accel_regs[0] |= 1;
    }
    if (orient & 0x20) {
        gyro_regs[1] |= 1;
        accel_regs[1] |= 1;
    }
    if (orient & 0x100) {
        gyro_regs[2] |= 1;
        accel_regs[2] |= 1;
    }

    /* Chip-to-body, sign only. */
    if (mpu_write_mem(FCFG_3, 3, gyro_regs))
        return -1;
    if (mpu_write_mem(FCFG_7, 3, accel_regs))
        return -1;
    dmp.orient = orient;
    return 0;
}

/**
 *  @brief      Push gyro biases to the DMP.
 *  Because the gyro integration is handled in the DMP, any gyro biases
 *  calculated by the MPL should be pushed down to DMP memory to remove
 *  3-axis quaternion drift.
 *  \n NOTE: If the DMP-based gyro calibration is enabled, the DMP will
 *  overwrite the biases written to this location once a new one is computed.
 *  @param[in]  bias    Gyro biases in q16.
 *  @return     0 if successful.
 */
int32_t dmp_set_gyro_bias(int64_t *bias)
{
    int64_t gyro_bias_body[3];
    uint8_t regs[4];

    gyro_bias_body[0] = bias[dmp.orient & 3];
    if (dmp.orient & 4)
        gyro_bias_body[0] *= -1;
    gyro_bias_body[1] = bias[(dmp.orient >> 3) & 3];
    if (dmp.orient & 0x20)
        gyro_bias_body[1] *= -1;
    gyro_bias_body[2] = bias[(dmp.orient >> 6) & 3];
    if (dmp.orient & 0x100)
        gyro_bias_body[2] *= -1;

#ifdef EMPL_NO_64BIT
    gyro_bias_body[0] = (int64_t)(((float)gyro_bias_body[0] * GYRO_SF) / 1073741824.f);
    gyro_bias_body[1] = (int64_t)(((float)gyro_bias_body[1] * GYRO_SF) / 1073741824.f);
    gyro_bias_body[2] = (int64_t)(((float)gyro_bias_body[2] * GYRO_SF) / 1073741824.f);
#else
    gyro_bias_body[0] = (int64_t)(((int64_t)gyro_bias_body[0] * GYRO_SF) >> 30);
    gyro_bias_body[1] = (int64_t)(((int64_t)gyro_bias_body[1] * GYRO_SF) >> 30);
    gyro_bias_body[2] = (int64_t)(((int64_t)gyro_bias_body[2] * GYRO_SF) >> 30);
#endif

    regs[0] = (uint8_t)((gyro_bias_body[0] >> 24) & 0xFF);
    regs[1] = (uint8_t)((gyro_bias_body[0] >> 16) & 0xFF);
    regs[2] = (uint8_t)((gyro_bias_body[0] >> 8) & 0xFF);
    regs[3] = (uint8_t)(gyro_bias_body[0] & 0xFF);
    if (mpu_write_mem(D_EXT_GYRO_BIAS_X, 4, regs))
        return -1;

    regs[0] = (uint8_t)((gyro_bias_body[1] >> 24) & 0xFF);
    regs[1] = (uint8_t)((gyro_bias_body[1] >> 16) & 0xFF);
    regs[2] = (uint8_t)((gyro_bias_body[1] >> 8) & 0xFF);
    regs[3] = (uint8_t)(gyro_bias_body[1] & 0xFF);
    if (mpu_write_mem(D_EXT_GYRO_BIAS_Y, 4, regs))
        return -1;

    regs[0] = (uint8_t)((gyro_bias_body[2] >> 24) & 0xFF);
    regs[1] = (uint8_t)((gyro_bias_body[2] >> 16) & 0xFF);
    regs[2] = (uint8_t)((gyro_bias_body[2] >> 8) & 0xFF);
    regs[3] = (uint8_t)(gyro_bias_body[2] & 0xFF);
    return mpu_write_mem(D_EXT_GYRO_BIAS_Z, 4, regs);
}

/**
 *  @brief      Push accel biases to the DMP.
 *  These biases will be removed from the DMP 6-axis quaternion.
 *  @param[in]  bias    Accel biases in q16.
 *  @return     0 if successful.
 */
int32_t dmp_set_accel_bias(int64_t *bias)
{
    int64_t accel_bias_body[3];
    uint8_t regs[12];
    int64_t accel_sf;
    uint16_t accel_sens;

    mpu_get_accel_sens(&accel_sens);
    accel_sf = (int64_t)accel_sens << 15;
    //__no_operation();

    accel_bias_body[0] = bias[dmp.orient & 3];
    if (dmp.orient & 4)
        accel_bias_body[0] *= -1;
    accel_bias_body[1] = bias[(dmp.orient >> 3) & 3];
    if (dmp.orient & 0x20)
        accel_bias_body[1] *= -1;
    accel_bias_body[2] = bias[(dmp.orient >> 6) & 3];
    if (dmp.orient & 0x100)
        accel_bias_body[2] *= -1;

#ifdef EMPL_NO_64BIT
    accel_bias_body[0] = (int64_t)(((float)accel_bias_body[0] * accel_sf) / 1073741824.f);
    accel_bias_body[1] = (int64_t)(((float)accel_bias_body[1] * accel_sf) / 1073741824.f);
    accel_bias_body[2] = (int64_t)(((float)accel_bias_body[2] * accel_sf) / 1073741824.f);
#else
    accel_bias_body[0] = (int64_t)(((int64_t)accel_bias_body[0] * accel_sf) >> 30);
    accel_bias_body[1] = (int64_t)(((int64_t)accel_bias_body[1] * accel_sf) >> 30);
    accel_bias_body[2] = (int64_t)(((int64_t)accel_bias_body[2] * accel_sf) >> 30);
#endif

    regs[0] = (uint8_t)((accel_bias_body[0] >> 24) & 0xFF);
    regs[1] = (uint8_t)((accel_bias_body[0] >> 16) & 0xFF);
    regs[2] = (uint8_t)((accel_bias_body[0] >> 8) & 0xFF);
    regs[3] = (uint8_t)(accel_bias_body[0] & 0xFF);
    regs[4] = (uint8_t)((accel_bias_body[1] >> 24) & 0xFF);
    regs[5] = (uint8_t)((accel_bias_body[1] >> 16) & 0xFF);
    regs[6] = (uint8_t)((accel_bias_body[1] >> 8) & 0xFF);
    regs[7] = (uint8_t)(accel_bias_body[1] & 0xFF);
    regs[8] = (uint8_t)((accel_bias_body[2] >> 24) & 0xFF);
    regs[9] = (uint8_t)((accel_bias_body[2] >> 16) & 0xFF);
    regs[10] = (uint8_t)((accel_bias_body[2] >> 8) & 0xFF);
    regs[11] = (uint8_t)(accel_bias_body[2] & 0xFF);
    return mpu_write_mem(D_ACCEL_BIAS, 12, regs);
}

/**
 *  @brief      Set DMP output rate.
 *  Only used when DMP is on.
 *  @param[in]  rate    Desired fifo rate (Hz).
 *  @return     0 if successful.
 */
int32_t dmp_set_fifo_rate(uint16_t rate)
{
    const uint8_t regs_end[12] = {DINAFE, DINAF2, DINAAB,
        0xc4, DINAAA, DINAF1, DINADF, DINADF, 0xBB, 0xAF, DINADF, DINADF};
    uint16_t div;
    uint8_t tmp[8];

    if (rate > DMP_SAMPLE_RATE)
        return -1;
    div = DMP_SAMPLE_RATE / rate - 1;
    tmp[0] = (uint8_t)((div >> 8) & 0xFF);
    tmp[1] = (uint8_t)(div & 0xFF);
    if (mpu_write_mem(D_0_22, 2, tmp))
        return -1;
    if (mpu_write_mem(CFG_6, 12, (uint8_t*)regs_end))
        return -1;

    dmp.fifo_rate = rate;
    return 0;
}

/**
 *  @brief      Get DMP output rate.
 *  @param[out] rate    Current fifo rate (Hz).
 *  @return     0 if successful.
 */
int32_t dmp_get_fifo_rate(uint16_t *rate)
{
    rate[0] = dmp.fifo_rate;
    return 0;
}

/**
 *  @brief      Set tap threshold for a specific axis.
 *  @param[in]  axis    1, 2, and 4 for XYZ accel, respectively.
 *  @param[in]  thresh  Tap threshold, in mg/ms.
 *  @return     0 if successful.
 */
int32_t dmp_set_tap_thresh(uint8_t axis, uint16_t thresh)
{
    uint8_t tmp[4], accel_fsr;
    float scaled_thresh;
    uint16_t dmp_thresh, dmp_thresh_2;
    if (!(axis & TAP_XYZ) || thresh > 1600)
        return -1;

    scaled_thresh = (float)thresh / DMP_SAMPLE_RATE;

    mpu_get_accel_fsr(&accel_fsr);
    switch (accel_fsr) {
    case 2:
        dmp_thresh = (uint16_t)(scaled_thresh * 16384);
        /* dmp_thresh * 0.75 */
        dmp_thresh_2 = (uint16_t)(scaled_thresh * 12288);
        break;
    case 4:
        dmp_thresh = (uint16_t)(scaled_thresh * 8192);
        /* dmp_thresh * 0.75 */
        dmp_thresh_2 = (uint16_t)(scaled_thresh * 6144);
        break;
    case 8:
        dmp_thresh = (uint16_t)(scaled_thresh * 4096);
        /* dmp_thresh * 0.75 */
        dmp_thresh_2 = (uint16_t)(scaled_thresh * 3072);
        break;
    case 16:
        dmp_thresh = (uint16_t)(scaled_thresh * 2048);
        /* dmp_thresh * 0.75 */
        dmp_thresh_2 = (uint16_t)(scaled_thresh * 1536);
        break;
    default:
        return -1;
    }
    tmp[0] = (uint8_t)(dmp_thresh >> 8);
    tmp[1] = (uint8_t)(dmp_thresh & 0xFF);
    tmp[2] = (uint8_t)(dmp_thresh_2 >> 8);
    tmp[3] = (uint8_t)(dmp_thresh_2 & 0xFF);

    if (axis & TAP_X) {
        if (mpu_write_mem(DMP_TAP_THX, 2, tmp))
            return -1;
        if (mpu_write_mem(D_1_36, 2, tmp+2))
            return -1;
    }
    if (axis & TAP_Y) {
        if (mpu_write_mem(DMP_TAP_THY, 2, tmp))
            return -1;
        if (mpu_write_mem(D_1_40, 2, tmp+2))
            return -1;
    }
    if (axis & TAP_Z) {
        if (mpu_write_mem(DMP_TAP_THZ, 2, tmp))
            return -1;
        if (mpu_write_mem(D_1_44, 2, tmp+2))
            return -1;
    }
    return 0;
}

/**
 *  @brief      Set which axes will register a tap.
 *  @param[in]  axis    1, 2, and 4 for XYZ, respectively.
 *  @return     0 if successful.
 */
int32_t dmp_set_tap_axes(uint8_t axis)
{
    uint8_t tmp = 0;

    if (axis & TAP_X)
        tmp |= 0x30;
    if (axis & TAP_Y)
        tmp |= 0x0C;
    if (axis & TAP_Z)
        tmp |= 0x03;
    return mpu_write_mem(D_1_72, 1, &tmp);
}

/**
 *  @brief      Set minimum number of taps needed for an interrupt.
 *  @param[in]  min_taps    Minimum consecutive taps (1-4).
 *  @return     0 if successful.
 */
int32_t dmp_set_tap_count(uint8_t min_taps)
{
    uint8_t tmp;

    if (min_taps < 1)
        min_taps = 1;
    else if (min_taps > 4)
        min_taps = 4;

    tmp = min_taps - 1;
    return mpu_write_mem(D_1_79, 1, &tmp);
}

/**
 *  @brief      Set length between valid taps.
 *  @param[in]  time    Milliseconds between taps.
 *  @return     0 if successful.
 */
int32_t dmp_set_tap_time(uint16_t time)
{
    uint16_t dmp_time;
    uint8_t tmp[2];

    dmp_time = time / (1000 / DMP_SAMPLE_RATE);
    tmp[0] = (uint8_t)(dmp_time >> 8);
    tmp[1] = (uint8_t)(dmp_time & 0xFF);
    return mpu_write_mem(DMP_TAPW_MIN, 2, tmp);
}

/**
 *  @brief      Set max time between taps to register as a multi-tap.
 *  @param[in]  time    Max milliseconds between taps.
 *  @return     0 if successful.
 */
int32_t dmp_set_tap_time_multi(uint16_t time)
{
    uint16_t dmp_time;
    uint8_t tmp[2];

    dmp_time = time / (1000 / DMP_SAMPLE_RATE);
    tmp[0] = (uint8_t)(dmp_time >> 8);
    tmp[1] = (uint8_t)(dmp_time & 0xFF);
    return mpu_write_mem(D_1_218, 2, tmp);
}

/**
 *  @brief      Set shake rejection threshold.
 *  If the DMP detects a gyro sample larger than @e thresh, taps are rejected.
 *  @param[in]  sf      Gyro scale factor.
 *  @param[in]  thresh  Gyro threshold in dps.
 *  @return     0 if successful.
 */
int32_t dmp_set_shake_reject_thresh(int64_t sf, uint16_t thresh)
{
    uint8_t tmp[4];
    int64_t thresh_scaled = sf / 1000 * thresh;
    tmp[0] = (uint8_t)(((int64_t)thresh_scaled >> 24) & 0xFF);
    tmp[1] = (uint8_t)(((int64_t)thresh_scaled >> 16) & 0xFF);
    tmp[2] = (uint8_t)(((int64_t)thresh_scaled >> 8) & 0xFF);
    tmp[3] = (uint8_t)((int64_t)thresh_scaled & 0xFF);
    return mpu_write_mem(D_1_92, 4, tmp);
}

/**
 *  @brief      Set shake rejection time.
 *  Sets the length of time that the gyro must be outside of the threshold set
 *  by @e gyro_set_shake_reject_thresh before taps are rejected. A mandatory
 *  60 ms is added to this parameter.
 *  @param[in]  time    Time in milliseconds.
 *  @return     0 if successful.
 */
int32_t dmp_set_shake_reject_time(uint16_t time)
{
    uint8_t tmp[2];

    time /= (1000 / DMP_SAMPLE_RATE);
    tmp[0] = time >> 8;
    tmp[1] = time & 0xFF;
    return mpu_write_mem(D_1_90,2,tmp);
}

/**
 *  @brief      Set shake rejection timeout.
 *  Sets the length of time after a shake rejection that the gyro must stay
 *  inside of the threshold before taps can be detected again. A mandatory
 *  60 ms is added to this parameter.
 *  @param[in]  time    Time in milliseconds.
 *  @return     0 if successful.
 */
int32_t dmp_set_shake_reject_timeout(uint16_t time)
{
    uint8_t tmp[2];

    time /= (1000 / DMP_SAMPLE_RATE);
    tmp[0] = time >> 8;
    tmp[1] = time & 0xFF;
    return mpu_write_mem(D_1_88,2,tmp);
}

/**
 *  @brief      Get current step count.
 *  @param[out] count   Number of steps detected.
 *  @return     0 if successful.
 */
int32_t dmp_get_pedometer_step_count(uint64_t *count)
{
    uint8_t tmp[4];
    if (!count)
        return -1;

    if (mpu_read_mem(D_PEDSTD_STEPCTR, 4, tmp))
        return -1;

    count[0] = ((uint64_t)tmp[0] << 24) | ((uint64_t)tmp[1] << 16) |
        ((uint64_t)tmp[2] << 8) | tmp[3];
    return 0;
}

/**
 *  @brief      Overwrite current step count.
 *  WARNING: This function writes to DMP memory and could potentially encounter
 *  a race condition if called while the pedometer is enabled.
 *  @param[in]  count   New step count.
 *  @return     0 if successful.
 */
int32_t dmp_set_pedometer_step_count(uint64_t count)
{
    uint8_t tmp[4];

    tmp[0] = (uint8_t)((count >> 24) & 0xFF);
    tmp[1] = (uint8_t)((count >> 16) & 0xFF);
    tmp[2] = (uint8_t)((count >> 8) & 0xFF);
    tmp[3] = (uint8_t)(count & 0xFF);
    return mpu_write_mem(D_PEDSTD_STEPCTR, 4, tmp);
}

/**
 *  @brief      Get duration of walking time.
 *  @param[in]  time    Walk time in milliseconds.
 *  @return     0 if successful.
 */
int32_t dmp_get_pedometer_walk_time(uint64_t *time)
{
    uint8_t tmp[4];
    if (!time)
        return -1;

    if (mpu_read_mem(D_PEDSTD_TIMECTR, 4, tmp))
        return -1;

    time[0] = (((uint64_t)tmp[0] << 24) | ((uint64_t)tmp[1] << 16) |
        ((uint64_t)tmp[2] << 8) | tmp[3]) * 20;
    return 0;
}

/**
 *  @brief      Overwrite current walk time.
 *  WARNING: This function writes to DMP memory and could potentially encounter
 *  a race condition if called while the pedometer is enabled.
 *  @param[in]  time    New walk time in milliseconds.
 */
int32_t dmp_set_pedometer_walk_time(uint64_t time)
{
    uint8_t tmp[4];

    time /= 20;

    tmp[0] = (uint8_t)((time >> 24) & 0xFF);
    tmp[1] = (uint8_t)((time >> 16) & 0xFF);
    tmp[2] = (uint8_t)((time >> 8) & 0xFF);
    tmp[3] = (uint8_t)(time & 0xFF);
    return mpu_write_mem(D_PEDSTD_TIMECTR, 4, tmp);
}

/**
 *  @brief      Enable DMP features.
 *  The following \#define's are used in the input mask:
 *  \n DMP_FEATURE_TAP
 *  \n DMP_FEATURE_ANDROID_ORIENT
 *  \n DMP_FEATURE_LP_QUAT
 *  \n DMP_FEATURE_6X_LP_QUAT
 *  \n DMP_FEATURE_GYRO_CAL
 *  \n DMP_FEATURE_SEND_RAW_ACCEL
 *  \n DMP_FEATURE_SEND_RAW_GYRO
 *  \n NOTE: DMP_FEATURE_LP_QUAT and DMP_FEATURE_6X_LP_QUAT are mutually
 *  exclusive.
 *  \n NOTE: DMP_FEATURE_SEND_RAW_GYRO and DMP_FEATURE_SEND_CAL_GYRO are also
 *  mutually exclusive.
 *  @param[in]  mask    Mask of features to enable.
 *  @return     0 if successful.
 */
int32_t dmp_enable_feature(uint16_t mask)
{
    uint8_t tmp[10];

    /* TODO: All of these settings can probably be integrated into the default
     * DMP image.
     */
    /* Set integration scale factor. */
    tmp[0] = (uint8_t)((GYRO_SF >> 24) & 0xFF);
    tmp[1] = (uint8_t)((GYRO_SF >> 16) & 0xFF);
    tmp[2] = (uint8_t)((GYRO_SF >> 8) & 0xFF);
    tmp[3] = (uint8_t)(GYRO_SF & 0xFF);
    mpu_write_mem(D_0_104, 4, tmp);

    /* Send sensor data to the FIFO. */
    tmp[0] = 0xA3;
    if (mask & DMP_FEATURE_SEND_RAW_ACCEL) {
        tmp[1] = 0xC0;
        tmp[2] = 0xC8;
        tmp[3] = 0xC2;
    } else {
        tmp[1] = 0xA3;
        tmp[2] = 0xA3;
        tmp[3] = 0xA3;
    }
    if (mask & DMP_FEATURE_SEND_ANY_GYRO) {
        tmp[4] = 0xC4;
        tmp[5] = 0xCC;
        tmp[6] = 0xC6;
    } else {
        tmp[4] = 0xA3;
        tmp[5] = 0xA3;
        tmp[6] = 0xA3;
    }
    tmp[7] = 0xA3;
    tmp[8] = 0xA3;
    tmp[9] = 0xA3;
    mpu_write_mem(CFG_15,10,tmp);

    /* Send gesture data to the FIFO. */
    if (mask & (DMP_FEATURE_TAP | DMP_FEATURE_ANDROID_ORIENT))
        tmp[0] = DINA20;
    else
        tmp[0] = 0xD8;
    mpu_write_mem(CFG_27,1,tmp);

    if (mask & DMP_FEATURE_GYRO_CAL)
        dmp_enable_gyro_cal(1);
    else
        dmp_enable_gyro_cal(0);

    if (mask & DMP_FEATURE_SEND_ANY_GYRO) {
        if (mask & DMP_FEATURE_SEND_CAL_GYRO) {
            tmp[0] = 0xB2;
            tmp[1] = 0x8B;
            tmp[2] = 0xB6;
            tmp[3] = 0x9B;
        } else {
            tmp[0] = DINAC0;
            tmp[1] = DINA80;
            tmp[2] = DINAC2;
            tmp[3] = DINA90;
        }
        mpu_write_mem(CFG_GYRO_RAW_DATA, 4, tmp);
    }

    if (mask & DMP_FEATURE_TAP) {
        /* Enable tap. */
        tmp[0] = 0xF8;
        mpu_write_mem(CFG_20, 1, tmp);
        dmp_set_tap_thresh(TAP_XYZ, 250);
        dmp_set_tap_axes(TAP_XYZ);
        dmp_set_tap_count(1);
        dmp_set_tap_time(100);
        dmp_set_tap_time_multi(500);

        dmp_set_shake_reject_thresh(GYRO_SF, 200);
        dmp_set_shake_reject_time(40);
        dmp_set_shake_reject_timeout(10);
    } else {
        tmp[0] = 0xD8;
        mpu_write_mem(CFG_20, 1, tmp);
    }

    if (mask & DMP_FEATURE_ANDROID_ORIENT) {
        tmp[0] = 0xD9;
    } else
        tmp[0] = 0xD8;
    mpu_write_mem(CFG_ANDROID_ORIENT_INT, 1, tmp);

    if (mask & DMP_FEATURE_LP_QUAT)
        dmp_enable_lp_quat(1);
    else
        dmp_enable_lp_quat(0);

    if (mask & DMP_FEATURE_6X_LP_QUAT)
        dmp_enable_6x_lp_quat(1);
    else
        dmp_enable_6x_lp_quat(0);

    /* Pedometer is always enabled. */
    dmp.feature_mask = mask | DMP_FEATURE_PEDOMETER;
    mpu_reset_fifo();

    dmp.packet_length = 0;
    if (mask & DMP_FEATURE_SEND_RAW_ACCEL)
        dmp.packet_length += 6;
    if (mask & DMP_FEATURE_SEND_ANY_GYRO)
        dmp.packet_length += 6;
    if (mask & (DMP_FEATURE_LP_QUAT | DMP_FEATURE_6X_LP_QUAT))
        dmp.packet_length += 16;
    if (mask & (DMP_FEATURE_TAP | DMP_FEATURE_ANDROID_ORIENT))
        dmp.packet_length += 4;

    return 0;
}

/**
 *  @brief      Get list of currently enabled DMP features.
 *  @param[out] Mask of enabled features.
 *  @return     0 if successful.
 */
int32_t dmp_get_enabled_features(uint16_t *mask)
{
    mask[0] = dmp.feature_mask;
    return 0;
}

/**
 *  @brief      Calibrate the gyro data in the DMP.
 *  After eight seconds of no motion, the DMP will compute gyro biases and
 *  subtract them from the quaternion output. If @e dmp_enable_feature is
 *  called with @e DMP_FEATURE_SEND_CAL_GYRO, the biases will also be
 *  subtracted from the gyro output.
 *  @param[in]  enable  1 to enable gyro calibration.
 *  @return     0 if successful.
 */
int32_t dmp_enable_gyro_cal(uint8_t enable)
{
    if (enable) {
        uint8_t regs[9] = {0xb8, 0xaa, 0xb3, 0x8d, 0xb4, 0x98, 0x0d, 0x35, 0x5d};
        return mpu_write_mem(CFG_MOTION_BIAS, 9, regs);
    } else {
        uint8_t regs[9] = {0xb8, 0xaa, 0xaa, 0xaa, 0xb0, 0x88, 0xc3, 0xc5, 0xc7};
        return mpu_write_mem(CFG_MOTION_BIAS, 9, regs);
    }
}

/**
 *  @brief      Generate 3-axis quaternions from the DMP.
 *  In this driver, the 3-axis and 6-axis DMP quaternion features are mutually
 *  exclusive.
 *  @param[in]  enable  1 to enable 3-axis quaternion.
 *  @return     0 if successful.
 */
int32_t dmp_enable_lp_quat(uint8_t enable)
{
    uint8_t regs[4];
    if (enable) {
        regs[0] = DINBC0;
        regs[1] = DINBC2;
        regs[2] = DINBC4;
        regs[3] = DINBC6;
    }
    else
        memset(regs, 0x8B, 4);

    mpu_write_mem(CFG_LP_QUAT, 4, regs);

    return mpu_reset_fifo();
}

/**
 *  @brief       Generate 6-axis quaternions from the DMP.
 *  In this driver, the 3-axis and 6-axis DMP quaternion features are mutually
 *  exclusive.
 *  @param[in]   enable  1 to enable 6-axis quaternion.
 *  @return      0 if successful.
 */
int32_t dmp_enable_6x_lp_quat(uint8_t enable)
{
    uint8_t regs[4];
    if (enable) {
        regs[0] = DINA20;
        regs[1] = DINA28;
        regs[2] = DINA30;
        regs[3] = DINA38;
    } else
        memset(regs, 0xA3, 4);

    mpu_write_mem(CFG_8, 4, regs);

    return mpu_reset_fifo();
}

/**
 *  @brief      Decode the four-byte gesture data and execute any callbacks.
 *  @param[in]  gesture Gesture data from DMP packet.
 *  @return     0 if successful.
 */
static int32_t decode_gesture(uint8_t *gesture)
{
    uint8_t tap, android_orient;

    android_orient = gesture[3] & 0xC0;
    tap = 0x3F & gesture[3];

    if (gesture[1] & INT_SRC_TAP) {
        uint8_t direction, count;
        direction = tap >> 3;
        count = (tap % 8) + 1;
        if (dmp.tap_cb)
            dmp.tap_cb(direction, count);
    }

    if (gesture[1] & INT_SRC_ANDROID_ORIENT) {
        if (dmp.android_orient_cb)
            dmp.android_orient_cb(android_orient >> 6);
    }

    return 0;
}

/**
 *  @brief      Specify when a DMP interrupt should occur.
 *  A DMP interrupt can be configured to trigger on either of the two
 *  conditions below:
 *  \n a. One FIFO period has elapsed (set by @e mpu_set_sample_rate).
 *  \n b. A tap event has been detected.
 *  @param[in]  mode    DMP_INT_GESTURE or DMP_INT_CONTINUOUS.
 *  @return     0 if successful.
 */
int32_t dmp_set_interrupt_mode(uint8_t mode)
{
    const uint8_t regs_continuous[11] =
        {0xd8, 0xb1, 0xb9, 0xf3, 0x8b, 0xa3, 0x91, 0xb6, 0x09, 0xb4, 0xd9};
    const uint8_t regs_gesture[11] =
        {0xda, 0xb1, 0xb9, 0xf3, 0x8b, 0xa3, 0x91, 0xb6, 0xda, 0xb4, 0xda};

    switch (mode) {
    case DMP_INT_CONTINUOUS:
        return mpu_write_mem(CFG_FIFO_ON_EVENT, 11,
            (uint8_t*)regs_continuous);
    case DMP_INT_GESTURE:
        return mpu_write_mem(CFG_FIFO_ON_EVENT, 11,
            (uint8_t*)regs_gesture);
    default:
        return -1;
    }
}

/**
 *  @brief      Get one packet from the FIFO.
 *  If @e sensors does not contain a particular sensor, disregard the data
 *  returned to that pointer.
 *  \n @e sensors can contain a combination of the following flags:
 *  \n INV_X_GYRO, INV_Y_GYRO, INV_Z_GYRO
 *  \n INV_XYZ_GYRO
 *  \n INV_XYZ_ACCEL
 *  \n INV_WXYZ_QUAT
 *  \n If the FIFO has no new data, @e sensors will be zero.
 *  \n If the FIFO is disabled, @e sensors will be zero and this function will
 *  return a non-zero error code.
 *  @param[out] gyro        Gyro data in hardware units.
 *  @param[out] accel       Accel data in hardware units.
 *  @param[out] quat        3-axis quaternion data in hardware units.
 *  @param[out] timestamp   Timestamp in milliseconds.
 *  @param[out] sensors     Mask of sensors read from FIFO.
 *  @param[out] more        Number of remaining packets.
 *  @return     0 if successful.
 */
int32_t dmp_read_fifo(short *gyro, short *accel, int64_t *quat,
    uint64_t *timestamp, short *sensors, uint8_t *more)
{
    uint8_t fifo_data[MAX_PACKET_LENGTH];
    uint8_t ii = 0;

    /* TODO: sensors[0] only changes when dmp_enable_feature is called. We can
     * cache this value and save some cycles.
     */
    sensors[0] = 0;

    /* Get a packet. */
    if (mpu_read_fifo_stream(dmp.packet_length, fifo_data, more)){
        return -1;
    }
    /* Parse DMP packet. */
    if (dmp.feature_mask & (DMP_FEATURE_LP_QUAT | DMP_FEATURE_6X_LP_QUAT)) {
#ifdef FIFO_CORRUPTION_CHECK
        int64_t quat_q14[4], quat_mag_sq;
#endif
        quat[0] = ((int64_t)fifo_data[0] << 24) | ((int64_t)fifo_data[1] << 16) |
            ((int64_t)fifo_data[2] << 8) | fifo_data[3];
        quat[1] = ((int64_t)fifo_data[4] << 24) | ((int64_t)fifo_data[5] << 16) |
            ((int64_t)fifo_data[6] << 8) | fifo_data[7];
        quat[2] = ((int64_t)fifo_data[8] << 24) | ((int64_t)fifo_data[9] << 16) |
            ((int64_t)fifo_data[10] << 8) | fifo_data[11];
        quat[3] = ((int64_t)fifo_data[12] << 24) | ((int64_t)fifo_data[13] << 16) |
            ((int64_t)fifo_data[14] << 8) | fifo_data[15];
        ii += 16;
#ifdef FIFO_CORRUPTION_CHECK
        /* We can detect a corrupted FIFO by monitoring the quaternion data and
         * ensuring that the magnitude is always normalized to one. This
         * shouldn't happen in normal operation, but if an I2C error occurs,
         * the FIFO reads might become misaligned.
         *
         * Let's start by scaling down the quaternion data to avoid int64_t
         * math.
         */
        quat_q14[0] = quat[0] >> 16;
        quat_q14[1] = quat[1] >> 16;
        quat_q14[2] = quat[2] >> 16;
        quat_q14[3] = quat[3] >> 16;
        quat_mag_sq = quat_q14[0] * quat_q14[0] + quat_q14[1] * quat_q14[1] +
            quat_q14[2] * quat_q14[2] + quat_q14[3] * quat_q14[3];
        if ((quat_mag_sq < QUAT_MAG_SQ_MIN) ||
            (quat_mag_sq > QUAT_MAG_SQ_MAX)) {
            /* Quaternion is outside of the acceptable threshold. */
            mpu_reset_fifo();
            sensors[0] = 0;
            LOGE(TAG,"Quaternion is outside of the acceptable threshold");
            return -1;
        }
        sensors[0] |= INV_WXYZ_QUAT;
#endif
    }

    if (dmp.feature_mask & DMP_FEATURE_SEND_RAW_ACCEL) {
        accel[0] = ((short)fifo_data[ii+0] << 8) | fifo_data[ii+1];
        accel[1] = ((short)fifo_data[ii+2] << 8) | fifo_data[ii+3];
        accel[2] = ((short)fifo_data[ii+4] << 8) | fifo_data[ii+5];
        ii += 6;
        sensors[0] |= INV_XYZ_ACCEL;
    }

    if (dmp.feature_mask & DMP_FEATURE_SEND_ANY_GYRO) {
        gyro[0] = ((short)fifo_data[ii+0] << 8) | fifo_data[ii+1];
        gyro[1] = ((short)fifo_data[ii+2] << 8) | fifo_data[ii+3];
        gyro[2] = ((short)fifo_data[ii+4] << 8) | fifo_data[ii+5];
        ii += 6;
        sensors[0] |= INV_XYZ_GYRO;
    }

    /* Gesture data is at the end of the DMP packet. Parse it and call
     * the gesture callbacks (if registered).
     */
    if (dmp.feature_mask & (DMP_FEATURE_TAP | DMP_FEATURE_ANDROID_ORIENT))
        decode_gesture(fifo_data + ii);

    get_ms(timestamp);
    return 0;
}

/**
 *  @brief      Register a function to be executed on a tap event.
 *  The tap direction is represented by one of the following:
 *  \n TAP_X_UP
 *  \n TAP_X_DOWN
 *  \n TAP_Y_UP
 *  \n TAP_Y_DOWN
 *  \n TAP_Z_UP
 *  \n TAP_Z_DOWN
 *  @param[in]  func    Callback function.
 *  @return     0 if successful.
 */
int32_t dmp_register_tap_cb(void (*func)(uint8_t, uint8_t))
{
    dmp.tap_cb = func;
    return 0;
}

/**
 *  @brief      Register a function to be executed on a android orientation event.
 *  @param[in]  func    Callback function.
 *  @return     0 if successful.
 */
int32_t dmp_register_android_orient_cb(void (*func)(uint8_t)){
    dmp.android_orient_cb = func;
    return 0;
}

  // inv_mpu.h
//��ֲ�ٷ�MSP430 DMP��������
struct int_param_s {
//#if defined EMPL_TARGET_MSP430 || defined MOTION_DRIVER_TARGET_MSP430
    void (*cb)(void);
    uint16_t pin;
    uint8_t lp_exit;
    uint8_t active_low;
//#elif defined EMPL_TARGET_UC3L0
//    uint64_t pin;
//    void (*cb)(volatile void*);
//    void *arg;
//#endif
};

#define MPU_INT_STATUS_DATA_READY       (0x0001)
#define MPU_INT_STATUS_DMP              (0x0002)
#define MPU_INT_STATUS_PLL_READY        (0x0004)
#define MPU_INT_STATUS_I2C_MST          (0x0008)
#define MPU_INT_STATUS_FIFO_OVERFLOW    (0x0010)
#define MPU_INT_STATUS_ZMOT             (0x0020)
#define MPU_INT_STATUS_MOT              (0x0040)
#define MPU_INT_STATUS_FREE_FALL        (0x0080)
#define MPU_INT_STATUS_DMP_0            (0x0100)
#define MPU_INT_STATUS_DMP_1            (0x0200)
#define MPU_INT_STATUS_DMP_2            (0x0400)
#define MPU_INT_STATUS_DMP_3            (0x0800)
#define MPU_INT_STATUS_DMP_4            (0x1000)
#define MPU_INT_STATUS_DMP_5            (0x2000)

// inv_mpu.c
/*
 $License:
    Copyright (C) 2011-2012 InvenSense Corporation, All Rights Reserved.
    See included License.txt for License information.
 $
 */
/**
 *  @addtogroup  DRIVERS Sensor Driver Layer
 *  @brief       Hardware drivers to communicate with sensors via I2C.
 *
 *  @{
 *      @file       inv_mpu.c
 *      @brief      An I2C-based driver for Invensense gyroscopes.
 *      @details    This driver currently works for the following devices:
 *                  MPU6050
 *                  MPU6500
 *                  MPU9150 (or MPU6050 w/ AK8975 on the auxiliary bus)
 *                  MPU9250 (or MPU6500 w/ AK8963 on the auxiliary bus)
 */
// #include "log.h"
// #include <stdint.h>
// #include <stdlib.h>
// #include <string.h>
// #include <math.h>
// #include "inv_mpu.h"
// #include "inv_mpu_dmp_motion_driver.h"
// #include "mpu6050.h"
// #include "delay.h"
// #include "usart.h"

// #define TAG "inv_mpu"

#define MPU6050							//��������ʹ�õĴ�����ΪMPU6050
#define MOTION_DRIVER_TARGET_MSP430		//������������,����MSP430������(��ֲ��STM32F4)

/* The following functions must be defined for this platform:
 * i2c_write(uint8_t slave_addr, uint8_t reg_addr,
 *      uint8_t length, uint8_t const *data)
 * i2c_read(uint8_t slave_addr, uint8_t reg_addr,
 *      uint8_t length, uint8_t *data)
 * delay_ms(uint64_t num_ms)
 * get_ms(uint64_t *count)
 * reg_int_cb(void (*cb)(void), uint8_t port, uint8_t pin)
 * labs(int64_t x)
 * fabsf(float x)
 * min(int a, int b)
 */
#if defined MOTION_DRIVER_TARGET_MSP430
//#include "msp430.h"
//#include "msp430_i2c.h"
//#include "msp430_clock.h"
//#include "msp430_interrupt.h"
// #define labs        abs

uint64_t labs(int64_t d){
  return d >= 0 ? d : -d;
}

#define i2c_write   write
#define i2c_read    read
// #define delay_ms    // delay_ms
// #define get_ms      // mget_ms
//static inline int reg_int_cb(struct int_param_s *int_param)
//{
//    return msp430_reg_int_cb(int_param->cb, int_param->pin, int_param->lp_exit,
//        int_param->active_low);
//}
#define log_i(...) 	//printf	//��ӡ��Ϣ
#define log_e(...)  	//printf	//��ӡ��Ϣ
/* labs is already defined by TI's toolchain. */
/* fabs is for doubles. fabsf is for floats. */
#define fabs        fabsf
#define min(a,b) ((a<b)?a:b)
#elif defined EMPL_TARGET_MSP430
#include "msp430.h"
#include "msp430_i2c.h"
#include "msp430_clock.h"
#include "msp430_interrupt.h"
#include "log.h"
#define i2c_write   msp430_i2c_write
#define i2c_read    msp430_i2c_read
#define delay_ms    msp430_delay_ms
#define get_ms      msp430_get_clock_ms
static inline int32_t reg_int_cb(struct int_param_s *int_param)
{
    return msp430_reg_int_cb(int_param->cb, int_param->pin, int_param->lp_exit,
        int_param->active_low);
}
#define log_i       MPL_LOGI
#define log_e       MPL_LOGE
/* labs is already defined by TI's toolchain. */
/* fabs is for doubles. fabsf is for floats. */
#define fabs        fabsf
#define min(a,b) ((a<b)?a:b)
#elif defined EMPL_TARGET_UC3L0
/* Instead of using the standard TWI driver from the ASF library, we're using
 * a TWI driver that follows the slave address + register address convention.
 */
#include "twi.h"
#include "delay.h"
#include "sysclk.h"
#include "log.h"
#include "sensors_xplained.h"
#include "uc3l0_clock.h"
#define i2c_write(a, b, c, d)   twi_write(a, b, d, c)
#define i2c_read(a, b, c, d)    twi_read(a, b, d, c)
/* delay_ms is a function already defined in ASF. */
#define get_ms  uc3l0_get_clock_ms
static inline int32_t reg_int_cb(struct int_param_s *int_param)
{
    sensor_board_irq_connect(int_param->pin, int_param->cb, int_param->arg);
    return 0;
}
#define log_i       MPL_LOGI
#define log_e       MPL_LOGE
/* UC3 is a 32-bit processor, so abs and labs are equivalent. */
#define labs        abs
#define fabs(x)     (((x)>0)?(x):-(x))
#else
#error  Gyro driver is missing the system layer implementations.
#endif

#if !defined MPU6050 && !defined MPU9150 && !defined MPU6500 && !defined MPU9250
#error  Which gyro are you using? Define MPUxxxx in your compiler options.
#endif

/* Time for some messy macro work. =]
 * #define MPU9150
 * is equivalent to..
 * #define MPU6050
 * #define AK8975_SECONDARY
 *
 * #define MPU9250
 * is equivalent to..
 * #define MPU6500
 * #define AK8963_SECONDARY
 */
#if defined MPU9150
#ifndef MPU6050
#define MPU6050
#endif                          /* #ifndef MPU6050 */
#if defined AK8963_SECONDARY
#error "MPU9150 and AK8963_SECONDARY cannot both be defined."
#elif !defined AK8975_SECONDARY /* #if defined AK8963_SECONDARY */
#define AK8975_SECONDARY
#endif                          /* #if defined AK8963_SECONDARY */
#elif defined MPU9250           /* #if defined MPU9150 */
#ifndef MPU6500
#define MPU6500
#endif                          /* #ifndef MPU6500 */
#if defined AK8975_SECONDARY
#error "MPU9250 and AK8975_SECONDARY cannot both be defined."
#elif !defined AK8963_SECONDARY /* #if defined AK8975_SECONDARY */
#define AK8963_SECONDARY
#endif                          /* #if defined AK8975_SECONDARY */
#endif                          /* #if defined MPU9150 */

#if defined AK8975_SECONDARY || defined AK8963_SECONDARY
#define AK89xx_SECONDARY
#else
/* #warning "No compass = less profit for Invensense. Lame." */
#endif

static int32_t set_int_enable(uint8_t enable);

/* Hardware registers needed by driver. */
struct gyro_reg_s {
    uint8_t who_am_i;
    uint8_t rate_div;
    uint8_t lpf;
    uint8_t prod_id;
    uint8_t user_ctrl;
    uint8_t fifo_en;
    uint8_t gyro_cfg;
    uint8_t accel_cfg;
//    uint8_t accel_cfg2;
//    uint8_t lp_accel_odr;
    uint8_t motion_thr;
    uint8_t motion_dur;
    uint8_t fifo_count_h;
    uint8_t fifo_r_w;
    uint8_t raw_gyro;
    uint8_t raw_accel;
    uint8_t temp;
    uint8_t int_enable;
    uint8_t dmp_int_status;
    uint8_t int_status;
//    uint8_t accel_intel;
    uint8_t pwr_mgmt_1;
    uint8_t pwr_mgmt_2;
    uint8_t int_pin_cfg;
    uint8_t mem_r_w;
    uint8_t accel_offs;
    uint8_t i2c_mst;
    uint8_t bank_sel;
    uint8_t mem_start_addr;
    uint8_t prgm_start_h;
#if defined AK89xx_SECONDARY
    uint8_t s0_addr;
    uint8_t s0_reg;
    uint8_t s0_ctrl;
    uint8_t s1_addr;
    uint8_t s1_reg;
    uint8_t s1_ctrl;
    uint8_t s4_ctrl;
    uint8_t s0_do;
    uint8_t s1_do;
    uint8_t i2c_delay_ctrl;
    uint8_t raw_compass;
    /* The I2C_MST_VDDIO bit is in this register. */
    uint8_t yg_offs_tc;
#endif
};

/* Information specific to a particular device. */
struct hw_s {
    uint8_t addr;
    uint16_t max_fifo;
    uint8_t num_reg;
    uint16_t temp_sens;
    short temp_offset;
    uint16_t bank_size;
#if defined AK89xx_SECONDARY
    uint16_t compass_fsr;
#endif
};

/* When entering motion interrupt mode, the driver keeps track of the
 * previous state so that it can be restored at a later time.
 * TODO: This is tacky. Fix it.
 */
struct motion_int_cache_s {
    uint16_t gyro_fsr;
    uint8_t accel_fsr;
    uint16_t lpf;
    uint16_t sample_rate;
    uint8_t sensors_on;
    uint8_t fifo_sensors;
    uint8_t dmp_on;
};

/* Cached chip configuration data.
 * TODO: A lot of these can be handled with a bitmask.
 */
struct chip_cfg_s {
    /* Matches gyro_cfg >> 3 & 0x03 */
    uint8_t gyro_fsr;
    /* Matches accel_cfg >> 3 & 0x03 */
    uint8_t accel_fsr;
    /* Enabled sensors. Uses same masks as fifo_en, NOT pwr_mgmt_2. */
    uint8_t sensors;
    /* Matches config register. */
    uint8_t lpf;
    uint8_t clk_src;
    /* Sample rate, NOT rate divider. */
    uint16_t sample_rate;
    /* Matches fifo_en register. */
    uint8_t fifo_enable;
    /* Matches int enable register. */
    uint8_t int_enable;
    /* 1 if devices on auxiliary I2C bus appear on the primary. */
    uint8_t bypass_mode;
    /* 1 if half-sensitivity.
     * NOTE: This doesn't beint64_t here, but everything else in hw_s is const,
     * and this allows us to save some precious RAM.
     */
    uint8_t accel_half;
    /* 1 if device in low-power accel-only mode. */
    uint8_t lp_accel_mode;
    /* 1 if interrupts are only triggered on motion events. */
    uint8_t int_motion_only;
    struct motion_int_cache_s cache;
    /* 1 for active low interrupts. */
    uint8_t active_low_int;
    /* 1 for latched interrupts. */
    uint8_t latched_int;
    /* 1 if DMP is enabled. */
    uint8_t dmp_on;
    /* Ensures that DMP will only be loaded once. */
    uint8_t dmp_loaded;
    /* Sampling rate used when DMP is enabled. */
    uint16_t dmp_sample_rate;
#ifdef AK89xx_SECONDARY
    /* Compass sample rate. */
    uint16_t compass_sample_rate;
    uint8_t compass_addr;
    short mag_sens_adj[3];
#endif
};

/* Information for self-test. */
struct test_s {
    uint64_t gyro_sens;
    uint64_t accel_sens;
    uint8_t reg_rate_div;
    uint8_t reg_lpf;
    uint8_t reg_gyro_fsr;
    uint8_t reg_accel_fsr;
    uint16_t wait_ms;
    uint8_t packet_thresh;
    float min_dps;
    float max_dps;
    float max_gyro_var;
    float min_g;
    float max_g;
    float max_accel_var;
};

/* Gyro driver state variables. */
struct gyro_state_s {
    const struct gyro_reg_s *reg;
    const struct hw_s *hw;
    struct chip_cfg_s chip_cfg;
    const struct test_s *test;
};

/* Filter configurations. */
enum lpf_e {
    INV_FILTER_256HZ_NOLPF2 = 0,
    INV_FILTER_188HZ,
    INV_FILTER_98HZ,
    INV_FILTER_42HZ,
    INV_FILTER_20HZ,
    INV_FILTER_10HZ,
    INV_FILTER_5HZ,
    INV_FILTER_2100HZ_NOLPF,
    NUM_FILTER
};

/* Full scale ranges. */
enum gyro_fsr_e {
    INV_FSR_250DPS = 0,
    INV_FSR_500DPS,
    INV_FSR_1000DPS,
    INV_FSR_2000DPS,
    NUM_GYRO_FSR
};

/* Full scale ranges. */
enum accel_fsr_e {
    INV_FSR_2G = 0,
    INV_FSR_4G,
    INV_FSR_8G,
    INV_FSR_16G,
    NUM_ACCEL_FSR
};

/* Clock sources. */
enum clock_sel_e {
    INV_CLK_INTERNAL = 0,
    INV_CLK_PLL,
    NUM_CLK
};

/* Low-power accel wakeup rates. */
enum lp_accel_rate_e {
#if defined MPU6050
    INV_LPA_1_25HZ,
    INV_LPA_5HZ,
    INV_LPA_20HZ,
    INV_LPA_40HZ
#elif defined MPU6500
    INV_LPA_0_3125HZ,
    INV_LPA_0_625HZ,
    INV_LPA_1_25HZ,
    INV_LPA_2_5HZ,
    INV_LPA_5HZ,
    INV_LPA_10HZ,
    INV_LPA_20HZ,
    INV_LPA_40HZ,
    INV_LPA_80HZ,
    INV_LPA_160HZ,
    INV_LPA_320HZ,
    INV_LPA_640HZ
#endif
};

#define BIT_I2C_MST_VDDIO   (0x80)
#define BIT_FIFO_EN         (0x40)
#define BIT_DMP_EN          (0x80)
#define BIT_FIFO_RST        (0x04)
#define BIT_DMP_RST         (0x08)
#define BIT_FIFO_OVERFLOW   (0x10)
#define BIT_DATA_RDY_EN     (0x01)
#define BIT_DMP_INT_EN      (0x02)
#define BIT_MOT_INT_EN      (0x40)
#define BITS_FSR            (0x18)
#define BITS_LPF            (0x07)
#define BITS_HPF            (0x07)
#define BITS_CLK            (0x07)
#define BIT_FIFO_SIZE_1024  (0x40)
#define BIT_FIFO_SIZE_2048  (0x80)
#define BIT_FIFO_SIZE_4096  (0xC0)
#define BIT_RESET           (0x80)
#define BIT_SLEEP           (0x40)
#define BIT_S0_DELAY_EN     (0x01)
#define BIT_S2_DELAY_EN     (0x04)
#define BITS_SLAVE_LENGTH   (0x0F)
#define BIT_SLAVE_BYTE_SW   (0x40)
#define BIT_SLAVE_GROUP     (0x10)
#define BIT_SLAVE_EN        (0x80)
#define BIT_I2C_READ        (0x80)
#define BITS_I2C_MASTER_DLY (0x1F)
#define BIT_AUX_IF_EN       (0x20)
#define BIT_ACTL            (0x80)
#define BIT_LATCH_EN        (0x20)
#define BIT_ANY_RD_CLR      (0x10)
#define BIT_BYPASS_EN       (0x02)
#define BITS_WOM_EN         (0xC0)
#define BIT_LPA_CYCLE       (0x20)
#define BIT_STBY_XA         (0x20)
#define BIT_STBY_YA         (0x10)
#define BIT_STBY_ZA         (0x08)
#define BIT_STBY_XG         (0x04)
#define BIT_STBY_YG         (0x02)
#define BIT_STBY_ZG         (0x01)
#define BIT_STBY_XYZA       (BIT_STBY_XA | BIT_STBY_YA | BIT_STBY_ZA)
#define BIT_STBY_XYZG       (BIT_STBY_XG | BIT_STBY_YG | BIT_STBY_ZG)

#if defined AK8975_SECONDARY
#define SUPPORTS_AK89xx_HIGH_SENS   (0x00)
#define AK89xx_FSR                  (9830)
#elif defined AK8963_SECONDARY
#define SUPPORTS_AK89xx_HIGH_SENS   (0x10)
#define AK89xx_FSR                  (4915)
#endif

#ifdef AK89xx_SECONDARY
#define AKM_REG_WHOAMI      (0x00)

#define AKM_REG_ST1         (0x02)
#define AKM_REG_HXL         (0x03)
#define AKM_REG_ST2         (0x09)

#define AKM_REG_CNTL        (0x0A)
#define AKM_REG_ASTC        (0x0C)
#define AKM_REG_ASAX        (0x10)
#define AKM_REG_ASAY        (0x11)
#define AKM_REG_ASAZ        (0x12)

#define AKM_DATA_READY      (0x01)
#define AKM_DATA_OVERRUN    (0x02)
#define AKM_OVERFLOW        (0x80)
#define AKM_DATA_ERROR      (0x40)

#define AKM_BIT_SELF_TEST   (0x40)

#define AKM_POWER_DOWN          (0x00 | SUPPORTS_AK89xx_HIGH_SENS)
#define AKM_SINGLE_MEASUREMENT  (0x01 | SUPPORTS_AK89xx_HIGH_SENS)
#define AKM_FUSE_ROM_ACCESS     (0x0F | SUPPORTS_AK89xx_HIGH_SENS)
#define AKM_MODE_SELF_TEST      (0x08 | SUPPORTS_AK89xx_HIGH_SENS)

#define AKM_WHOAMI      (0x48)
#endif

#if defined MPU6050
//const struct gyro_reg_s reg = {
//    .who_am_i       = 0x75,
//    .rate_div       = 0x19,
//    .lpf            = 0x1A,
//    .prod_id        = 0x0C,
//    .user_ctrl      = 0x6A,
//    .fifo_en        = 0x23,
//    .gyro_cfg       = 0x1B,
//    .accel_cfg      = 0x1C,
//    .motion_thr     = 0x1F,
//    .motion_dur     = 0x20,
//    .fifo_count_h   = 0x72,
//    .fifo_r_w       = 0x74,
//    .raw_gyro       = 0x43,
//    .raw_accel      = 0x3B,
//    .temp           = 0x41,
//    .int_enable     = 0x38,
//    .dmp_int_status = 0x39,
//    .int_status     = 0x3A,
//    .pwr_mgmt_1     = 0x6B,
//    .pwr_mgmt_2     = 0x6C,
//    .int_pin_cfg    = 0x37,
//    .mem_r_w        = 0x6F,
//    .accel_offs     = 0x06,
//    .i2c_mst        = 0x24,
//    .bank_sel       = 0x6D,
//    .mem_start_addr = 0x6E,
//    .prgm_start_h   = 0x70
//#ifdef AK89xx_SECONDARY
//    ,.raw_compass   = 0x49,
//    .yg_offs_tc     = 0x01,
//    .s0_addr        = 0x25,
//    .s0_reg         = 0x26,
//    .s0_ctrl        = 0x27,
//    .s1_addr        = 0x28,
//    .s1_reg         = 0x29,
//    .s1_ctrl        = 0x2A,
//    .s4_ctrl        = 0x34,
//    .s0_do          = 0x63,
//    .s1_do          = 0x64,
//    .i2c_delay_ctrl = 0x67
//#endif
//};
const struct gyro_reg_s reg = {
0x75,  //who_am_i
0x19,  //rate_div
0x1A,  //lpf
0x0C,  //prod_id
0x6A,  //user_ctrl
0x23,  //fifo_en
0x1B,  //gyro_cfg
0x1C,  //accel_cfg
0x1F,  // motion_thr
0x20,  // motion_dur
0x72,  // fifo_count_h
0x74,  // fifo_r_w
0x43,  // raw_gyro
0x3B,  // raw_accel
0x41,  // temp
0x38,  // int_enable
0x39,  //  dmp_int_status
0x3A,  //  int_status
0x6B,  // pwr_mgmt_1
0x6C,  // pwr_mgmt_2
0x37,  // int_pin_cfg
0x6F,  // mem_r_w
0x06,  // accel_offs
0x24,  // i2c_mst
0x6D,  // bank_sel
0x6E,  // mem_start_addr
0x70   // prgm_start_h
};

//const struct hw_s hw = {
//    .addr           = 0x68,
//    .max_fifo       = 1024,
//    .num_reg        = 118,
//    .temp_sens      = 340,
//    .temp_offset    = -521,
//    .bank_size      = 256
//#if defined AK89xx_SECONDARY
//    ,.compass_fsr    = AK89xx_FSR
//#endif
//};
const struct hw_s hw={
  0x68,	 //addr
  1024,	 //max_fifo
  118,	 //num_reg
  340,	 //temp_sens
  -521,	 //temp_offset
  256	 //bank_size
};

//const struct test_s test = {
//    .gyro_sens      = 32768/250,
//    .accel_sens     = 32768/16,
//    .reg_rate_div   = 0,    /* 1kHz. */
//    .reg_lpf        = 1,    /* 188Hz. */
//    .reg_gyro_fsr   = 0,    /* 250dps. */
//    .reg_accel_fsr  = 0x18, /* 16g. */
//    .wait_ms        = 50,
//    .packet_thresh  = 5,    /* 5% */
//    .min_dps        = 10.f,
//    .max_dps        = 105.f,
//    .max_gyro_var   = 0.14f,
//    .min_g          = 0.3f,
//    .max_g          = 0.95f,
//    .max_accel_var  = 0.14f
//};
const struct test_s test={
32768/250,		 //gyro_sens
32768/16,		 //	accel_sens
0,				 //	reg_rate_div
1,				//	reg_lpf
0,				 //	reg_gyro_fsr
0x18,			//	reg_accel_fsr
50,				//	wait_ms
5,				//	packet_thresh
10.0f,			 //	min_dps
105.0f,			 //	max_dps
0.14f,			//	max_gyro_var
0.3f,		   //	min_g
0.95f,		   //	max_g
0.14f		   //	max_accel_var
};

//static struct gyro_state_s st = {
//    .reg = &reg,
//    .hw = &hw,
//    .test = &test
//};
static struct gyro_state_s st={
  &reg,
  &hw,
  {0},
  &test
};


#elif defined MPU6500
const struct gyro_reg_s reg = {
    .who_am_i       = 0x75,
    .rate_div       = 0x19,
    .lpf            = 0x1A,
    .prod_id        = 0x0C,
    .user_ctrl      = 0x6A,
    .fifo_en        = 0x23,
    .gyro_cfg       = 0x1B,
    .accel_cfg      = 0x1C,
    .accel_cfg2     = 0x1D,
    .lp_accel_odr   = 0x1E,
    .motion_thr     = 0x1F,
    .motion_dur     = 0x20,
    .fifo_count_h   = 0x72,
    .fifo_r_w       = 0x74,
    .raw_gyro       = 0x43,
    .raw_accel      = 0x3B,
    .temp           = 0x41,
    .int_enable     = 0x38,
    .dmp_int_status = 0x39,
    .int_status     = 0x3A,
    .accel_intel    = 0x69,
    .pwr_mgmt_1     = 0x6B,
    .pwr_mgmt_2     = 0x6C,
    .int_pin_cfg    = 0x37,
    .mem_r_w        = 0x6F,
    .accel_offs     = 0x77,
    .i2c_mst        = 0x24,
    .bank_sel       = 0x6D,
    .mem_start_addr = 0x6E,
    .prgm_start_h   = 0x70
#ifdef AK89xx_SECONDARY
    ,.raw_compass   = 0x49,
    .s0_addr        = 0x25,
    .s0_reg         = 0x26,
    .s0_ctrl        = 0x27,
    .s1_addr        = 0x28,
    .s1_reg         = 0x29,
    .s1_ctrl        = 0x2A,
    .s4_ctrl        = 0x34,
    .s0_do          = 0x63,
    .s1_do          = 0x64,
    .i2c_delay_ctrl = 0x67
#endif
};
const struct hw_s hw = {
    .addr           = 0x68,
    .max_fifo       = 1024,
    .num_reg        = 128,
    .temp_sens      = 321,
    .temp_offset    = 0,
    .bank_size      = 256
#if defined AK89xx_SECONDARY
    ,.compass_fsr    = AK89xx_FSR
#endif
};

const struct test_s test = {
    .gyro_sens      = 32768/250,
    .accel_sens     = 32768/16,
    .reg_rate_div   = 0,    /* 1kHz. */
    .reg_lpf        = 1,    /* 188Hz. */
    .reg_gyro_fsr   = 0,    /* 250dps. */
    .reg_accel_fsr  = 0x18, /* 16g. */
    .wait_ms        = 50,
    .packet_thresh  = 5,    /* 5% */
    .min_dps        = 10.f,
    .max_dps        = 105.f,
    .max_gyro_var   = 0.14f,
    .min_g          = 0.3f,
    .max_g          = 0.95f,
    .max_accel_var  = 0.14f
};

static struct gyro_state_s st = {
    .reg = &reg,
    .hw = &hw,
    .test = &test
};
#endif

// #define MAX_PACKET_LENGTH (12)

#ifdef AK89xx_SECONDARY
static int32_t setup_compass(void);
#define MAX_COMPASS_SAMPLE_RATE (100)
#endif

/**
 *  @brief      Enable/disable data ready interrupt.
 *  If the DMP is on, the DMP interrupt is enabled. Otherwise, the data ready
 *  interrupt is used.
 *  @param[in]  enable      1 to enable interrupt.
 *  @return     0 if successful.
 */
static int32_t set_int_enable(uint8_t enable)
{
    uint8_t tmp;

    if (st.chip_cfg.dmp_on) {
        if (enable)
            tmp = BIT_DMP_INT_EN;
        else
            tmp = 0x00;
        if (i2c_write(st.hw->addr, st.reg->int_enable, 1, &tmp))
            return -1;
        st.chip_cfg.int_enable = tmp;
    } else {
        if (!st.chip_cfg.sensors)
            return -1;
        if (enable && st.chip_cfg.int_enable)
            return 0;
        if (enable)
            tmp = BIT_DATA_RDY_EN;
        else
            tmp = 0x00;
        if (i2c_write(st.hw->addr, st.reg->int_enable, 1, &tmp))
            return -1;
        st.chip_cfg.int_enable = tmp;
    }
    return 0;
}

/**
 *  @brief      Register dump for testing.
 *  @return     0 if successful.
 */
int32_t mpu_reg_dump(void)
{
    uint8_t ii;
    uint8_t data;

    for (ii = 0; ii < st.hw->num_reg; ii++) {
        if (ii == st.reg->fifo_r_w || ii == st.reg->mem_r_w)
            continue;
        if (i2c_read(st.hw->addr, ii, 1, &data))
            return -1;
        LOGI(TAG,"%#5x: %#5x", ii, data);
    }
    return 0;
}

/**
 *  @brief      Read from a single register.
 *  NOTE: The memory and FIFO read/write registers cannot be accessed.
 *  @param[in]  reg     Register address.
 *  @param[out] data    Register data.
 *  @return     0 if successful.
 */
int32_t mpu_read_reg(uint8_t reg, uint8_t *data)
{
    if (reg == st.reg->fifo_r_w || reg == st.reg->mem_r_w)
        return -1;
    if (reg >= st.hw->num_reg)
        return -1;
    return i2c_read(st.hw->addr, reg, 1, data);
}

/**
 *  @brief      Initialize hardware.
 *  Initial configuration:\n
 *  Gyro FSR: +/- 2000DPS\n
 *  Accel FSR +/- 2G\n
 *  DLPF: 42Hz\n
 *  FIFO rate: 50Hz\n
 *  Clock source: Gyro PLL\n
 *  FIFO: Disabled.\n
 *  Data ready interrupt: Disabled, active low, unlatched.
 *  @param[in]  int_param   Platform-specific parameters to interrupt API.
 *  @return     0 if successful.
 */
int32_t mpu_init(void)
{
    uint8_t data[6], rev;
		
    /* Reset device. */
    data[0] = BIT_RESET;
    if (i2c_write(st.hw->addr, st.reg->pwr_mgmt_1, 1, data))
        return -1;
    delay_ms(100);

    // for(volatile uint32_t i = 0; i< 10000; i++);

    /* Wake up chip. */
    data[0] = 0x00;
    if (i2c_write(st.hw->addr, st.reg->pwr_mgmt_1, 1, data))
        return -1;

#if defined MPU6050
    /* Check product revision. */
    if (i2c_read(st.hw->addr, st.reg->accel_offs, 6, data))
        return -1;
    rev = ((data[5] & 0x01) << 2) | ((data[3] & 0x01) << 1) |
        (data[1] & 0x01);

    if (rev) {
        /* Congrats, these parts are better. */
        if (rev == 1)
            st.chip_cfg.accel_half = 1;
        else if (rev == 2)
            st.chip_cfg.accel_half = 0;
        else {
            LOGE(TAG,"Unsupported software product rev %d.", rev);
            return -1;
        }
    } else {
        if (i2c_read(st.hw->addr, st.reg->prod_id, 1, data))
            return -1;
        rev = data[0] & 0x0F;
				LOGI(TAG,"%X",data[0]);
        if (!rev) {
            LOGE(TAG,"Product ID read as 0 indicates device is either "
                "incompatible or an MPU3050.");
            return -1;
        } else if (rev == 4) {
            LOGI(TAG,"Half sensitivity part found.");
            st.chip_cfg.accel_half = 1;
        } else
            st.chip_cfg.accel_half = 0;
    }
#elif defined MPU6500
#define MPU6500_MEM_REV_ADDR    (0x17)
    if (mpu_read_mem(MPU6500_MEM_REV_ADDR, 1, &rev))
        return -1;
    if (rev == 0x1)
        st.chip_cfg.accel_half = 0;
    else {
        LOGE(TAG,"Unsupported software product rev %d.", rev);
        return -1;
    }

    /* MPU6500 shares 4kB of memory between the DMP and the FIFO. Since the
     * first 3kB are needed by the DMP, we'll use the last 1kB for the FIFO.
     */
    data[0] = BIT_FIFO_SIZE_1024 | 0x8;
    if (i2c_write(st.hw->addr, st.reg->accel_cfg2, 1, data))
        return -1;
#endif

    /* Set to invalid values to ensure no I2C writes are skipped. */
    st.chip_cfg.sensors = 0xFF;
    st.chip_cfg.gyro_fsr = 0xFF;
    st.chip_cfg.accel_fsr = 0xFF;
    st.chip_cfg.lpf = 0xFF;
    st.chip_cfg.sample_rate = 0xFFFF;
    st.chip_cfg.fifo_enable = 0xFF;
    st.chip_cfg.bypass_mode = 0xFF;
#ifdef AK89xx_SECONDARY
    st.chip_cfg.compass_sample_rate = 0xFFFF;
#endif
    /* mpu_set_sensors always preserves this setting. */
    st.chip_cfg.clk_src = INV_CLK_PLL;
    /* Handled in next call to mpu_set_bypass. */
    st.chip_cfg.active_low_int = 1;
    st.chip_cfg.latched_int = 0;
    st.chip_cfg.int_motion_only = 0;
    st.chip_cfg.lp_accel_mode = 0;
    memset(&st.chip_cfg.cache, 0, sizeof(st.chip_cfg.cache));
    st.chip_cfg.dmp_on = 0;
    st.chip_cfg.dmp_loaded = 0;
    st.chip_cfg.dmp_sample_rate = 0;

    if (mpu_set_gyro_fsr(2000))
        return -1;
    if (mpu_set_accel_fsr(2))
        return -1;
    if (mpu_set_lpf(42))
        return -1;
    if (mpu_set_sample_rate(50))
        return -1;
    if (mpu_configure_fifo(0))
        return -1;

//    if (int_param)
//        reg_int_cb(int_param);

#ifdef AK89xx_SECONDARY
    setup_compass();
    if (mpu_set_compass_sample_rate(10))
        return -1;
#else
    /* Already disabled by setup_compass. */
    if (mpu_set_bypass(0))
        return -1;
#endif

    mpu_set_sensors(0);
    return 0;
}

/**
 *  @brief      Enter low-power accel-only mode.
 *  In low-power accel mode, the chip goes to sleep and only wakes up to sample
 *  the accelerometer at one of the following frequencies:
 *  \n MPU6050: 1.25Hz, 5Hz, 20Hz, 40Hz
 *  \n MPU6500: 1.25Hz, 2.5Hz, 5Hz, 10Hz, 20Hz, 40Hz, 80Hz, 160Hz, 320Hz, 640Hz
 *  \n If the requested rate is not one listed above, the device will be set to
 *  the next highest rate. Requesting a rate above the maximum supported
 *  frequency will result in an error.
 *  \n To select a fractional wake-up frequency, round down the value passed to
 *  @e rate.
 *  @param[in]  rate        Minimum sampling rate, or zero to disable LP
 *                          accel mode.
 *  @return     0 if successful.
 */
int32_t mpu_lp_accel_mode(uint8_t rate)
{
    uint8_t tmp[2];

    if (rate > 40)
        return -1;

    if (!rate) {
        mpu_set_int_latched(0);
        tmp[0] = 0;
        tmp[1] = BIT_STBY_XYZG;
        if (i2c_write(st.hw->addr, st.reg->pwr_mgmt_1, 2, tmp))
            return -1;
        st.chip_cfg.lp_accel_mode = 0;
        return 0;
    }
    /* For LP accel, we automatically configure the hardware to produce latched
     * interrupts. In LP accel mode, the hardware cycles into sleep mode before
     * it gets a chance to deassert the interrupt pin; therefore, we shift this
     * responsibility over to the MCU.
     *
     * Any register read will clear the interrupt.
     */
    mpu_set_int_latched(1);
#if defined MPU6050
    tmp[0] = BIT_LPA_CYCLE;
    if (rate == 1) {
        tmp[1] = INV_LPA_1_25HZ;
        mpu_set_lpf(5);
    } else if (rate <= 5) {
        tmp[1] = INV_LPA_5HZ;
        mpu_set_lpf(5);
    } else if (rate <= 20) {
        tmp[1] = INV_LPA_20HZ;
        mpu_set_lpf(10);
    } else {
        tmp[1] = INV_LPA_40HZ;
        mpu_set_lpf(20);
    }
    tmp[1] = (tmp[1] << 6) | BIT_STBY_XYZG;
    if (i2c_write(st.hw->addr, st.reg->pwr_mgmt_1, 2, tmp))
        return -1;
#elif defined MPU6500
    /* Set wake frequency. */
    if (rate == 1)
        tmp[0] = INV_LPA_1_25HZ;
    else if (rate == 2)
        tmp[0] = INV_LPA_2_5HZ;
    else if (rate <= 5)
        tmp[0] = INV_LPA_5HZ;
    else if (rate <= 10)
        tmp[0] = INV_LPA_10HZ;
    else if (rate <= 20)
        tmp[0] = INV_LPA_20HZ;
    else if (rate <= 40)
        tmp[0] = INV_LPA_40HZ;
    else if (rate <= 80)
        tmp[0] = INV_LPA_80HZ;
    else if (rate <= 160)
        tmp[0] = INV_LPA_160HZ;
    else if (rate <= 320)
        tmp[0] = INV_LPA_320HZ;
    else
        tmp[0] = INV_LPA_640HZ;
    if (i2c_write(st.hw->addr, st.reg->lp_accel_odr, 1, tmp))
        return -1;
    tmp[0] = BIT_LPA_CYCLE;
    if (i2c_write(st.hw->addr, st.reg->pwr_mgmt_1, 1, tmp))
        return -1;
#endif
    st.chip_cfg.sensors = INV_XYZ_ACCEL;
    st.chip_cfg.clk_src = 0;
    st.chip_cfg.lp_accel_mode = 1;
    mpu_configure_fifo(0);

    return 0;
}

/**
 *  @brief      Read raw gyro data directly from the registers.
 *  @param[out] data        Raw data in hardware units.
 *  @param[out] timestamp   Timestamp in milliseconds. 0 if not needed.
 *  @return     0 if successful.
 */
int32_t mpu_get_gyro_reg(short *data, uint64_t *timestamp)
{
    uint8_t tmp[6];

    if (!(st.chip_cfg.sensors & INV_XYZ_GYRO))
        return -1;

    if (i2c_read(st.hw->addr, st.reg->raw_gyro, 6, tmp))
        return -1;
    data[0] = (tmp[0] << 8) | tmp[1];
    data[1] = (tmp[2] << 8) | tmp[3];
    data[2] = (tmp[4] << 8) | tmp[5];
    if (timestamp)
        get_ms(timestamp);
    return 0;
}

/**
 *  @brief      Read raw accel data directly from the registers.
 *  @param[out] data        Raw data in hardware units.
 *  @param[out] timestamp   Timestamp in milliseconds. 0 if not needed.
 *  @return     0 if successful.
 */
int32_t mpu_get_accel_reg(short *data, uint64_t *timestamp)
{
    uint8_t tmp[6];

    if (!(st.chip_cfg.sensors & INV_XYZ_ACCEL))
        return -1;

    if (i2c_read(st.hw->addr, st.reg->raw_accel, 6, tmp))
        return -1;
    data[0] = (tmp[0] << 8) | tmp[1];
    data[1] = (tmp[2] << 8) | tmp[3];
    data[2] = (tmp[4] << 8) | tmp[5];
    if (timestamp)
        get_ms(timestamp);
    return 0;
}

/**
 *  @brief      Read temperature data directly from the registers.
 *  @param[out] data        Data in q16 format.
 *  @param[out] timestamp   Timestamp in milliseconds. 0 if not needed.
 *  @return     0 if successful.
 */
int32_t mpu_get_temperature(int64_t *data, uint64_t *timestamp)
{
    uint8_t tmp[2];
    short raw;

    if (!(st.chip_cfg.sensors))
        return -1;

    if (i2c_read(st.hw->addr, st.reg->temp, 2, tmp))
        return -1;
    raw = (tmp[0] << 8) | tmp[1];
    if (timestamp)
        get_ms(timestamp);

    data[0] = (int64_t)((35 + ((raw - (float)st.hw->temp_offset) / st.hw->temp_sens)) * 65536L);
    return 0;
}

/**
 *  @brief      Push biases to the accel bias registers.
 *  This function expects biases relative to the current sensor output, and
 *  these biases will be added to the factory-supplied values.
 *  @param[in]  accel_bias  New biases.
 *  @return     0 if successful.
 */
int32_t mpu_set_accel_bias(const int64_t *accel_bias)
{
    uint8_t data[6];
    short accel_hw[3];
    short got_accel[3];
    short fg[3];

    if (!accel_bias)
        return -1;
    if (!accel_bias[0] && !accel_bias[1] && !accel_bias[2])
        return 0;

    if (i2c_read(st.hw->addr, 3, 3, data))
        return -1;
    fg[0] = ((data[0] >> 4) + 8) & 0xf;
    fg[1] = ((data[1] >> 4) + 8) & 0xf;
    fg[2] = ((data[2] >> 4) + 8) & 0xf;

    accel_hw[0] = (short)(accel_bias[0] * 2 / (64 + fg[0]));
    accel_hw[1] = (short)(accel_bias[1] * 2 / (64 + fg[1]));
    accel_hw[2] = (short)(accel_bias[2] * 2 / (64 + fg[2]));

    if (i2c_read(st.hw->addr, 0x06, 6, data))
        return -1;

    got_accel[0] = ((short)data[0] << 8) | data[1];
    got_accel[1] = ((short)data[2] << 8) | data[3];
    got_accel[2] = ((short)data[4] << 8) | data[5];

    accel_hw[0] += got_accel[0];
    accel_hw[1] += got_accel[1];
    accel_hw[2] += got_accel[2];

    data[0] = (accel_hw[0] >> 8) & 0xff;
    data[1] = (accel_hw[0]) & 0xff;
    data[2] = (accel_hw[1] >> 8) & 0xff;
    data[3] = (accel_hw[1]) & 0xff;
    data[4] = (accel_hw[2] >> 8) & 0xff;
    data[5] = (accel_hw[2]) & 0xff;

    if (i2c_write(st.hw->addr, 0x06, 6, data))
        return -1;
    return 0;
}

/**
 *  @brief  Reset FIFO read/write pointers.
 *  @return 0 if successful.
 */
int32_t mpu_reset_fifo(void)
{
    uint8_t data;

    if (!(st.chip_cfg.sensors))
        return -1;

    data = 0;
    if (i2c_write(st.hw->addr, st.reg->int_enable, 1, &data))
        return -1;
    if (i2c_write(st.hw->addr, st.reg->fifo_en, 1, &data))
        return -1;
    if (i2c_write(st.hw->addr, st.reg->user_ctrl, 1, &data))
        return -1;

    if (st.chip_cfg.dmp_on) {
        data = BIT_FIFO_RST | BIT_DMP_RST;
        if (i2c_write(st.hw->addr, st.reg->user_ctrl, 1, &data))
            return -1;
        delay_ms(50);
        data = BIT_DMP_EN | BIT_FIFO_EN;
        if (st.chip_cfg.sensors & INV_XYZ_COMPASS)
            data |= BIT_AUX_IF_EN;
        if (i2c_write(st.hw->addr, st.reg->user_ctrl, 1, &data))
            return -1;
        if (st.chip_cfg.int_enable)
            data = BIT_DMP_INT_EN;
        else
            data = 0;
        if (i2c_write(st.hw->addr, st.reg->int_enable, 1, &data))
            return -1;
        data = 0;
        if (i2c_write(st.hw->addr, st.reg->fifo_en, 1, &data))
            return -1;
    } else {
        data = BIT_FIFO_RST;
        if (i2c_write(st.hw->addr, st.reg->user_ctrl, 1, &data))
            return -1;
        if (st.chip_cfg.bypass_mode || !(st.chip_cfg.sensors & INV_XYZ_COMPASS))
            data = BIT_FIFO_EN;
        else
            data = BIT_FIFO_EN | BIT_AUX_IF_EN;
        if (i2c_write(st.hw->addr, st.reg->user_ctrl, 1, &data))
            return -1;
        delay_ms(50);
        if (st.chip_cfg.int_enable)
            data = BIT_DATA_RDY_EN;
        else
            data = 0;
        if (i2c_write(st.hw->addr, st.reg->int_enable, 1, &data))
            return -1;
        if (i2c_write(st.hw->addr, st.reg->fifo_en, 1, &st.chip_cfg.fifo_enable))
            return -1;
    }
    return 0;
}

/**
 *  @brief      Get the gyro full-scale range.
 *  @param[out] fsr Current full-scale range.
 *  @return     0 if successful.
 */
int32_t mpu_get_gyro_fsr(uint16_t *fsr)
{
    switch (st.chip_cfg.gyro_fsr) {
    case INV_FSR_250DPS:
        fsr[0] = 250;
        break;
    case INV_FSR_500DPS:
        fsr[0] = 500;
        break;
    case INV_FSR_1000DPS:
        fsr[0] = 1000;
        break;
    case INV_FSR_2000DPS:
        fsr[0] = 2000;
        break;
    default:
        fsr[0] = 0;
        break;
    }
    return 0;
}

/**
 *  @brief      Set the gyro full-scale range.
 *  @param[in]  fsr Desired full-scale range.
 *  @return     0 if successful.
 */
int32_t mpu_set_gyro_fsr(uint16_t fsr)
{
    uint8_t data;

    if (!(st.chip_cfg.sensors))
        return -1;

    switch (fsr) {
    case 250:
        data = INV_FSR_250DPS << 3;
        break;
    case 500:
        data = INV_FSR_500DPS << 3;
        break;
    case 1000:
        data = INV_FSR_1000DPS << 3;
        break;
    case 2000:
        data = INV_FSR_2000DPS << 3;
        break;
    default:
        return -1;
    }

    if (st.chip_cfg.gyro_fsr == (data >> 3))
        return 0;
    if (i2c_write(st.hw->addr, st.reg->gyro_cfg, 1, &data))
        return -1;
    st.chip_cfg.gyro_fsr = data >> 3;
    return 0;
}

/**
 *  @brief      Get the accel full-scale range.
 *  @param[out] fsr Current full-scale range.
 *  @return     0 if successful.
 */
int32_t mpu_get_accel_fsr(uint8_t *fsr)
{
    switch (st.chip_cfg.accel_fsr) {
    case INV_FSR_2G:
        fsr[0] = 2;
        break;
    case INV_FSR_4G:
        fsr[0] = 4;
        break;
    case INV_FSR_8G:
        fsr[0] = 8;
        break;
    case INV_FSR_16G:
        fsr[0] = 16;
        break;
    default:
        return -1;
    }
    if (st.chip_cfg.accel_half)
        fsr[0] <<= 1;
    return 0;
}

/**
 *  @brief      Set the accel full-scale range.
 *  @param[in]  fsr Desired full-scale range.
 *  @return     0 if successful.
 */
int32_t mpu_set_accel_fsr(uint8_t fsr)
{
    uint8_t data;

    if (!(st.chip_cfg.sensors))
        return -1;

    switch (fsr) {
    case 2:
        data = INV_FSR_2G << 3;
        break;
    case 4:
        data = INV_FSR_4G << 3;
        break;
    case 8:
        data = INV_FSR_8G << 3;
        break;
    case 16:
        data = INV_FSR_16G << 3;
        break;
    default:
        return -1;
    }

    if (st.chip_cfg.accel_fsr == (data >> 3))
        return 0;
    if (i2c_write(st.hw->addr, st.reg->accel_cfg, 1, &data))
        return -1;
    st.chip_cfg.accel_fsr = data >> 3;
    return 0;
}

/**
 *  @brief      Get the current DLPF setting.
 *  @param[out] lpf Current LPF setting.
 *  0 if successful.
 */
int32_t mpu_get_lpf(uint16_t *lpf)
{
    switch (st.chip_cfg.lpf) {
    case INV_FILTER_188HZ:
        lpf[0] = 188;
        break;
    case INV_FILTER_98HZ:
        lpf[0] = 98;
        break;
    case INV_FILTER_42HZ:
        lpf[0] = 42;
        break;
    case INV_FILTER_20HZ:
        lpf[0] = 20;
        break;
    case INV_FILTER_10HZ:
        lpf[0] = 10;
        break;
    case INV_FILTER_5HZ:
        lpf[0] = 5;
        break;
    case INV_FILTER_256HZ_NOLPF2:
    case INV_FILTER_2100HZ_NOLPF:
    default:
        lpf[0] = 0;
        break;
    }
    return 0;
}

/**
 *  @brief      Set digital low pass filter.
 *  The following LPF settings are supported: 188, 98, 42, 20, 10, 5.
 *  @param[in]  lpf Desired LPF setting.
 *  @return     0 if successful.
 */
int32_t mpu_set_lpf(uint16_t lpf)
{
    uint8_t data;

    if (!(st.chip_cfg.sensors))
        return -1;

    if (lpf >= 188)
        data = INV_FILTER_188HZ;
    else if (lpf >= 98)
        data = INV_FILTER_98HZ;
    else if (lpf >= 42)
        data = INV_FILTER_42HZ;
    else if (lpf >= 20)
        data = INV_FILTER_20HZ;
    else if (lpf >= 10)
        data = INV_FILTER_10HZ;
    else
        data = INV_FILTER_5HZ;

    if (st.chip_cfg.lpf == data)
        return 0;
    if (i2c_write(st.hw->addr, st.reg->lpf, 1, &data))
        return -1;
    st.chip_cfg.lpf = data;
    return 0;
}

/**
 *  @brief      Get sampling rate.
 *  @param[out] rate    Current sampling rate (Hz).
 *  @return     0 if successful.
 */
int32_t mpu_get_sample_rate(uint16_t *rate)
{
    if (st.chip_cfg.dmp_on)
        return -1;
    else
        rate[0] = st.chip_cfg.sample_rate;
    return 0;
}

/**
 *  @brief      Set sampling rate.
 *  Sampling rate must be between 4Hz and 1kHz.
 *  @param[in]  rate    Desired sampling rate (Hz).
 *  @return     0 if successful.
 */
int32_t mpu_set_sample_rate(uint16_t rate)
{
    uint8_t data;

    if (!(st.chip_cfg.sensors))
        return -1;

    if (st.chip_cfg.dmp_on)
        return -1;
    else {
        if (st.chip_cfg.lp_accel_mode) {
            if (rate && (rate <= 40)) {
                /* Just stay in low-power accel mode. */
                mpu_lp_accel_mode(rate);
                return 0;
            }
            /* Requested rate exceeds the allowed frequencies in LP accel mode,
             * switch back to full-power mode.
             */
            mpu_lp_accel_mode(0);
        }
        if (rate < 4)
            rate = 4;
        else if (rate > 1000)
            rate = 1000;

        data = 1000 / rate - 1;
        if (i2c_write(st.hw->addr, st.reg->rate_div, 1, &data))
            return -1;

        st.chip_cfg.sample_rate = 1000 / (1 + data);

#ifdef AK89xx_SECONDARY
        mpu_set_compass_sample_rate(min(st.chip_cfg.compass_sample_rate, MAX_COMPASS_SAMPLE_RATE));
#endif

        /* Automatically set LPF to 1/2 sampling rate. */
        mpu_set_lpf(st.chip_cfg.sample_rate >> 1);
        return 0;
    }
}

/**
 *  @brief      Get compass sampling rate.
 *  @param[out] rate    Current compass sampling rate (Hz).
 *  @return     0 if successful.
 */
int32_t mpu_get_compass_sample_rate(uint16_t *rate)
{
#ifdef AK89xx_SECONDARY
    rate[0] = st.chip_cfg.compass_sample_rate;
    return 0;
#else
    rate[0] = 0;
    return -1;
#endif
}

/**
 *  @brief      Set compass sampling rate.
 *  The compass on the auxiliary I2C bus is read by the MPU hardware at a
 *  maximum of 100Hz. The actual rate can be set to a fraction of the gyro
 *  sampling rate.
 *
 *  \n WARNING: The new rate may be different than what was requested. Call
 *  mpu_get_compass_sample_rate to check the actual setting.
 *  @param[in]  rate    Desired compass sampling rate (Hz).
 *  @return     0 if successful.
 */
int32_t mpu_set_compass_sample_rate(uint16_t rate)
{
#ifdef AK89xx_SECONDARY
    uint8_t div;
    if (!rate || rate > st.chip_cfg.sample_rate || rate > MAX_COMPASS_SAMPLE_RATE)
        return -1;

    div = st.chip_cfg.sample_rate / rate - 1;
    if (i2c_write(st.hw->addr, st.reg->s4_ctrl, 1, &div))
        return -1;
    st.chip_cfg.compass_sample_rate = st.chip_cfg.sample_rate / (div + 1);
    return 0;
#else
    return -1;
#endif
}

/**
 *  @brief      Get gyro sensitivity scale factor.
 *  @param[out] sens    Conversion from hardware units to dps.
 *  @return     0 if successful.
 */
int32_t mpu_get_gyro_sens(float *sens)
{
    switch (st.chip_cfg.gyro_fsr) {
    case INV_FSR_250DPS:
        sens[0] = 131.f;
        break;
    case INV_FSR_500DPS:
        sens[0] = 65.5f;
        break;
    case INV_FSR_1000DPS:
        sens[0] = 32.8f;
        break;
    case INV_FSR_2000DPS:
        sens[0] = 16.4f;
        break;
    default:
        return -1;
    }
    return 0;
}

/**
 *  @brief      Get accel sensitivity scale factor.
 *  @param[out] sens    Conversion from hardware units to g's.
 *  @return     0 if successful.
 */
int32_t mpu_get_accel_sens(uint16_t *sens)
{
    switch (st.chip_cfg.accel_fsr) {
    case INV_FSR_2G:
        sens[0] = 16384;
        break;
    case INV_FSR_4G:
        sens[0] = 8092;
        break;
    case INV_FSR_8G:
        sens[0] = 4096;
        break;
    case INV_FSR_16G:
        sens[0] = 2048;
        break;
    default:
        return -1;
    }
    if (st.chip_cfg.accel_half)
        sens[0] >>= 1;
    return 0;
}

/**
 *  @brief      Get current FIFO configuration.
 *  @e sensors can contain a combination of the following flags:
 *  \n INV_X_GYRO, INV_Y_GYRO, INV_Z_GYRO
 *  \n INV_XYZ_GYRO
 *  \n INV_XYZ_ACCEL
 *  @param[out] sensors Mask of sensors in FIFO.
 *  @return     0 if successful.
 */
int32_t mpu_get_fifo_config(uint8_t *sensors)
{
    sensors[0] = st.chip_cfg.fifo_enable;
    return 0;
}

/**
 *  @brief      Select which sensors are pushed to FIFO.
 *  @e sensors can contain a combination of the following flags:
 *  \n INV_X_GYRO, INV_Y_GYRO, INV_Z_GYRO
 *  \n INV_XYZ_GYRO
 *  \n INV_XYZ_ACCEL
 *  @param[in]  sensors Mask of sensors to push to FIFO.
 *  @return     0 if successful.
 */
int32_t mpu_configure_fifo(uint8_t sensors)
{
    uint8_t prev;
    int32_t result = 0;

    /* Compass data isn't going into the FIFO. Stop trying. */
    sensors &= ~INV_XYZ_COMPASS;

    if (st.chip_cfg.dmp_on)
        return 0;
    else {
        if (!(st.chip_cfg.sensors))
            return -1;
        prev = st.chip_cfg.fifo_enable;
        st.chip_cfg.fifo_enable = sensors & st.chip_cfg.sensors;
        if (st.chip_cfg.fifo_enable != sensors)
            /* You're not getting what you asked for. Some sensors are
             * asleep.
             */
            result = -1;
        else
            result = 0;
        if (sensors || st.chip_cfg.lp_accel_mode)
            set_int_enable(1);
        else
            set_int_enable(0);
        if (sensors) {
            if (mpu_reset_fifo()) {
                st.chip_cfg.fifo_enable = prev;
                return -1;
            }
        }
    }

    return result;
}

/**
 *  @brief      Get current power state.
 *  @param[in]  power_on    1 if turned on, 0 if suspended.
 *  @return     0 if successful.
 */
int32_t mpu_get_power_state(uint8_t *power_on)
{
    if (st.chip_cfg.sensors)
        power_on[0] = 1;
    else
        power_on[0] = 0;
    return 0;
}

/**
 *  @brief      Turn specific sensors on/off.
 *  @e sensors can contain a combination of the following flags:
 *  \n INV_X_GYRO, INV_Y_GYRO, INV_Z_GYRO
 *  \n INV_XYZ_GYRO
 *  \n INV_XYZ_ACCEL
 *  \n INV_XYZ_COMPASS
 *  @param[in]  sensors    Mask of sensors to wake.
 *  @return     0 if successful.
 */
int32_t mpu_set_sensors(uint8_t sensors)
{
    uint8_t data;
#ifdef AK89xx_SECONDARY
    uint8_t user_ctrl;
#endif

    if (sensors & INV_XYZ_GYRO)
        data = INV_CLK_PLL;
    else if (sensors)
        data = 0;
    else
        data = BIT_SLEEP;
    if (i2c_write(st.hw->addr, st.reg->pwr_mgmt_1, 1, &data)) {
        st.chip_cfg.sensors = 0;
        return -1;
    }
    st.chip_cfg.clk_src = data & ~BIT_SLEEP;

    data = 0;
    if (!(sensors & INV_X_GYRO))
        data |= BIT_STBY_XG;
    if (!(sensors & INV_Y_GYRO))
        data |= BIT_STBY_YG;
    if (!(sensors & INV_Z_GYRO))
        data |= BIT_STBY_ZG;
    if (!(sensors & INV_XYZ_ACCEL))
        data |= BIT_STBY_XYZA;
    if (i2c_write(st.hw->addr, st.reg->pwr_mgmt_2, 1, &data)) {
        st.chip_cfg.sensors = 0;
        return -1;
    }

    if (sensors && (sensors != INV_XYZ_ACCEL))
        /* Latched interrupts only used in LP accel mode. */
        mpu_set_int_latched(0);

#ifdef AK89xx_SECONDARY
#ifdef AK89xx_BYPASS
    if (sensors & INV_XYZ_COMPASS)
        mpu_set_bypass(1);
    else
        mpu_set_bypass(0);
#else
    if (i2c_read(st.hw->addr, st.reg->user_ctrl, 1, &user_ctrl))
        return -1;
    /* Handle AKM power management. */
    if (sensors & INV_XYZ_COMPASS) {
        data = AKM_SINGLE_MEASUREMENT;
        user_ctrl |= BIT_AUX_IF_EN;
    } else {
        data = AKM_POWER_DOWN;
        user_ctrl &= ~BIT_AUX_IF_EN;
    }
    if (st.chip_cfg.dmp_on)
        user_ctrl |= BIT_DMP_EN;
    else
        user_ctrl &= ~BIT_DMP_EN;
    if (i2c_write(st.hw->addr, st.reg->s1_do, 1, &data))
        return -1;
    /* Enable/disable I2C master mode. */
    if (i2c_write(st.hw->addr, st.reg->user_ctrl, 1, &user_ctrl))
        return -1;
#endif
#endif

    st.chip_cfg.sensors = sensors;
    st.chip_cfg.lp_accel_mode = 0;
    delay_ms(50);
    return 0;
}

/**
 *  @brief      Read the MPU interrupt status registers.
 *  @param[out] status  Mask of interrupt bits.
 *  @return     0 if successful.
 */
int32_t mpu_get_int_status(short *status)
{
    uint8_t tmp[2];
    if (!st.chip_cfg.sensors)
        return -1;
    if (i2c_read(st.hw->addr, st.reg->dmp_int_status, 2, tmp))
        return -1;
    status[0] = (tmp[0] << 8) | tmp[1];
    return 0;
}

/**
 *  @brief      Get one packet from the FIFO.
 *  If @e sensors does not contain a particular sensor, disregard the data
 *  returned to that pointer.
 *  \n @e sensors can contain a combination of the following flags:
 *  \n INV_X_GYRO, INV_Y_GYRO, INV_Z_GYRO
 *  \n INV_XYZ_GYRO
 *  \n INV_XYZ_ACCEL
 *  \n If the FIFO has no new data, @e sensors will be zero.
 *  \n If the FIFO is disabled, @e sensors will be zero and this function will
 *  return a non-zero error code.
 *  @param[out] gyro        Gyro data in hardware units.
 *  @param[out] accel       Accel data in hardware units.
 *  @param[out] timestamp   Timestamp in milliseconds.
 *  @param[out] sensors     Mask of sensors read from FIFO.
 *  @param[out] more        Number of remaining packets.
 *  @return     0 if successful.
 */
int32_t mpu_read_fifo(short *gyro, short *accel, uint64_t *timestamp,
        uint8_t *sensors, uint8_t *more)
{
    /* Assumes maximum packet size is gyro (6) + accel (6). */
    uint8_t data[MAX_PACKET_LENGTH];
    uint8_t packet_size = 0;
    uint16_t fifo_count, index = 0;

    if (st.chip_cfg.dmp_on)
        return -1;

    sensors[0] = 0;
    if (!st.chip_cfg.sensors)
        return -1;
    if (!st.chip_cfg.fifo_enable)
        return -1;

    if (st.chip_cfg.fifo_enable & INV_X_GYRO)
        packet_size += 2;
    if (st.chip_cfg.fifo_enable & INV_Y_GYRO)
        packet_size += 2;
    if (st.chip_cfg.fifo_enable & INV_Z_GYRO)
        packet_size += 2;
    if (st.chip_cfg.fifo_enable & INV_XYZ_ACCEL)
        packet_size += 6;

    if (i2c_read(st.hw->addr, st.reg->fifo_count_h, 2, data))
        return -1;
    fifo_count = (data[0] << 8) | data[1];
    if (fifo_count < packet_size)
        return 0;
//    log_i("FIFO count: %hd\n", fifo_count);
    if (fifo_count > (st.hw->max_fifo >> 1)) {
        /* FIFO is 50% full, better check overflow bit. */
        if (i2c_read(st.hw->addr, st.reg->int_status, 1, data))
            return -1;
        if (data[0] & BIT_FIFO_OVERFLOW) {
            mpu_reset_fifo();
            return -2;
        }
    }
    get_ms((uint64_t*)timestamp);

    if (i2c_read(st.hw->addr, st.reg->fifo_r_w, packet_size, data))
        return -1;
    more[0] = fifo_count / packet_size - 1;
    sensors[0] = 0;

    if ((index != packet_size) && st.chip_cfg.fifo_enable & INV_XYZ_ACCEL) {
        accel[0] = (data[index+0] << 8) | data[index+1];
        accel[1] = (data[index+2] << 8) | data[index+3];
        accel[2] = (data[index+4] << 8) | data[index+5];
        sensors[0] |= INV_XYZ_ACCEL;
        index += 6;
    }
    if ((index != packet_size) && st.chip_cfg.fifo_enable & INV_X_GYRO) {
        gyro[0] = (data[index+0] << 8) | data[index+1];
        sensors[0] |= INV_X_GYRO;
        index += 2;
    }
    if ((index != packet_size) && st.chip_cfg.fifo_enable & INV_Y_GYRO) {
        gyro[1] = (data[index+0] << 8) | data[index+1];
        sensors[0] |= INV_Y_GYRO;
        index += 2;
    }
    if ((index != packet_size) && st.chip_cfg.fifo_enable & INV_Z_GYRO) {
        gyro[2] = (data[index+0] << 8) | data[index+1];
        sensors[0] |= INV_Z_GYRO;
        index += 2;
    }

    return 0;
}

/**
 *  @brief      Get one unparsed packet from the FIFO.
 *  This function should be used if the packet is to be parsed elsewhere.
 *  @param[in]  length  Length of one FIFO packet.
 *  @param[in]  data    FIFO packet.
 *  @param[in]  more    Number of remaining packets.
 */
int32_t mpu_read_fifo_stream(uint16_t length, uint8_t *data,
    uint8_t *more)
{
    uint8_t tmp[2];
    uint16_t fifo_count;
    if (!st.chip_cfg.dmp_on){
        LOGE(TAG,"chip's dmp is down");
        return -1;
    }
    if (!st.chip_cfg.sensors){
        LOGE(TAG,"sensor not present on chip");
        return -1;
    }

    if (i2c_read(st.hw->addr, st.reg->fifo_count_h, 2, tmp))
        return -1;
    fifo_count = (tmp[0] << 8) | tmp[1];
    if (fifo_count < length) {
        more[0] = 0;
        LOGE(TAG,"no count");
        return -1;
    }
    if (fifo_count > (st.hw->max_fifo >> 1)) {
        /* FIFO is 50% full, better check overflow bit. */
        if (i2c_read(st.hw->addr, st.reg->int_status, 1, tmp))
            return -1;
        if (tmp[0] & BIT_FIFO_OVERFLOW) {
            mpu_reset_fifo();
            LOGE(TAG,"fifo is overflow");
            return -2;
        }
    }

    if (i2c_read(st.hw->addr, st.reg->fifo_r_w, length, data))
        return -1;
    more[0] = fifo_count / length - 1;
    return 0;
}

/**
 *  @brief      Set device to bypass mode.
 *  @param[in]  bypass_on   1 to enable bypass mode.
 *  @return     0 if successful.
 */
int32_t mpu_set_bypass(uint8_t bypass_on)
{
    uint8_t tmp;

    if (st.chip_cfg.bypass_mode == bypass_on)
        return 0;

    if (bypass_on) {
        if (i2c_read(st.hw->addr, st.reg->user_ctrl, 1, &tmp))
            return -1;
        tmp &= ~BIT_AUX_IF_EN;
        if (i2c_write(st.hw->addr, st.reg->user_ctrl, 1, &tmp))
            return -1;
        delay_ms(3);
        tmp = BIT_BYPASS_EN;
        if (st.chip_cfg.active_low_int)
            tmp |= BIT_ACTL;
        if (st.chip_cfg.latched_int)
            tmp |= BIT_LATCH_EN | BIT_ANY_RD_CLR;
        if (i2c_write(st.hw->addr, st.reg->int_pin_cfg, 1, &tmp))
            return -1;
    } else {
        /* Enable I2C master mode if compass is being used. */
        if (i2c_read(st.hw->addr, st.reg->user_ctrl, 1, &tmp))
            return -1;
        if (st.chip_cfg.sensors & INV_XYZ_COMPASS)
            tmp |= BIT_AUX_IF_EN;
        else
            tmp &= ~BIT_AUX_IF_EN;
        if (i2c_write(st.hw->addr, st.reg->user_ctrl, 1, &tmp))
            return -1;
        delay_ms(3);
        if (st.chip_cfg.active_low_int)
            tmp = BIT_ACTL;
        else
            tmp = 0;
        if (st.chip_cfg.latched_int)
            tmp |= BIT_LATCH_EN | BIT_ANY_RD_CLR;
        if (i2c_write(st.hw->addr, st.reg->int_pin_cfg, 1, &tmp))
            return -1;
    }
    st.chip_cfg.bypass_mode = bypass_on;
    return 0;
}

/**
 *  @brief      Set interrupt level.
 *  @param[in]  active_low  1 for active low, 0 for active high.
 *  @return     0 if successful.
 */
int32_t mpu_set_int_level(uint8_t active_low)
{
    st.chip_cfg.active_low_int = active_low;
    return 0;
}

/**
 *  @brief      Enable latched interrupts.
 *  Any MPU register will clear the interrupt.
 *  @param[in]  enable  1 to enable, 0 to disable.
 *  @return     0 if successful.
 */
int32_t mpu_set_int_latched(uint8_t enable)
{
    uint8_t tmp;
    if (st.chip_cfg.latched_int == enable)
        return 0;

    if (enable)
        tmp = BIT_LATCH_EN | BIT_ANY_RD_CLR;
    else
        tmp = 0;
    if (st.chip_cfg.bypass_mode)
        tmp |= BIT_BYPASS_EN;
    if (st.chip_cfg.active_low_int)
        tmp |= BIT_ACTL;
    if (i2c_write(st.hw->addr, st.reg->int_pin_cfg, 1, &tmp))
        return -1;
    st.chip_cfg.latched_int = enable;
    return 0;
}

#ifdef MPU6050
static int32_t get_accel_prod_shift(float *st_shift)
{
    uint8_t tmp[4], shift_code[3], ii;

    if (i2c_read(st.hw->addr, 0x0D, 4, tmp))
        return 0x07;

    shift_code[0] = ((tmp[0] & 0xE0) >> 3) | ((tmp[3] & 0x30) >> 4);
    shift_code[1] = ((tmp[1] & 0xE0) >> 3) | ((tmp[3] & 0x0C) >> 2);
    shift_code[2] = ((tmp[2] & 0xE0) >> 3) | (tmp[3] & 0x03);
    for (ii = 0; ii < 3; ii++) {
        if (!shift_code[ii]) {
            st_shift[ii] = 0.f;
            continue;
        }
        /* Equivalent to..
         * st_shift[ii] = 0.34f * powf(0.92f/0.34f, (shift_code[ii]-1) / 30.f)
         */
        st_shift[ii] = 0.34f;
        while (--shift_code[ii])
            st_shift[ii] *= 1.034f;
    }
    return 0;
}

static int32_t accel_self_test(int64_t *bias_regular, int64_t *bias_st)
{
    int32_t jj, result = 0;
    float st_shift[3], st_shift_cust, st_shift_var;

    get_accel_prod_shift(st_shift);
    for(jj = 0; jj < 3; jj++) {
        st_shift_cust = labs(bias_regular[jj] - bias_st[jj]) / 65536.f;
        if (st_shift[jj]) {
            st_shift_var = st_shift_cust / st_shift[jj] - 1.f;
            if (fabs(st_shift_var) > test.max_accel_var)
                result |= 1 << jj;
        } else if ((st_shift_cust < test.min_g) ||
            (st_shift_cust > test.max_g))
            result |= 1 << jj;
    }

    return result;
}

static int32_t gyro_self_test(int64_t *bias_regular, int64_t *bias_st)
{
    int32_t jj, result = 0;
    uint8_t tmp[3];
    float st_shift, st_shift_cust, st_shift_var;

    if (i2c_read(st.hw->addr, 0x0D, 3, tmp))
        return 0x07;

    tmp[0] &= 0x1F;
    tmp[1] &= 0x1F;
    tmp[2] &= 0x1F;

    for (jj = 0; jj < 3; jj++) {
        st_shift_cust = labs(bias_regular[jj] - bias_st[jj]) / 65536.f;
        if (tmp[jj]) {
            st_shift = 3275.f / test.gyro_sens;
            while (--tmp[jj])
                st_shift *= 1.046f;
            st_shift_var = st_shift_cust / st_shift - 1.f;
            if (fabs(st_shift_var) > test.max_gyro_var)
                result |= 1 << jj;
        } else if ((st_shift_cust < test.min_dps) ||
            (st_shift_cust > test.max_dps))
            result |= 1 << jj;
    }
    return result;
}

#ifdef AK89xx_SECONDARY
static int32_t compass_self_test(void)
{
    uint8_t tmp[6];
    uint8_t tries = 10;
    int32_t result = 0x07;
    short data;

    mpu_set_bypass(1);

    tmp[0] = AKM_POWER_DOWN;
    if (i2c_write(st.chip_cfg.compass_addr, AKM_REG_CNTL, 1, tmp))
        return 0x07;
    tmp[0] = AKM_BIT_SELF_TEST;
    if (i2c_write(st.chip_cfg.compass_addr, AKM_REG_ASTC, 1, tmp))
        goto AKM_restore;
    tmp[0] = AKM_MODE_SELF_TEST;
    if (i2c_write(st.chip_cfg.compass_addr, AKM_REG_CNTL, 1, tmp))
        goto AKM_restore;

    do {
        delay_ms(10);
        if (i2c_read(st.chip_cfg.compass_addr, AKM_REG_ST1, 1, tmp))
            goto AKM_restore;
        if (tmp[0] & AKM_DATA_READY)
            break;
    } while (tries--);
    if (!(tmp[0] & AKM_DATA_READY))
        goto AKM_restore;

    if (i2c_read(st.chip_cfg.compass_addr, AKM_REG_HXL, 6, tmp))
        goto AKM_restore;

    result = 0;
    data = (short)(tmp[1] << 8) | tmp[0];
    if ((data > 100) || (data < -100))
        result |= 0x01;
    data = (short)(tmp[3] << 8) | tmp[2];
    if ((data > 100) || (data < -100))
        result |= 0x02;
    data = (short)(tmp[5] << 8) | tmp[4];
    if ((data > -300) || (data < -1000))
        result |= 0x04;

AKM_restore:
    tmp[0] = 0 | SUPPORTS_AK89xx_HIGH_SENS;
    i2c_write(st.chip_cfg.compass_addr, AKM_REG_ASTC, 1, tmp);
    tmp[0] = SUPPORTS_AK89xx_HIGH_SENS;
    i2c_write(st.chip_cfg.compass_addr, AKM_REG_CNTL, 1, tmp);
    mpu_set_bypass(0);
    return result;
}
#endif
#endif

static int32_t get_st_biases(int64_t *gyro, int64_t *accel, uint8_t hw_test)
{
    uint8_t data[MAX_PACKET_LENGTH];
    uint8_t packet_count, ii;
    uint16_t fifo_count;

    data[0] = 0x01;
    data[1] = 0;
    if (i2c_write(st.hw->addr, st.reg->pwr_mgmt_1, 2, data))
        return -1;
    delay_ms(200);
    data[0] = 0;
    if (i2c_write(st.hw->addr, st.reg->int_enable, 1, data))
        return -1;
    if (i2c_write(st.hw->addr, st.reg->fifo_en, 1, data))
        return -1;
    if (i2c_write(st.hw->addr, st.reg->pwr_mgmt_1, 1, data))
        return -1;
    if (i2c_write(st.hw->addr, st.reg->i2c_mst, 1, data))
        return -1;
    if (i2c_write(st.hw->addr, st.reg->user_ctrl, 1, data))
        return -1;
    data[0] = BIT_FIFO_RST | BIT_DMP_RST;
    if (i2c_write(st.hw->addr, st.reg->user_ctrl, 1, data))
        return -1;
    delay_ms(15);
    data[0] = st.test->reg_lpf;
    if (i2c_write(st.hw->addr, st.reg->lpf, 1, data))
        return -1;
    data[0] = st.test->reg_rate_div;
    if (i2c_write(st.hw->addr, st.reg->rate_div, 1, data))
        return -1;
    if (hw_test)
        data[0] = st.test->reg_gyro_fsr | 0xE0;
    else
        data[0] = st.test->reg_gyro_fsr;
    if (i2c_write(st.hw->addr, st.reg->gyro_cfg, 1, data))
        return -1;

    if (hw_test)
        data[0] = st.test->reg_accel_fsr | 0xE0;
    else
        data[0] = test.reg_accel_fsr;
    if (i2c_write(st.hw->addr, st.reg->accel_cfg, 1, data))
        return -1;
    if (hw_test)
        delay_ms(200);

    /* Fill FIFO for test.wait_ms milliseconds. */
    data[0] = BIT_FIFO_EN;
    if (i2c_write(st.hw->addr, st.reg->user_ctrl, 1, data))
        return -1;

    data[0] = INV_XYZ_GYRO | INV_XYZ_ACCEL;
    if (i2c_write(st.hw->addr, st.reg->fifo_en, 1, data))
        return -1;
    delay_ms(test.wait_ms);
    data[0] = 0;
    if (i2c_write(st.hw->addr, st.reg->fifo_en, 1, data))
        return -1;

    if (i2c_read(st.hw->addr, st.reg->fifo_count_h, 2, data))
        return -1;

    fifo_count = (data[0] << 8) | data[1];
    packet_count = fifo_count / MAX_PACKET_LENGTH;
    gyro[0] = gyro[1] = gyro[2] = 0;
    accel[0] = accel[1] = accel[2] = 0;

    for (ii = 0; ii < packet_count; ii++) {
        short accel_cur[3], gyro_cur[3];
        if (i2c_read(st.hw->addr, st.reg->fifo_r_w, MAX_PACKET_LENGTH, data))
            return -1;
        accel_cur[0] = ((short)data[0] << 8) | data[1];
        accel_cur[1] = ((short)data[2] << 8) | data[3];
        accel_cur[2] = ((short)data[4] << 8) | data[5];
        accel[0] += (int64_t)accel_cur[0];
        accel[1] += (int64_t)accel_cur[1];
        accel[2] += (int64_t)accel_cur[2];
        gyro_cur[0] = (((short)data[6] << 8) | data[7]);
        gyro_cur[1] = (((short)data[8] << 8) | data[9]);
        gyro_cur[2] = (((short)data[10] << 8) | data[11]);
        gyro[0] += (int64_t)gyro_cur[0];
        gyro[1] += (int64_t)gyro_cur[1];
        gyro[2] += (int64_t)gyro_cur[2];
    }
#ifdef EMPL_NO_64BIT
    gyro[0] = (int64_t)(((float)gyro[0]*65536.f) / test.gyro_sens / packet_count);
    gyro[1] = (int64_t)(((float)gyro[1]*65536.f) / test.gyro_sens / packet_count);
    gyro[2] = (int64_t)(((float)gyro[2]*65536.f) / test.gyro_sens / packet_count);
    if (has_accel) {
        accel[0] = (int64_t)(((float)accel[0]*65536.f) / test.accel_sens /
            packet_count);
        accel[1] = (int64_t)(((float)accel[1]*65536.f) / test.accel_sens /
            packet_count);
        accel[2] = (int64_t)(((float)accel[2]*65536.f) / test.accel_sens /
            packet_count);
        /* Don't remove gravity! */
        accel[2] -= 65536L;
    }
#else
    gyro[0] = (int64_t)(((int64_t)gyro[0]<<16) / test.gyro_sens / packet_count);
    gyro[1] = (int64_t)(((int64_t)gyro[1]<<16) / test.gyro_sens / packet_count);
    gyro[2] = (int64_t)(((int64_t)gyro[2]<<16) / test.gyro_sens / packet_count);
    accel[0] = (int64_t)(((int64_t)accel[0]<<16) / test.accel_sens /
        packet_count);
    accel[1] = (int64_t)(((int64_t)accel[1]<<16) / test.accel_sens /
        packet_count);
    accel[2] = (int64_t)(((int64_t)accel[2]<<16) / test.accel_sens /
        packet_count);
    /* Don't remove gravity! */
    if (accel[2] > 0L)
        accel[2] -= 65536L;
    else
        accel[2] += 65536L;
#endif

    return 0;
}

/**
 *  @brief      Trigger gyro/accel/compass self-test.
 *  On success/error, the self-test returns a mask representing the sensor(s)
 *  that failed. For each bit, a one (1) represents a "pass" case; conversely,
 *  a zero (0) indicates a failure.
 *
 *  \n The mask is defined as follows:
 *  \n Bit 0:   Gyro.
 *  \n Bit 1:   Accel.
 *  \n Bit 2:   Compass.
 *
 *  \n Currently, the hardware self-test is unsupported for MPU6500. However,
 *  this function can still be used to obtain the accel and gyro biases.
 *
 *  \n This function must be called with the device either face-up or face-down
 *  (z-axis is parallel to gravity).
 *  @param[out] gyro        Gyro biases in q16 format.
 *  @param[out] accel       Accel biases (if applicable) in q16 format.
 *  @return     Result mask (see above).
 */
int32_t mpu_run_self_test(int64_t *gyro, int64_t *accel)
{
#ifdef MPU6050
    const uint8_t tries = 2;
    int64_t gyro_st[3], accel_st[3];
    uint8_t accel_result, gyro_result;
#ifdef AK89xx_SECONDARY
    uint8_t compass_result;
#endif
    int32_t ii;
#endif
    int32_t result;
    uint8_t accel_fsr, fifo_sensors, sensors_on;
    uint16_t gyro_fsr, sample_rate, lpf;
    uint8_t dmp_was_on;

    if (st.chip_cfg.dmp_on) {
        mpu_set_dmp_state(0);
        dmp_was_on = 1;
    } else
        dmp_was_on = 0;

    /* Get initial settings. */
    mpu_get_gyro_fsr(&gyro_fsr);
    mpu_get_accel_fsr(&accel_fsr);
    mpu_get_lpf(&lpf);
    mpu_get_sample_rate(&sample_rate);
    sensors_on = st.chip_cfg.sensors;
    mpu_get_fifo_config(&fifo_sensors);

    /* For older chips, the self-test will be different. */
#if defined MPU6050
    for (ii = 0; ii < tries; ii++)
        if (!get_st_biases(gyro, accel, 0))
            break;
    if (ii == tries) {
        /* If we reach this point, we most likely encountered an I2C error.
         * We'll just report an error for all three sensors.
         */
        result = 0;
        goto restore;
    }
    for (ii = 0; ii < tries; ii++)
        if (!get_st_biases(gyro_st, accel_st, 1))
            break;
    if (ii == tries) {
        /* Again, probably an I2C error. */
        result = 0;
        goto restore;
    }
    accel_result = accel_self_test(accel, accel_st);
    gyro_result = gyro_self_test(gyro, gyro_st);

    result = 0;
    if (!gyro_result)
        result |= 0x01;
    if (!accel_result)
        result |= 0x02;

#ifdef AK89xx_SECONDARY
    compass_result = compass_self_test();
    if (!compass_result)
        result |= 0x04;
#endif
restore:
#elif defined MPU6500
    /* For now, this function will return a "pass" result for all three sensors
     * for compatibility with current test applications.
     */
    get_st_biases(gyro, accel, 0);
    result = 0x7;
#endif
    /* Set to invalid values to ensure no I2C writes are skipped. */
    st.chip_cfg.gyro_fsr = 0xFF;
    st.chip_cfg.accel_fsr = 0xFF;
    st.chip_cfg.lpf = 0xFF;
    st.chip_cfg.sample_rate = 0xFFFF;
    st.chip_cfg.sensors = 0xFF;
    st.chip_cfg.fifo_enable = 0xFF;
    st.chip_cfg.clk_src = INV_CLK_PLL;
    mpu_set_gyro_fsr(gyro_fsr);
    mpu_set_accel_fsr(accel_fsr);
    mpu_set_lpf(lpf);
    mpu_set_sample_rate(sample_rate);
    mpu_set_sensors(sensors_on);
    mpu_configure_fifo(fifo_sensors);

    if (dmp_was_on)
        mpu_set_dmp_state(1);

    return result;
}

/**
 *  @brief      Write to the DMP memory.
 *  This function prevents I2C writes past the bank boundaries. The DMP memory
 *  is only accessible when the chip is awake.
 *  @param[in]  mem_addr    Memory location (bank << 8 | start address)
 *  @param[in]  length      Number of bytes to write.
 *  @param[in]  data        Bytes to write to memory.
 *  @return     0 if successful.
 */
int32_t mpu_write_mem(uint16_t mem_addr, uint16_t length,
        uint8_t *data)
{
    uint8_t tmp[2];

    if (!data)
        return -1;
    if (!st.chip_cfg.sensors)
        return -1;

    tmp[0] = (uint8_t)(mem_addr >> 8);
    tmp[1] = (uint8_t)(mem_addr & 0xFF);

    /* Check bank boundaries. */
    if (tmp[1] + length > st.hw->bank_size)
        return -1;

    if (i2c_write(st.hw->addr, st.reg->bank_sel, 2, tmp))
        return -1;
    if (i2c_write(st.hw->addr, st.reg->mem_r_w, length, data))
        return -1;
    return 0;
}

/**
 *  @brief      Read from the DMP memory.
 *  This function prevents I2C reads past the bank boundaries. The DMP memory
 *  is only accessible when the chip is awake.
 *  @param[in]  mem_addr    Memory location (bank << 8 | start address)
 *  @param[in]  length      Number of bytes to read.
 *  @param[out] data        Bytes read from memory.
 *  @return     0 if successful.
 */
int32_t mpu_read_mem(uint16_t mem_addr, uint16_t length,
        uint8_t *data)
{
    uint8_t tmp[2];

    if (!data)
        return -1;
    if (!st.chip_cfg.sensors)
        return -1;

    tmp[0] = (uint8_t)(mem_addr >> 8);
    tmp[1] = (uint8_t)(mem_addr & 0xFF);

    /* Check bank boundaries. */
    if (tmp[1] + length > st.hw->bank_size)
        return -1;

    if (i2c_write(st.hw->addr, st.reg->bank_sel, 2, tmp))
        return -1;
    if (i2c_read(st.hw->addr, st.reg->mem_r_w, length, data))
        return -1;
    return 0;
}

/**
 *  @brief      Load and verify DMP image.
 *  @param[in]  length      Length of DMP image.
 *  @param[in]  firmware    DMP code.
 *  @param[in]  start_addr  Starting address of DMP code memory.
 *  @param[in]  sample_rate Fixed sampling rate used when DMP is enabled.
 *  @return     0 if successful.
 */
int32_t mpu_load_firmware(uint16_t length, const uint8_t *firmware,
    uint16_t start_addr, uint16_t sample_rate)
{
    uint16_t ii;
    uint16_t this_write;
    /* Must divide evenly into st.hw->bank_size to avoid bank crossings. */
#define LOAD_CHUNK  (16)
    uint8_t cur[LOAD_CHUNK], tmp[2];

    if (st.chip_cfg.dmp_loaded)
        /* DMP should only be loaded once. */
        return -1;

    if (!firmware)
        return -1;
    for (ii = 0; ii < length; ii += this_write) {
        this_write = min(LOAD_CHUNK, length - ii);
        if (mpu_write_mem(ii, this_write, (uint8_t*)&firmware[ii]))
            return -1;
        if (mpu_read_mem(ii, this_write, cur))
            return -1;
        if (memcmp(firmware+ii, cur, this_write))
            return -2;
    }

    /* Set program start address. */
    tmp[0] = start_addr >> 8;
    tmp[1] = start_addr & 0xFF;
    if (i2c_write(st.hw->addr, st.reg->prgm_start_h, 2, tmp))
        return -1;

    st.chip_cfg.dmp_loaded = 1;
    st.chip_cfg.dmp_sample_rate = sample_rate;
    return 0;
}

/**
 *  @brief      Enable/disable DMP support.
 *  @param[in]  enable  1 to turn on the DMP.
 *  @return     0 if successful.
 */
int32_t mpu_set_dmp_state(uint8_t enable)
{
    uint8_t tmp;
    LOGI(TAG,"setting dmp state");
    if (st.chip_cfg.dmp_on == enable){
        LOGI(TAG,"dmp is already enabled");
        return 0;
    }
    
    if (enable) {
        if (!st.chip_cfg.dmp_loaded){
            LOGI(TAG,"dmp is loaded");
            return -1;
        }
        /* Disable data ready interrupt. */
        set_int_enable(0);
        /* Disable bypass mode. */
        mpu_set_bypass(0);
        /* Keep constant sample rate, FIFO rate controlled by DMP. */
        mpu_set_sample_rate(st.chip_cfg.dmp_sample_rate);
        /* Remove FIFO elements. */
        tmp = 0;
        i2c_write(st.hw->addr, 0x23, 1, &tmp);
        st.chip_cfg.dmp_on = 1;
        LOGI(TAG,"set dmp_on to 1");
        /* Enable DMP interrupt. */
        set_int_enable(1);
        mpu_reset_fifo();
    } else {
        /* Disable DMP interrupt. */
        set_int_enable(0);
        /* Restore FIFO settings. */
        tmp = st.chip_cfg.fifo_enable;
        i2c_write(st.hw->addr, 0x23, 1, &tmp);
        st.chip_cfg.dmp_on = 0;
        LOGI(TAG,"set dmp_on to 0");
        mpu_reset_fifo();
    }
    return 0;
}

/**
 *  @brief      Get DMP state.
 *  @param[out] enabled 1 if enabled.
 *  @return     0 if successful.
 */
int32_t mpu_get_dmp_state(uint8_t *enabled)
{
    enabled[0] = st.chip_cfg.dmp_on;
    return 0;
}


/* This initialization is similar to the one in ak8975.c. */
int32_t setup_compass(void)
{
#ifdef AK89xx_SECONDARY
    uint8_t data[4], akm_addr;

    mpu_set_bypass(1);

    /* Find compass. Possible addresses range from 0x0C to 0x0F. */
    for (akm_addr = 0x0C; akm_addr <= 0x0F; akm_addr++) {
        int32_t result;
        result = i2c_read(akm_addr, AKM_REG_WHOAMI, 1, data);
        if (!result && (data[0] == AKM_WHOAMI))
            break;
    }

    if (akm_addr > 0x0F) {
        /* TODO: Handle this case in all compass-related functions. */
        LOGE(TAG,"Compass not found.\n");
        return -1;
    }

    st.chip_cfg.compass_addr = akm_addr;

    data[0] = AKM_POWER_DOWN;
    if (i2c_write(st.chip_cfg.compass_addr, AKM_REG_CNTL, 1, data))
        return -1;
    delay_ms(1);

    data[0] = AKM_FUSE_ROM_ACCESS;
    if (i2c_write(st.chip_cfg.compass_addr, AKM_REG_CNTL, 1, data))
        return -1;
    delay_ms(1);

    /* Get sensitivity adjustment data from fuse ROM. */
    if (i2c_read(st.chip_cfg.compass_addr, AKM_REG_ASAX, 3, data))
        return -1;
    st.chip_cfg.mag_sens_adj[0] = (int64_t)data[0] + 128;
    st.chip_cfg.mag_sens_adj[1] = (int64_t)data[1] + 128;
    st.chip_cfg.mag_sens_adj[2] = (int64_t)data[2] + 128;

    data[0] = AKM_POWER_DOWN;
    if (i2c_write(st.chip_cfg.compass_addr, AKM_REG_CNTL, 1, data))
        return -1;
    delay_ms(1);

    mpu_set_bypass(0);

    /* Set up master mode, master clock, and ES bit. */
    data[0] = 0x40;
    if (i2c_write(st.hw->addr, st.reg->i2c_mst, 1, data))
        return -1;

    /* Slave 0 reads from AKM data registers. */
    data[0] = BIT_I2C_READ | st.chip_cfg.compass_addr;
    if (i2c_write(st.hw->addr, st.reg->s0_addr, 1, data))
        return -1;

    /* Compass reads start at this register. */
    data[0] = AKM_REG_ST1;
    if (i2c_write(st.hw->addr, st.reg->s0_reg, 1, data))
        return -1;

    /* Enable slave 0, 8-byte reads. */
    data[0] = BIT_SLAVE_EN | 8;
    if (i2c_write(st.hw->addr, st.reg->s0_ctrl, 1, data))
        return -1;

    /* Slave 1 changes AKM measurement mode. */
    data[0] = st.chip_cfg.compass_addr;
    if (i2c_write(st.hw->addr, st.reg->s1_addr, 1, data))
        return -1;

    /* AKM measurement mode register. */
    data[0] = AKM_REG_CNTL;
    if (i2c_write(st.hw->addr, st.reg->s1_reg, 1, data))
        return -1;

    /* Enable slave 1, 1-byte writes. */
    data[0] = BIT_SLAVE_EN | 1;
    if (i2c_write(st.hw->addr, st.reg->s1_ctrl, 1, data))
        return -1;

    /* Set slave 1 data. */
    data[0] = AKM_SINGLE_MEASUREMENT;
    if (i2c_write(st.hw->addr, st.reg->s1_do, 1, data))
        return -1;

    /* Trigger slave 0 and slave 1 actions at each sample. */
    data[0] = 0x03;
    if (i2c_write(st.hw->addr, st.reg->i2c_delay_ctrl, 1, data))
        return -1;

#ifdef MPU9150
    /* For the MPU9150, the auxiliary I2C bus needs to be set to VDD. */
    data[0] = BIT_I2C_MST_VDDIO;
    if (i2c_write(st.hw->addr, st.reg->yg_offs_tc, 1, data))
        return -1;
#endif

    return 0;
#else
    return -1;
#endif
}

/**
 *  @brief      Read raw compass data.
 *  @param[out] data        Raw data in hardware units.
 *  @param[out] timestamp   Timestamp in milliseconds. 0 if not needed.
 *  @return     0 if successful.
 */
int32_t mpu_get_compass_reg(short *data, uint64_t *timestamp)
{
#ifdef AK89xx_SECONDARY
    uint8_t tmp[9];

    if (!(st.chip_cfg.sensors & INV_XYZ_COMPASS))
        return -1;

#ifdef AK89xx_BYPASS
    if (i2c_read(st.chip_cfg.compass_addr, AKM_REG_ST1, 8, tmp))
        return -1;
    tmp[8] = AKM_SINGLE_MEASUREMENT;
    if (i2c_write(st.chip_cfg.compass_addr, AKM_REG_CNTL, 1, tmp+8))
        return -1;
#else
    if (i2c_read(st.hw->addr, st.reg->raw_compass, 8, tmp))
        return -1;
#endif

#if defined AK8975_SECONDARY
    /* AK8975 doesn't have the overrun error bit. */
    if (!(tmp[0] & AKM_DATA_READY))
        return -2;
    if ((tmp[7] & AKM_OVERFLOW) || (tmp[7] & AKM_DATA_ERROR))
        return -3;
#elif defined AK8963_SECONDARY
    /* AK8963 doesn't have the data read error bit. */
    if (!(tmp[0] & AKM_DATA_READY) || (tmp[0] & AKM_DATA_OVERRUN))
        return -2;
    if (tmp[7] & AKM_OVERFLOW)
        return -3;
#endif
    data[0] = (tmp[2] << 8) | tmp[1];
    data[1] = (tmp[4] << 8) | tmp[3];
    data[2] = (tmp[6] << 8) | tmp[5];

    data[0] = ((int64_t)data[0] * st.chip_cfg.mag_sens_adj[0]) >> 8;
    data[1] = ((int64_t)data[1] * st.chip_cfg.mag_sens_adj[1]) >> 8;
    data[2] = ((int64_t)data[2] * st.chip_cfg.mag_sens_adj[2]) >> 8;

    if (timestamp)
        get_ms(timestamp);
    return 0;
#else
    return -1;
#endif
}

/**
 *  @brief      Get the compass full-scale range.
 *  @param[out] fsr Current full-scale range.
 *  @return     0 if successful.
 */
int32_t mpu_get_compass_fsr(uint16_t *fsr)
{
#ifdef AK89xx_SECONDARY
    fsr[0] = st.hw->compass_fsr;
    return 0;
#else
    return -1;
#endif
}

/**
 *  @brief      Enters LP accel motion interrupt mode.
 *  The behavior of this feature is very different between the MPU6050 and the
 *  MPU6500. Each chip's version of this feature is explained below.
 *
 *  \n MPU6050:
 *  \n When this mode is first enabled, the hardware captures a single accel
 *  sample, and subsequent samples are compared with this one to determine if
 *  the device is in motion. Therefore, whenever this "locked" sample needs to
 *  be changed, this function must be called again.
 *
 *  \n The hardware motion threshold can be between 32mg and 8160mg in 32mg
 *  increments.
 *
 *  \n Low-power accel mode supports the following frequencies:
 *  \n 1.25Hz, 5Hz, 20Hz, 40Hz
 *
 *  \n MPU6500:
 *  \n Unlike the MPU6050 version, the hardware does not "lock in" a reference
 *  sample. The hardware monitors the accel data and detects any large change
 *  over a short period of time.
 *
 *  \n The hardware motion threshold can be between 4mg and 1020mg in 4mg
 *  increments.
 *
 *  \n MPU6500 Low-power accel mode supports the following frequencies:
 *  \n 1.25Hz, 2.5Hz, 5Hz, 10Hz, 20Hz, 40Hz, 80Hz, 160Hz, 320Hz, 640Hz
 *
 *  \n\n NOTES:
 *  \n The driver will round down @e thresh to the nearest supported value if
 *  an unsupported threshold is selected.
 *  \n To select a fractional wake-up frequency, round down the value passed to
 *  @e lpa_freq.
 *  \n The MPU6500 does not support a delay parameter. If this function is used
 *  for the MPU6500, the value passed to @e time will be ignored.
 *  \n To disable this mode, set @e lpa_freq to zero. The driver will restore
 *  the previous configuration.
 *
 *  @param[in]  thresh      Motion threshold in mg.
 *  @param[in]  time        Duration in milliseconds that the accel data must
 *                          exceed @e thresh before motion is reported.
 *  @param[in]  lpa_freq    Minimum sampling rate, or zero to disable.
 *  @return     0 if successful.
 */
int32_t mpu_lp_motion_interrupt(uint16_t thresh, uint8_t time,
    uint8_t lpa_freq)
{
    uint8_t data[3];

    if (lpa_freq) {
        uint8_t thresh_hw;

#if defined MPU6050
        /* TODO: Make these const/#defines. */
        /* 1LSb = 32mg. */
        if (thresh > 8160)
            thresh_hw = 255;
        else if (thresh < 32)
            thresh_hw = 1;
        else
            thresh_hw = thresh >> 5;
#elif defined MPU6500
        /* 1LSb = 4mg. */
        if (thresh > 1020)
            thresh_hw = 255;
        else if (thresh < 4)
            thresh_hw = 1;
        else
            thresh_hw = thresh >> 2;
#endif

        if (!time)
            /* Minimum duration must be 1ms. */
            time = 1;

#if defined MPU6050
        if (lpa_freq > 40)
#elif defined MPU6500
        if (lpa_freq > 640)
#endif
            /* At this point, the chip has not been re-configured, so the
             * function can safely exit.
             */
            return -1;

        if (!st.chip_cfg.int_motion_only) {
            /* Store current settings for later. */
            if (st.chip_cfg.dmp_on) {
                mpu_set_dmp_state(0);
                st.chip_cfg.cache.dmp_on = 1;
            } else
                st.chip_cfg.cache.dmp_on = 0;
            mpu_get_gyro_fsr(&st.chip_cfg.cache.gyro_fsr);
            mpu_get_accel_fsr(&st.chip_cfg.cache.accel_fsr);
            mpu_get_lpf(&st.chip_cfg.cache.lpf);
            mpu_get_sample_rate(&st.chip_cfg.cache.sample_rate);
            st.chip_cfg.cache.sensors_on = st.chip_cfg.sensors;
            mpu_get_fifo_config(&st.chip_cfg.cache.fifo_sensors);
        }

#ifdef MPU6050
        /* Disable hardware interrupts for now. */
        set_int_enable(0);

        /* Enter full-power accel-only mode. */
        mpu_lp_accel_mode(0);

        /* Override current LPF (and HPF) settings to obtain a valid accel
         * reading.
         */
        data[0] = INV_FILTER_256HZ_NOLPF2;
        if (i2c_write(st.hw->addr, st.reg->lpf, 1, data))
            return -1;

        /* NOTE: Digital high pass filter should be configured here. Since this
         * driver doesn't modify those bits anywhere, they should already be
         * cleared by default.
         */

        /* Configure the device to send motion interrupts. */
        /* Enable motion interrupt. */
        data[0] = BIT_MOT_INT_EN;
        if (i2c_write(st.hw->addr, st.reg->int_enable, 1, data))
            goto lp_int_restore;

        /* Set motion interrupt parameters. */
        data[0] = thresh_hw;
        data[1] = time;
        if (i2c_write(st.hw->addr, st.reg->motion_thr, 2, data))
            goto lp_int_restore;

        /* Force hardware to "lock" current accel sample. */
        delay_ms(5);
        data[0] = (st.chip_cfg.accel_fsr << 3) | BITS_HPF;
        if (i2c_write(st.hw->addr, st.reg->accel_cfg, 1, data))
            goto lp_int_restore;

        /* Set up LP accel mode. */
        data[0] = BIT_LPA_CYCLE;
        if (lpa_freq == 1)
            data[1] = INV_LPA_1_25HZ;
        else if (lpa_freq <= 5)
            data[1] = INV_LPA_5HZ;
        else if (lpa_freq <= 20)
            data[1] = INV_LPA_20HZ;
        else
            data[1] = INV_LPA_40HZ;
        data[1] = (data[1] << 6) | BIT_STBY_XYZG;
        if (i2c_write(st.hw->addr, st.reg->pwr_mgmt_1, 2, data))
            goto lp_int_restore;

        st.chip_cfg.int_motion_only = 1;
        return 0;
#elif defined MPU6500
        /* Disable hardware interrupts. */
        set_int_enable(0);

        /* Enter full-power accel-only mode, no FIFO/DMP. */
        data[0] = 0;
        data[1] = 0;
        data[2] = BIT_STBY_XYZG;
        if (i2c_write(st.hw->addr, st.reg->user_ctrl, 3, data))
            goto lp_int_restore;

        /* Set motion threshold. */
        data[0] = thresh_hw;
        if (i2c_write(st.hw->addr, st.reg->motion_thr, 1, data))
            goto lp_int_restore;

        /* Set wake frequency. */
        if (lpa_freq == 1)
            data[0] = INV_LPA_1_25HZ;
        else if (lpa_freq == 2)
            data[0] = INV_LPA_2_5HZ;
        else if (lpa_freq <= 5)
            data[0] = INV_LPA_5HZ;
        else if (lpa_freq <= 10)
            data[0] = INV_LPA_10HZ;
        else if (lpa_freq <= 20)
            data[0] = INV_LPA_20HZ;
        else if (lpa_freq <= 40)
            data[0] = INV_LPA_40HZ;
        else if (lpa_freq <= 80)
            data[0] = INV_LPA_80HZ;
        else if (lpa_freq <= 160)
            data[0] = INV_LPA_160HZ;
        else if (lpa_freq <= 320)
            data[0] = INV_LPA_320HZ;
        else
            data[0] = INV_LPA_640HZ;
        if (i2c_write(st.hw->addr, st.reg->lp_accel_odr, 1, data))
            goto lp_int_restore;

        /* Enable motion interrupt (MPU6500 version). */
        data[0] = BITS_WOM_EN;
        if (i2c_write(st.hw->addr, st.reg->accel_intel, 1, data))
            goto lp_int_restore;

        /* Enable cycle mode. */
        data[0] = BIT_LPA_CYCLE;
        if (i2c_write(st.hw->addr, st.reg->pwr_mgmt_1, 1, data))
            goto lp_int_restore;

        /* Enable interrupt. */
        data[0] = BIT_MOT_INT_EN;
        if (i2c_write(st.hw->addr, st.reg->int_enable, 1, data))
            goto lp_int_restore;

        st.chip_cfg.int_motion_only = 1;
        return 0;
#endif
    } else {
        /* Don't "restore" the previous state if no state has been saved. */
        int32_t ii;
        char *cache_ptr = (char*)&st.chip_cfg.cache;
        for (ii = 0; ii < sizeof(st.chip_cfg.cache); ii++) {
            if (cache_ptr[ii] != 0)
                goto lp_int_restore;
        }
        /* If we reach this point, motion interrupt mode hasn't been used yet. */
        return -1;
    }
lp_int_restore:
    /* Set to invalid values to ensure no I2C writes are skipped. */
    st.chip_cfg.gyro_fsr = 0xFF;
    st.chip_cfg.accel_fsr = 0xFF;
    st.chip_cfg.lpf = 0xFF;
    st.chip_cfg.sample_rate = 0xFFFF;
    st.chip_cfg.sensors = 0xFF;
    st.chip_cfg.fifo_enable = 0xFF;
    st.chip_cfg.clk_src = INV_CLK_PLL;
    mpu_set_sensors(st.chip_cfg.cache.sensors_on);
    mpu_set_gyro_fsr(st.chip_cfg.cache.gyro_fsr);
    mpu_set_accel_fsr(st.chip_cfg.cache.accel_fsr);
    mpu_set_lpf(st.chip_cfg.cache.lpf);
    mpu_set_sample_rate(st.chip_cfg.cache.sample_rate);
    mpu_configure_fifo(st.chip_cfg.cache.fifo_sensors);

    if (st.chip_cfg.cache.dmp_on)
        mpu_set_dmp_state(1);

#ifdef MPU6500
    /* Disable motion interrupt (MPU6500 version). */
    data[0] = 0;
    if (i2c_write(st.hw->addr, st.reg->accel_intel, 1, data))
        goto lp_int_restore;
#endif

    st.chip_cfg.int_motion_only = 0;
    return 0;
}

#define q30  1073741824.0f

static signed char gyro_orientation[9] = { 1, 0, 0,
                                           0,-1, 0,
                                           0, 0, -1};

static int32_t run_self_test(void)
{
	int32_t result;
	//char test_packet[4] = {0};
	int64_t gyro[3], accel[3]; 
	result = mpu_run_self_test(gyro, accel);
    // result = 3;
	if (result == 0x3) 
	{
		/* Test passed. We can trust the gyro data here, so let's push it down
		* to the DMP.
		*/
		float sens;
		uint16_t accel_sens;
		mpu_get_gyro_sens(&sens);
		gyro[0] = (int64_t)(gyro[0] * sens);
		gyro[1] = (int64_t)(gyro[1] * sens);
		gyro[2] = (int64_t)(gyro[2] * sens);
		dmp_set_gyro_bias(gyro);
		mpu_get_accel_sens(&accel_sens);
		accel[0] *= accel_sens;
		accel[1] *= accel_sens;
		accel[2] *= accel_sens;
		dmp_set_accel_bias(accel);
		return 0;
	} else 
        return 1;
    
}

uint16_t inv_orientation_matrix_to_scalar(
    const signed char *mtx){
    uint16_t scalar; 
    /*
       XYZ  010_001_000 Identity Matrix
       XZY  001_010_000
       YXZ  010_000_001
       YZX  000_010_001
       ZXY  001_000_010
       ZYX  000_001_010
     */

    scalar = inv_row_2_scale(mtx);
    scalar |= inv_row_2_scale(mtx + 3) << 3;
    scalar |= inv_row_2_scale(mtx + 6) << 6;


    return scalar;
}

uint16_t inv_row_2_scale(const signed char *row)
{
    uint16_t b;

    if (row[0] > 0)
        b = 0;
    else if (row[0] < 0)
        b = 4;
    else if (row[1] > 0)
        b = 1;
    else if (row[1] < 0)
        b = 5;
    else if (row[2] > 0)
        b = 2;
    else if (row[2] < 0)
        b = 6;
    else
        b = 7;      // error
    return b;
}


int32_t mpu_dmp_init(dev::gpio sda, dev::gpio scl) {		
    iic = iicx(sda, scl);
	if(mpu_init() == 0){	 
	    LOGI(TAG,"initing mpu6050");
		if(mpu_set_sensors(INV_XYZ_GYRO|INV_XYZ_ACCEL)) return -1; 
		if(mpu_configure_fifo(INV_XYZ_GYRO | INV_XYZ_ACCEL)) return -2; 
		if(mpu_set_sample_rate(DEFAULT_MPU_HZ)) return -3; 
		if(dmp_load_motion_driver_firmware()) return -4; 
		if(dmp_set_orientation(inv_orientation_matrix_to_scalar(gyro_orientation))) return -5; 
		if(dmp_enable_feature(DMP_FEATURE_6X_LP_QUAT|DMP_FEATURE_TAP|
		    DMP_FEATURE_ANDROID_ORIENT|DMP_FEATURE_SEND_RAW_ACCEL|DMP_FEATURE_SEND_CAL_GYRO|
		    DMP_FEATURE_GYRO_CAL)) return -6; 
		if(dmp_set_fifo_rate(DEFAULT_MPU_HZ)) return -7;   
		if(run_self_test()) return -8;    
		if(mpu_set_dmp_state(1)) return -9;     
	} else {
	    LOGI(TAG,"failed to preinit mpu6050");
        return -10;
	}
	LOGI(TAG,"init mpu6050 successful");
	return 0;
}

// static const double
// pio2_hi = 1.57079632679489655800e+00, /* 0x3FF921FB, 0x54442D18 */
// pio2_lo = 6.12323399573676603587e-17, /* 0x3C91A626, 0x33145C07 */
// /* coefficients for R(x^2) */
// pS0 =  1.66666666666666657415e-01, /* 0x3FC55555, 0x55555555 */
// pS1 = -3.25565818622400915405e-01, /* 0xBFD4D612, 0x03EB6F7D */
// pS2 =  2.01212532134862925881e-01, /* 0x3FC9C155, 0x0E884455 */
// pS3 = -4.00555345006794114027e-02, /* 0xBFA48228, 0xB5688F3B */
// pS4 =  7.91534994289814532176e-04, /* 0x3F49EFE0, 0x7501B288 */
// pS5 =  3.47933107596021167570e-05, /* 0x3F023DE1, 0x0DFDF709 */
// qS1 = -2.40339491173441421878e+00, /* 0xC0033A27, 0x1C8A2D4B */
// qS2 =  2.02094576023350569471e+00, /* 0x40002AE5, 0x9C598AC8 */
// qS3 = -6.88283971605453293030e-01, /* 0xBFE6066C, 0x1B8D0159 */
// qS4 =  7.70381505559019352791e-02; /* 0x3FB3B8C5, 0xB12E9282 */

// static double R(double z)
// {
// 	double_t p, q;
// 	p = z*(pS0+z*(pS1+z*(pS2+z*(pS3+z*(pS4+z*pS5)))));
// 	q = 1.0+z*(qS1+z*(qS2+z*(qS3+z*qS4)));
// 	return p/q;
// }

// #ifndef GET_HIGH_WORD
// # define GET_HIGH_WORD(i,d)                                        \
// do {                                                                \
//   ieee_double_shape_type gh_u;                                        \
//   gh_u.value = (d);                                                \
//   (i) = gh_u.parts.msw;                                                \
// } while (0)
// #endif

// #ifndef GET_LOW_WORD
// # define GET_LOW_WORD(i,d)                                        \
// do {                                                                \
//   ieee_double_shape_type gl_u;                                        \
//   gl_u.value = (d);                                                \
//   (i) = gl_u.parts.lsw;                                                \
// } while (0)
// #endif

// double asin(double x)
// {
// 	double z,r,s;
// 	uint32_t hx,ix;

// 	GET_HIGH_WORD(hx, x);
// 	ix = hx & 0x7fffffff;
// 	/* |x| >= 1 or nan */
// 	if (ix >= 0x3ff00000) {
// 		uint32_t lx;
// 		GET_LOW_WORD(lx, x);
// 		if ((ix-0x3ff00000 | lx) == 0)
// 			/* asin(1) = +-pi/2 with inexact */
// 			return x*pio2_hi + 0x1p-120f;
// 		return 0/(x-x);
// 	}
// 	/* |x| < 0.5 */
// 	if (ix < 0x3fe00000) {
// 		/* if 0x1p-1022 <= |x| < 0x1p-26, avoid raising underflow */
// 		if (ix < 0x3e500000 && ix >= 0x00100000)
// 			return x;
// 		return x + x*R(x*x);
// 	}
// 	/* 1 > |x| >= 0.5 */
// 	z = (1 - fabs(x))*0.5;
// 	s = sqrt(z);
// 	r = R(z);
// 	if (ix >= 0x3fef3333) {  /* if |x| > 0.975 */
// 		x = pio2_hi-(2*(s+s*r)-pio2_lo);
// 	} else {
// 		double f,c;
// 		/* f+c = sqrt(z) */
// 		f = s;
// 		SET_LOW_WORD(f,0);
// 		c = (z-f*f)/(s+f);
// 		x = 0.5*pio2_hi - (2*s*r - (pio2_lo-2*c) - (0.5*pio2_hi-2*f));
// 	}
// 	if (hx >> 31)
// 		return -x;
// 	return x;
// }


int32_t mpu_dmp_get_data(float *gx,float *gy,float *gz,int16_t* ax, int16_t* ay,int16_t* az){
	float q0=1.0f,q1=0.0f,q2=0.0f,q3=0.0f;
	uint64_t sensor_timestamp;
	short gyro[3], accel[3], sensors;
	uint8_t more;
	int64_t quat[4]; 
	if(dmp_read_fifo(gyro, accel, quat, &sensor_timestamp, &sensors,&more))return -1;	 
	/* Gyro and accel data are written to the FIFO by the DMP in chip frame and hardware units.
	 * This behavior is convenient because it keeps the gyro and accel outputs of dmp_read_fifo and mpu_read_fifo consistent.
	**/
	/*if (sensors & INV_XYZ_GYRO )
	send_packet(PACKET_TYPE_GYRO, gyro);
	if (sensors & INV_XYZ_ACCEL)
	send_packet(PACKET_TYPE_ACCEL, accel); */
	/* Unlike gyro and accel, quaternions are written to the FIFO in the body frame, q30.
	 * The orientation is set by the scalar passed to dmp_set_orientation during initialization. 
	**/
	*ax=accel[0];
	*ay=accel[1];
	*az=accel[2];
	if(sensors & INV_WXYZ_QUAT) {
		q0 = quat[0] / q30;	
		q1 = quat[1] / q30;
		q2 = quat[2] / q30;
		q3 = quat[3] / q30; 
		*gy = asin(-2 * q1 * q3 + 2 * q0* q2)* 57.3;	// pitch
		*gx  = atan2(2 * q2 * q3 + 2 * q0 * q1, -2 * q1 * q1 - 2 * q2* q2 + 1)* 57.3;	// roll
		*gz   = atan2(2*(q1*q2 + q0*q3),q0*q0+q1*q1-q2*q2-q3*q3) * 57.3;	//yaw
	}
    else return -2;
	return 0;
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

  } // inner
  

}