#include <iostream>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <bits/stdc++.h>
#include "linker.h"
using namespace std;

void equation_solver()           //add infinite many solution
{

        cout<<"\n\n\n\t\t\t\t WELCOME TO \n\t\t\t\t*EQUATON SOLVER*\n\n\n";
        int choice;
        cout<<"\t\t1.Linear equation\n\\n\t\t2.Polynomial equation\n\t\t4.Exit\n\n..........";
        cin>>choice;
        //getchar();
        if(choice == 1){
            cout<<"\n\n\n\n\t\t1. Input equation\n\t\t 2.Input coefficient of equation\n.........."<<endl;
            //getchar();
            cin>>choice;

            if(choice == 1){
                solve_linear_equation();
            }
            else{
                cout<<"Wrong input"<<endl;
            }
        }
        else if(choice == 2){
            input_controller();
        }
        else if(choice == 4){
            return;
        }
        else{
            cout<<"Wrong input"<<endl;
        }

        return;

}



int main()
{
    int number ;
    //freopen("in.txt","r",stdin);
    cout<<"Enter choice: \n";
    cin>>number;
    if(number==1){
    while(1){
        equation_solver();
    }
    }
    return 0;
}
