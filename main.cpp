#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <string>
#include <algorithm>

// Structure to hold comparison and swap counts
struct CounterStats {
    unsigned long long comparisons;
    unsigned long long swaps;

    CounterStats() : comparisons(0), swaps(0) {}

    void reset() {
        comparisons = 0;
        swaps = 0;
    }

    // Get total operations (sum of comparisons and swaps)
    unsigned long long getTotalOperations() const {
        return comparisons + swaps;
    }
};

// Insertion Sort
void insertionSort(std::vector<int>& arr, CounterStats& counter) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        // Move elements of arr[0..i-1] that are greater than key
        // to one position ahead of their current position
        while (j >= 0) {
            counter.comparisons++; // Count comparison
            if (arr[j] > key) {
                arr[j + 1] = arr[j]; // Count as swap
                counter.swaps++;
                j--;
            }
            else {
                break;
            }
        }
        arr[j + 1] = key;
    }
}

// Merge function for Merge Sort
void merge(std::vector<int>& arr, int left, int mid, int right, CounterStats& counter) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays
    std::vector<int> L(n1), R(n2);

    // Copy data to temporary arrays
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Merge the temporary arrays back into arr[left..right]
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        counter.comparisons++; // Count comparison
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        counter.swaps++; // Count as swap/assignment
        k++;
    }

    // Copy remaining elements of L[]
    while (i < n1) {
        arr[k] = L[i];
        counter.swaps++; // Count as swap/assignment
        i++;
        k++;
    }

    // Copy remaining elements of R[]
    while (j < n2) {
        arr[k] = R[j];
        counter.swaps++; // Count as swap/assignment
        j++;
        k++;
    }
}

// Recursive Merge Sort
void mergeSort(std::vector<int>& arr, int left, int right, CounterStats& counter) {
    if (left < right) {
        // Same as (left+right)/2, but avoids overflow for large left and right
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(arr, left, mid, counter);
        mergeSort(arr, mid + 1, right, counter);

        // Merge the sorted halves
        merge(arr, left, mid, right, counter);
    }
}

// Function to perform the merge sort
void mergeSort(std::vector<int>& arr, CounterStats& counter) {
    mergeSort(arr, 0, arr.size() - 1, counter);
}

// Partition function for QuickSort
int partition(std::vector<int>& arr, int low, int high, CounterStats& counter) {
    int pivot = arr[high]; // Choosing the last element as pivot
    int i = low - 1; // Index of smaller element

    for (int j = low; j < high; j++) {
        counter.comparisons++; // Count comparison
        if (arr[j] <= pivot) {
            i++;
            // Swap arr[i] and arr[j]
            std::swap(arr[i], arr[j]);
            counter.swaps++; // Count swap
        }
    }

    // Swap arr[i+1] and arr[high] (put the pivot in its correct position)
    std::swap(arr[i + 1], arr[high]);
    counter.swaps++; // Count swap

    return i + 1;
}

// Recursive QuickSort
void quickSort(std::vector<int>& arr, int low, int high, CounterStats& counter) {
    if (low < high) {
        // pi is partitioning index, arr[pi] is now at right place
        int pi = partition(arr, low, high, counter);

        // Separately sort elements before and after partition
        quickSort(arr, low, pi - 1, counter);
        quickSort(arr, pi + 1, high, counter);
    }
}

// Function to perform the quick sort
void quickSort(std::vector<int>& arr, CounterStats& counter) {
    quickSort(arr, 0, arr.size() - 1, counter);
}

// Function to generate random numbers
std::vector<int> generateRandomNumbers(int size) {
    std::vector<int> numbers(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 10000);

    for (int i = 0; i < size; i++) {
        numbers[i] = distrib(gen);
    }

    return numbers;
}

// Function to print array
void printArray(const std::vector<int>& arr, int limit = -1) {
    int n = (limit > 0 && limit < arr.size()) ? limit : arr.size();
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
        // Add a newline every 10 elements for better readability
        if ((i + 1) % 10 == 0) {
            std::cout << std::endl;
        }
    }
    if (n % 10 != 0) {
        std::cout << std::endl;
    }
}

