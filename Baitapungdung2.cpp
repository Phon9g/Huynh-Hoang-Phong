#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// a. Định nghĩa cấu trúc dữ liệu cho số hạng
struct Term {
    double coefficient; // Hệ số - số thực
    int degree;         // Bậc - số nguyên từ 0 đến 100

    // Constructor để khởi tạo
    Term(double coef = 0.0, int deg = 0) : coefficient(coef), degree(deg) {
        if (deg < 0 || deg > 100) {
            throw invalid_argument("Bac phai nam trong khoang 0 den 100");
        }
    }
};

// Hàm in một số hạng
void printTerm(const Term& t) {
    cout << t.coefficient << "x^" << t.degree;
}

// Hàm in toàn bộ dãy
void printPolynomial(const vector<Term>& poly) {
    if (poly.empty()) {
        cout << "Day trong" << endl;
        return;
    }
    for (size_t i = 0; i < poly.size(); i++) {
        printTerm(poly[i]);
        if (i < poly.size() - 1) cout << " + ";
    }
    cout << endl;
}

// b. Thuật toán sắp xếp tăng dần theo bậc (sử dụng Quick Sort)
int partition(vector<Term>& arr, int low, int high) {
    int pivot = arr[high].degree;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j].degree <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<Term>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Hàm sắp xếp dãy theo bậc
void sortByDegree(vector<Term>& poly) {
    quickSort(poly, 0, poly.size() - 1);
}

int main() {
    int n;
    cout << "Nhap so luong so hang n: ";
    cin >> n;

    vector<Term> polynomial;
    polynomial.reserve(n); // Đặt trước dung lượng để tối ưu

    cout << "Nhap " << n << " so hang (he so va bac):\n";
    for (int i = 0; i < n; i++) {
        double coef;
        int deg;
        cout << "So hang " << i + 1 << ":\n";
        cout << "He so: ";
        cin >> coef;
        cout << "Bac: ";
        cin >> deg;
        try {
            polynomial.emplace_back(coef, deg);
        } catch (const invalid_argument& e) {
            cout << e.what() << endl;
            i--; // Nhập lại số hạng này
        }
    }

    cout << "\nDay truoc khi sap xep:\n";
    printPolynomial(polynomial);

    // Sắp xếp theo bậc
    sortByDegree(polynomial);

    cout << "\nDay sau khi sap xep theo bac tang dan:\n";
    printPolynomial(polynomial);

    return 0;
}
/*
Nhap so luong so hang n: 5
Nhap 5 so hang (he so va bac):
So hang 1:
He so: 2.5
Bac: 3
So hang 2:
He so: -1.0
Bac: 0
So hang 3:
He so: 3.7
Bac: 5
So hang 4:
He so: 0.8
Bac: 2
So hang 5:
He so: -4.2
Bac: 1