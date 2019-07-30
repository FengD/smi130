/**
  * Copyright (C) 2019 Hirain Technologies
  * License: Modified BSD Software License Agreement
  * Author: Feng DING
  * Description: This file used to define the i2c bus actions
  */

#include "i2c_bus_action.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define I2C_NODE	"/dev/i2c-"

namespace hirain {
  int openBus(int bus) {
    int fd;
    char fdName[64];
    snprintf(fdName, 64, "%s%d", I2C_NODE, bus);
    if ((fd = open(fdName, O_RDWR)) < 0)
    /* ERROR HANDLING: you can check errno to see what went wrong */
    perror("Failed to open the i2c bus");
    return fd;
  }

  int configBusSlaveAddr(int fd, int addr) {
    int ret = ioctl(fd, I2C_SLAVE, addr);
    if (ret < 0)
    printf("Failed to config slave address.\n");
    return ret;
  }

  int configBusTenbit(int fd, int flag) {
    int ret = ioctl(fd, I2C_TENBIT, flag);
    if (ret < 0)
    printf("Failed to config tenbit.\n");
    return ret;
  }

  int readBus(int fd, unsigned char *buf, int bufSize) {
    return read(fd, buf, bufSize);
  }

  int writeBus(int fd, unsigned char *buf, int bufSize) {
    return write(fd, buf, bufSize);
  }

  int readRegister(int fd, int regAddr, unsigned char *buf, int bufSize) {
    unsigned char regBuf[2];
    int ret;
    regBuf[0] = (regAddr >> 0)&0xFF;
    regBuf[1] = (regAddr >> 8)&0xFF;

    ret = writeBus(fd, regBuf, 2);
    if (ret < 0) {
      printf("Failed to write [0x%02x 0x%02x] (reg: %04x).\n", regBuf[0], regBuf[1], regAddr);
      return ret;
    }
    return readBus(fd, buf, bufSize);
  }

  int writeRegister (int fd, int regAddr, int value) {
    unsigned char regBuf[2];
    regBuf[1] = (value >> 0)&0xFF;
    regBuf[0] = (regAddr >> 0)&0xFF;

    return writeBus(fd, regBuf, 2);
  }
} // namespace hirain
