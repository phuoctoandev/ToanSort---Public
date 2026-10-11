#include <vector>
#include <algorithm>
#include <cmath>

namespace pt {

    void _ptsort_recursive(std::vector<int>& arr, int a, int b, int depth = 0) {
        if (b - a <= 32) {  // đoạn nhỏ thì sort cho lẹ
            std::sort(arr.begin() + a, arr.begin() + b + 1);
            return;
        }

        int pivot_a = arr[a];
        int pivot_b = arr[b];
        int pivot_m = arr[(a + b) / 2];

        int pivot_min = std::min({ pivot_a, pivot_b, pivot_m });
        int pivot_max = std::max({ pivot_a, pivot_b, pivot_m });

        std::vector<int> mid;
        mid.reserve(b - a + 1);

        int left_idx = a;
        int right_idx = b;

        for (int i = a; i <= b; ++i) {
            int val = arr[i];
            if (val < pivot_min) {
                arr[left_idx++] = val;
            }
            else if (val > pivot_max) {
                arr[right_idx--] = val;
            }
            else {
                mid.push_back(val);
            }
        }

        // Ghi mid vào giữa
        for (int i = 0; i < mid.size(); ++i)
            arr[left_idx + i] = mid[i];

        // Đệ quy tiếp vào 3 vùng
        _ptsort_recursive(arr, a, left_idx - 1, depth + 1);
        _ptsort_recursive(arr, left_idx + mid.size(), b, depth + 1);
        _ptsort_recursive(arr, left_idx, left_idx + mid.size() - 1, depth + 1);
    }

    void ptsort(std::vector<int>& arr) {
        if (!arr.empty())
            _ptsort_recursive(arr, 0, arr.size() - 1);
    }

    // overload dạng return
    std::vector<int> _ptsort(std::vector<int> arr) {
        _ptsort(arr);
        return arr;
    }

}
