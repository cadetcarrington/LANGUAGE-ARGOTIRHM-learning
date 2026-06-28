CXX ?= g++
MPICXX ?= mpicxx
NVCC ?= nvcc

CXXFLAGS ?= -O3 -march=native -funroll-loops -fopenmp -std=c++17 -Wall -Wextra
NVCCFLAGS ?= -O3 -std=c++17 \
	-gencode arch=compute_70,code=sm_70 \
	-gencode arch=compute_70,code=compute_70

INCLUDE = -I./include

COMMON_SRC = src/file_operations.cpp src/matrix_operations.cpp src/dgemm_optimized.cpp
TARGET = matmul_main
CPU_TARGETS = dgemm_simd dgemm_openmp

.PHONY: all mpi cuda all-optional clean

all: $(TARGET) $(CPU_TARGETS)
	@echo "编译完成，默认目标: $(TARGET) $(CPU_TARGETS)"

$(TARGET): src/main.cpp $(COMMON_SRC) include/*.h
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ src/main.cpp $(COMMON_SRC)

dgemm_simd: dgemm_versions/dgemm_simd.cpp $(COMMON_SRC) include/*.h
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ dgemm_versions/dgemm_simd.cpp $(COMMON_SRC)

dgemm_openmp: dgemm_versions/dgemm_openmp.cpp $(COMMON_SRC) include/*.h
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ dgemm_versions/dgemm_openmp.cpp $(COMMON_SRC)

mpi: dgemm_mpi

dgemm_mpi: dgemm_versions/dgemm_mpi.cpp $(COMMON_SRC) include/*.h
	$(MPICXX) $(CXXFLAGS) $(INCLUDE) -o $@ dgemm_versions/dgemm_mpi.cpp $(COMMON_SRC)

cuda: dgemm_cuda

dgemm_cuda: dgemm_versions/dgemm_cuda.cu
	$(NVCC) $(NVCCFLAGS) -o $@ dgemm_versions/dgemm_cuda.cu

all-optional: all mpi cuda

clean:
	rm -f src/*.o $(TARGET) $(CPU_TARGETS) dgemm_mpi dgemm_cuda result.txt
