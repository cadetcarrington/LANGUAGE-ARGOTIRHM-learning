# MPI 并行编程入门

MPI（Message Passing Interface）并行编程的入门练习。

## 文件

- [mpihelloworld.cpp](mpihelloworld.cpp)：MPI 版 Hello World，演示 `MPI_Init` / `MPI_Comm_size`（进程总数）/ `MPI_Comm_rank`（当前进程秩）/ `MPI_Get_processor_name` / `MPI_Finalize` 的基本用法。
- [makefile](makefile)：用 `mpicxx` 编译，`make clean` 清理产物。

## 使用

```bash
make                    # 编译
mpirun -np 4 ./mpihelloworld   # 以 4 个进程运行
```