// Function to save the array to a file
void saveArrayToFile(const std::vector<int>& arr, const std::string& filename) {
    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        for (size_t i = 0; i < arr.size(); i++) {
            outFile << arr[i] << std::endl;
        }
        outFile.close();
    }
    else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}

// Function to save results to CSV
void saveResultsToCSV(const std::vector<int>& sizes,
    const std::vector<CounterStats>& insertionStats,
    const std::vector<CounterStats>& mergeStats,
    const std::vector<CounterStats>& quickStats,
    const std::string& filename = "sorting_results.csv") {
    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        // Write header
        outFile << "Size,Insertion Sort Comparisons,Insertion Sort Swaps,Insertion Sort Total,"
            << "Merge Sort Comparisons,Merge Sort Swaps,Merge Sort Total,"
            << "Quick Sort Comparisons,Quick Sort Swaps,Quick Sort Total\n";

        // Write data
        for (size_t i = 0; i < sizes.size(); i++) {
            outFile << sizes[i] << ","
                << insertionStats[i].comparisons << ","
                << insertionStats[i].swaps << ","
                << insertionStats[i].getTotalOperations() << ","
                << mergeStats[i].comparisons << ","
                << mergeStats[i].swaps << ","
                << mergeStats[i].getTotalOperations() << ","
                << quickStats[i].comparisons << ","
                << quickStats[i].swaps << ","
                << quickStats[i].getTotalOperations() << "\n";
        }
        outFile.close();
        std::cout << "Results saved to " << filename << std::endl;
    }
    else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}

