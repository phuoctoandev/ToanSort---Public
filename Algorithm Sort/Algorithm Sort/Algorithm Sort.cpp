#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <functional>
#include "Pt.h"



// Bubble Sort (không khuyến khích dùng)
void bubble_sort(std::vector<int>& arr) {
    size_t n = arr.size();
    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < n - 1 - i; ++j)
            if (arr[j] > arr[j + 1])
                std::swap(arr[j], arr[j + 1]);
}

// Merge Sort
void merge(std::vector<int>& arr, int l, int m, int r) {
    std::vector<int> L(arr.begin() + l, arr.begin() + m + 1);
    std::vector<int> R(arr.begin() + m + 1, arr.begin() + r + 1);
    int i = 0, j = 0, k = l;
    while (i < L.size() && j < R.size())
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < L.size()) arr[k++] = L[i++];
    while (j < R.size()) arr[k++] = R[j++];
}

void merge_sort(std::vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        merge_sort(arr, l, m);
        merge_sort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// Quick Sort (chuẩn)
int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j] < pivot)
            std::swap(arr[++i], arr[j]);
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quick_sort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

bool is_sorted(const std::vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); ++i)
        if (arr[i] < arr[i - 1]) return false;
    return true;
}


void benchmark(const std::string& name, const std::vector<int>& input,
    std::function<void(std::vector<int>&)> sort_func) {
    std::vector<int> arr = input;

    auto start = std::chrono::high_resolution_clock::now();
    sort_func(arr);
    auto end = std::chrono::high_resolution_clock::now();

    double duration = std::chrono::duration<double>(end - start).count();
    bool sorted_ok = is_sorted(arr);

    std::cout << name << duration << "s | sorted = "
        << (sorted_ok ? "true ✅" : "false ❌") << "\n";
}


// ToanSort sẽ gọi từ pt::_ptsort(arr) như ông build

int main() {
    const int N = 1000000; // có thể thử 10 triệu nếu máy khỏe
    std::vector<int> original(N);
    std::mt19937 rng(42);
    std::uniform_int_distribution<int> dist(0, 1000000);

    for (int& x : original)
        x = dist(rng);

    // Test từng thuật toán



    std::cout << "---------------------------------------------------- \n";

    benchmark("std::merge: ", original, [](std::vector<int>& arr) {
        merge_sort(arr, 0, arr.size() - 1);
        });

    benchmark("Quick Sort: ", original, [](std::vector<int>& arr) {
        quick_sort(arr, 0, arr.size() - 1);
        });

    benchmark("ToanSort: ", original, pt::sort); // Gọi hàm thuật toán của ông

    benchmark("std::sort: ", original, [](std::vector<int>& arr) {
        std::sort(arr.begin(), arr.end());
        });


   





    return 0;
}
