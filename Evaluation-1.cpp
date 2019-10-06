/*
Author:G Pradyumn
2018csb1088
*/
#include<iostream>

using namespace std;

template<typename T1,typename T2>
struct node{
    T1 reg;
    T2 x;
    int ht,subtree;
    node *left,*right;
    node(){
        left=right=NULL;
        ht=0;
        subtree=1;
    }
};

template<typename T1,typename T2>
struct best{
    T1 reg;
    T2 pos;
    best(){
        reg=-1;
        pos=-1;
    }
};

template<typename T1, typename T2>
class cars{
    node<T1,T2> *h1,*h2;
    T2 curr;
    double eps=1e-6;
    public:
    cars(){
        curr=0;
        h1=NULL,h2=NULL;
    }
   
    void change_time(T2 val){
        curr=val;
    }

    T2 abs(T2 val){
        if(val+eps<0.0){
            val=val*(-1);
        }
        return val;
    }

    int search(T2 x,node<T1,T2> *p){
        if(p==NULL){
            return 0;
        }
        if(abs(p->x-x)<=eps){
            return 1;
        }
        if(x+eps<p->x){
            return search(x,p->left);
        }
        else if(x>p->x+eps){
            return search(x,p->right);
        }
    }

    int height(node<T1,T2> *x){
        if(x==NULL){
            return 0;
        }
        return x->ht;
    }

    //returns height of the current node x using height function.
    int getHeight(node<T1,T2> *x){
        if(x==NULL){
            return 0;
        }
        return height(x->left)-height(x->right);
    }

    //Create a new node
    node<T1,T2> *newnode(T2 x,T1 r){
        node<T1,T2> *temp=new node<T1,T2>;
        temp->x=x;
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
        int sa=0,sb=0,sc=0;
        if(a!=NULL)
        	sa=a->subtree;
        sb=x->subtree;
        sb-=sa;
        if(b!=NULL)
        	sc=b->subtree;
        sa+=sb;
        sb+=sc;
        x->right->left=x;
        x->right=b;
        a->subtree=sa;
        x->subtree=sb;
        x->ht=1+max(height(x->left),height(x->right));
        a->ht=1+max(height(a->left),height(a->right));
        return a;
    }

    //x is rotated right with its left subtree

    node<T1,T2> *rightrot(node<T1,T2> *x){
        node<T1,T2> *a,*b;
        a=x->left;
        b=a->right;
        int sa=0,sb=0,sc=0;
        if(a!=NULL)
        	sa=a->subtree;
        sb=x->subtree;
        sb-=sa;
        if(b!=NULL)
        	sc=b->subtree;
        sa+=sb;
        sb+=sc;
        a->subtree=sa;
        x->subtree=sb;
        x->left=b;
        a->right=x;
        x->ht=1+max(height(x->left),height(x->right));
        a->ht=1+max(height(a->left),height(a->right));
        return a;
    }

    //ht = left-right

