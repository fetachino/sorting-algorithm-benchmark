set terminal png size 800,600 enhanced font 'Arial,12'
set output 'theoretical_comparison.png'
set title 'Comparison with Theoretical Complexity'
set xlabel 'Input Size'
set ylabel 'Operations'
set key top left
set grid
plot 'theoretical_data.txt' using 1:2 with lines title 'O(n²)', \
     'theoretical_data.txt' using 1:3 with lines title 'O(n log n)', \
     'sorting_results.csv' using 1:4 with linespoints title 'Insertion Sort Total', \
     'sorting_results.csv' using 1:7 with linespoints title 'Merge Sort Total', \
     'sorting_results.csv' using 1:10 with linespoints title 'Quick Sort Total'
