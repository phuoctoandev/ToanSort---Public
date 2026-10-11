// pt_algorithm.h
#pragma once
#ifndef PT_ALGORITHM_H
#define PT_ALGORITHM_H

#include <vector>
#include <unordered_map>

namespace pt {

    enum Region {
        LEFT,
        MID,
        RIGHT
    };

    // --- Sorting ---
    void sort(std::vector<int>& arr);

    // --- Searching ---
    Region locate(int value, int pivot_a, int pivot_b);
    int linear_find(const std::vector<int>& arr, int target);
    int binary_find(const std::vector<int>& arr, int target);
    int lower_bound(const std::vector<int>& arr, int target);
    int upper_bound(const std::vector<int>& arr, int target);

    // --- Filtering & Stats ---
    std::vector<int> filter_range(const std::vector<int>& arr, int low, int high);
    std::vector<int> top_k(std::vector<int> arr, int k, bool max_first = true);
    std::vector<int> unique(std::vector<int> arr);
    int count(const std::vector<int>& arr, int target);
    std::unordered_map<int, int> count_all(const std::vector<int>& arr);
    std::unordered_map<int, std::vector<int>> index_all(const std::vector<int>& arr);

    // --- Database struct ---
    struct Database {
        std::vector<int> data;

        void insert(int value);
        void insert_many(const std::vector<int>& values);
        void sort();

        int binary_find(int target) const;
        int linear_find(int target) const;

        std::vector<int> top_k(int k, bool max_first = true) const;
        std::vector<int> range(int low, int high) const;
        std::vector<int> unique() const;
        std::unordered_map<int, int> count_all() const;
        std::unordered_map<int, std::vector<int>> index_all() const;
    };

} // namespace pt

#endif // PT_ALGORITHM_H
