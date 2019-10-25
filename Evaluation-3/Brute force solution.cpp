#include<iostream>

using namespace std;

int main(){
    int n;
    cin>>n;
    string s;
    cin>>s;
    int m;
    cin>>m;
    while(m--){
        int i1,j1,i2,j2;
        cin>>i1>>j1>>i2>>j2;
        --i1,--i2,--j1,--j2;
        int y=1;
        while(i1<=j1){
            if(s[i1]!=s[i2]){
                y=0;
                break;
            }
            ++i1;
            ++i2;
        }
        if(y){
            cout<<"1\n";
        }
        else{
            cout<<"0\n";
        }
    }
    return 0;
}
