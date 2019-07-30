/**
  * Copyright (C) 2019 Hirain Technologies
  * License: Modified BSD Software License Agreement
  * Author: Feng DING
  * Description: This file used to define the smi130 actions by i2c
  */

#ifndef _SMI130_I2C_ACTION_H_
#define _SMI130_I2C_ACTION_H_
namespace hirain {
  int configI2C();
  int readAcc(unsigned char *buf, int bufSize);
  int readGyro(unsigned char *buf, int bufSize);
  int configAcc(int regAddr, int value);
  int configGyro(int regAddr, int value);
} // namespace hirain

#endif // _SMI130_I2C_ACTION_H_
