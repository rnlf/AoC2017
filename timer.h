#include <type_traits>
#include <cstdlib>
#include <cstdint>
#include <time.h>

static constexpr uint64_t S_TO_NS = 1000000000;

static uint64_t nanoseconds() {
  timespec r;
  clock_gettime(CLOCK_MONOTONIC, &r);
  return r.tv_sec * S_TO_NS + r.tv_nsec;
}


template<typename F, typename... Args>
auto measure_time(unsigned const count, F f, Args... args) {

  typedef typename std::invoke_result_t<F, Args...> res_type;
  
  std::vector<res_type> results(count);

  const auto start = nanoseconds();
  for(unsigned i = 0; i < count; ++i) {
    results[i] = f(args...);
  }

  auto const end = nanoseconds();
  auto const duration = end - start;

  for(int i = 0; i < results.size()-1; ++i) {
    if(results[i] != results[i+1]) {
      printf("Tested function returns inconsistent results!\n");
      abort();
    }
  }

  printf("Total time: %lu.%09lus\n", duration / S_TO_NS, duration % S_TO_NS);
  printf("Per run:    %lu.%09lus\n", (duration/count) / S_TO_NS, (duration/count) % S_TO_NS);
  
  return results;
}
