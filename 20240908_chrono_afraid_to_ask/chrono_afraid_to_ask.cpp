// 20240910_chrono_afraid_to_ask/create_times.cpp

#include <cxxabi.h>
#include <dlfcn.h>

#include <string>
#include <sstream>
#include <chrono>
#include <thread>
#include <map>
#include <functional>
#include <iostream>

#if 0
#include <fmt/format.h>
#include <fmt/chrono.h>

using fmt::println;
using fmt::format;
#else
#include <print>
#endif

using namespace std;
using namespace chrono;

using namespace abi;

namespace {

template<class T>
string typeName() {
  int err;
  auto name_cstr = __cxa_demangle(typeid(T).name(), NULL, NULL, &err);
  string name = name_cstr;
  free(name_cstr);
  return name;
}

string typeName(auto& x) {
  int err;
  auto name_cstr = __cxa_demangle(typeid(x).name(), NULL, NULL, &err);
  string name = name_cstr;
  free(name_cstr);
  return name;
}

// fill map of functions named example_0, example_1, ... from exported symbols
using exampleFuncT = void(*)();
map<string, exampleFuncT> funcByName;
auto loadfuncs = []() -> int {
  auto thisprog = dlopen(NULL, RTLD_GLOBAL);
  for(int i = 0; i < 100; ++i) {
    auto funcname = "example_"s + to_string(i);
    void* funcptr = dlsym(thisprog, funcname.c_str());
    if(funcptr == nullptr) {
      break;
    }
    funcByName[funcname] = (exampleFuncT)funcptr;
  }
  return 0;
}();
}

#if 0
namespace {
enum class numbers: int8_t {
  zero,
  one
};
using enum numbers;
using fmt::enums::format_as;
}
#endif

void now_timepoint() {
  println("Create timepoints\n");

  auto nowtime = system_clock::now();
  println("Current time \"{}\"", nowtime);

#if 0
  auto nowutc = utc_clock::now();
  println("Current utc time \"{}\"", nowutc);
#endif

  auto zerotime = time_point<system_clock, nanoseconds>{};
  println("Zero time \"{}\"", zerotime);

  auto atime = sys_time<nanoseconds>{};
  println("A time \"{}\"", atime);

  println("");

  auto localtm = time_point<local_t, nanoseconds>{};
  println("Localtm type {}", typeName(localtm));
  println("Local time \"{}\"", localtm);
  auto localnanos = localtm - floor<seconds>(localtm);
  println("Local nanos {} type {}", localnanos, typeName(localnanos));

#if 0
  auto localutc = zoned_time{"UTC", localtm};
  println("Local utc type {}", typeName(localutc));
  println("Local utc \"{}\"", localutc);

  auto localcentral = zoned_time{"America/Chicago", localtm};
  println("Local central \"{}\"", localcentral);

  auto localcentralutc = zoned_time{"UTC", localcentral};
  println("Local central utc \"{}\"", localcentralutc);
#endif

  println("");

  auto steadynow = steady_clock::now();
  println("Steady now type {}", typeName(steadynow));


  auto isotime = sys_time<nanoseconds>{};
  string tz;
  minutes offset;

  stringstream isostr("2024-09-10_12:34:56.987Z");
  isostr >> chrono::parse("%F_%T%Z", isotime, tz, offset);
  println("isotime {} tz {} offset {}", isotime, tz, offset);

  tz.clear();
  offset = 0min;
  isostr.seekg(0);
  isostr << "2024-12-10_09:17:25.510-05:00";
  isostr >> chrono::parse("%F_%T%Ez", isotime, tz, offset);
  println("isotime {} tz {} offset {}", isotime, tz, offset);

  println("");

  auto durtime = sys_days{2024y/August/13} + 06h + 01min + 32s + 123456789ns;
  println("durtime {}", durtime);

  auto durtime2 = sys_time{years{55} + months{3} + days{17} + 9h + 13min + 17s + 351ms};
  println("durtime2 {} type {}", durtime2, typeName(durtime2));

  auto durtime3 = sys_days{year_month_day{2025y, month{3}, 17d}} + 9h + 13min + 17s + 351ms;
  println("durtime3 {}", durtime3);

  println("");
}

void timers() {

  jthread timer1{[]() {
    println("{}: start timer", system_clock::now());
    this_thread::sleep_for(5s);
    println("{}: end timer", system_clock::now());
  }
  };

}

