#include <iostream>
#include <chrono>

template <size_t N>
void lu_factorization(double (&rL)[N][N], double (&rU)[N][N]){
    for (size_t n = 0; n < N; n++){
        for (size_t i = n+1; i < N; i++){
            rL[i][n]=rU[i][n]/rU[n][n];
        }
        for (size_t j = n+1; j < N; j++){
            for (size_t k = 0; k < N; k++){
                rU[j][k]=rU[j][k]-rU[n][k]*rL[j][n];
            }
        }
    }
}

template <size_t N>
void forward(double (&rL)[N][N], double (&rb)[N]){
    for(size_t i=1; i<N; i++){
        for(size_t j=0; j<i; j++){
            rb[i]=rb[i]-rb[j]*rL[i][j];
        }
    }
}

template <size_t N>
void backward(double (&rU)[N][N], double (&rb)[N]){
    rb[N-1]=rb[N-1]/(rU[N-1][N-1]);
    size_t i;
    for(size_t k=0; k<=N-2; k++){
        i=N-2-k;
        for(size_t j=i+1; j<=N-1; j++){
            rb[i]=rb[i]-rb[j]*rU[i][j];
        }
        rb[i]=rb[i]/(rU[i][i]);
    }
}

template <size_t N>
void product(double (&rA)[N][N], double (&rx)[N], double (&ry)[N]){
    for(size_t i=0; i<N; i++){
        for(size_t j=0; j<N; j++){
            ry[i]=ry[i]+rA[i][j]*rx[j];
        }
    }
}

template <size_t N>
void fill_dense(double (&rL)[N][N], double (&rU)[N][N], double (&rb)[N]){
    srand(time(NULL));
    for (size_t i=0; i<N; i++){
        for (size_t j=0; j<N; j++){
            rU[i][j]= rand() % 9 + 1;
            rL[i][j]= 0.;
        }
        rL[i][i]= 1;
        rb[i]=1;
    }
}

template <size_t N>
void fill_sparse(double (&rL)[N][N], double (&rU)[N][N], double (&rb)[N]){
    srand(time(NULL));
    for (size_t i=0; i<N; i++){
        for (size_t j=0; j<N; j++){
            rU[i][j]= 0.;
            rL[i][j]= 0.;
        }
        rL[i][i]= 1;
        rb[i]=1;
    }
    
    rU[0][0]= rand() % 9 + 1;
    rU[0][1]= -1;
    for (size_t i=1; i<N-1; i++){
        rU[i][i]= rand() % 9 + 1;
        rU[i][i+1]= -1.;
        rU[i][i-1]= -1.;
    }
    rU[N-1][N-1]= 1.;
    rU[N-1][N-2]= -1;
}

int main(){
    srand(time(NULL));
    const int M=400;
    std::cout << "Matrix size M: " << M << std::endl;
    auto tbegin = std::chrono::high_resolution_clock::now();
    double L[M][M], U[M][M], b[M];
    
    /* depending on what you want to solve (sparse or dense system)
     * (un)comment the accurate lines.
     */
    //fill_sparse(L, U, b);
    fill_dense(L, U, b);

    lu_factorization(L, U);
    forward(L, b);
    backward(U, b);
    
    auto tend = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = tend-tbegin;
    std::cout << "execution time (s): " << duration.count() << std::endl;
    return 0;
}
 
