# Sorting Algorithm Benchmark

[![C++](https://img.shields.io/badge/C++-17-00599C?logo=cplusplus&logoColor=white)](https://isocpp.org/)
[![Gnuplot](https://img.shields.io/badge/Gnuplot-visualization-F0A202)](http://www.gnuplot.info/)
[![Benchmark](https://img.shields.io/badge/Benchmark-instrumented-2A9D8F)](#measured-results)

A C++ benchmark comparing insertion sort, merge sort, and quicksort across increasingly large randomized inputs. The program counts comparisons and swaps, exports results, and supports Gnuplot visualizations on linear and logarithmic scales.

## Key finding

At 10,000 elements, insertion sort required roughly **49.8 million** measured operations, compared with approximately **254 thousand** for merge sort and **253 thousand** for quicksort. The experiment makes the practical difference between quadratic and `n log n` growth visible.

## Measured results

| Input size | Insertion total operations | Merge total operations | Quick total operations |
| ---: | ---: | ---: | ---: |
| 100 | 4,518 | 1,221 | 1,052 |
| 1,000 | 486,487 | 18,675 | 18,488 |
| 5,000 | 12,480,130 | 117,019 | 105,933 |
| 10,000 | 49,784,822 | 254,072 | 252,819 |

The measured growth illustrates insertion sort's quadratic behavior and the substantially better scaling of merge sort and quicksort.

## Visualizations

![Linear-scale comparison](linearscale.png)

![Log-scale comparison](logscale.png)

## Build and run

```console
g++ -std=c++17 -O2 main.cpp -o sorting-benchmark
./sorting-benchmark
```

With Gnuplot installed, run `generate_all_plots.sh` to regenerate the charts.

## Testing and verification

The benchmark was verified by compiling with a C++17 compiler and checking that each algorithm produces sorted output for the generated input sizes. The committed `sorting_results.csv` records the comparison, swap, and total-operation counters used in the charts.

```console
g++ -std=c++17 -O2 -Wall -Wextra main.cpp -o sorting-benchmark
./sorting-benchmark
```

This is an independent algorithm-analysis portfolio project; no formal course attribution is claimed in the source materials.

## Testing and verification

The benchmark was verified by compiling with a C++17 compiler and checking that each algorithm produces sorted output for the generated input sizes. The committed `sorting_results.csv` records the comparison, swap, and total-operation counters used in the charts.

```console
g++ -std=c++17 -O2 -Wall -Wextra main.cpp -o sorting-benchmark
./sorting-benchmark
```

This is an independent algorithm-analysis portfolio project; no formal course attribution is claimed in the source materials.

## Skills demonstrated

- C++ algorithm implementation
- Experimental algorithm analysis
- Comparisons and swap instrumentation
- CSV export and Gnuplot visualization
- Relating measured behavior to Big-O complexity

## About the author

Built by **Ahmed Balde** to connect algorithm theory with measured runtime behavior. See more C++, Python, data, and software-engineering work on [GitHub](https://github.com/fetachino).
