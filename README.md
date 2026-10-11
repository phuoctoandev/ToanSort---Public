# ToanSort

**An experimental sorting algorithm concept implemented with AI assistance.**

## Overview

ToanSort is an experimental sorting project based on my own algorithmic ideas.

The original motivation was to explore alternative ways of sorting integer arrays and compare their performance with existing sorting algorithms, particularly `std::sort`.

I developed the core idea of dividing data into three regions using pivot values selected from the beginning, middle, and end of the array. The implementation was then developed with assistance from Google Gemini.

This repository preserves the original experiment as a starting point for future analysis, learning, and redesign.

## Algorithm Concept

The current implementation uses the following approach:

1. Select values from the beginning, middle, and end of the array.
2. Determine the minimum and maximum among those three values.
3. Divide elements into three regions:
   - **LEFT:** values smaller than the selected minimum.
   - **MID:** values between the selected minimum and maximum, inclusive.
   - **RIGHT:** values greater than the selected maximum.
4. Recursively process the resulting regions.
5. Use `std::sort` for sufficiently small subarrays.

The implementation is experimental. The current source code may not fully or correctly realize the intended algorithm, and its correctness and performance require further verification.

## Benchmarking

The original benchmark compares ToanSort with:

- `std::sort`
- Merge Sort
- Quick Sort

The benchmark uses a randomly generated integer array containing 1,000,000 elements, with values in the range `[0, 1,000,000]`. The random generator uses a fixed seed for reproducibility.

Each algorithm receives a copy of the same original input array.

These tests represent only one input distribution and one test configuration. They do not establish that ToanSort is generally faster than the comparison algorithms.

## AI Assistance

The algorithm concept and initial direction came from me. Google Gemini assisted in translating the ideas into C++ code.

I do not present the current implementation as entirely hand-written code. Reviewing, testing, understanding, and improving the implementation are part of the project's ongoing learning process.

## Known Limitations

- Correctness has not been established for all input cases.
- The recursive partitioning logic needs further review.
- Additional memory is used when collecting the middle region.
- Performance has not been systematically evaluated across different input distributions and array sizes.
- Memory usage, recursion depth, and worst-case behavior require further investigation.

## Future Plans

- Verify the partitioning logic and recursive boundaries.
- Test empty arrays, duplicate values, sorted arrays, reverse-sorted arrays, and random arrays.
- Compare output against `std::sort` as a correctness reference.
- Expand benchmarking and report repeated measurements.
- Investigate memory allocation, recursion depth, and performance bottlenecks.
- Revisit and potentially redesign the original algorithm as my understanding of algorithms and C++ improves.

## Project Status

**Early experimental prototype — not production-ready.**

ToanSort is a record of an early algorithmic idea and its AI-assisted implementation. Its purpose is to preserve the original concept and provide a foundation for future testing and improvement, not to claim a proven replacement for established sorting algorithms.

---

*An early idea, preserved for future experiments.*
