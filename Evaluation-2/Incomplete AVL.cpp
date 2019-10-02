/*
                                            Programming Evaluation 2
    Author: G Pradyumn
    2018csb1088
*/
#include<iostream>
#include<math.h>

using namespace std;

//This AVL is for registration number
template<typename T1,typename T2>
struct node{
    T1 reg;//registration number
    T2 speed;
    T2 x;
    int ht;
    node *left,*right;
    node(){
        left=right=NULL;
        ht=0;
    }
};

template<typename T1, typename T2>
class cars{
    node<T1,T2> *root;
    double eps=1e-6;
    T2 curr;
    public:
    cars(){
        curr=0;
        root=NULL;
    }

    T2 abs(T2 val){
        if(val+eps<0.0){
            val=val*-1;
        }
        return val;
    }

    int search(T1 x,node<T1,T2> *p){
        if(p==NULL){
            return 0;
        }
        if(abs(p->reg-x)<=eps){
            return 1;
        }
        if(x+eps<p->reg){
            return search(x,p->left);
        }
        else if(x>p->reg+eps){
            return search(x,p->right);
        }
    }

    int height(node<T1,T2> *x){
        if(x==NULL){
            return 0;
        }
        return x->ht;
    }

    int getHeight(node<T1,T2> *x){
        if(x==NULL){
            return 0;
        }
        return height(x->left)-height(x->right);
    }

    node<T1,T2> *newnode(T2 x,T1 r,T2 vel){
        node<T1,T2> *temp=new node<T1,T2>;
        temp->x=x;
        temp->speed=vel;
        temp->reg=r;
        temp->ht=1;
        temp->left=temp->right=NULL;
        return temp;
    }

    //x is to be rotated left with its right subtree

    node<T1,T2> *leftrot(node<T1,T2> *x){
        node<T1,T2> *a,*b;
        a=x->right;
        b=x->right->left;
        a->left=x;
        x->right=b;
        x->ht=1+max(height(x->left),height(x->right));
        a->ht=1+max(height(a->left),height(a->right));
        return a;
    }

    //x is rotated right with its left subtree

    node<T1,T2> *rightrot(node<T1,T2> *x){
        node<T1,T2> *a,*b;
        a=x->left;
        b=a->right;
        x->left=b;
        a->right=x;
        x->ht=1+max(height(x->left),height(x->right));
        a->ht=1+max(height(a->left),height(a->right));
        return a;
    }

    //ht = left-right

    node<T1,T2> *insert_util(T2 val,node<T1,T2> *p,T1 r,T2 vel){
        if(p==NULL){
            return newnode(val,r,vel);
        }
        else if(r+eps<p->reg){
            p->left=insert_util(val,p->left,r,vel);
        }
        else{
            p->right=insert_util(val,p->right,r,vel);
        }
        p->ht=1+max(height(p->left),height(p->right));
        int diff=getHeight(p);
        if(abs(diff)<=1){
            return p;
        }
        if(diff>1 && val+eps<p->left->x){
            return rightrot(p);
        }
        if(diff<-1 && val>eps+p->right->x){
            return leftrot(p);
        }
        if(diff>1 && val>eps+p->left->x){
            p->left=leftrot(p->left);
            return rightrot(p);
        }
        if(diff<-1 && val+eps<p->right->x){
            p->right=rightrot(p->right);
            return leftrot(p);
        }
        return p;
    }

    int insert(T2 pos, T1 r, T2 vel){
        if(root==NULL){
            root=newnode(pos,r,vel);
            return 1;
        }
        else if(search(r,root)){
            return 0;
        }
        else{
            root=insert_util(pos,root,r,vel);
            return 1;
        }
    }

    int inorder(node<T1,T2> *p){
        while(p->left!=NULL){
            p=p->left;
        }
        return p->x;
    }
   
    void preorder(node<T1,T2> *p){
        if(p==NULL){
           // cout<<"NULL\n";
            return;
        }
        cout<<p->x<<" "<<p->subtree<<endl;
        preorder(p->left);
        preorder(p->right);
    }