void durations() {

  auto dur1 = duration<int64_t>{};
  println("Duration of int64_t {} type {}", dur1, typeName(dur1));

  auto dur2 = duration<long, nano>{123};
  println("Duration of long {} type {}", dur2, typeName(dur2));

  auto dur3 = duration<double, nano>{123.456};
  println("Duration of double and nano {} type {}", dur3, typeName(dur3));

  auto dur4 = nanoseconds{123456789};
  println("Nanoseconds duration {} type {}", dur4, typeName(dur4));

  auto dur5 = milliseconds{2min + 10s + 300ms};
  println("Milliseconds duration {} type {}", dur5, typeName(dur5));
  println("Milliseconds formatted {:%T}", dur5);

  auto colondur = milliseconds{};
  stringstream colonstr("01:05:10.123");
  colonstr >> chrono::parse("%T", colondur);
  println("colondur {} {:%T}", colondur, colondur);

  //auto dur6 = hours{2min + 10s + 300ms};
  auto dur6 = duration<long, ratio<3600>>{123};
  println("Hours duration {} type {}", dur6, typeName(dur6));
  println("Hours formatted {:%T}", dur6);

  auto dur7 = duration<long, ratio<3600>>{duration_cast<hours>(2min + 10s + 300ms)};
  println("Hours duration {} type {}", dur7, typeName(dur7));
  println("Hours formatted {:%T}", dur7);

  auto dur8 = duration<long, ratio<1, 1000>>{hours{2} + 2min + 10s + 300ms};
  println("Hours duration {} type {}", dur8, typeName(dur8));
  println("Hours formatted {:%T}", dur8);

}

void timepoint_ops() {
  //auto durtime = sys_days{2024y/August/13} + 06h + 01min + 32s + 123456789ns;
  auto date = 2024y/February/15;
  println("date {} type {}", date, typeName(date));

  auto t = sys_days{year_month_day{2024y, February, 15d}} + 9h + 13min + 17s + 351ms;
  println("t \"{}\"", t);

  t = sys_days{2024y/February/15d} + 9h + 13min + 17s + 351ms;
  println("t \"{}\"", t);

  auto t_plus_1_min = t + 1min;
  println("add 1 minute \"{}\"", t_plus_1_min);

// 1d is not 1 day but 1st of month
  auto t_plus_1_day = t + days{1};
  println("add 1 day \"{}\"", t_plus_1_day);

  date = time_point_cast<days>(t);
  println("date from t by cast {} year {} month {} day {}", date, date.year(), date.month(), date.day());

  date = floor<days>(t);
  println("date from t by floor {} year {} month {} day {}", date, date.year(), date.month(), date.day());

  date = ceil<days>(t);
  println("date from t by ceil {} year {} month {} day {}", date, date.year(), date.month(), date.day());

  date = round<days>(t);
  println("date from t by round {} year {} month {} day {}", date, date.year(), date.month(), date.day());

#if 0
  auto time = hh_mm_ss{t.time_since_epoch()};
  println("time from t since epoch {}", time);

  time = hh_mm_ss{t - floor<days>(t)};
  println("time from t {} hour {} minute {} second {} subsecond {}", time, time.hours(), time.minutes(), time.seconds(), time.subseconds());
#endif

  println("");

}

