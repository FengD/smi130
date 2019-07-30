/**
  * Copyright (C) 2019 Hirain Technologies
  * License: Modified BSD Software License Agreement
  * Author: Feng DING
  * Description: This file used to define the smi130 info unpack actions
  */

#include "smi130_uncode_reg_buf.h"

namespace hirain {
  void encodeAcc(unsigned char *buf, uint16_t *acc) {
    acc[0] = (buf[0x03]<<8 | buf[0x02]);
    acc[1] = (buf[0x05]<<8 | buf[0x04]);
    acc[2] = (buf[0x07]<<8 | buf[0x06]);
  }

  void encodeGyro(unsigned char *buf, uint16_t *gyro) {
    gyro[0] = (buf[0x03]<<8 | buf[0x02]);
    gyro[1] = (buf[0x05]<<8 | buf[0x04]);
    gyro[2] = (buf[0x07]<<8 | buf[0x06]);
  }

  void encodeTemp(unsigned char *buf, uint8_t *temp) {
    temp[0] = buf[0x08];
  }
} // namespace hirain
