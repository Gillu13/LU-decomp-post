#include <Eigen/Dense>
#include <iostream>
#include <cmath>
#include <chrono>
#include <time.h>

typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> MatrixXd;
typedef Eigen::VectorXd VectXd;


void fill_dense(int N, MatrixXd & rM, VectXd & rf){
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            rM(i,j)= 1.0*(rand() % 9 + 1);
        }
        rf(i)=1;
    }
}

int main(){
    srand(time(NULL));
    int M=710;
    auto tbegin = std::chrono::high_resolution_clock::now();
    VectXd x(M), f(M);
    MatrixXd A(M,M);
    
    fill_dense(M, A, f);
    
    x = A.lu().solve(f); 

    auto tend = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = tend-tbegin;
    std::cout << "execution time (s): " << duration.count() << std::endl;
    
    return 0;
}
