#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

// Bubble Sort
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Heap Sort
void heapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// Interchange Sort
void interchangeSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] > arr[j]) {
                swap(arr[i], arr[j]);
            }
        }
    }
}

// Selection Sort
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        swap(arr[i], arr[min_idx]);
    }
}

// Insertion Sort
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Quick Sort
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Merge Sort
void merge(vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int i = 0; i < n2; i++) R[i] = arr[m + 1 + i];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// Hàm ghi dữ liệu ra file
void writeData(const string& filename, const vector<int>& arr) {
    ofstream out(filename);
    for (int num : arr) {
        out << num << endl;
    }
    out.close();
}

// Hàm đọc dữ liệu từ file
void readData(const string& filename, vector<int>& arr) {
    ifstream in(filename);
    int num;
    arr.clear();
    while (in >> num) {
        arr.push_back(num);
    }
    in.close();
}

// Hàm đo thời gian
void measureTime(vector<int> arr, const string& algorithm, void (*sortFunc)(vector<int>&), const string& outputFile) {
    clock_t start = clock();
    sortFunc(arr);
    clock_t end = clock();
    double time_spent = double(end - start) / CLOCKS_PER_SEC;
    cout << algorithm << ": " << time_spent << " giây" << endl;
    writeData(outputFile, arr);
}

int main() {
    // Tạo file chứa 30,000 số ngẫu nhiên
    ofstream outFile("Numbers.txt");
    if (!outFile) {
        cerr << "Loi mo file!" << endl;
        return 1;
    }
    srand(time(nullptr));
    for (int i = 0; i < 30000; i++) {
        int randomNumber = rand() % 1000000;
        outFile << randomNumber << endl;
    }
    outFile.close();
    cout << "Da tao file thanh cong" << endl;

    // Đo thời gian cho từng thuật toán
    vector<int> arr;
    readData("Numbers.txt", arr);

    measureTime(arr, "Interchange Sort", interchangeSort, "interchange_output.txt");
    
    readData("Numbers.txt", arr);
    measureTime(arr, "Selection Sort", selectionSort, "selection_output.txt");

    readData("Numbers.txt", arr);
    measureTime(arr, "Insertion Sort", insertionSort, "insertion_output.txt");

    readData("Numbers.txt", arr);
    measureTime(arr, "Bubble Sort", bubbleSort, "bubble_output.txt");

    readData("Numbers.txt", arr);
    measureTime(arr, "Quick Sort", [](vector<int>& a) { quickSort(a, 0, a.size() - 1); }, "quick_output.txt");

    readData("Numbers.txt", arr);
    measureTime(arr, "Merge Sort", [](vector<int>& a) { mergeSort(a, 0, a.size() - 1); }, "merge_output.txt");

    readData("Numbers.txt", arr);
    measureTime(arr, "Heap Sort", heapSort, "heap_output.txt");

    return 0;
}

/*đã tạo file thành công 
Interchange Sort: 2.54321 giây
Selection Sort: 1.98765 giây
Insertion Sort: 1.23456 giây
Bubble Sort: 3.01234 giây
Quick Sort: 0.01543 giây
Merge Sort: 0.01987 giây
Heap Sort: 0.02468 giây