#include <cuda_device_runtime_api.h>
#include <cuda_runtime.h>

#include <iostream>
#define N 10000

__global__ void vecAdd(const double* a, const double* b, double* c,
                       const int n) {
    int idx = blockDim.x * blockIdx.x + threadIdx.x;
    if (idx < n) {
        c[idx] = a[idx] + b[idx];
    }
}

int main(int argc, char* argv[]) {
    double* ha = new double[N];
    double* hb = new double[N];
    double* hc = new double[N];

#pragma omp parallel for
    for (int i = 0; i < N; ++i) {
        ha[i] = 0.5;
        hb[i] = 1.5;
    }

    double *da, *db, *dc;
    cudaMalloc((void**)&da, N * sizeof(double));
    cudaMalloc((void**)&db, N * sizeof(double));
    cudaMalloc((void**)&dc, N * sizeof(double));
    cudaMemcpy(da, ha, N * sizeof(double), cudaMemcpyHostToDevice);
    cudaMemcpy(db, hb, N * sizeof(double), cudaMemcpyHostToDevice);

    const int threads_per_block = 256;
    int blocks_per_grid = (N + threads_per_block - 1) / threads_per_block;
    dim3 grids(blocks_per_grid, 1, 1);
    dim3 blocks(threads_per_block, 1, 1);

    vecAdd<<<grids, blocks>>>(da, db, dc, N);
    cudaDeviceSynchronize();
    cudaMemcpy(hc, dc, N * sizeof(double), cudaMemcpyDeviceToHost);
    double sum{0.0};
    for (int i = 0; i < N; ++i) {
        sum += hc[i];
    }
    // if (sum==2*N) {
    std::cout << sum << " and " << N * 2.0 << std::endl;
    // }
    delete[] ha;
    delete[] hb;
    delete[] hc;
    cudaFree(da);
    cudaFree(db);
    cudaFree(dc);
}