extern "C" {

void example_0() {
  println("Type of time_point");

// provide clock with its implicit default clock duration
  auto t1 = time_point<system_clock>{};
  println("t1 type {}", typeName(t1));
  println("t1 value \"{}\"", t1);

// fully specify clock and duration
  auto t2 = time_point<system_clock, duration<long, ratio<1, 1000>>>{};
  println("t2 type {}", typeName(t2));

// provide clock and predefined duration
  auto t3 = time_point<system_clock, milliseconds>{};
  println("t3 type {}", typeName(t3));

// initialize with duration value for implicit system clock
  auto t4 = sys_time{0ms};
  println("t4 type {}", typeName(t4));

// provide predefined duration for implicit system clock
  auto t5 = sys_time<milliseconds>{};
  println("t5 type {}", typeName(t5));

// use duration of days with system clock
  auto t6 = sys_days{};
  println("t6 type {}", typeName(t6));

#if EX_0_ERR_0
// fails because clock is not specified
  auto e1 = time_point{};
#endif

#if EX_0_ERR_1
// fails because duration is not specified
  auto e2 = sys_time{};
#endif

  println("");
}

void example_1() {
  println("Type of duration");

// provide fully-specified type and period of 1/1000 seconds
  auto d1 = duration<long, ratio<1, 1000>>{};
  println("d1 type {}", typeName(d1));
  println("d1 value {}", d1);

// provide type and period of 1 second with implicit 1 denominator
  auto d2 = duration<long, ratio<1>>{};
  println("d2 type {}", typeName(d2));
  println("d2 value {}", d2);

// provide type and implicit 1-second resolution
  auto d3 = duration<long>{};
  println("d3 type {}", typeName(d3));
  println("d3 value {}", d3);

// provide floating-point type and 1/1000 seconds = 1 millisecond period
  auto d4 = duration<double, ratio<1, 1000>>{};
  println("d4 type {}", typeName(d4));
  println("d4 value {}", d4);

// provide type and predefined resolution
  auto d5 = duration<long, milli>{};
  println("d5 type {}", typeName(d5));
  println("d5 value {}", d5);

// use predefined duration
  auto d6 = milliseconds{};
  println("d6 type {}", typeName(d6));
  println("d6 value {}", d6);

// initialize 1/1000 seconds = 1 millisecond resolution with floating-point value
  auto d7 = duration<double, ratio<1, 1000>>{1.5};
  println("d7 type {}", typeName(d7));
  println("d7 value {}", d7);

// provide type and 60 seconds = 1 minute resolution
  auto d8 = duration<long, ratio<60, 1>>{};
  println("d8 type {}", typeName(d8));
  println("d8 value {}", d8);

// provide type and 3600 seconds = 1 hour period
  auto d9 = duration<long, ratio<60*60, 1>>{};
  println("d9 type {}", typeName(d9));
  println("d9 value {}", d9);

// provide type and 86400 seconds = 1 day period
  auto d10 = duration<long, ratio<60*60*24, 1>>{};
  println("d10 type {}", typeName(d10));
  println("d10 value {}", d10);

// provide type and 100 seconds = 1 hectosecond period
  auto d11 = duration<long, ratio<100, 1>>{};
  println("d11 type {}", typeName(d11));
  println("d11 value {}", d11);

// provide type and 100 seconds = 1 kilosecond period
  auto d12 = duration<long, ratio<1000, 1>>{};
  println("d12 type {}", typeName(d12));
  println("d12 value {}", d12);

// provide type and 5 seconds period
  auto d13 = duration<long, ratio<5, 1>>{};
  println("d13 type {}", typeName(d13));
  println("d13 value {}", d13);

// provide type and 100/2 = 50 seconds period
  auto d14 = duration<long, ratio<100, 2>>{};
  println("d14 type {}", typeName(d14));
  println("d14 value {}", d14);

// provide type and 100/3 = 33.3 seconds period
  auto d15 = duration<double, ratio<100, 3>>{};
  println("d15 type {}", typeName(d15));
  println("d15 value {}", d15);

// initialize with negative value
  auto d16 = seconds{-123};
  println("d16 type {}", typeName(d16));
  println("d16 value {}", d16);

// initialize with overflow value
  auto d17 = duration<int16_t>{numeric_limits<int16_t>::max() + 2};
  println("d17 type {}", typeName(d17));
  println("d17 value {}", d17);

// initialize with overflow value
// bug in gcc-14 println
  auto d18 = duration<int16_t>{numeric_limits<int16_t>::max() + 1};
  println("d18 type {}", typeName(d18));
  println("d18 value {}", d18);

// initialize with value in int8_t range
// another bug in gcc-14 println
  auto d19 = duration<int8_t>{54};
  println("d19 type {}", typeName(d19));
  println("d19 value {}", d19);
  cout << format("d19 format value {}", d19) << "\n";
  auto s = format("{}", d19);
  println("s \"{}\"", s);

// initialize int8_t representation with overflow value
// duration_cast to different representation type sheds light on bug above
  auto d20 = duration<int8_t>{numeric_limits<int8_t>::max() + 1};
  println("d20 type {}", typeName(d20));
  println("d20 value {}", d20);
  println("d20 duration_cast value {}", duration_cast<seconds>(d20));

  auto d21 = duration<int64_t>{numeric_limits<int64_t>::min()};
  println("d21 type {}", typeName(d21));
  println("d21 value {}", d21);
  cout << format("d21 format value {}", d21) << "\n";
  println("d21 duration_cast value {}", duration_cast<seconds>(d21));

  auto d22 = duration<int64_t>::min();
  println("d22 type {}", typeName(d22));
  println("d22 value {}", d22);
  cout << format("d22 format value {}", d22) << "\n";

  auto d23 = duration_cast<duration<make_unsigned_t<int64_t>>>(d21);
  //println("d23 duration_cast unsigned value {}", d23);

  auto d24 = duration<int8_t>{54};
  println("d24 type {}", typeName(d24));
  println("d24 count {}", +d24.count());
  cout << format("d24 format count {}", +d24.count()) << "\n";
  auto s2 = format("{}", +d24.count());
  println("s \"{}\"", s2);

#if 0
  {
  auto d1 = duration<int64_t>{numeric_limits<int64_t>::min()};
  auto d3 = duration_cast<duration<make_unsigned_t<int64_t>>>(d1);
  println("d3 duration_cast unsigned value {}", d3);
  }
#endif

#if 0
  fmt::println("number zero \"{}\"", zero);
  //cout << "zero \"" << zero <<"\"" << "\n";
#endif

#if EX_1_ERR_0
// fails because type and period is missing
  auto e1 = duration{};
#endif

#if EX_1_ERR_1
// fails because floating-point initial value is invalid for integer type
  auto e2 = duration<long, ratio<1, 1000>>{1.5};
#endif

#if EX_1_ERR_2
// fails because milliseconds is itself a duration, not a predefined period
// use milli instead
  auto e3 = duration<long, milliseconds>{};
#endif

#if EX_1_ERR_3
// duration of unsigned type is fine but may not work well with other parts of the library
// but println does not compile
  auto e4 = duration<uint64_t>{};
  println("e4 value {}", e4);
#endif

#if EX_1_ERR_4
// duration of unsigned type is fine but may not work well with other parts of the library
// but println does not compile
  auto e5 = duration<uint64_t>{};
  println("e5 type {}", typeName(e5));
  //println("e5 value {}", e5);
  auto e6 = sys_time{e5};
  println("e6 type {}", typeName(e6));
  println("e6 value {}", e6);
  auto e7 = time_point<system_clock, duration<uint64_t>>{};
  println("e7 type {}", typeName(e7));
  println("e7 value {}", e7);
#endif

#if EX_1_ERR_5
  {
  auto d4 = duration<uint64_t>{};
  //println("d4 value {}", d4);
  auto t1 = time_point<system_clock, duration<uint64_t>>{};
  println("t1 value {}", t1);
  }
#endif

  println("");
}

void example_2() {
  println("Steady clock");

// provide clock with its implicit default clock duration
  auto t1 = time_point<steady_clock>{};
  println("t1 type {}", typeName(t1));
  //println("t1 value \"{}\"", t1);
  auto d1 = hh_mm_ss{t1.time_since_epoch()};
  println("time from t since epoch {}", d1);

// fully specify clock and duration
  auto t2 = time_point<steady_clock, duration<long, ratio<1, 1000>>>{};
  println("t2 type {}", typeName(t2));

// provide clock and predefined duration
  auto t3 = time_point<steady_clock, milliseconds>{};
  println("t3 type {}", typeName(t3));

#if EX_0_ERR_0
// fails because clock is not specified
  auto e1 = time_point{};
#endif

#if EX_0_ERR_1
// fails because duration is not specified
  auto e2 = sys_time{};
#endif

  println("");
}

void example_3() {
  println("Different timepoint values");

// provide clock with its implicit default clock duration
  auto t1 = steady_clock::now();
  //println("t1 value \"{}\"", t1);
  auto d1 = hh_mm_ss{t1.time_since_epoch()};
  println("time since steady_clock epoch {}", d1);

// fully specify clock and duration
  auto t2 = time_point<steady_clock, duration<long, ratio<1, 1000>>>{};
  println("t2 type {}", typeName(t2));

// provide clock and predefined duration
  auto t3 = time_point<steady_clock, milliseconds>{};
  println("t3 type {}", typeName(t3));

#if EX_0_ERR_0
// fails because clock is not specified
  auto e1 = time_point{};
#endif

#if EX_0_ERR_1
// fails because duration is not specified
  auto e2 = sys_time{};
#endif

  println("");
}


}

void fails_0() {
#if FAIL_0
  auto t1 = time_point{};
#endif

}

int main(int argc, char* argv[]) {
  (void)argc;
  (void)argv;
#if 0
  now_timepoint();
  durations();
  timers();
  durations();
  timepoint_ops();
#endif

// call function named for each argument
  for(int i = 1; i < argc; ++i) {
    auto funcname = argv[i];
    if(!funcByName.contains(funcname)) {
      println(stderr, "function {} not found", funcname);
      return 1;
    }
    println("{}:", funcname);
    funcByName[funcname]();
  }

}
