#include <mpi.h>
#include <cstdio>

using namespace std;

int main (int argc, char ** argv){
    //初始化 MPI 环境
    MPI_Init(NULL, NULL);

    // 通过调用以下方法来得到所有可以工作的进程数量
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // 得到当前进程的秩
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // 得到当前进程的名字
    char prcessname[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(prcessname, &name_len);

    // 打印一条带有当前进程名字，秩以及整个 communicator 的大小的 hello world 消息。 
    printf("Hello world from processor %s, rank %d out of %d processors\n",prcessname, world_rank, world_size);
    
    MPI_Finalize();
    return 0;
}