    node<T1,T2> *insert_util(T2 val,node<T1,T2> *p,T1 r){
        if(p==NULL){
            return newnode(val,r);
        }
        else if(val+eps<p->x){
            p->left=insert_util(val,p->left,r);
            p->subtree=p->subtree+1;
        }
        else{
            p->right=insert_util(val,p->right,r);
            p->subtree=p->subtree+1;
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

    node<T1,T2> *insert(node<T1,T2> *root,T2 val,T1 r){
        if(root==NULL){
            root=newnode(val,r);
            return root;
        }
        else if(search(val,root)){
            return NULL;
        }
        else{
            root=insert_util(val,root,r);
            return root;
        }
    }

    T2 inorder(node<T1,T2> *c,node<T1,T2> *p){
        while(p->left!=NULL){
            p=p->left;
        }
        c->reg=p->reg;
        return p->x;
    }
    
    int set_up_insert(T2 x,int dir,T1 r){
        node<T1,T2> *temp;
        int a;
        if(dir==0){
            temp=insert(h1,x,r);
            if(temp==NULL){
                a=0;
            }
            else{
                h1=temp;
                a=1;
            }
        }
        else{
            temp=insert(h2,x,r);
            if(temp==NULL){
                a=0;
            }
            else{
                h2=temp;
                a=1;
            }
        }
        return a;
    }
    /*This function was used for debugging purposes
    void preorder(node<T1,T2> *p){
        if(p==NULL){
            return;
        }
        cout<<p->x<<" "<<p->subtree<<endl;
        preorder(p->left);
        preorder(p->right);
    }*/

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
                p->subtree-=1;
                p->x=inorder(p,p->right);
                p->right=del_util(p->x,p->right);
            }
        }
        else if(val+eps<p->x){
            p->left=del_util(val,p->left);
            p->subtree-=1;
        }
        else{
            p->right=del_util(val,p->right);
            p->subtree-=1;
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
   
    int set_up_del(int dir,T2 x){
        if(dir==0){
            if(search(x,h1)){
                h1=del_util(x,h1);
                return 1;
            }
            else{
                return 0;
            }
        }
        else{
            if(search(x,h2)){
                h2=del_util(x,h2);
                return 1;
            }
            else{
                return 0;
            }
        }
    }

    //Helper function to find nearest left node
    best<T1,T2> nearest_left(T2 x,node<T1,T2> *root){
        best<T1,T2> a;
        if(root==NULL){
            return a;
        }
        while(1){
            if(root==NULL){
                break;
            }
            if(abs(root->x-x)<=eps){
                root=root->left;
                continue;
            }
            if((a.reg==-1 || (root->x>a.pos)) && (root->x+eps<x)){
                a.pos=root->x;
                a.reg=root->reg;
            }
            if(root->x+eps<x){
                root=root->right;
            }
            else{
                root=root->left;
            }
        }
        return a;
    }

    //Helper function to find nearest right node.
    best<T1,T2> nearest_right(T2 x,node<T1,T2> *root){
        best<T1,T2> a;
        if(root==NULL){
            return a;
        }
        while(1){
            if(root==NULL){
                break;
            }
            if(abs(root->x-x)<=eps){
                root=root->right;
                continue;
            }
            if((a.reg==-1 || abs(root->x - x)+eps<abs(a.pos-x)) && (root->x+eps>x)){
                a.pos=root->x;
                a.reg=root->reg;
            }
            if(root->x+eps<x){
                root=root->right;
            }
            else{
                root=root->left;
            }
        }
        return a;
    }

    T1 immediate_left_util(T1 dir,T2 x,T2 curr){
        best<T1,T2> a1,a2;
        if(dir==0){
            a1=nearest_left(x,h1);
            a2=nearest_left(x-2*curr,h2);
        }
        else{
            a1=nearest_left(x+2*curr,h1);
            a2=nearest_left(x,h2);
        }
        if(a1.reg!=-1 && a2.reg!=-1){
            if(abs(a1.pos-2*curr-a2.pos)<=eps){
                if(a1.reg<a2.reg){
                    cout<<a1.reg<<" ";
                    return a2.reg;
                }
                else{
                    cout<<a2.reg<<" ";
                    return a1.reg;
                }
            }
            else if(abs(a1.pos-curr)+eps>abs(a2.pos+curr)){
                return a1.reg;
            }
            else{
                return a2.reg;
            }
        }
        else{
            if(a1.reg!=-1){
                return a1.reg;
            }
            else{
                return a2.reg;
            }
        }
    }

    T1 immediate_right_util(T1 dir,T2 x,T2 curr){
        best<T1,T2> a1,a2;
        if(dir==0){
            a1=nearest_right(x,h1);
            a2=nearest_right(x-2*curr,h2);
        }
        else{
            a1=nearest_right(x+2*curr,h1);
            a2=nearest_right(x,h2);
        }
        if(a1.reg!=-1 && a2.reg!=-1){
            if(abs(a1.pos-a2.pos-2*curr)<=eps){
                if(a1.reg<a2.reg){
                    cout<<a1.reg<<" ";
                    return a2.reg;
                }
                else{
                    cout<<a2.reg<<" ";
                    return a1.reg;
                }
            }
            else if(abs(a1.pos-curr)+eps<abs(a2.pos+curr)){
                return a1.reg;
            }
            else{
                return a2.reg;
            }
        }
        else{
            if(a1.reg!=-1){
                return a1.reg;
            }
            else{
                return a2.reg;
            }
        }
    }

    int subtree_size_left(T2 pos,node<T1,T2> *root){
        int ans=0;
        while(root!=NULL){
            if(abs(root->x-pos)<=eps){
                root=root->left;
            }
            else if(root->x>pos){
                root=root->left;
            }
            else{
                ans+=root->subtree;
                if(root->right!=NULL){
                    ans-=root->right->subtree;
                }
                root=root->right;
            }
        }
        return ans;
    }

    int left_util(int dir,T2 x,T2 curr){
        int ans=0;
        if(dir==0){
            int a1=subtree_size_left(x,h1);
            int a2=subtree_size_left(x-2*curr,h2);
            ans=a1+a2;
        }
        else{
            int a1=subtree_size_left(x+2*curr,h1);
            int a2=subtree_size_left(x,h2);
            ans=a1+a2;
        }
        return ans;
    }

    int subtree_size_right(T2 pos,node<T1,T2> *root){
        int ans=0;
        while(root!=NULL){
            if(abs(root->x-pos)<=eps){
                root=root->right;
            }
            else if(root->x<pos){
                root=root->right;
            }
            else{
                ans+=root->subtree;
                if(root->left!=NULL){
                    ans-=root->left->subtree;
                }
                root=root->left;
            }
        }
        return ans;
    }

    int right_util(int dir,T2 x,T2 curr){
        int ans=0;
        if(dir==0){
            int a1=subtree_size_right(x,h1);
            int a2=subtree_size_right(x-2*curr,h2);
            ans=a1+a2;
        }
        else{
            int a1=subtree_size_right(x+2*curr,h1);
            int a2=subtree_size_right(x,h2);
            ans=a1+a2;
        }
        return ans;
    }

    int dir_zero_util(T2 pos,node<T1,T2> *root){
        int ans=0;
        while(root!=NULL){
            if(root->x>pos){
                root=root->left;
            }
            else{
                ans+=root->subtree;
                if(root->right!=NULL){
                    ans-=root->right->subtree;
                }
                root=root->right;
            }
        }
        return ans;
    }

    int for_direction_zero(T2 x,T2 t){
        T2 x1=x-2*curr,x2=x-2*t;
        if(search(x1,h2)){
            x1--;
        }
        if(search(x2,h2)){
            ++x2;
        }
        int a1=0,a2=0;
        a1=dir_zero_util(x1,h2);
        a2=dir_zero_util(x2,h2);
        return a1-a2;
    }

    int dir_one_util(T2 pos,node<T1,T2> *root){
        int ans=0;
        while(root!=NULL){
            if(root->x<pos){
                root=root->right;
            }
            else{
                ans+=root->subtree;
                if(root->left!=NULL){
                    ans-=root->left->subtree;
                }
                root=root->left;
            }
        }
        return ans;
    }

    int for_direction_one(T2 x,T2 t){
        T2 x1=x+2*curr,x2=x+2*t;
        if(search(x1,h1)){
            ++x1;
        }
        if(search(x2,h1)){
            --x2;
        }
        int a1=0,a2=0;
        a1=dir_one_util(x1,h1);
        a2=dir_one_util(x2,h1);
        return a1-a2;
    }
};

/*
    Insert cars with direction dir and position x-time_in;
    We keep two trees, one for left moving cars and other for right moving cars.
    To search for a car,first get position of car from reg_num class,then search for that position in cars class.
    Second tree stores registration number, position and direction.
We get registration number from this class, then using cars class, we do appropriate operations.
This class contains the correct input format, which we then change according to the function in cars class.
*/


/*
Author:G Pradyumn
2018csb1088
*/

template<typename T1,typename T2>
struct reg{
    T1 x;
    T2 pos;
    int dir,ht;
    reg* left,*right;
    reg(){
    	ht=0;
    	left=right=NULL;
    }
};

template<typename T1,typename T2>
struct for_val{
    T1 dir;
    T2 pos;
};

//T1 for int and T2 for float
template<typename T1,typename T2>
class get_car{
    reg<T1,T2> *root;
    cars<T1,T2> highway;
    double eps=1e-6;
    public:
	
