#include <iostream>
#include "utils/headers/math_functions.h"

int main() {
    checkSmooth(quad, "quad", -10, 10, 1000);
    checkSmooth(absFunc, "absFunc", -10, 10, 1000, 0.05);  // ����absFunc�����Գ���ʹ�ø�С����ֵ
    checkSmooth(piecewise, "piecewise", -10, 10, 1000);

    std::cin.get();

    return 0;
}