    node<T1,T2> *del_util(T2 val,node<T1,T2> *p){
        if(abs(p->x-val)<=eps){
            if(p->left==NULL && p->right==NULL){
                return NULL;
            }
            else if(p->left==NULL){
                node<T1,T2> *temp=p->right;
                delete p;
                return temp;
            }
            else if(p->right==NULL){
                node<T1,T2> *temp=p->left;
                delete p;
                return temp;
            }
            else{
                p->x=inorder(p->right);
                p->right=del_util(p->x,p->right);
            }
        }
        else if(val+eps<p->x){
            p->left=del_util(val,p->left);
        }
        else{
            p->right=del_util(val,p->right);
        }
        p->ht=1+max(height(p->left),height(p->right));
        int diff=getHeight(p);
        if(abs(diff)<=1){
            return p;
        }
        if(diff>1 && getHeight(p->left)>=0){
            return rightrot(p);
        }
        if(diff<-1 && getHeight(p->right)<=0){
            return leftrot(p);
        }
        if(diff>1 && getHeight(p->left)<0){
            p->left=leftrot(p->left);
            return rightrot(p);
        }
        if(diff<-1 && getHeight(p->right)>0){
            p->right=rightrot(p->right);
            return leftrot(p);
        }
    }

    int del(T1 val){
        if(!search(val,root)){
            return 0;
        }
        root=del_util(val,root);
        return 1;
    }

    //Code below this,in the class, works fine
};

/*
    Heap -> parent->i/2,left child->2*i, right child->2*i+1;
*/
template<typename T1,typename T2>
struct time{
    T1 num;
    T2 t,x;
};

                                                                                                                                                                                                                                                                        //Author: G Pradyumn
template<typename T1,typename T2>
class heap{
    static const int SIZE=1e5+5;
    time<T1,T2> arr[SIZE];
    int n;
    const int inf=-1e9;//this is only  used for deleting key from heap
    public: 
    heap(){
        n=0;
    }

    T2 get_min(){
        return arr[1].t;
    }

    /* Function to print the heap for debugging
    void print_heap(){
        int k=1;
        for(int i=1;i<=n;i++){
            if(i==pow(2,k)){
                cout<<endl;
                ++k;
            }
            cout<<arr[i]<<" ";
        }
        cout<<endl;
    }*/
    
    int insert(T2 t,T1 r,T2 pos){
        ++n;
        arr[n].t=t;
        arr[n].num=r;
        arr[n].x=pos;
        int s=n;
        while(s!=1 && arr[s].t<arr[s/2].t){
            time<T1,T2> temp=arr[s];
            arr[s]=arr[s/2];
            arr[s/2]=temp;
            s=s/2;
        }
        return 1;
    }
    
    void decrease_key(int i,T2 val){
        arr[i].t=val;
        while(i!=1 && arr[i].t<arr[i/2].t){
            time<T1,T2> temp=arr[i];
            arr[i]=arr[i/2];
            arr[i/2]=temp;
            i=i/2;
        }
    }

    void Heapify(int i){
        int l=2*i;
        int r=2*i+1;
        int curr=i;
        if(l<=n and arr[l].t<arr[curr].t){
            curr=l;
        }
        if(r<=n and arr[r].t<arr[curr].t){
            curr=r;
        }
        if(curr!=i){
            time<T1,T2> temp=arr[curr];
            arr[curr]=arr[i];
            arr[i]=temp;
            Heapify(curr);
        }
    }

    T2 extract_min(){
        if(n==0){
            return -1;
        }
        if(n==1){
            n=0;
            return arr[1].t;
        }
        T2 temp=arr[1].t;
        arr[1]=arr[n];
        --n;
        Heapify(1);
        return temp;
    }

    //We replace that node with a very small value and then extract it;
    void delete_key(int i){
        decrease_key(i,inf);
        extract_min();
    }
    /*
        Heap functions above work fine.
    */
};

/*  one AVL tree for position, one for registration number and one heap for minimum time of collision.
    We insert position into the position avl based on its insertion position but, we insert x-vt in the tree at that position
*/

template<typename T1,typename T2>
class highway{
    cars<T1,T2> reg;//registration number
    cars<T2,T1> pos;//position to get the left and right neighbour of the current car
    heap<T1,T2> min_heap;
    public:

};

int main(){
    highway<int,float> need_more_time;
    //cout<<need_more_time.insert(1,1,1)<<need_more_time.del(1)<<need_more_time.insert(1,1,1);
    heap<int,float> check;
    cout<<check.insert(1,1,1);
    cout<<check.insert(1,1,1);
    return 0;
}
