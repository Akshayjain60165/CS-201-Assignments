#include<bits/stdc++.h>

using namespace std;

int a[100005];

void swap(int &a,int &b){
	int c=a;
	a=b;
	b=c;
}

int partition(int lo,int hi){
	int p=a[lo];
	int i=lo+1,j=lo+1;
	for(;j<=hi;++j){
		if(a[j]<p){
			swap(a[j],a[i]);
			++i;
		}
	}
	swap(a[i-1],a[lo]);
	return i-1;
}

int sort(int lo,int hi){
	int r=rand()%(hi-lo+1);
	r+=lo;
	swap(a[r],a[lo]);
	return partition(lo,hi);
}

void quicksort(int lo,int hi){
	if(lo<hi){
		int p=sort(lo,hi);
		//cout<<p<<endl;
		quicksort(lo,p-1);
		quicksort(p+1,hi);
	}
}

int main(){
	int n;
	//cin>>n;
	n=100000;
	for(int i=0;i<n;i++){
		//cin>>a[i];
		a[i]=(i+1005)%n;
	}
	clock_t t;
	t=clock();
	quicksort(0,n-1);
	cout<<"TIME taken: "<<(float)(clock()-t)/CLOCKS_PER_SEC<<endl;
	/*for(int i=0;i<n;i++){
		cout<<a[i]<<" ";
	}
	cout<<endl;*/
	return 0;
}
