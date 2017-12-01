#include <cstdint>
#include <time.h>


struct Timer {
  uint64_t start;
  static uint64_t constexpr nanoseconds = 1000000000;
  static auto constexpr clock = CLOCK_MONOTONIC;

  static uint64_t constexpr to_nanoseconds(timespec const& t) {
    return t.tv_sec * nanoseconds + t.tv_nsec;
  }

  Timer() {
    timespec r;
    clock_gettime(clock, &r);
    start = to_nanoseconds(r);
  }


  ~Timer() {
    timespec r;
    clock_gettime(clock, &r);
    auto duration = to_nanoseconds(r) - start;

    printf("Total time: %u.%09us\n", duration / nanoseconds, duration % nanoseconds);

  }
};
