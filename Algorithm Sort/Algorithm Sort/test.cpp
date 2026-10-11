#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include "Pt.h" // file có _ptsort()

int main() {
    // Khởi tạo seed và engine random
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 1000); // giá trị từ 0 đến 1000

    // Tạo vector 100 số random
    std::vector<int> data(100);
    for (int& x : data) {
        x = dist(gen);
    }

    // Hiện mảng ban đầu
    std::cout << "Trước khi sort:\n";
    for (int x : data) std::cout << x << " ";
    std::cout << "\n";

    // Gọi thuật toán của ông
    pt::_ptsort(data);

    // Hiện mảng sau khi sort
    std::cout << "Sau khi sort:\n";
    for (int x : data) std::cout << x << " ";
    std::cout << "\n";

    // Kiểm tra đúng không
    bool sorted = std::is_sorted(data.begin(), data.end());
    std::cout << "✅ Sorted đúng? " << (sorted ? "YES" : "NO 😭") << "\n";

    return 0;
}
