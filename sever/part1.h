#pragma once
#include<iostream>
#include<vector>
#include<thread>
#include<cmath>
#include<mutex>
template <typename T>
class amatrix{
    public:
    int x=0;
    int y=0;
    std::vector<std::vector<T>> Matrix;
    amatrix(){};
    amatrix(int rows,int cols):x(rows),y(cols),Matrix(x,std::vector<T>(y,0.0f)){};
    ~amatrix(){};
};
//元素类型为float，支持动态加载矩阵和确定矩阵大小，以及矩阵的乘法与加法，矩阵乘法使用常规的O(n^3)复杂度实现即可
template <typename T>
class matrix{
    public:
    std::vector<std::vector<T>> add(amatrix<T> matrix1,amatrix<T> matrix2){
        std::vector<std::thread> threads;
        amatrix<T> matrix3(matrix1.x, matrix1.y);
        const int num_threads = std::thread::hardware_concurrency();
        auto worker = [&](int start_row,int end_row) {
            for(int i=start_row;i<end_row;i++){
                for(int j=0;j<matrix2.y;j++){
                    matrix3.Matrix[i][j]=matrix1.Matrix[i][j]+matrix2.Matrix[i][j];
                }
            }
        };
        int rows_per_thread = matrix1.x / num_threads;
        for(int i = 0; i < num_threads; ++i) {
            int start_row = i * rows_per_thread;
            int end_row = (i == num_threads - 1) ? matrix1.x : (i + 1) * rows_per_thread;
            threads.emplace_back(worker, start_row, end_row);
        }
        for(auto& t : threads){
                t.join();
            }
            return matrix3.Matrix;
        }   
    std::vector<std::vector<T>> mutiply(amatrix<T> matrix1,amatrix<T> matrix2){
        std::vector<std::thread> threads;
        amatrix<T> matrix3(matrix1.x, matrix2.y);
        const int num_threads = std::thread::hardware_concurrency();
        auto worker = [&](int start_row,int end_row) {
        for(int i=start_row;i<end_row;i++){
            for(int j=0;j<matrix2.y;j++){
                for(int a=0;a<matrix1.y;a++){
                matrix3.Matrix[i][j]+=matrix1.Matrix[i][a]*matrix2.Matrix[a][j];
                }
        }
    }
};
    int rows_per_thread = matrix1.x / num_threads;
    for(int i = 0; i < num_threads; ++i) {
        int start_row = i * rows_per_thread;
        int end_row = (i == num_threads - 1) ? matrix1.x : (i + 1) * rows_per_thread;
        threads.emplace_back(worker, start_row, end_row);
    }
    for(auto& t : threads){
            t.join();
        }
    return matrix3.Matrix;
}

};
//参数是一个矩阵，返回也是一个矩阵，对于这个矩阵的每一个元素，如果其大于0，则不变，如果小于0，则变为0。简单的说就是对矩阵的每一个元素和0取max

template <typename T>
std::vector<std::vector<T>> relu(amatrix<T> a){
    std::vector<std::thread> threads;
    amatrix<T> matrix(a.x, a.y);
    const int num_threads = std::thread::hardware_concurrency();
    auto worker = [&](int start_row,int end_row) {
    for(int i=start_row;i<end_row;i++){
        for(int j=0;j<a.y;j++){
            if(a.Matrix[i][j]<0){
                matrix.Matrix[i][j]=0;
            }
            else{
                matrix.Matrix[i][j]=a.Matrix[i][j];
            }
    }
    }
};
    int rows_per_thread = a.x / num_threads;
    for(int i = 0; i < num_threads; ++i) {
        int start_row = i * rows_per_thread;
        int end_row = (i == num_threads - 1) ? a.x : (i + 1) * rows_per_thread;
        threads.emplace_back(worker, start_row, end_row);
    }
    for(auto& t : threads){
            t.join();
        }
    return matrix.Matrix;
}
//输入是一个向量（你可以用行/列为一的矩阵做也可以用std::vector做），返回也是向量。![](imgs/image.png)
template <typename T>
std::vector<T> softmax(std::vector<T> a){
    std::vector<T> x(a.size());
    T b=0;
    for(int i=0;i<a.size();i++){
        b+=std::exp(a[i]);
    }
    for(int i=0;i<a.size();i++){
        x[i]=std::exp(a[i])/b;
    }
    
    return x;
}
//model类
template <typename T>
class modelbase{
    public:
    amatrix<T> weight1,bias1,weight2,bias2,a;
    modelbase():weight1(784,500),bias1(1,500),weight2(500,10),bias2(1,10),a(1,784){}
    virtual ~modelbase()=default;
    virtual std::vector<T> forward(amatrix<T> a)=0;
};
template <typename T>
class model:public modelbase<T>{
    public:
    model(){};
    
    std::vector<T> forward(amatrix<T> a) override{
        matrix<T> anewculculate;
        
        amatrix<T> x(a.x, this->weight1.y);
        amatrix<T> y(a.x, this->weight1.y);
        amatrix<T> h(a.x, this->weight1.y);
        amatrix<T> z(a.x, this->weight2.y);
        amatrix<T> u(a.x, this->weight2.y);
        
        x.Matrix = anewculculate.template mutiply(a, this->weight1);
        y.Matrix = anewculculate.template add(x, this->bias1);
        h.Matrix = relu<T>(y);
        z.Matrix = anewculculate.template mutiply(h, this->weight2);
        u.Matrix = anewculculate.template add(z, this->bias2);
        
        std::vector<T> q(10);
        for(int i=0;i<10;i++){
            q[i] = u.Matrix[0][i];
        }
        
        return softmax(q);
    }
};
