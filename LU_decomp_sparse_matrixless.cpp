#include <iostream>
#include <chrono>


void lu_factorization(int N, double * pa, double * pb, double * pc){
    pc[0]=pc[0]/pb[0];
    pb[0]=pb[0];
    for(int i=1; i<=N; i++){
        pb[i]=pb[i]-pa[i]*pc[i-1];
        pc[i]=pc[i]/pb[i];
    }
}

void forward(int N, double * pa, double * pb, double * pf){
    pf[0]=pf[0]/pb[0];
    for(int i=1; i<=N; i++){
        pf[i]=(pf[i]-pa[i]*pf[i-1])/pb[i];
    }
}

void backward(int N, double * pc, double * pf){
    for(int i=N-1; i>=0; i--){
        pf[i]=pf[i]-pc[i]*pf[i+1];
    }
}

int main(){
    int M=1500;
    std::cout << "Matrix size M: " << M << std::endl;
    srand(time(NULL));
    
    auto tbegin = std::chrono::high_resolution_clock::now();
    double * a = new double[M+1];
    double * b = new double[M+1];
    double * c = new double[M+1];
    double * f = new double[M+1];
    
    a[0]=0.0;
    for(int i=1; i<=M; i++){
        a[i]=-1.;
    }
    
    b[M]=1.0;
    for(int i=0; i<M; i++){
        b[i]=rand() % 9 + 1;
    }
    
    c[M]=0.0;
    for(int i=0; i<M; i++){
        c[i]=-1.;
    }
    
    f[0]=1.0;
    for(int i=1; i<=M; i++){
        f[i]=0.;
    }
    
    lu_factorization(M, a, b, c);
    forward(M, a, b,f);
    backward(M, c, f);
    /*
    for(int i=0; i<=M;i++){
        std::cout << "x[" << i << "]=" << f[i] << std::endl;
    }
    */
    
    auto tend = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = tend-tbegin;
    std::cout << "execution time (s): " << duration.count() << std::endl;
    return 0;
}
 