// Function to generate GNUPlot scripts for visualization
void generateGnuplotScripts(const std::vector<int>& sizes) {
    // Linear scale comparison plot
    std::ofstream comparePlot("comparisons_plot.gnu");
    if (comparePlot.is_open()) {
        comparePlot << "set terminal png size 800,600 enhanced font 'Arial,12'\n";
        comparePlot << "set output 'comparisons_plot.png'\n";
        comparePlot << "set title 'Number of Comparisons by Algorithm'\n";
        comparePlot << "set xlabel 'Input Size'\n";
        comparePlot << "set ylabel 'Number of Comparisons'\n";
        comparePlot << "set key top left\n";
        comparePlot << "set grid\n";
        comparePlot << "plot 'sorting_results.csv' using 1:2 with linespoints title 'Insertion Sort', \\\n";
        comparePlot << "     'sorting_results.csv' using 1:5 with linespoints title 'Merge Sort', \\\n";
        comparePlot << "     'sorting_results.csv' using 1:8 with linespoints title 'Quick Sort'\n";
        comparePlot.close();
    }

    // Linear scale swaps plot
    std::ofstream swapsPlot("swaps_plot.gnu");
    if (swapsPlot.is_open()) {
        swapsPlot << "set terminal png size 800,600 enhanced font 'Arial,12'\n";
        swapsPlot << "set output 'swaps_plot.png'\n";
        swapsPlot << "set title 'Number of Swaps by Algorithm'\n";
        swapsPlot << "set xlabel 'Input Size'\n";
        swapsPlot << "set ylabel 'Number of Swaps'\n";
        swapsPlot << "set key top left\n";
        swapsPlot << "set grid\n";
        swapsPlot << "plot 'sorting_results.csv' using 1:3 with linespoints title 'Insertion Sort', \\\n";
        swapsPlot << "     'sorting_results.csv' using 1:6 with linespoints title 'Merge Sort', \\\n";
        swapsPlot << "     'sorting_results.csv' using 1:9 with linespoints title 'Quick Sort'\n";
        swapsPlot.close();
    }

    // Total operations plot
    std::ofstream totalPlot("total_operations_plot.gnu");
    if (totalPlot.is_open()) {
        totalPlot << "set terminal png size 800,600 enhanced font 'Arial,12'\n";
        totalPlot << "set output 'total_operations_plot.png'\n";
        totalPlot << "set title 'Total Operations by Algorithm'\n";
        totalPlot << "set xlabel 'Input Size'\n";
        totalPlot << "set ylabel 'Number of Operations (Comparisons + Swaps)'\n";
        totalPlot << "set key top left\n";
        totalPlot << "set grid\n";
        totalPlot << "plot 'sorting_results.csv' using 1:4 with linespoints title 'Insertion Sort', \\\n";
        totalPlot << "     'sorting_results.csv' using 1:7 with linespoints title 'Merge Sort', \\\n";
        totalPlot << "     'sorting_results.csv' using 1:10 with linespoints title 'Quick Sort'\n";
        totalPlot.close();
    }

    // Log scale comparison plot
    std::ofstream logComparePlot("log_comparisons_plot.gnu");
    if (logComparePlot.is_open()) {
        logComparePlot << "set terminal png size 800,600 enhanced font 'Arial,12'\n";
        logComparePlot << "set output 'log_comparisons_plot.png'\n";
        logComparePlot << "set title 'Number of Comparisons by Algorithm (Log Scale)'\n";
        logComparePlot << "set xlabel 'Input Size'\n";
        logComparePlot << "set ylabel 'Number of Comparisons (Log Scale)'\n";
        logComparePlot << "set logscale y\n";
        logComparePlot << "set key top left\n";
        logComparePlot << "set grid\n";
        logComparePlot << "plot 'sorting_results.csv' using 1:2 with linespoints title 'Insertion Sort', \\\n";
        logComparePlot << "     'sorting_results.csv' using 1:5 with linespoints title 'Merge Sort', \\\n";
        logComparePlot << "     'sorting_results.csv' using 1:8 with linespoints title 'Quick Sort'\n";
        logComparePlot.close();
    }

    // Log scale swaps plot
    std::ofstream logSwapsPlot("log_swaps_plot.gnu");
    if (logSwapsPlot.is_open()) {
        logSwapsPlot << "set terminal png size 800,600 enhanced font 'Arial,12'\n";
        logSwapsPlot << "set output 'log_swaps_plot.png'\n";
        logSwapsPlot << "set title 'Number of Swaps by Algorithm (Log Scale)'\n";
        logSwapsPlot << "set xlabel 'Input Size'\n";
        logSwapsPlot << "set ylabel 'Number of Swaps (Log Scale)'\n";
        logSwapsPlot << "set logscale y\n";
        logSwapsPlot << "set key top left\n";
        logSwapsPlot << "set grid\n";
        logSwapsPlot << "plot 'sorting_results.csv' using 1:3 with linespoints title 'Insertion Sort', \\\n";
        logSwapsPlot << "     'sorting_results.csv' using 1:6 with linespoints title 'Merge Sort', \\\n";
        logSwapsPlot << "     'sorting_results.csv' using 1:9 with linespoints title 'Quick Sort'\n";
        logSwapsPlot.close();
    }

    // Log scale total operations plot
    std::ofstream logTotalPlot("log_total_operations_plot.gnu");
    if (logTotalPlot.is_open()) {
        logTotalPlot << "set terminal png size 800,600 enhanced font 'Arial,12'\n";
        logTotalPlot << "set output 'log_total_operations_plot.png'\n";
        logTotalPlot << "set title 'Total Operations by Algorithm (Log Scale)'\n";
        logTotalPlot << "set xlabel 'Input Size'\n";
        logTotalPlot << "set ylabel 'Number of Operations (Log Scale)'\n";
        logTotalPlot << "set logscale y\n";
        logTotalPlot << "set key top left\n";
        logTotalPlot << "set grid\n";
        logTotalPlot << "plot 'sorting_results.csv' using 1:4 with linespoints title 'Insertion Sort', \\\n";
        logTotalPlot << "     'sorting_results.csv' using 1:7 with linespoints title 'Merge Sort', \\\n";
        logTotalPlot << "     'sorting_results.csv' using 1:10 with linespoints title 'Quick Sort'\n";
        logTotalPlot.close();
    }

    // Theoretical comparison plot with O(n²) and O(n log n)
    std::ofstream theoreticalPlot("theoretical_comparison.gnu");
    if (theoreticalPlot.is_open()) {
        theoreticalPlot << "set terminal png size 800,600 enhanced font 'Arial,12'\n";
        theoreticalPlot << "set output 'theoretical_comparison.png'\n";
        theoreticalPlot << "set title 'Comparison with Theoretical Complexity'\n";
        theoreticalPlot << "set xlabel 'Input Size'\n";
        theoreticalPlot << "set ylabel 'Operations'\n";
        theoreticalPlot << "set key top left\n";
        theoreticalPlot << "set grid\n";

        // Create a temporary file for theoretical curves
        std::ofstream theoData("theoretical_data.txt");
        if (theoData.is_open()) {
            for (size_t i = 0; i < sizes.size(); i++) {
                int n = sizes[i];
                // Scaled theoretical complexity values
                double n_squared = n * n / 1000.0;
                double n_log_n = n * log2(n) / 100.0;
                theoData << n << " " << n_squared << " " << n_log_n << "\n";
            }
            theoData.close();

            theoreticalPlot << "plot 'theoretical_data.txt' using 1:2 with lines title 'O(n²)', \\\n";
            theoreticalPlot << "     'theoretical_data.txt' using 1:3 with lines title 'O(n log n)', \\\n";
            theoreticalPlot << "     'sorting_results.csv' using 1:4 with linespoints title 'Insertion Sort Total', \\\n";
            theoreticalPlot << "     'sorting_results.csv' using 1:7 with linespoints title 'Merge Sort Total', \\\n";
            theoreticalPlot << "     'sorting_results.csv' using 1:10 with linespoints title 'Quick Sort Total'\n";
        }
        theoreticalPlot.close();
    }

    // Master script to run all plots
    std::ofstream masterScript("generate_all_plots.bat");
    if (masterScript.is_open()) {
        masterScript << "gnuplot comparisons_plot.gnu\n";
        masterScript << "gnuplot swaps_plot.gnu\n";
        masterScript << "gnuplot total_operations_plot.gnu\n";
        masterScript << "gnuplot log_comparisons_plot.gnu\n";
        masterScript << "gnuplot log_swaps_plot.gnu\n";
        masterScript << "gnuplot log_total_operations_plot.gnu\n";
        masterScript << "gnuplot theoretical_comparison.gnu\n";
        masterScript.close();
        std::cout << "GNUPlot scripts generated. Run 'generate_all_plots.bat' to create all plots." << std::endl;
    }

    // For Unix/Linux/Mac
    std::ofstream unixScript("generate_all_plots.sh");
    if (unixScript.is_open()) {
        unixScript << "#!/bin/bash\n";
        unixScript << "gnuplot comparisons_plot.gnu\n";
        unixScript << "gnuplot swaps_plot.gnu\n";
        unixScript << "gnuplot total_operations_plot.gnu\n";
        unixScript << "gnuplot log_comparisons_plot.gnu\n";
        unixScript << "gnuplot log_swaps_plot.gnu\n";
        unixScript << "gnuplot log_total_operations_plot.gnu\n";
        unixScript << "gnuplot theoretical_comparison.gnu\n";
        unixScript.close();
        std::cout << "GNUPlot scripts generated. Run 'bash generate_all_plots.sh' on Unix/Linux/Mac to create all plots." << std::endl;
    }
}

