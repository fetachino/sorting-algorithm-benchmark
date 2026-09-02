set terminal png size 800,600 enhanced font 'Arial,12'
set output 'swaps_plot.png'
set title 'Number of Swaps by Algorithm'
set xlabel 'Input Size'
set ylabel 'Number of Swaps'
set key top left
set grid
plot 'sorting_results.csv' using 1:3 with linespoints title 'Insertion Sort', \
     'sorting_results.csv' using 1:6 with linespoints title 'Merge Sort', \
     'sorting_results.csv' using 1:9 with linespoints title 'Quick Sort'
