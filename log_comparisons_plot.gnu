set terminal png size 800,600 enhanced font 'Arial,12'
set output 'log_comparisons_plot.png'
set title 'Number of Comparisons by Algorithm (Log Scale)'
set xlabel 'Input Size'
set ylabel 'Number of Comparisons (Log Scale)'
set logscale y
set key top left
set grid
plot 'sorting_results.csv' using 1:2 with linespoints title 'Insertion Sort', \
     'sorting_results.csv' using 1:5 with linespoints title 'Merge Sort', \
     'sorting_results.csv' using 1:8 with linespoints title 'Quick Sort'
