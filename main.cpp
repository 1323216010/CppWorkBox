#include <iostream>
#include "utils/headers/math_functions.h"

int main() {
    checkSmooth(quad, "quad", -10, 10, 1000);
    checkSmooth(absFunc, "absFunc", -10, 10, 1000, 0.05);  // 对于absFunc，可以尝试使用更小的阈值
    checkSmooth(piecewise, "piecewise", -10, 10, 1000);

    std::cin.get();

    return 0;
}