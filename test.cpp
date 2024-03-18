#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> v = { 1, 2, 4, 4, 5, 6, 7 };
    int target = 4;

    // 使用默认比较操作 (小于)
    auto it = std::upper_bound(v.begin(), v.end(), target);

    if (it != v.end()) {
        std::cout << "The first element greater than " << target << " is " << *it << std::endl;
    }
    else {
        std::cout << "No elements are greater than " << target << std::endl;
    }

    return 0;
}
