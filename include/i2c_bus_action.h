/**
  * Copyright (C) 2019 Hirain Technologies
  * License: Modified BSD Software License Agreement
  * Author: Feng DING
  * Description: This file used to define the i2c bus actions
  */

#ifndef _I2C_BUS_ACTION_H_
#define _I2C_BUS_ACTION_H_

namespace hirain {
  int openBus(int bus);
  int configBusSlaveAddr(int fd, int addr);
  int configBusTenbit(int fd, int flag);
  int readBus(int fd, unsigned char *buf, int bufSize);
  int writeBus(int fd, unsigned char *buf, int bufSize);
  int readRegister(int fd, int regAddr, unsigned char *buf, int bufSize);
  int writeRegister (int fd, int regAddr, int value);
} // namespace hirain

#endif // _I2C_BUS_ACTION_H_
