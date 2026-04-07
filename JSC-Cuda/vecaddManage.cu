#include <cuda_device_runtime_api.h>
#include <cuda_runtime.h>

#include <iostream>
#define N 10000

#define CUDA_CHECK(call) \
    if ((call) != cudaSuccess) { \
        std::cerr << "CUDA error: " << cudaGetErrorString(cudaGetLastError()) \
                  << " at line " << __LINE__ << std::endl; \
        exit(1); \
    }

__global__ void vecAdd(const double* a, const double* b, double* c,
                       const int n) {
    int idx = blockDim.x * blockIdx.x + threadIdx.x;
    if (idx < n) {
        c[idx] = a[idx] + b[idx];
    }
}

int main(int args, char* argv[]) {
    
    
    double* a ;
    double* b ;
    double* c ;
    size_t size = N*sizeof(double);
    CUDA_CHECK(cudaMallocManaged(&a, size));
    CUDA_CHECK(cudaMallocManaged(&b, size));
    CUDA_CHECK(cudaMallocManaged(&c, size));
    cudaMemLocation location = {.type = cudaMemLocationTypeHost};
    cudaMemPrefetchAsync((void *)a, size, location, 0 );
    cudaMemPrefetchAsync((void *)b, size, location, 0 );
    

#pragma omp parallel for
    for (int i = 0; i < N; ++i) {
        a[i] = 0.5;
        b[i] = 1.5;
    }

    // double *da, *db, *dc;

    // cudaMalloc((void**)&da, N * sizeof(double));
    // cudaMalloc((void**)&db, N * sizeof(double));
    // cudaMalloc((void**)&dc, N * sizeof(double));
    // cudaMemcpy(da, ha, N * sizeof(double), cudaMemcpyHostToDevice);
    // cudaMemcpy(db, hb, N * sizeof(double), cudaMemcpyHostToDevice);

    const int threads_per_block = 256;
    int blocks_per_grid = (N + threads_per_block - 1) / threads_per_block;
    dim3 grids(blocks_per_grid, 1, 1);
    dim3 blocks(threads_per_block, 1, 1);

    vecAdd<<<grids, blocks>>>(a, b, c, N);
    CUDA_CHECK(cudaDeviceSynchronize());

    double sum{0.0};
    for (int i = 0; i < N; ++i) {
        sum += c[i];
    }

    std::cout << sum << " and " << N * 2.0 << std::endl;

    CUDA_CHECK(cudaFree(a));
    CUDA_CHECK(cudaFree(b));
    CUDA_CHECK(cudaFree(c));
}