#pragma once
#include "part1.h"
#include <iostream>
#include <string>
#include <fstream>
template <typename T>
modelbase<T> *read(std::string a)
{
    if (a == "mnist-fc")
    {
        modelbase<T> *model1 = new model<T>();
        if (!model1)
        {
            std::cerr << "Error: read<T>(a) failed!" << std::endl;
            return nullptr;
        }
        std::fstream file1("/home/wly/text/sever/mnist-fc/fc1.weight", std::ios::in | std::ios::binary);
        if (!file1.is_open())
        {
            std::cout << "cannot found" << std::endl;
            return nullptr;
        }
        for (int i = 0; i < 784; i++)
        {
            for (int j = 0; j < 500; j++)
            {
                if (!file1.read(reinterpret_cast<char *>(&model1->weight1.Matrix[i][j]), sizeof(float)))
                {
                    std::cout << "数据读取失败，可能是文件数据不足" << std::endl;
                    return nullptr;
                }
            }
        }
        file1.close();

        std::fstream file2("/home/wly/text/sever/mnist-fc//fc1.bias", std::ios::in | std::ios::binary);
        if (!file2.is_open())
        {
            std::cout << "cannot found" << std::endl;
            return nullptr;
        }
        for (int i = 0; i < 1; i++)
        {
            for (int j = 0; j < 500; j++)
            {
                if (!file2.read(reinterpret_cast<char *>(&model1->bias1.Matrix[i][j]), sizeof(float)))
                {
                    std::cout << "数据读取失败，可能是文件数据不足" << std::endl;
                    return nullptr;
                }
            }
        }
        file2.close();

        std::fstream file3("/home/wly/text/sever/mnist-fc/fc2.weight", std::ios::in | std::ios::binary);
        if (!file3.is_open())
        {
            std::cout << "cannot found" << std::endl;
            return nullptr;
        }
        for (int i = 0; i < 500; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                if (!file3.read(reinterpret_cast<char *>(&model1->weight2.Matrix[i][j]), sizeof(float)))
                {
                    std::cout << "数据读取失败，可能是文件数据不足" << std::endl;
                    return nullptr;
                }
            }
        }
        file3.close();

        std::fstream file4("/home/wly/text/sever/mnist-fc/fc2.weight", std::ios::in | std::ios::binary);
        if (!file4.is_open())
        {
            std::cout << "cannot found" << std::endl;
            return nullptr;
        }
        for (int i = 0; i < 1; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                if (!file4.read(reinterpret_cast<char *>(&model1->weight2.Matrix[i][j]), sizeof(float)))
                {
                    std::cout << "数据读取失败，可能是文件数据不足" << std::endl;
                    return nullptr;
                }
            }
        }
        file4.close();
        return model1;
    }
    if (a == "mnist-fc-plus")
    {
        modelbase<T> *model1 = new model<T>();
        if (!model1)
        {
            std::cerr << "Error: read<T>(a) failed!" << std::endl;
            return nullptr;
        }
        std::fstream file1("/home/wly/text/sever/mnist-fc-plus/fc1.weight", std::ios::in | std::ios::binary);
        if (!file1.is_open())
        {
            std::cout << "cannot found" << std::endl;
            return nullptr;
        }
        for (int i = 0; i < 784; i++)
        {
            for (int j = 0; j < 500; j++)
            {
                if (!file1.read(reinterpret_cast<char *>(&model1->weight1.Matrix[i][j]), sizeof(double)))
                {
                    std::cout << "数据读取失败，可能是文件数据不足" << std::endl;
                    return nullptr;
                }
            }
        }
        file1.close();

        std::fstream file2("/home/wly/text/sever/mnist-fc-plus/fc1.bias", std::ios::in | std::ios::binary);
        if (!file2.is_open())
        {
            std::cout << "cannot found" << std::endl;
            return nullptr;
        }
        for (int i = 0; i < 1; i++)
        {
            for (int j = 0; j < 500; j++)
            {
                if (!file2.read(reinterpret_cast<char *>(&model1->bias1.Matrix[i][j]), sizeof(double)))
                {
                    std::cout << "数据读取失败，可能是文件数据不足" << std::endl;
                    return nullptr;
                }
            }
        }
        file2.close();

        std::fstream file3("/home/wly/text/sever/mnist-fc-plus/fc2.weight", std::ios::in | std::ios::binary);
        if (!file3.is_open())
        {
            std::cout << "cannot found" << std::endl;
            return 0;
        }
        for (int i = 0; i < 500; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                if (!file3.read(reinterpret_cast<char *>(&model1->weight2.Matrix[i][j]), sizeof(double)))
                {
                    std::cout << "数据读取失败，可能是文件数据不足" << std::endl;
                    return nullptr;
                }
            }
        }
        file3.close();

        std::fstream file4("/home/wly/text/sever/mnist-fc-plus/fc2.weight", std::ios::in | std::ios::binary);
        if (!file4.is_open())
        {
            std::cout << "cannot found" << std::endl;
            return nullptr;
        }
        for (int i = 0; i < 1; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                if (!file4.read(reinterpret_cast<char *>(&model1->weight2.Matrix[i][j]), sizeof(double)))
                {
                    std::cout << "数据读取失败，可能是文件数据不足" << std::endl;
                    return nullptr;
                }
            }
        }
        file4.close();
        return model1;
    }
    return nullptr;
}