// Function to analyze the growth rates based on the results
void analyzeGrowthRates(const std::vector<int>& sizes,
    const std::vector<CounterStats>& insertionStats,
    const std::vector<CounterStats>& mergeStats,
    const std::vector<CounterStats>& quickStats) {
    std::cout << "\n============ Growth Rate Analysis ============\n";

    for (size_t i = 1; i < sizes.size(); i++) {
        double sizeRatio = static_cast<double>(sizes[i]) / sizes[i - 1];

        std::cout << "Size increase from " << sizes[i - 1] << " to " << sizes[i]
            << " (ratio: " << std::fixed << std::setprecision(2) << sizeRatio << "x)\n";

            // Insertion Sort (expected O(n²))
            double insertionCompRatio = static_cast<double>(insertionStats[i].comparisons) / insertionStats[i - 1].comparisons;
            double insertionTotalRatio = static_cast<double>(insertionStats[i].getTotalOperations()) / insertionStats[i - 1].getTotalOperations();
            double expectedSquared = sizeRatio * sizeRatio;
            std::cout << "  Insertion Sort comparisons: " << std::fixed << std::setprecision(2)
                << insertionCompRatio << "x (Expected for O(n²): ~" << expectedSquared << "x)\n";
            std::cout << "  Insertion Sort total operations: " << std::fixed << std::setprecision(2)
                << insertionTotalRatio << "x\n";

            // Merge Sort (expected O(n log n))
            double mergeCompRatio = static_cast<double>(mergeStats[i].comparisons) / mergeStats[i - 1].comparisons;
            double mergeTotalRatio = static_cast<double>(mergeStats[i].getTotalOperations()) / mergeStats[i - 1].getTotalOperations();
            double expectedNLogN = sizeRatio * (log2(sizes[i]) / log2(sizes[i - 1]));
            std::cout << "  Merge Sort comparisons: " << std::fixed << std::setprecision(2)
                << mergeCompRatio << "x (Expected for O(n log n): ~" << expectedNLogN << "x)\n";
            std::cout << "  Merge Sort total operations: " << std::fixed << std::setprecision(2)
                << mergeTotalRatio << "x\n";

            // Quick Sort (expected O(n log n) on average)
            double quickCompRatio = static_cast<double>(quickStats[i].comparisons) / quickStats[i - 1].comparisons;
            double quickTotalRatio = static_cast<double>(quickStats[i].getTotalOperations()) / quickStats[i - 1].getTotalOperations();
            std::cout << "  Quick Sort comparisons: " << std::fixed << std::setprecision(2)
                << quickCompRatio << "x (Expected for O(n log n): ~" << expectedNLogN << "x)\n";
            std::cout << "  Quick Sort total operations: " << std::fixed << std::setprecision(2)
                << quickTotalRatio << "x\n";

            std::cout << std::endl;
    }

    std::cout << "=========== Summary of Complexity ===========\n";
    std::cout << "Insertion Sort: Theoretical O(n²) - ";
    if (insertionStats.back().comparisons > 0.5 * sizes.back() * sizes.back() &&
        insertionStats.back().comparisons < 2 * sizes.back() * sizes.back()) {
        std::cout << "Confirmed by experiment\n";
    }
    else {
        std::cout << "Results vary from theory\n";
    }

    std::cout << "Merge Sort: Theoretical O(n log n) - ";
    if (mergeStats.back().comparisons > 0.1 * sizes.back() * log2(sizes.back()) &&
        mergeStats.back().comparisons < 10 * sizes.back() * log2(sizes.back())) {
        std::cout << "Confirmed by experiment\n";
    }
    else {
        std::cout << "Results vary from theory\n";
    }

    std::cout << "Quick Sort: Theoretical O(n log n) average case - ";
    if (quickStats.back().comparisons > 0.1 * sizes.back() * log2(sizes.back()) &&
        quickStats.back().comparisons < 10 * sizes.back() * log2(sizes.back())) {
        std::cout << "Confirmed by experiment\n";
    }
    else {
        std::cout << "Results vary from theory or encountered worst-case O(n²)\n";
    }
}

