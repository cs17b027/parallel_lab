#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>

void rand_generator(int n,int *a)
{
    for(int i = 0; i < n ; ++i)
    {
        a[i] = rand()%100;
    }
}

int main(int argc, char** argv)
{
    int n = 2;
    int a[n];

    rand_generator(n,a);

    int np,rank;

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &np);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int src = (rank - 1 + np)%np;
    int dst = (rank + 1)%np;

    MPI_Send(a, n, MPI_INT, dst, dst, MPI_COMM_WORLD);
    MPI_Recv(&a,)

    return 0;
}