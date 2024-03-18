#include "headers/math_functions.h"
#include <NumCpp.hpp>
#include <cmath>

double quad(double x) {
    return std::pow(x, 2);
}

double absFunc(double x) {
    return std::abs(x);
}

double piecewise(double x) {
    return x < 0 ? 2 * x : x;
}

bool isSmooth(std::function<double(double)> func, double start, double end, int numPoints, double threshold) {
    auto xs = nc::linspace<double>(start, end, numPoints); // 在指定区间内生成均匀分布的点
    double prevDerivative = (func(xs[1]) - func(xs[0])) / (xs[1] - xs[0]);

    for (int i = 1; i < xs.size() - 1; ++i) {
        double derivative = (func(xs[i + 1]) - func(xs[i])) / (xs[i + 1] - xs[i]); // 计算相邻两点间的导数
        if (std::abs(derivative - prevDerivative) > threshold) { 
            return false;
        }
        prevDerivative = derivative;
    }
    return true;
}

void checkSmooth(std::function<double(double)> func, const std::string& funcName, double start, double end, int numPoints, double threshold) {
    std::cout << "Function " << funcName << " is " << (isSmooth(func, start, end, numPoints, threshold) ? "smooth." : "not smooth.") << std::endl;
}
