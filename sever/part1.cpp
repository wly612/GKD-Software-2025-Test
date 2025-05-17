#include"part1.h"
#include<vector>
#include<cmath>
#include<iostream>
template std::vector<std::vector<float>> matrix<float>::add(amatrix<float> ,amatrix<float>);
template std::vector<std::vector<float>> matrix<float>::mutiply(amatrix<float> ,amatrix<float> );
template std::vector<std::vector<float>> relu(amatrix<float> );
template std::vector<float> softmax(std::vector<float> );
/*拥有forward方法，传入1 * 784的矩阵，返回长为10的向量

先将输入矩阵和weight1做矩阵乘法，得到长宽为1 * 500的临时矩阵

再和bias1做加法（逐元素相加），得到长宽为1 * 500的临时矩阵

经过relu函数，得到长宽为1 * 500的临时矩阵

再和weight2做矩阵乘法，得到1 * 10的临时矩阵

再和bias2做矩阵加法，得到1 * 10的矩阵

最后经过softmax函数，返回长为10的向量

用公式描述则是： softmax(relu(x * w1 + b1) * w2 + b2)*/
template std::vector<float> model<float>::forward(amatrix<float> );
template std::vector<double> model<double>::forward(amatrix<double> );