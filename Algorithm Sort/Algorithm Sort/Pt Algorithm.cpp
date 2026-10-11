// pt_algorithm.cpp
#include "Pt.h"
#include <algorithm>
#include <future>
#include <unordered_map>
#include <set>
#include <map>
#include <numeric>

namespace pt {

    constexpr int INSERTION_SORT_THRESHOLD = 32;

    int partition(std::vector<int>& arr, int low, int high) {
        int pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; ++j) {
            if (arr[j] < pivot) {
                std::swap(arr[++i], arr[j]);
            }
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

    void sort(std::vector<int>& arr) {
        if (arr.empty()) return;
        int size = arr.size();

        if (size <= INSERTION_SORT_THRESHOLD) {
            quick_sort(arr, 0, size - 1);
            return;
        }

        int pivot_a = arr[0];
        int pivot_b = arr[size - 1];
        int pivot_m = arr[size / 2];
        int pivot_min = std::min({ pivot_a, pivot_b, pivot_m });
        int pivot_max = std::max({ pivot_a, pivot_b, pivot_m });

        if (pivot_min == pivot_max) {
            quick_sort(arr, 0, size - 1);
            return;
        }

        std::vector<int> left, mid, right;
        left.reserve(size);
        mid.reserve(size);
        right.reserve(size);

        for (int v : arr) {
            if (v < pivot_min) left.push_back(v);
            else if (v > pivot_max) right.push_back(v);
            else mid.push_back(v);
        }

        bool use_async = size > 50000;

        if (use_async) {
            auto left_future = std::async(std::launch::async, [&]() {
                quick_sort(left, 0, left.size() - 1);
                });
            auto right_future = std::async(std::launch::async, [&]() {
                quick_sort(right, 0, right.size() - 1);
                });
            quick_sort(mid, 0, mid.size() - 1);
            left_future.wait();
            right_future.wait();
        }
        else {
            quick_sort(left, 0, left.size() - 1);
            quick_sort(mid, 0, mid.size() - 1);
            quick_sort(right, 0, right.size() - 1);
        }

        arr.clear();
        arr.insert(arr.end(), left.begin(), left.end());
        arr.insert(arr.end(), mid.begin(), mid.end());
        arr.insert(arr.end(), right.begin(), right.end());
    }

    Region locate(int value, int pivot_a, int pivot_b) {
        if (value < pivot_a) return LEFT;
        if (value > pivot_b) return RIGHT;
        return MID;
    }

    int linear_find(const std::vector<int>& arr, int target) {
        if (arr.empty()) return -1;
        int a = 0, b = arr.size() - 1;
        while (a <= b) {
            int pivot_a = arr[a], pivot_b = arr[b];
            Region region = locate(target, pivot_a, pivot_b);
            if (region == LEFT) b = a + (b - a) / 3;
            else if (region == RIGHT) a = b - (b - a) / 3;
            else {
                for (int i = a; i <= b; ++i)
                    if (arr[i] == target) return i;
                return -1;
            }
        }
        return -1;
    }

    int binary_find(const std::vector<int>& arr, int target) {
        int left = 0, right = arr.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] == target) return mid;
            else if (arr[mid] < target) left = mid + 1;
            else right = mid - 1;
        }
        return -1;
    }

    int lower_bound(const std::vector<int>& arr, int target) {
        int left = 0, right = arr.size();
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] < target) left = mid + 1;
            else right = mid;
        }
        return (left < arr.size()) ? left : -1;
    }

    int upper_bound(const std::vector<int>& arr, int target) {
        int left = 0, right = arr.size();
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] <= target) left = mid + 1;
            else right = mid;
        }
        return (left < arr.size()) ? left : -1;
    }

    std::vector<int> filter_range(const std::vector<int>& arr, int low, int high) {
        std::vector<int> result;
        for (int v : arr)
            if (v >= low && v <= high)
                result.push_back(v);
        return result;
    }

    std::vector<int> top_k(std::vector<int> arr, int k, bool max_first) {
        std::sort(arr.begin(), arr.end(), [=](int a, int b) {
            return max_first ? a > b : a < b;
            });
        if (k > arr.size()) k = arr.size();
        return std::vector<int>(arr.begin(), arr.begin() + k);
    }

    std::vector<int> unique(std::vector<int> arr) {
        std::sort(arr.begin(), arr.end());
        arr.erase(std::unique(arr.begin(), arr.end()), arr.end());
        return arr;
    }

    int count(const std::vector<int>& arr, int target) {
        return std::count(arr.begin(), arr.end(), target);
    }

    std::unordered_map<int, int> count_all(const std::vector<int>& arr) {
        std::unordered_map<int, int> freq;
        for (int v : arr) ++freq[v];
        return freq;
    }

    std::unordered_map<int, std::vector<int>> index_all(const std::vector<int>& arr) {
        std::unordered_map<int, std::vector<int>> index;
        for (size_t i = 0; i < arr.size(); ++i) {
            index[arr[i]].push_back(i);
        }
        return index;
    }

    void Database::insert(int value) {
        data.push_back(value);
    }

    void Database::insert_many(const std::vector<int>& values) {
        data.insert(data.end(), values.begin(), values.end());
    }

    void Database::sort() {
        pt::sort(data);
    }

    int Database::binary_find(int target) const {
        return pt::binary_find(data, target);
    }

    int Database::linear_find(int target) const {
        return pt::linear_find(data, target);
    }

    std::vector<int> Database::top_k(int k, bool max_first) const {
        return pt::top_k(data, k, max_first);
    }

    std::vector<int> Database::range(int low, int high) const {
        return pt::filter_range(data, low, high);
    }

    std::vector<int> Database::unique() const {
        return pt::unique(data);
    }

    std::unordered_map<int, int> Database::count_all() const {
        return pt::count_all(data);
    }

    std::unordered_map<int, std::vector<int>> Database::index_all() const {
        return pt::index_all(data);
    }

} // namespace pt