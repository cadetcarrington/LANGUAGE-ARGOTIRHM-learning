# dgemm_test

请优先运行 `M=1024` 的算例；当 `M=1024` 已经通过并且耗时满足要求后，再运行 `M=4096`。

## Optimized DGEMM versions

矩阵布局保持原始代码不变：

- `A`: `M x N`, row-major
- `B`: `N x M`, row-major
- `res`: `M x M`, row-major
- 最终结果仍为 `res = A * B + C`

四份 DGEMM 优化代码：

- `dgemm_versions/dgemm_simd.cpp`: 单线程版本，B 转置打包 + 4x4 寄存器分块 + 循环展开 + SIMD/FMA 路径
- `dgemm_versions/dgemm_openmp.cpp`: 多线程 OpenMP 版本，外层 block 并行 + SIMD/FMA kernel
- `dgemm_versions/dgemm_mpi.cpp`: MPI 版本，按行分块 scatter/gather，广播 B，每个 rank 计算本地行块
- `dgemm_versions/dgemm_cuda.cu`: CUDA 版本，16x16 shared-memory tiled DGEMM，V100 原生 `sm_70`，并保留 `compute_70` PTX 以兼容 H100 等更新 GPU

现有 `./matmul_main 1024|4096` 已改为调用 OpenMP 优化 DGEMM。

## Build

默认只构建 CPU 目标，避免没有 MPI/CUDA 环境时失败：

```bash
make clean
make
```

可选目标：

```bash
make mpi
make cuda
make all-optional
```

## Run

```bash
./matmul_main 1024
./dgemm_simd 1024
OMP_NUM_THREADS=32 ./dgemm_openmp 1024
mpirun -np 4 ./dgemm_mpi 1024
./dgemm_cuda 1024
```

`4096` 算例：

```bash
OMP_NUM_THREADS=32 ./matmul_main 4096
OMP_NUM_THREADS=32 ./dgemm_openmp 4096
mpirun -np 4 ./dgemm_mpi 4096
./dgemm_cuda 4096
```
