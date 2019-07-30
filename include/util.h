/**
  * Copyright (C) 2019 Hirain Technologies
  * License: Modified BSD Software License Agreement
  * Author: Feng DING
  * Description:
  */

#ifndef _UTIL_H_
#define _UTIL_H_

#include <time.h>
#include <pthread.h>

namespace hirain {
  int create_thread(pthread_t *thread, void *thread_func(void *), void *arg);

  void calc_time_diff(const struct timespec *lo, const struct timespec *hi, struct timespec *diff);
} // namespace hirain

#endif // _UTIL_H_
