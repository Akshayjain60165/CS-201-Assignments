#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

template<typename T>
using ordered_set = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;

const int infI=1e9+5;
const long long infL=1e16;
const int MOD=1e9+7;
const int MAX=1e5+5;

#define mp make_pair
#define in &
#define pb push_back
#define ii pair<int,int>
#define iii pair<ii,int>
#define ll long long
#define pll pair<ll,ll>
#define vl vector<vector<ll> >
#define vi vector<int>
#define vvi vector<vector<int> >
#define eb emplace_back
#define forn(i,a,b) for(int i=a;i<b;i++)
#define fastio ios_base::sync_with_stdio(0);cin.tie(0)
#define endl '\n'
#define popb pop_back();
#define se second
#define fi first

ll power(ll a,ll b){
    if(b==1){
        return a;
    }
    ll temp=power(a,b/2);
    temp=(temp*temp)%MOD;
    if(b%2){
        temp=(temp*a)%MOD;
    }
    return temp;
}

//only use if mod is prime
ll mod_inv(ll a,ll mod){
    return power(a,mod-2);
}

void extended_gcd(ll a,ll b,ll &x,ll &y){
    if(b==0){
        x=1;
        y=0;
        return;
    }
    ll x1,y1;
    extended_gcd(b,a%b,x1,y1);
    x=y1;
    y=x1-((a/b)*y1);
    return;
}

vvi adj;
vector<int> tin,low;
vector<bool> vis;
int t;

void dfs(int v,int p){
    vis[v]=true;
    tin[v]=low[v]=++t;
    for(auto x:adj[v]){
        if(x==p){
            continue;
        }
        if(vis[x]){
            low[v]=min(low[v],tin[x]);//back edge
        }
        else{
            dfs(x,v);
            low[v]=min(low[v],low[x]);//if there is a vertex with a back edge, then all edges in between those two vertices cannot be bridges.
            if(low[x]>tin[v]){
                cout<<v<<" "<<x<<endl;
            }
        }
    }
}

int main(){
    int n,m;
    cin>>n>>m;
    adj.resize(n);
    low.resize(n);
    tin.resize(n);
    vis.resize(n,false);
    fill(low.begin(),low.end(),0);
    fill(tin.begin(),tin.end(),0);
    forn(i,0,m){
        int s,d;
        cin>>s>>d;
        --s,--d;
        adj[s].pb(d);
        adj[d].pb(s);
    }
    forn(i,0,n){
        if(vis[i]==false){
            dfs(i,-1);
        }
    }
    return 0;
}
