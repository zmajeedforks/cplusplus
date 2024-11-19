// 20240910_chrono_afraid_to_ask/create_times.cpp

#include <chrono>

#include <fmt/format.h>
#include <fmt/chrono.h>

using namespace std;
using namespace chrono;

using fmt::format;
using fmt::print;
using fmt::println;

void now_timepoint() {
  println("Create timepoints\n");

  auto nowtime = system_clock::now();
  println("Current time \"{}\"", nowtime);

  auto zerotime = time_point<system_clock, nanoseconds>{};
  println("Zero time \"{}\"", zerotime);

  auto atime = sys_time<nanoseconds>{};
  println("A time \"{}\"", atime);

  auto localtm = time_point<local_t, nanoseconds>{};
  auto localnanos = (localtm - floor<seconds>(localtm)).count();
  println("Local time \"{}\"", localnanos);

  auto localutc = zoned_time{"UTC", localtm};
  //println("Local utc \"{}\"", localutc);

  println("");
}

int main() {
  now_timepoint();
}
