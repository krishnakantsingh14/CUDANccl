#include<iostream>
#include<cuda_runtime.h>
#define BLOCK_SIZE 32

__global__ void matrixTranspose(double *a, double *at, int nrows) {

    int x = blockDim.y*blockIdx.y + threadIdx.y ;
    int y = blockDim.x*blockIdx.x + threadIdx.x ;
    if ((x < nrows) && (y<nrows)) {

        int input_idx = y * nrows + x;           // Row-major in input
        int output_idx = x * nrows + y;

        at[output_idx] =  a[input_idx];
    }

}


int main(int argc, char ** argv) {
    const int N {1000};
    size_t N_size = N;  // Convert to size_t first
    size_t total_elements = N_size * N_size;
    size_t alloc_size = total_elements * sizeof(double);

    // double **a = new double*[N];
    // for (int i=0; i< N; ++i ) {
    //     a[i] = new double [N]{static_cast<double>(i)};
    // }
    
    double *a; // = new double[N*N]{};
    // const int threads_per_block = 256;
    double *at; // = new double[N*N]{};
    
    cudaMallocManaged((void**)&a, alloc_size); 
    cudaMallocManaged((void**)&at, alloc_size); 
    #pragma omp parallel for 
    for (int i=0; i<total_elements; ++i) {
        a[i] = i;
    }
    
    dim3 threadsPerBlock(BLOCK_SIZE, BLOCK_SIZE, 1);
    dim3 nBlocks( (N+BLOCK_SIZE-1)/BLOCK_SIZE, (N+BLOCK_SIZE-1)/BLOCK_SIZE, 1);
    

    matrixTranspose<<<nBlocks, threadsPerBlock>>>(a, at, N);
    cudaDeviceSynchronize();
    cudaFree(a);
    cudaFree(at);

    return 0;
}