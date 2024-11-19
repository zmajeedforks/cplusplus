<!-- 20240910_chrono_afraid_to_ask/README.md -->

# Everything you were afraid to ask about chrono\*<br><sub>(\*But always wanted to know)</sub>

## 1. C++ chrono library

C++ chrono is a standard library for time and date

- Introduced in C++11
- Much improved in C++20
- Full support in GCC 14 released May 2024
- Video repo https://github.com/opensourceu/20240910_chrono_afraid_to_ask

## 2. Acknowledgement & Thanks!

C++ chrono was made possible by these notable contributions

- Extending `<chrono>` to Calendars and Time Zones
  - C++ proposal P0355R7, 2018
  - Howard E. Hinnant, Tomasz Kamiński
- Implement C++20 std::chrono
  - GCC Bug 104167, 2022-2023
  - Jonathan Wakely
- A Foundation to Sleep On: Clocks, Points in Time, and Time Durations
  - C++ proposal N2661, 2008
  - Howard E. Hinnant, Walter E. Brown, Jeff Garland, Marc Paterno
- C++ standard and GCC maintainers

## 3. Fundamental concepts

- **Timepoint:** A specific time
  - The time displayed on our watches, clocks and phones
  - Also known as real time or wall clock time
  - `2024-09-10T12:34:56Z` in ISO-8601 format, for example
  - Is `c++ chrono::time_point` type

- **Duration:** A length of time
  - The time displayed by a timer or stopwatch
  - Sometimes called age, interval or period
  - The difference of two timepoints
  - 5 minutes, 3 days or 34 years, for example
  - Is `c++ chrono::duration` type

## 4. What is `time_point`?

- It's a duration measured against a clock
- What's the `type` of `c++ time_point`?
  - `c++ template<class Clock, class Duration = typename Clock::duration> class time_point`

- There isn't just one clock - two are often used
  - **System clock** for schedules and appointments
  - **Steady clock** for timing, countdowns, playback timelines

## 5. What is `duration`?

- Duration is a length of time
  - 5 minutes, 1 hour, 2 days
- It's a signed numeric **scaling** of 1-second **period**
- What's the `type` of `c++ duration`?
  - `c++ template<class Rep, class Period = ratio<1>> class duration`
- `Rep` is type of numeric representation like `c++ int`, `c++ long`, `c++ double`
- `Period` is rational multiple of 1 second
  - `c++ ratio<1, 1000>` is period of 1/1000 second (millisecond)
  - `c++ ratio<60, 1>` is period of 60/1 second (minute)

## 6. Example 1: Type of `time_point`: A closer look

- Valid examples
```bash
make example_0
```

## 7. Example 2: Type of `time_point`: Pitfalls

- Examples that do not compile
```bash
cmake --fresh -DCMAKE_CXX_FLAGS=-DEX_0_ERR_0
make example_0
```

## 8. Example 3: Type of `duration`: A closer look

```bash
make example_1
```

## 9. Example 4: Type of `duration`: Pitfalls

```bash
cmake --fresh -DCMAKE_CXX_FLAGS=-DEX_1_ERR_0
make example_1
```

## 10. Create `time_point`

- Get clock's current time
- Zero-initialize a timepoint
- Read a time string
- Initialize with a duration
- Copy another timepoint

## 11. Create `duration`

- Initialize with a numeric multiple of the period
- use duration literals for hours and smaller units
- initialize multiples of builtin durations from years down to nanoseconds
- Use an arithmetic expression of literals and initialized durations
- Read a duration string

## 12. Print `chrono` objects

-

## 13. Break down `time_point`

- `c++ time_point` is fully-specified date and time in UTC
- Get date from `c++ time_point`
  - `time_point_cast<days>`

## 14. What can you do with `time_point`?

## 15. What can you do with `duration`?

## 16. What can't you do?

summarize previous errors
some obvious, some not
- Can't add timepoints
- can't directly get any component of timepoint

## 17. Common use cases

- Timer

often we need time and time calculations in other contexts

timer counts down or counts up
stopwatch is timing
schedule is time comparison
when? versus how long?
periodic
alarm
look up uses of time date calendar problems programming

## Exercise 1: Timepoints

1. Get current time
2. Create a timepoint for 9 am on September 23rd, 2024 UTC time

