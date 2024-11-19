<!-- 20240910_chrono_afraid_to_ask/README.md -->

# Everything you were afraid to ask about chrono*<br><sub>(*But always wanted to know)</sub>

## C++ chrono library

The C++ chrono is a standard library for handling time and dates

## Fundamental concepts

- Timepoint -a specific time
  - The time displayed on our watches, clocks and phones
  - Also known as real time or wall clock time
  - `2024-09-10T12:34:56Z` in ISO-8601 format, for example

- Duration - a length of time
  - The time displayed by a timer or stopwatch
  - Sometimes called age, interval or period
  - The difference of two timepoints
  - 5 minutes, 3 days or 34 years, for example

## What is `time_point`?

- The `type` of `timepoint`?
  - template<class Clock, class Duration = typename Clock::duration> class time_point

## What is `duration`?

- The `type` of `duration`?
  - template<class Rep, class Period = std::ratio<1>> class duration

## Create a `time_point`