	T2 abs(T2 val){
		if(val+eps<0){
			val*=-1;
		}
		return val;
	}
	
    get_car(){
        root=NULL;
    }

    //This function searches for the position of car with registration number r and returns its direction and position.
    for_val<T1,T2> search_position(T1 r,reg<T1,T2> *p){
        if(p->x==r){
            for_val<T1,T2> a;
            a.dir=p->dir;
            a.pos=p->pos;
            return a;
        }
        if(p->x<r){
            return search_position(r,p->right);
        }
        else{
            return search_position(r,p->left);
        }
    }

    //Searches for car with registration number x and returns 1 if found.
    int search(T1 x,reg<T1,T2> *p){
        if(p==NULL){
            return 0;
        }
        if(x==p->x){
            return 1;
        }
        if(x<p->x){
            return search(x,p->left);
        }
        else if(x>p->x){
            return search(x,p->right);
        }
    }

    int height(reg<T1,T2> *x){
        if(x==NULL){
            return 0;
        }
        return x->ht;
    }

    int getHeight(reg<T1,T2> *x){
        if(x==NULL){
            return 0;
        }
        return height(x->left)-height(x->right);
    }

    reg<T1,T2> *newnode(T1 x,T2 position,T1 dir){
        reg<T1,T2> *temp=new reg<T1,T2>;
        temp->x=x;
        temp->dir=dir;
        temp->ht=1;
        temp->pos=position;
        temp->left=temp->right=NULL;
        return temp;
    }

