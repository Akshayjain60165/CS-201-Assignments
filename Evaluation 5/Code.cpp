/*
                                            Programming evaluation 5
    Author: G Pradyumn
    2018csb1088
*/

#include<iostream>
#include<math.h>

using namespace std;

const int MAX=3e5+5;

/*
    We make a min heap in which we insert all the edges according to their probabilities.
    heap stores -log10(total probability to reach this node), vertex number and total red edges used till now.
*/

struct edge{
    double p;
    int ind,nr;
    edge(){
        nr=0;
    }
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

    void swap(edge &a,edge &b){
        edge c=a;
        a=b;
        b=c;
    }

    void insert(double val,int index,int ai){
        int ind1=n;
        arr[ind1].p=val;
        arr[ind1].ind=index;
        arr[ind1].nr=ai;
        while(ind1>1 && arr[ind1].p+eps<arr[parent(ind1)].p){
            swap(arr[ind1],arr[parent(ind1)]);
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
            swap(arr[ind],arr[i]);
            heapify(i);
        }
    }

    edge extract_min(){
        if(n==1){
            edge a;
            a.ind=-1;
            a.p=0;
            a.nr=1e5;
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

/*
list is used to implement adjacency list of a node.
*/

struct pt{
    double p;
    int dest,col;
    pt *next;
    pt(){
         next=NULL;
     }
};

class list{
    pt *root;
    int s;
    public:
    list(){
        root=NULL;
        s=0;
    }

    pt *getroot(){
        return root;
    }

    int size(){
        return s;
    }

    void insert(int d,double prob,int c){
        pt *temp=new pt;
        temp->dest=d;
        temp->col=c;
        temp->p=prob;
        temp->next=root;
        root=temp;
        ++s;
    }
};

int dijkstra(int n,int m,double g,int k){
    list adj[n];
    for(int i=0;i<m;i++){
        double p,val;
        int s,d,c;
        cin>>s>>d>>p>>c;
        val=-log10(1.0-p);
        --s,--d;
        adj[s].insert(d,val,c);
        adj[d].insert(s,val,c);
    }
    min_heap h(MAX);
    h.insert(0,0,0);
    double *vis[n];//visited[node number][number of red edges used till now]=-log10(max probability to reach this node)
    //we need to keep vis <=g and second index <=k for an answer;
    for(int i=0;i<n;i++){
        vis[i]=new double[k+1]; 
        for(int j=0;j<=k;j++){
            vis[i][j]=-1;
        }
    }
    while(!h.empty()){
        edge a=h.extract_min();
        int u=a.ind;
        double pr=a.p;
        int nr=a.nr;
        pt *r=adj[u].getroot();
        if(vis[u][nr]!=-1){
            continue;
        }
        vis[u][nr]=pr;
        for(int i=0;i<adj[u].size();++i){
            if(nr+r->col<=k){
                h.insert(pr+r->p,r->dest,nr+r->col);
            }   
            r=r->next;
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<=k;j++){
            cout<<vis[i][j]<<" ";
        }
        cout<<endl;
    }
    for(int i=0;i<k+1;++i){
        if(vis[n-1][i]<=g && vis[n-1][i]!=-1){
            return 1;
        }
    }
    return 0;
}

int main(){
    freopen("input.txt","r",stdin);
    freopen("out.txt","w",stdout);
    double g;
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
