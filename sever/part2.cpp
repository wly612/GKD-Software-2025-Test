//读取mnist-fc文件夹中的四个矩阵
#include<iostream>
#include <fstream>
#include"part2.h"
template modelbase<float>* read<float>(std::string );

template modelbase<double>* read<double>(std::string  );