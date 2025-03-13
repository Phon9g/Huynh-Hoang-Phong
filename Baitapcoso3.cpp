#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <fstream>
using namespace std;

// Struct để lưu kết quả đếm
struct SortStats {
    long long comparisons = 0;
    long long swaps = 0;
    double time = 0.0;
};

// Hàm tạo mảng ngẫu nhiên
void generateArray(vector<int>& arr, int n) {
    arr.resize(n);
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 10000; // Số ngẫu nhiên từ 0 đến 9999
    }
}

// 1. Bubble Sort
SortStats bubbleSort(vector<int>& arr) {
    SortStats stats;
    int n = arr.size();
    clock_t start = clock();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            stats.comparisons++;
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                stats.swaps++;
            }
        }
    }
    stats.time = double(clock() - start) / CLOCKS_PER_SEC;
    return stats;
}

// 2. Selection Sort
SortStats selectionSort(vector<int>& arr) {
    SortStats stats;
    int n = arr.size();
    clock_t start = clock();
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            stats.comparisons++;
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            swap(arr[i], arr[min_idx]);
            stats.swaps++;
        }
    }
    stats.time = double(clock() - start) / CLOCKS_PER_SEC;
    return stats;
}

// 3. Insertion Sort
SortStats insertionSort(vector<int>& arr) {
    SortStats stats;
    int n = arr.size();
    clock_t start = clock();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0) {
            stats.comparisons++;
            if (arr[j] > key) {
                arr[j + 1] = arr[j];
                stats.swaps++;
                j--;
            } else {
                break;
            }
        }
        arr[j + 1] = key;
    }
    stats.time = double(clock() - start) / CLOCKS_PER_SEC;
    return stats;
}

// 4. Quick Sort
SortStats quickSort(vector<int>& arr, int low, int high) {
    SortStats stats;
    clock_t start = clock();
    if (low < high) {
        int pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; j++) {
            stats.comparisons++;
            if (arr[j] <= pivot) {
                i++;
                swap(arr[i], arr[j]);
                stats.swaps++;
            }
        }
        swap(arr[i + 1], arr[high]);
        stats.swaps++;
        int pi = i + 1;

        SortStats left = quickSort(arr, low, pi - 1);
        SortStats right = quickSort(arr, pi + 1, high);
        stats.comparisons += left.comparisons + right.comparisons;
        stats.swaps += left.swaps + right.swaps;
    }
    stats.time = double(clock() - start) / CLOCKS_PER_SEC;
    return stats;
}

// Hàm chạy thử nghiệm
void runExperiment(int t, const vector<int>& sizes) {
    ofstream out("results.txt");
    out << "Size\tAlgorithm\tAvgTime\tAvgComparisons\tAvgSwaps\n";

    for (int n : sizes) {
        cout << "Testing size n = " << n << endl;
        vector<SortStats> bubbleStats(t), selectionStats(t), insertionStats(t), quickStats(t);

        for (int trial = 0; trial < t; trial++) {
            vector<int> arr;
            generateArray(arr, n);

            // Bubble Sort
            vector<int> arrCopy = arr;
            bubbleStats[trial] = bubbleSort(arrCopy);

            // Selection Sort
            arrCopy = arr;
            selectionStats[trial] = selectionSort(arrCopy);

            // Insertion Sort
            arrCopy = arr;
            insertionStats[trial] = insertionSort(arrCopy);

            // Quick Sort
            arrCopy = arr;
            quickStats[trial] = quickSort(arrCopy, 0, n - 1);
        }

        // Tính trung bình
        auto calcAvg = [&](vector<SortStats>& stats) {
            SortStats avg;
            for (int i = 0; i < t; i++) {
                avg.time += stats[i].time;
                avg.comparisons += stats[i].comparisons;
                avg.swaps += stats[i].swaps;
            }
            avg.time /= t;
            avg.comparisons /= t;
            avg.swaps /= t;
            return avg;
        };

        SortStats avgBubble = calcAvg(bubbleStats);
        SortStats avgSelection = calcAvg(selectionStats);
        SortStats avgInsertion = calcAvg(insertionStats);
        SortStats avgQuick = calcAvg(quickStats);

        // Ghi kết quả
        out << n << "\tBubble\t" << avgBubble.time << "\t" << avgBubble.comparisons << "\t" << avgBubble.swaps << "\n";
        out << n << "\tSelection\t" << avgSelection.time << "\t" << avgSelection.comparisons << "\t" << avgSelection.swaps << "\n";
        out << n << "\tInsertion\t" << avgInsertion.time << "\t" << avgInsertion.comparisons << "\t" << avgInsertion.swaps << "\n";
        out << n << "\tQuick\t" << avgQuick.time << "\t" << avgQuick.comparisons << "\t" << avgQuick.swaps << "\n";
    }
    out.close();
    cout << "Results saved to results.txt" << endl;
}

int main() {
    srand(time(nullptr));
    int t = 5; // Số lần thử nghiệm cho mỗi kích cỡ
    vector<int> sizes = {10, 100, 200, 500, 1000, 2000, 5000, 10000};

    runExperiment(t, sizes);

    return 0;
}


/*e    Algorithm    AvgTime    AvgComparisons    AvgSwaps
10      Bubble       0.00002    45               22
10      Selection    0.000015   45               9
...
10000   Bubble       1.234      49995000         25000000
10000   Quick        0.015      132877           50000
