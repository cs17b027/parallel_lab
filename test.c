#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<mpi.h>
//#include<time.h>


/// did not calculated time and assuming the graph is there in graph.txt file in single line (e.g.   1 0 1 1)

int main(int argc , char** argv)
{
    int N = 2;// number of nodes in graph
    int rank,np;

    int src = 0;//source of shortest path
    int dst = 1;// destination of shortest path

    //boilerplate code to get rank and number or processes
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&np);

    // creating 2 dimenstions and calculating number of rows and colums
    int dim[2] = {0,0};
    MPI_Dims_create(np,2,dim);
    int n = N/dim[0];

    int* a = (int*)malloc(n*n*sizeof(int));
    int* b = (int*)malloc(n*n*sizeof(int));
    int ans[n*n];
    int* buff = (int*)malloc(n*n*sizeof(int));
    MPI_Status status;
    int length = 0;
    int flag = 0;
    int res;


    FILE *fp = fopen("graph.txt","r");
    fseek(fp,2*n*n*rank,SEEK_SET);

    for(int i = 0 ; i < n*n ; ++i)
    {
        fscanf(fp,"%d",&a[i]);
        b[i] = a[i];
        ans[i] = 0;
    }

    fclose(fp);

    // creating a cratesian plane to arrange the preocess
    int periods[2] = {1,1};
    MPI_Comm new_comm;
    MPI_Cart_create(MPI_COMM_WORLD,2,dim,periods,1,&new_comm);

    int r,l,u,d;
    MPI_Cart_shift(new_comm,0,1,&l,&r);
    MPI_Cart_shift(new_comm,1,1,&u,&d);


    while(length != n)
    {
        //cheking if we got shortest path
        int srange = (rank/dim[0])*n;
        int drange = (rank%dim[0])*n;

        if(src >= srange && src < srange+n && dst >= drange && dst < drange+n)
        {
            int tmps = src - srange;
            int tmpd = dst - drange;

            if(ans[tmps*n + tmpd] != 0 || a[tmps*n + tmpd] != 0) 
            {
                flag = 1;
                res = length+1;
            }
        }


        // matrix multiplication
        for(int i = 0; i < dim[0]; ++i)
        {
            MPI_Sendrecv(a,n*n,MPI_INT,l,1,buff,n*n,MPI_INT,r,1,new_comm,&status);

            int* temp;
            temp = a;
            a = buff;
            buff = temp;

            MPI_Sendrecv(b,n*n,MPI_INT,u,2,buff,n*n,MPI_INT,d,2,new_comm,&status);

            temp = b;
            b = buff;
            buff = temp;

            for(int i = 0 ; i < n ; ++i)
            {
                for(int j = 0 ; j < n ; ++j)
                {
                    for(int k = 0 ; k < n ; ++k)
                    {
                        ans[i*n + j] += a[i*n + k]*b[k*n + j];
                    }
                }
            }
        }

        for(int i = 0 ; i < n*n ; ++i)
            b[i] = ans[i];

        MPI_Barrier(new_comm);

        length++;
    }

    if(flag)
        printf("the shortest path is: %d", res);
}