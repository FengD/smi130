/**
  * Copyright (C) 2019 Hirain Technologies
  * License: Modified BSD Software License Agreement
  * Author: Feng DING
  * Description: This file used to define the smi130 actions by i2c
  */

#include "smi130_i2c_action.h"
#include "i2c_bus_action.h"

#define I2C_SLAVE_ADDR_ACC 0x18
#define I2C_SLAVE_ADDR_GYRO 0x68
// acu1 0, LMU 1
#define I2C_NB 1

namespace hirain {
  static int fdAcc, fdGyro;
  int configI2C() {
    int ret;
    fdAcc = openBus(I2C_NB);
    if (fdAcc < 0)
    return -1;

    ret = configBusSlaveAddr(fdAcc, I2C_SLAVE_ADDR_ACC);
    if (ret < 0)
    return -1;

    ret = configBusTenbit(fdAcc, 0);
    if (ret < 0)
    return -1;

    fdGyro = openBus(I2C_NB);
    if (fdGyro < 0)
    return -1;

    ret = configBusSlaveAddr(fdGyro, I2C_SLAVE_ADDR_GYRO);
    if (ret < 0)
    return -1;

    ret = configBusTenbit(fdGyro, 0);
    if (ret < 0)
    return -1;
    return 0;
  }

  int readAcc(unsigned char *buf, int bufSize) {
    return readRegister(fdAcc, 0x00, buf, bufSize);
  }

  int configAcc(int regAddr, int value) {
    return writeRegister(fdAcc, regAddr, value);
  }

  int readGyro(unsigned char *buf, int bufSize) {
    return readRegister(fdGyro, 0x00, buf, bufSize);
  }

  int configGyro(int regAddr, int value) {
    return writeRegister(fdGyro, regAddr, value);
  }
} // namespace hirain
