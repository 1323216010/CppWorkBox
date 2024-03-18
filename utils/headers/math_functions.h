
// include/math_functions.h
#ifndef MATH_FUNCTIONS_H
#define MATH_FUNCTIONS_H

#include <functional>
#include <iostream>

// º¯ÊýÉùÃ÷
double quad(double x);
double absFunc(double x);
double piecewise(double x);
bool isSmooth(std::function<double(double)> func, double start, double end, int numPoints, double threshold = 0.1);
void checkSmooth(std::function<double(double)> func, const std::string& funcName, double start, double end, int numPoints, double threshold = 0.1);

#endif // MATH_FUNCTIONS_H
