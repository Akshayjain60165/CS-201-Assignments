/*
                                            Programming evaluation 5
    Author: G Pradyumn
    2018csb1088
*/

#include<iostream>
#include<math.h>

using namespace std;

/*
    We make a min heap in which we insert all the edges according to their probabilities.
    heap stores -log10(probability of success) and vertex number.
*/

struct edge{
    float p;
    int ind;
};

class min_heap{
    int n,max_size;
    edge *arr;
    int inf=-1e9;
    double eps=1e-9;
    public:
    min_heap(int k){
        max_size=k+1;
        n=1;
        arr=new edge[k+1];
    }

    int parent(int i){
        return i/2;
    }

    int l_child(int i){
        return 2*i;
    }

    int r_child(int i){
        return 2*i+1;
    }

    void swap(float &a,float &b){
        float c=a;
        a=b;
        b=c;
    }

    void insert(float val,int index){
        int ind1=n;
        arr[ind1].p=val;
        arr[ind1].ind=index;
        while(ind1>1 && arr[ind1].p+eps<arr[parent(ind1)].p){
            swap(arr[ind1].p,arr[parent(ind1)].p);
            ind1=parent(ind1);
        }
        ++n;
    }

    void heapify(int ind){
        int i=ind;
        if(l_child(i)<n && arr[i].p>arr[l_child(i)].p+eps){
            i=l_child(ind);
        }
        if(r_child(ind)<n && arr[i].p>arr[l_child(ind)].p+eps){
            i=r_child(ind);
        }
        if(i!=ind){
            swap(arr[ind].p,arr[i].p);
            heapify(i);
        }
    }

    edge extract_min(){
        if(n==1){
            edge a;
            a.ind=-1;
            a.p=0;
            return a;
        }
        if(n==2){
            --n;
            return arr[1];
        }
        --n;
        edge t=arr[1];
        arr[1]=arr[n];
        heapify(1);
        return t;
    }

    int size(){
        return n;
    }

    bool empty(){
        if(n==1){
            return true;
        }
        return false;
    }
};

int dijkstra(int n,int m,float g,int k){
    int adj[n][n];
    float prob[n][n];
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            adj[i][j]=-1;
        }
    }
    for(int i=0;i<m;i++){
        float p,val;
        int s,d,c;
        cin>>s>>d>>p>>c;
        val=-log10(1.0-p);
        --s,--d;
        prob[s][d]=prob[d][s]=val;
        adj[s][d]=adj[d][s]=c;
    }
    min_heap h(m);
    h.insert(0,0);
    float l[n],used[n];
    for(int i=0;i<n;i++){
        l[i]=1e5;
        used[i]=1e5;
    }
    l[0]=0;//probability of length till now
    used[0]=0;//number of red edges used
    int vis[n]={};
    vis[0]=1;
    while(!h.empty() && l[n-1]>g){
        edge a=h.extract_min();
        int u=a.ind;
        int pr=a.p;
        for(int i=0;i<n;i++){
            if(adj[u][i]!=-1 && vis[i]==0){
                if(l[i]>pr+prob[u][i] && used[u]+adj[u][i]<=k){
                    l[i]=pr+prob[u][i];
                    used[i]=used[u]+adj[u][i];
                    h.insert(l[i],i);
                    vis[i]=1;
                }
            }
        }        
        for(int i=0;i<n;i++){
            cout<<l[i]<<" ";
        }
        cout<<endl;
    }
    if(l[n-1]<=g){
        return 1;
    }
    return 0;
}

int main(){
    float g;
    int k,n,m;
    cin>>g>>k>>n>>m;
    if(dijkstra(n,m,g,k)){
        cout<<"YES\n";
    }
    else{
        cout<<"NO\n";
    }
    return 0;
}
