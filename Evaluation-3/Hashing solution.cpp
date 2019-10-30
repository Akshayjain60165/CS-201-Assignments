/*
                                        Author: G Pradyumn
                                        2018CSB1088
                                        Programming evaluation 3
*/
#include<iostream>

using namespace std;

const int MOD=1e9+7;

/*
      See this video for reference -> https://www.youtube.com/watch?v=rA1ZevamGDc
*/

int main(){
    int n;
    cin>>n;
    long long val[n]={},h[n]={};
    val[0]=1;
    for(int i=1;i<n;i++){
        val[i]=(val[i-1]*7)%MOD;
    }
    string s;
    cin>>s;
    h[0]=s[0]-'0'+1;
    for(int i=1;i<n;++i){
        h[i]=(h[i-1]*7+s[i]-'0'+1)%MOD;
    }
    int m;
    cin>>m;
    while(m--){
        int i1,i2,j1,j2;
        cin>>i1>>j1>>i2>>j2;
        --i1,--i2,--j2,--j1;
        if(j2-i2!=j1-i1){
            cout<<"0\n";
            continue;
        }
        int a1,a2=0,b1,b2=0;
        a1=h[j1],b1=h[j2];
        if(i1>0){
            a2=(h[i1-1]*val[j1-i1+1])%MOD;
        }
        if(i2>0){
            b2=(h[i2-1]*val[j2-i2+1])%MOD;
        }
        if(a1<a2){
            a1+=MOD;
        }
        if(b1<b2){
            b1+=MOD;
        }
        //cout<<a1-a2<<" "<<b1-b2<<endl;
        if((a1-a2)%MOD==(b1-b2)%MOD){
            cout<<"1\n";
        }
        else{
            cout<<"0\n";
        }
    }
    return 0;
}
