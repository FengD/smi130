#include <stdio.h>
#include <time.h>

#include "util.h"

#include "smi130_i2c_action.h"
#include "smi130_uncode_reg_buf.h"

#define BUFSIZE 64
char tmp[64];

uint8_t imu_gyr_temp[1] = {0};
uint16_t imu_acc[3] = {0};
uint16_t imu_gyr[3] = {0};

uint8_t bufAcc[BUFSIZE], bufGyro[BUFSIZE];

pthread_t imuThread;

int smi130Config(void) {
  if (hirain::configAcc(0x10, 0x0b) < 0) {
    return -1;
  }

  if (hirain::configGyro(0x0f, 0x04) < 0) {
    return -1;
  }

  if (hirain::configGyro(0x10, 0x07) < 0) {
    return -1;
  }
  return 0;
}

int init(void) {
  if (hirain::configI2C() < 0) {
    return -1;
  }

  if (smi130Config() < 0) {
    return -3;
  }

  return 0;
}

void taskImu() {
  hirain::readAcc(bufAcc, BUFSIZE);
  hirain::readGyro(bufGyro, BUFSIZE);
  hirain::encodeAcc(bufAcc, imu_acc);
  hirain::encodeGyro(bufGyro, imu_gyr);
  hirain::encodeTemp(bufGyro, imu_gyr_temp);
}


static void *imuThreadFn(void *data) {
  (void) data;

  int interval_time_usec = 10000;
  struct timespec unpack_interval;
  unpack_interval.tv_sec = interval_time_usec / 1000000;
  unpack_interval.tv_nsec = (interval_time_usec * 1000) % 1000000000;
  struct timespec start_time, end_time, elapsed_time, sleep_time;

  for (;;) {
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    if (!unpack_interval.tv_sec && !unpack_interval.tv_nsec)
      break;
    // 10ms step
    taskImu();

    clock_gettime(CLOCK_MONOTONIC, &end_time);

    hirain::calc_time_diff(&start_time, &end_time, &elapsed_time);
    hirain::calc_time_diff(&elapsed_time, &unpack_interval, &sleep_time);
    if (sleep_time.tv_sec < 0) {
      printf("Elapsed time ([%6lu.%06ld]) greater than interval. Skipping sleep!\n",
             (unsigned long)elapsed_time.tv_sec,
             elapsed_time.tv_nsec / 1000);
      continue;
    }

    clock_nanosleep(CLOCK_MONOTONIC, 0, &sleep_time, NULL);
  }

  return NULL;
}

int main() {
  if (init() < 0) {
    printf("init error\n");
    return 0;
  }

  pthread_create(&imuThread, NULL, imuThreadFn, NULL);
  pthread_join(imuThread, NULL);

  return 0;
}