    //x is to be rotated left with its right subtree

    reg<T1,T2> *leftrot(reg<T1,T2> *x){
        reg<T1,T2> *a,*b;
        a=x->right;
        b=x->right->left;
        x->right->left=x;
        x->right=b;
        x->ht=1+max(height(x->left),height(x->right));
        a->ht=1+max(height(a->left),height(a->right));
        return a;
    }

    //x is rotated right with its left subtree

    reg<T1,T2> *rightrot(reg<T1,T2> *x){
        reg<T1,T2> *a,*b;
        a=x->left;
        b=a->right;
        x->left=b;
        a->right=x;
        x->ht=1+max(height(x->left),height(x->right));
        a->ht=1+max(height(a->left),height(a->right));
        return a;
    }

    //ht = left-right

    reg<T1,T2> *insert_util_util(T2 x,T1 val,reg<T1,T2> *p,T1 d){
        if(p==NULL){
            return newnode(val,x,d);
        }
        else if(val<p->x){
            p->left=insert_util_util(x,val,p->left,d);
        }
        else{
            p->right=insert_util_util(x,val,p->right,d);
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

    int insert_util(T1 val,T2 x,int d){
        if(root==NULL){
            root=newnode(val,x,d);
            return 1;
        }
        else if(search(val,root)){
            return 0;
        }
        else{
            root=insert_util_util(x,val,root,d);
            return 1;
        }
    }

    int inorder(reg<T1,T2> *c,reg<T1,T2> *p){
        while(p->left!=NULL){
            p=p->left;
        }
        c->dir=p->dir;
        c->pos=p->pos;
        return p->x;
    }

    /* This function was used for debugging purposes.
    void preorder(reg<T1,T2> *p){
        if(p==NULL){
            return;
        }
        cout<<p->x<<" "<<p->pos<<endl;
        preorder(p->left);
        preorder(p->right);
    }*/

    reg<T1,T2> *del_util(T1 val,reg<T1,T2> *p){
        if(p->x==val){
            if(p->left==NULL && p->right==NULL){
                return NULL;
            }
            else if(p->left==NULL){
                reg<T1,T2> *temp=p->right;
                delete p;
                return temp;
            }
            else if(p->right==NULL){
                reg<T1,T2> *temp=p->left;
                delete p;
                return temp;
            }
            else{
                p->x=inorder(p,p->right);
                p->right=del_util(p->x,p->right);
            }
        }
        else if(val<p->x){
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

    int insert(T1 r, T2 x, T2 t, T1 d){
        int a;
        if(d==0){
           a=insert_util(r,x+t,d);
        }
        else{
            a=insert_util(r,x-t,d);
        }
        if(a==1){
            if(d==1)
                highway.set_up_insert(x-t,d,r);
            else{
                highway.set_up_insert(x+t,d,r);
            }
            highway.change_time(t);
        }
        return a;
    }
   
   int remove(T1 r,T2 t){
       int a=search(r,root);
       if(a==1){
           for_val<T1,T2> k=search_position(r,root);
           highway.set_up_del(k.dir,k.pos);
           del(r);   
            highway.change_time(t);
       }
       return a;
   }
    /*
        Ask if registration number is valid for left and right queries , else add search(r,root)
        before all for_val statements.
    */
   int find_immediate_left(T1 r,T2 t){
       for_val<T1,T2> k=search_position(r,root);
       T1 ans=highway.immediate_left_util(k.dir,k.pos,t);
       return ans;
   }

    int find_immediate_right(T1 r,T2 t){
        for_val<T1,T2> k=search_position(r,root);
        T1 ans=highway.immediate_right_util(k.dir,k.pos,t);
        return ans;
    }

    int count_left(T1 r,T2 t){
        for_val<T1,T2> k=search_position(r,root);
        int ans=highway.left_util(k.dir,k.pos,t);
        return ans;
    }

    int count_right(T1 r,T2 t){
    	for_val<T1,T2> k=search_position(r,root);
    	int ans=highway.right_util(k.dir,k.pos,t);
    	return ans;
    }
    
    int number_of_crossings(T1 r,T2 t){
    	for_val<T1,T2> k=search_position(r,root);
    	int ans;
    	if(k.dir==0){
    		ans=highway.for_direction_zero(k.pos,t);
    	}
    	else{
    		ans=highway.for_direction_one(k.pos,t);
    	}
    	return ans;
    }
};

int main(){
	get_car<int,double> please_work;
	int t;
    cin>>t;
    for(int i=1;i<=t;i++){
        int choice;
        cin>>choice;
        if(choice==1){
            int reg,d;
            double pos,time;
            cin>>reg>>pos>>time>>d;
            please_work.insert(reg,pos,time,d);
            continue;
        }
        int r;
        double t;
        cin>>r>>t;
        if(choice==2){
            please_work.remove(r,t);
        }
        if(choice==3){
            cout<<please_work.find_immediate_left(r,t)<<endl;
        }
        if(choice==4){
            cout<<please_work.find_immediate_right(r,t)<<endl;
        }
        if(choice==5){
            cout<<please_work.count_left(r,t)<<endl;
        }
        if(choice==6){
            cout<<please_work.count_right(r,t)<<endl;
        }
        if(choice==7){
            cout<<please_work.number_of_crossings(r,t)<<endl;
        }
    }
    return 0;
}
