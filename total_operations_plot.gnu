set terminal png size 800,600 enhanced font 'Arial,12'
set output 'total_operations_plot.png'
set title 'Total Operations by Algorithm'
set xlabel 'Input Size'
set ylabel 'Number of Operations (Comparisons + Swaps)'
set key top left
set grid
plot 'sorting_results.csv' using 1:4 with linespoints title 'Insertion Sort', \
     'sorting_results.csv' using 1:7 with linespoints title 'Merge Sort', \
     'sorting_results.csv' using 1:10 with linespoints title 'Quick Sort'
