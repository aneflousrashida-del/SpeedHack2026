#include <sys/time.h>
#include <stddef.h>
#include <stdint.h>
#include <math.h>
#include <stdio.h>
#include <time.h>

extern "C" int new_clock_gettime(clockid_t clk_id, struct timespec *tp) {
    struct timespec currenttp;
    int r = clock_gettime(clk_id, &currenttp);
    if (r == 0 && (clk_id == CLOCK_MONOTONIC || clk_id == CLOCK_BOOTTIME || clk_id == CLOCK_REALTIME)) {
        double speed = 1.5;
        uint64_t fake_ns = (uint64_t)(((double)currenttp.tv_sec * 1e9 + currenttp.tv_nsec) * speed);
        if (tp) {
            tp->tv_sec = fake_ns / 1000000000ULL;
            tp->tv_nsec = fake_ns % 1000000000ULL;
        }
    } else if (tp) {
        *tp = currenttp;
    }
    return r;
}

extern "C" int new_gettimeofday(struct timeval *tv, void *tz) {
    struct timeval currenttv;
    int r = gettimeofday(&currenttv, (struct timezone *)tz);
    if (r == 0 && tv != nullptr) {
        double speed = 1.5;
        uint64_t fake_us = (uint64_t)(((double)currenttv.tv_sec * 1e6 + currenttv.tv_usec) * speed);
        tv->tv_sec = fake_us / 1000000ULL;
        tv->tv_usec = fake_us % 1000000ULL;
    }
    return r;
}