// Function to verify all arrays are sorted correctly
bool verifySorting(const std::vector<int>& arr1,
    const std::vector<int>& arr2,
    const std::vector<int>& arr3) {
    // Check that all arrays are sorted
    bool arr1Sorted = std::is_sorted(arr1.begin(), arr1.end());
    bool arr2Sorted = std::is_sorted(arr2.begin(), arr2.end());
    bool arr3Sorted = std::is_sorted(arr3.begin(), arr3.end());

    // Check that all arrays contain the same elements (have the same sum)
    long long sum1 = 0, sum2 = 0, sum3 = 0;
    for (size_t i = 0; i < arr1.size(); i++) {
        sum1 += arr1[i];
        sum2 += arr2[i];
        sum3 += arr3[i];
    }

    bool sameContent = (sum1 == sum2) && (sum2 == sum3);

    return arr1Sorted && arr2Sorted && arr3Sorted && sameContent;
}

int main() {
    std::vector<int> sizes = { 100, 1000, 5000, 10000 };
    std::vector<CounterStats> insertionStats(sizes.size());
    std::vector<CounterStats> mergeStats(sizes.size());
    std::vector<CounterStats> quickStats(sizes.size());

    for (size_t i = 0; i < sizes.size(); i++) {
        int size = sizes[i];
        std::cout << "\n===== Testing with " << size << " elements =====\n";

        // Generate random numbers
        std::vector<int> original = generateRandomNumbers(size);

        // Save the original array for reference
        saveArrayToFile(original, "original_" + std::to_string(size) + ".txt");

        // Insertion Sort
        std::vector<int> arr1 = original;
        CounterStats insertionCounter;
        auto start = std::chrono::high_resolution_clock::now();
        insertionSort(arr1, insertionCounter);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;

        std::cout << "Insertion Sort:\n";
        std::cout << "  Comparisons: " << insertionCounter.comparisons << std::endl;
        std::cout << "  Swaps: " << insertionCounter.swaps << std::endl;
        std::cout << "  Total Operations: " << insertionCounter.getTotalOperations() << std::endl;
        std::cout << "  Time: " << elapsed.count() << " seconds\n";
        insertionStats[i] = insertionCounter;

        // Print sorted array for sizes 100 and 1000
        if (size <= 1000) {
            std::cout << "  Sorted elements:\n";
            printArray(arr1);

            // Save the sorted array
            saveArrayToFile(arr1, "insertion_sorted_" + std::to_string(size) + ".txt");
        }

        // Merge Sort
        std::vector<int> arr2 = original;
        CounterStats mergeCounter;
        start = std::chrono::high_resolution_clock::now();
        mergeSort(arr2, mergeCounter);
        end = std::chrono::high_resolution_clock::now();
        elapsed = end - start;

        std::cout << "Merge Sort:\n";
        std::cout << "  Comparisons: " << mergeCounter.comparisons << std::endl;
        std::cout << "  Swaps: " << mergeCounter.swaps << std::endl;
        std::cout << "  Total Operations: " << mergeCounter.getTotalOperations() << std::endl;
        std::cout << "  Time: " << elapsed.count() << " seconds\n";
        mergeStats[i] = mergeCounter;

        // Print sorted array for sizes 100 and 1000
        if (size <= 1000) {
            std::cout << "  Sorted elements:\n";
            printArray(arr2);

            // Save the sorted array
            saveArrayToFile(arr2, "merge_sorted_" + std::to_string(size) + ".txt");
        }

        // Quick Sort
        std::vector<int> arr3 = original;
        CounterStats quickCounter;
        start = std::chrono::high_resolution_clock::now();
        quickSort(arr3, quickCounter);
        end = std::chrono::high_resolution_clock::now();
        elapsed = end - start;

        std::cout << "Quick Sort:\n";
        std::cout << "  Comparisons: " << quickCounter.comparisons << std::endl;
        std::cout << "  Swaps: " << quickCounter.swaps << std::endl;
        std::cout << "  Total Operations: " << quickCounter.getTotalOperations() << std::endl;
        std::cout << "  Time: " << elapsed.count() << " seconds\n";
        quickStats[i] = quickCounter;

        // Print sorted array for sizes 100 and 1000
        if (size <= 1000) {
            std::cout << "  Sorted elements:\n";
            printArray(arr3);

            // Save the sorted array
            saveArrayToFile(arr3, "quick_sorted_" + std::to_string(size) + ".txt");
        }

        // Verify sorting is correct
        if (verifySorting(arr1, arr2, arr3)) {
            std::cout << "Verification: All algorithms sorted correctly!\n";
        }
        else {
            std::cout << "WARNING: Sorting verification failed!\n";
        }
    }

    // Save results to CSV for easy plotting
    saveResultsToCSV(sizes, insertionStats, mergeStats, quickStats);

    // Generate GNUPlot scripts for visualization
    generateGnuplotScripts(sizes);

    // Analyze growth rates
    analyzeGrowthRates(sizes, insertionStats, mergeStats, quickStats);

    return 0;
}