/*
000coool
Manish Kumar Srivastava
IIT Tirupati
*/
#pragma region headers
//Basic Necessities
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,popcnt,abm,mmx,avx,avx2,fma,tune=native")
#include<iostream>
#include<cassert>
#include<algorithm>
#include<numeric>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<ctime>
#include<cctype>
#include<bitset>
#include<fstream>
#include<tuple>
//C++ templates
#include<queue>
#include<deque>
#include<stack>
#include<vector>
#include<string>
#include<set>
#include<unordered_set>
#include<map>
#include<unordered_map>
#pragma endregion
#pragma region shortcuts
//Shortcuts
// #define MAX (int64_t)1e18+7
// #define MIN (int64_t)-1e18-7
#define N (int64_t)1e5+7
#define M (int64_t)1e6+7
#define mid (l+r)/2
#define outl(a) printf("%lld\n",a)
#define outs(a) printf("%lld ",a)
#define out(a)  printf("%lld",a)
#define mod 1000000007
#define mem(a) memset(a,0,sizeof(a))
#define all(a) a.begin(),a.end()
#define mp(a,b) make_pair(a,b)
using namespace std;
int64_t scan(){
  int64_t a;
  scanf("%lld",&a);
  return a;
}
#pragma endregion
// 
  #include<omp.h>
  int nthread=3;
//
//  
  #include<mpi.h>
// 
#pragma region main
int main(int argc,char **argv){
  MPI_Init(&argc,&argv);
  MPI_Comm comm=MPI_COMM_WORLD;
  int rank;
  int numberOfCores;
  MPI_Comm_rank(comm,&rank);
  MPI_Comm_size(comm,&numberOfCores);
  int64_t arr[]={1,2};
  int64_t m=2;
  for(int64_t i=0;i<m;i++){
    if(i==0&&rank==0){
      int64_t a=rand()%numberOfCores;
      MPI_Send(arr,2,MPI_LONG_LONG_INT,a,a,comm);
    }
    else{
      int flag;
      MPI_Iprobe(MPI_ANY_SOURCE,MPI_ANY_TAG,comm,&flag,MPI_STATUS_IGNORE);
      if(flag){
          MPI_Recv(arr,2,MPI_LONG_LONG_INT,MPI_ANY_SOURCE,MPI_ANY_TAG,comm,MPI_STATUS_IGNORE);
          int64_t a=rand()%numberOfCores;
          MPI_Send(arr,2,MPI_LONG_LONG_INT,a,a,comm);
      }
    }
    MPI_Barrier(comm);
  }
  MPI_Finalize();
}
#pragma endregion
