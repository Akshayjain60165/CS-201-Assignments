#include<bits/stdc++.h>

using namespace std;

/*
  This code checks the output from my code and a brute force code to match their outputs and tells whether the optimised code
  is working correctly or not.
*/

int main(){
    ifstream f1("out1.txt"),f2("out2.txt");
    while(!f1.eof()){
        int a,b;
        f1>>a;
        f2>>b;
        if(a!=b){
            cout<<"WRONG\n";
            exit(0);
        }
    }
    if(!f2.eof()){
        cout<<"WRONG\n";
    }
    else{
        cout<<"CORRECT\n";
    }
}
