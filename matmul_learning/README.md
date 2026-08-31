# 矩阵乘法学习

DGEMM（双精度矩阵乘法）优化与 Strassen 算法的学习项目，从朴素实现逐步演进到 SIMD / OpenMP / MPI / CUDA 多个版本。

## 目录结构

| 目录 | 内容 |
|---|---|
| [Strassen/matmul/](Strassen/matmul/README.md) | **主项目**（dgemm_test）：完整的 DGEMM 优化实现，含四个版本--`dgemm_simd.cpp`（单线程 SIMD/FMA + 4x4 寄存器分块）、`dgemm_openmp.cpp`（OpenMP 多线程）、`dgemm_mpi.cpp`（MPI 按行分块）、`dgemm_cuda.cu`（CUDA 16x16 分块，V100 sm_70）。详见其 [README](Strassen/matmul/README.md) |
| `Strassen_improve/` | Strassen 算法改进版（现存编译产物 `matmul_main` 与 `.o` 文件） |
| `matmul/` | 早期版本（现存编译产物与 `.o` 文件） |
| `old_matmul/` | 旧版本，内含 `openmpi-4.1.6/` 完整源码（文件量大，是本目录的主要体积来源） |
| `dgemm.tar.gz` | 初始代码压缩包 |

## 使用（主项目）

```bash
cd Strassen/matmul
make          # 默认只构建 CPU 目标
make mpi      # 可选：构建 MPI 版本
make cuda     # 可选：构建 CUDA 版本
./matmul_main 1024   # 先跑 M=1024 算例，通过后再跑 4096
```
