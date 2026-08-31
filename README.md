# algorithm_learning

算法学习与刷题代码仓库（C / C++ 为主）。每个子目录都有自己的 README，点击目录名即可查看。

## 目录结构

| 目录 | 内容 |
|---|---|
| [算法基础课/](算法基础课/README.md) | AcWing 算法基础课学习笔记与配套习题，按章节分为 10 个文件夹（排序、二分、高精度、数据结构、搜索图论、动态规划等） |
| [acwing_training/](acwing_training/README.md) | AcWing 在线习题代码（710~801，语法课与基础课第一讲） |
| [luogu/](luogu/README.md) | 洛谷刷题代码（并查集、前缀和、差分、DFS 等，含分组练习） |
| [蓝桥/](蓝桥/README.md) | 蓝桥杯真题练习（最小字符串、数组轮盘、斐波那契字符串等） |
| [CACC/](CACC/README.md) | CACC 竞赛题目（约瑟夫环、区间操作、宝物探测） |
| [寒假作业/](寒假作业/README.md) | 寒假作业题目（L1002~L1049） |
| [C++experiment/](C++experiment/README.md) | C++ 面向对象分析与设计实验课作业（C3~C6，附实验指导书） |
| [cppsel/](cppsel/README.md) | C++ 语法专项练习 |
| [MPI_LEARNING/](MPI_LEARNING/README.md) | MPI 并行编程入门（HelloWorld + Makefile） |
| [matmul_learning/](matmul_learning/README.md) | 矩阵乘法优化：DGEMM 的 SIMD / OpenMP / MPI / CUDA 版本与 Strassen 算法（内含 openmpi-4.1.6 源码，文件较多） |

## 说明

- 各目录下的源码均以题号或题目名命名，可用 `g++ xxx.cpp -o xxx` 直接编译。
- 编译产生的二进制文件不入库：`ignore_binaries.sh` 会全量扫描文件头（Magic Number）识别二进制并写入 `.gitignore`。
- `算法基础课/` 内笔记（md）与代码（cpp）放在同一文件夹，笔记中的链接可直接跳转到对应代码。
