#include <Eigen/Sparse>
#include <iostream>
#include <cmath>
#include <chrono>
#include <time.h>

typedef Eigen::SparseMatrix<double> SpMat;
typedef Eigen::VectorXd VectXd;


void fill_sparse(int N, SpMat & rM, VectXd & rf){
    srand(time(NULL));
    rM.coeffRef(0,0) = rand() % 9 + 1;
    rM.coeffRef(0,1) = -1.0;
    for(int i=1; i<N-1; i++){
        rM.coeffRef(i,i) = rand() % 9 + 1;
        rM.coeffRef(i,i-1) =-1.0;
        rM.coeffRef(i,i+1) =-1.0;
    }
    rM.coeffRef(N-1,N-2) =-1.0;
    rM.coeffRef(N-1,N-1) =1.0;
    
    rf[0] = 1;
}

int main(){
    srand(time(NULL));
    int M=710;
    auto tbegin = std::chrono::high_resolution_clock::now();

    SpMat A(M,M);
    VectXd f(M), x(M);
    
    fill_sparse(M, A, f);

    Eigen::SparseLU<SpMat, Eigen::COLAMDOrdering<int> > solver;
    
    solver.analyzePattern(A); 
    solver.factorize(A); 
    x = solver.solve(f);
    
    auto tend = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = tend-tbegin;
    std::cout << "execution time (s): " << duration.count() << std::endl;
    return 0;
}
 
