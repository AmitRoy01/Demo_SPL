#include<bits/stdc++.h>
#include "linear.h"
#define SIZE 100000
#define phi 1e-12

using namespace std;

int n;
double *a,*b,*c, r, s, old_r, old_s,dr,ds,root_p, root_q;
bool last = false;
//for last rest equation

void initialize_array()
{
    a = new double[SIZE];
    b = new double[SIZE];
    c = new double[SIZE];
}

void deleted_array()
{
    delete a;
    delete b;
    delete c;

}


double find_absolute(double x)
{
    //return absolute value
    if(x<0)
    {
        x *= -1;
    }

    return x;
}



double remove_error(double value)
{
    //floating point never goes to zero. for a particular error we need to avoid these error
    int integer = value;
    if(find_absolute(integer - value) <= phi)
    {

        value = (double)integer;
    }

    return value;
}



void print_solution(double x,double p, double q)
{

    if(!last)
    {
        //for r and s , we need to change sign of r and s
        p = (-1)*remove_error(p);
        q =(-1)*remove_error(q);
    }
    else
    {
        // we find solution from rest of equation
        p = remove_error(p);
        q = remove_error(q);
    }

    double determinant = (p*p) - (4*x*q);


    if(determinant<0)
    {
        determinant *= -1;

        determinant = sqrt(determinant);

        if(p == 0)
        {
            //pure imaginary number
            if((determinant/(2*x)) == 1)
            {
                //coefficient 1 , not necessary to print
                cout<<"\tRoot : "<<"i"<<endl;
                cout<<"\tRoot: "<<"-i"<<endl;
            }
            else
            {
                //there are coefficient
                cout<<"\tRoot: "<<(determinant/(2*x))<<"i"<<endl;
                cout<<"\tRoot: "<<(determinant/(2*x))<<"-i"<<endl;
            }
        }
        else
        {
            //when not a pure imaginary number
            if((determinant/(2*x)) == 1)
            {
                //coefficient 1 , not necessary to print
                cout<<"\tRoot: "<<((-p)/(2*x))<<" + "<<"i"<<endl;
                cout<<"\tRoot: "<<((-p)/(2*x))<<" - "<<"i"<<endl;
            }
            else
            {
                //there are coefficient
                cout<<"\tRoot: "<<((-p)/(2*x))<<" + "<<(determinant/(2*x))<<"i"<<endl;
                cout<<"\tRoot: "<<((-p)/(2*x))<<" - "<<(determinant/(2*x))<<"i"<<endl;
            }
        }
    }
    else
    {
        //cout<<determine<<endl;
        determinant = sqrt(determinant);
        //cout<<determine<<endl;
        double first = remove_error(((-p) - determinant)/(2*x));
        double second =  remove_error(((-p) + determinant)/(2*x));

        cout<<"\tRoot: "<<first<<endl;
        cout<<"\tRoot: "<<second<<endl;

    }
}



void print_single_root(double x, double y)
{
    // If existance equation has only one solution
    //x *= -1;
    //y *= -1;

    double root = -(y/x);

    cout<<"\tRoot: "<<root<<endl;
}






void R_S_calculation()
{
    //for iteration we need to find r and s. From r and s we find two solution of equation

    dr = (b[0]*c[3] - b[1]*c[2]) / (c[2]*c[2] - c[1]*c[3]);
    ds = (b[1]*c[1] - b[0]*c[2]) / (c[2]*c[2] - c[1]*c[3]);

    old_r = r ;
    old_s = s;

    r += dr;
    s += ds;
}


void calculate_column(double p[], double q[])
{
    //iteration column to find solution
    q[n] = p[n];
    q[n-1] = p[n-1] + q[n]*r;

    for(int i=n-2; i>=0; i--)
    {
        q[i] = p[i] + (q[i+1]*r) + (q[i+2]*s);
    }
}



void reduce_equation()
{
    //After iteration we find two solution and the equations's power reduce by two.
    //Replace a[] coefficient by b[] coefficient
    for(int i=0; i<n-1; i++)
    {
        a[i] = b[i+2];
    }

    n -= 2;
}





void find_root()
{
    //iteration until equation goes to power 1 or 2
    double ratio_s, ratio_r;

    if(n == 0)
    {
        cout<<"No such variable.\n Wrong input\n\n";
        exit(0);
    }
    else if(n == 1)
    {
        print_single_root(a[n], a[n-1]);
    }
    else if(n == 2)
    {
        last = true;
        print_solution(a[n], a[n-1], a[n-2]);
    }
    else
    {

        while(1)
        {
            calculate_column(a,b);
            calculate_column(b,c);

            R_S_calculation();

            ratio_s = ds/old_s;
            ratio_r = dr/old_r;


            if(((find_absolute(b[0]) <= phi) && (find_absolute(b[1]) <= phi)) || ((find_absolute(ratio_r) <= phi) || (find_absolute(ratio_s) <= phi)))
            {

                print_solution(1,r,s);

                if(n == 4)
                {
                    last = true;            //for last part there no sign change
                    print_solution(b[n],b[n-1],b[n-2]);
                    break;              //equation go to zero
                }

                if(n == 3)
                {
                    print_single_root(b[n], b[n-1]);
                    break;
                }

                reduce_equation();
            }
        }
    }
}


void starting_method(double pass[], int total)
{

    initialize_array();         //initialize array as dynamic for controll million of data
    //copy array to global array
    for(int i= total; i>=0; i--)
    {
        a[i] = pass[i];
        //cout<<" - "<<a[i]<<endl;

    }
    n = total;


    r = a[n-1]/a[n];
    s = a[n-2]/a[n];

    if(r == 0)
    {
        r = 0.1;        //default value of r
    }

    if(s ==0)
    {
        s = 0.1;        //default value of s
    }

    find_root();

    deleted_array();         //deallocate memmory
    return;
}
