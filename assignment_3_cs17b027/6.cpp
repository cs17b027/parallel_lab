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
#define MAX (int64_t)1e18+7
#define MIN (int64_t)-1e18-7
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
  // #include<thread>
  #include<omp.h>
  int nthread=10;
//
int64_t sum[10];
void computeSum(int id,vector<int64_t> v){
  int64_t l=((int64_t)v.size()/nthread)*id;
  int64_t r=((int64_t)v.size()/nthread)*(id+1);
  if(l==0&&r==0){
    l=id;
    r=id+1;
  }
  if(id==nthread-1){
    r=v.size();
  }
  for(int64_t i=l;i<min(r,(int64_t)v.size());i++){
    sum[id]+=v[i];
  }
}
#pragma region main
int main(){
  ifstream fin;
  fin.open("input.txt");
  int64_t n;
  fin>>n;
  vector<int64_t> v;
  for(int64_t i=0;i<n;i++){
    int64_t a;
    fin>>a;
    v.push_back(a);
  }
  omp_set_num_threads(nthread);
  #pragma omp parallel
  {
    computeSum(omp_get_thread_num(),v);
  }
  int64_t main_sum=0;
  for(int64_t i:sum){
    main_sum+=i;
  }
  cout<<main_sum<<endl;

}
#pragma endregion
