#include<mpi.h>
#include<omp.h>
#include<iostream>
#include<vector>
#include <algorithm> // Required for ranges::fold_left
#include <numeric> // Required for std::accumulate
#include<random>
#include<cuda_runtime.h>



__global__ void vecadd(const int * __restrict__ a, const int * __restrict__ b, int *c, size_t Nelements ) {
    const int idx = blockDim.x*blockIdx.x + threadIdx.x ;
    if (idx < Nelements) {
        c[idx] = a[idx] + b[idx];
    }
}



void fillvector(std::vector<int>& vec, size_t nelements) {
    

    #pragma omp parallel 
    {
        std::default_random_engine rd{static_cast<unsigned int>(42+ omp_get_thread_num())};
        std::uniform_int_distribution gen{1,100};
     
    #pragma omp for
        for (int i=0; i<nelements; ++i) {
            // vec.push_back(static_cast<int>(gen(rd)));
            vec[i] = 1; //gen(rd);
        
        }
    }

}




int main(int argc, char * argv[]) {
    MPI_Init(&argc, &argv);
    int rank, size;

    MPI_Comm comm{MPI_COMM_WORLD}; 
    MPI_Comm_rank(comm, &rank);

    int deviceCount;
    cudaGetDeviceCount(&deviceCount);
    std::cout<<"Number of GPUs: " << deviceCount <<std::endl; 
    cudaDeviceProp prop;
    cudaGetDeviceProperties(&prop, 0);

    int dev;
    cudaGetDevice(&dev);

    // cudaDeviceProp prop;
    cudaGetDeviceProperties(&prop, dev);

    std::cout << "Rank " << rank
          << " uses GPU " << dev
          << " (" << prop.name << ")"
          << std::endl;

    std::cout << "Rank " << rank << " using GPU: " << prop.name 
          << " with PCI Bus ID: " << prop.pciBusID << std::endl;

    if (deviceCount > 0) {
        // This assigns Rank 0 to GPU 0, Rank 1 to GPU 1, etc.
        // The modulo % ensures it wraps around if you have more ranks than GPUs
        cudaSetDevice(rank % deviceCount);
    }

    MPI_Comm_size(comm, &size); 
    const size_t Nelements{10000}; 
    
    std::vector<int>local_vec_first {0}; 
    local_vec_first.resize(Nelements);

    std::vector<int>local_vec_second {0}; 
    local_vec_second.resize(Nelements);
    std::cout << "Rank: " << rank << std::endl; 
    fillvector(local_vec_first, Nelements);
    fillvector(local_vec_second, Nelements);


    int *dfirst, *dsecond, *dresult;
    cudaMalloc((void**)&dfirst, Nelements*sizeof(int)); 
    cudaMalloc((void**)&dsecond, Nelements*sizeof(int)) ;
    cudaMalloc((void**)&dresult, Nelements*sizeof(int)) ;

    cudaMemcpy(dfirst, local_vec_first.data(), Nelements*sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(dsecond, local_vec_second.data(), Nelements*sizeof(int), cudaMemcpyHostToDevice);
    const int threadsPerBlock {1024};
    const int nblocks = (Nelements + threadsPerBlock - 1) / threadsPerBlock;
    // const int nblocks { (Nelements/1024) +1 };
    vecadd<<<nblocks, threadsPerBlock>>>(dfirst, dsecond, dresult, Nelements);
    
    cudaDeviceSynchronize();
    std::vector<int>results {0}; 
    results.resize(Nelements);
    cudaMemcpy(results.data(), dresult, Nelements*sizeof(int), cudaMemcpyDeviceToHost);
    cudaFree(dfirst);
    cudaFree(dsecond);
    
    std::vector<int>global_sum ( Nelements, 0);
    // std::vector<int>global_sum {0}; 
    // global_sum.resize(Nelements)
    bool OnlyHost {false} ;
    if (OnlyHost) {
        
        MPI_Reduce(results.data(), global_sum.data(), Nelements, MPI_INT, MPI_SUM, 0, comm);
    }
    else {
        
        int *gs {nullptr};
        if (rank==0) {
            cudaMalloc((void **)&gs, Nelements*sizeof(int) );
        }
        MPI_Reduce(dresult, gs, Nelements, MPI_INT, MPI_SUM, 0, comm);
        cudaMemcpy(global_sum.data(), gs, Nelements*sizeof(int), cudaMemcpyDeviceToHost );
        cudaFree(gs);

    }


    if (rank==0) {
        std::cout << std::accumulate(global_sum.begin(), global_sum.end(), 0 ) << std::endl;
    }
    
    cudaFree(dresult);
    
    // if (rank == 0) {        

    // }
    // cudaFree();
    MPI_Finalize();

}
