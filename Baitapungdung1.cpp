#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Hàm kiểm tra số nguyên tố
bool isPrime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

// Hàm tính tổng các chữ số của một số
int sumOfDigits(int n) {
    int sum = 0;
    n = abs(n); // Xử lý số âm
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

// a. Tìm vị trí của k phần tử lớn nhất
vector<int> findKMaxPositions(vector<int>& arr, int k) {
    int n = arr.size();
    vector<pair<int, int>> valueIndex(n); // Lưu giá trị và chỉ số gốc
    for (int i = 0; i < n; i++) {
        valueIndex[i] = {arr[i], i};
    }
    
    // Sắp xếp giảm dần theo giá trị
    sort(valueIndex.begin(), valueIndex.end(), greater<pair<int, int>>());
    
    // Lấy k vị trí đầu
    vector<int> positions;
    for (int i = 0; i < min(k, n); i++) {
        positions.push_back(valueIndex[i].second);
    }
    return positions;
}

// b. Sắp xếp tăng dần theo tổng các chữ số
void sortBySumOfDigits(vector<int>& arr) {
    sort(arr.begin(), arr.end(), [](int a, int b) {
        int sumA = sumOfDigits(a);
        int sumB = sumOfDigits(b);
        if (sumA == sumB) return a < b; // Nếu tổng bằng nhau, so sánh giá trị gốc
        return sumA < sumB;
    });
}

// c. Xóa các số nguyên tố
void removePrimes(vector<int>& arr) {
    arr.erase(remove_if(arr.begin(), arr.end(), isPrime), arr.end());
}

// Hàm in mảng
void printArray(const vector<int>& arr) {
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;
}

int main() {
    int n, k;
    cout << "Nhap so phan tu n: ";
    cin >> n;
    cout << "Nhap so luong phan tu lon nhat can tim k: ";
    cin >> k;

    vector<int> arr(n);
    cout << "Nhap " << n << " so nguyen:\n";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // a. Vị trí của k phần tử lớn nhất
    cout << "a. Vi tri cua " << k << " phan tu lon nhat:\n";
    vector<int> positions = findKMaxPositions(arr, k);
    for (int pos : positions) {
        cout << pos << " ";
    }
    cout << endl;

    // b. Sắp xếp theo tổng các chữ số
    cout << "b. Mang sau khi sap xep theo tong cac chu so:\n";
    sortBySumOfDigits(arr);
    printArray(arr);

    // c. Xóa các số nguyên tố
    cout << "c. Mang sau khi xoa cac so nguyen to:\n";
    removePrimes(arr);
    printArray(arr);

    return 0;
}

/*Nhap so phan tu n: 6
Nhap so luong phan tu lon nhat can tim k: 2
Nhap 6 so nguyen:
-10 25 13 98 7 100
a. Vi tri cua 2 phan tu lon nhat:
5 3
b. Mang sau khi sap xep theo tong cac chu so:
-10 100 13 7 25 98
c. Mang sau khi xoa cac so nguyen to:
-10 100 25 98