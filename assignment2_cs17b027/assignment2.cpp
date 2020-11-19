#include<bits/stdc++.h>
#include<thread>
#include<chrono>
using namespace std;

typedef unsigned long long intl;

intl n;
double thr;

vector< vector<double> > a;
vector< vector<double> > b;
bool flag = false;
bool check = true;
intl counti = 0;

void random_matrix_generator()
{
   double lbound = 0;
   double ubound = 10;
   uniform_real_distribution<double> urd(lbound, ubound);
   default_random_engine re;
   re.seed(27);
   for (intl i = 0; i < n; i++)
   {
       vector<double> temp,temp2;

     for (intl j = 0; j < n; j++)
     {
         double tempo = urd(re);
         temp.push_back(tempo);
         temp2.push_back(tempo);
     }

     a.push_back(temp);
     b.push_back(temp2);
   } 
}

/*void example_timer_usage()
{
  auto start = chrono::high_resolution_clock::now();
  auto stop = chrono::high_resolution_clock::now();
  auto duration = <chrono::milliseconds>(stop - start);
  cout << duration.count() << endl;
}*/

void calculate_row(intl i)
{
    for(intl j = 1 ; j < n-1 ; ++j)
    {
        if(check)
        {
            b[i][j] = (a[i][j-1] + a[i][j+1] + a[i-1][j] + a[i+1][j] + a[i][j])/5;

            if(abs(b[i][j] - a[i][j]) < thr)
            {
                flag = true;
            }
        }

        else
        {
            a[i][j] = (b[i][j-1] + b[i][j+1] + b[i-1][j] + b[i+1][j] + b[i][j])/5;

            if(abs(b[i][j] - a[i][j]) < thr)
            {
                flag = true;
            }
        } 
    }
}

void calculate_cell(intl i , intl j)
{
    if(check)
    {
        b[i][j] = (a[i][j-1] + a[i][j+1] + a[i-1][j] + a[i+1][j] + a[i][j])/5;

        if(abs(b[i][j] - a[i][j]) < thr)
        {
            flag = true;
        }
    }

    else
    {
        a[i][j] = (b[i][j-1] + b[i][j+1] + b[i-1][j] + b[i+1][j] + b[i][j])/5;

        if(abs(b[i][j] - a[i][j]) < thr)
        {
            flag = true;
        }
    }
}

void calculate_border(intl dir)
{
    if(dir == 1)
    {
        for(intl j = 1 ; j < n-1 ; ++j)
        {
            if(check)
            {
                b[0][j] = (a[0][j-1] + a[0][j+1] + a[1][j] + a[0][j])/5;

                if(abs(b[0][j] - a[0][j]) < thr)
                {
                    flag = true;
                }
            }

            else
            {
                a[0][j] = (b[0][j-1] + b[0][j+1] + b[1][j] + b[0][j])/5;

                if(abs(b[0][j] - a[0][j]) < thr)
                {
                    flag = true;
                }
            } 
        }
    }
    else if(dir == 2)
    {
        for(intl i = 1 ; i < n-1 ; ++i)
        {
            if(check)
            {
                b[i][0] = (a[i][1] + a[i-1][0] + a[i+1][0] + a[i][0])/5;

                if(abs(b[i][0] - a[i][0]) < thr)
                {
                    flag = true;
                }
            }

            else
            {
                a[i][0] = (b[i][1] + b[i-1][0] + b[i+1][0] + b[i][0])/5;

                if(abs(a[i][0] - b[i][0]) < thr)
                {
                    flag = true;
                }
            } 
        }
    }
    else if(dir == 3)
    {
        for(intl j = 1 ; j < n-1 ; ++j)
        {
            if(check)
            {
                b[n-1][j] = (a[n-1][j-1] + a[n-1][j+1] + a[n-2][j] + a[n-1][j])/5;

                if(abs(b[n-1][j] - a[n-1][j]) < thr)
                {
                    flag = true;
                }
            }

            else
            {
                a[n-1][j] = (b[n-1][j-1] + b[n-1][j+1] + b[n-2][j] + b[n-1][j])/5;

                if(abs(b[n-1][j] - a[n-1][j]) < thr)
                {
                    flag = true;
                }
            } 
        }
    }
    else
    {
        for(intl i = 1 ; i < n-1 ; ++i)
        {
            if(check)
            {
                b[i][n-1] = (a[i][n-2] + a[i-1][n-1] + a[i+1][n-1] + a[i][n-1])/5;

                if(abs(b[i][0] - a[i][0]) < thr)
                {
                    flag = true;
                }
            }

            else
            {
                a[i][n-1] = (b[i][n-2] + b[i-1][n-1] + b[i+1][n-1] + b[i][n-1])/5;

                if(abs(a[i][0] - b[i][0]) < thr)
                {
                    flag = true;
                }
            } 
        }
    }
}

void calculate()
{
    bool check = true;
}

int main(int argc , char** argv)
{
    n = stoi(argv[1]);
    thr = stod(argv[2]);

    random_matrix_generator();

    thread threads[n];

    auto start = chrono::high_resolution_clock::now();
    
    while(!flag)
    {
        for(intl i = 1 ; i < n-1 ; ++i)
        {
            threads[i] = thread(calculate_row,i);
            //calculate_row(i);

            /*for (intl j = 1; j < n-1; j++)
            {
                threads[(i-1)*(n-1)+j] = thread(calculate_cell,i,j);
            }*/
        }

        for (intl i = 1; i < n-1; i++)
        {
            threads[i].join();
        }

        //cout << "iteration " << counti << " completed ..." << endl;

        check = !check;

        counti++;
    }
    
    auto stop = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << duration.count() << endl << counti << endl;

    return 0;
}