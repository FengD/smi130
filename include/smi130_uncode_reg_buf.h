/**
  * Copyright (C) 2019 Hirain Technologies
  * License: Modified BSD Software License Agreement
  * Author: Feng DING
  * Description: This file used to define the smi130 info unpack actions
  */

#ifndef _SMI130_UNCODE_REG_BUF_H_
#define _SMI130_UNCODE_REG_BUF_H_
#include <stdint.h>

namespace hirain {
  void encodeAcc(unsigned char *buf, uint16_t *acc);

  void encodeGyro(unsigned char *buf, uint16_t *gyro);

  void encodeTemp(unsigned char *buf, uint8_t *temp);
} // namespace hirain

#endif // _SMI130_UNCODE_REG_BUF_H_
