/*
                                            Programming Evaluation 4
    Author:G Pradyumn
    2018csb1088
*/
#include<iostream>

using namespace std;

struct node{
    char c;
    bool ended;
    node *left,*right;
    int num;
    node(){
        ended=false;
        left=right=NULL;
        num=1;
    }
};

class trie{
    node *root=new node;
    
    public:

    trie(){
        root->c='$';
    }

    node *newNode(char a,bool word_ended){
        node *temp=new node;
        temp->c=a;
        temp->ended=word_ended;
        temp->num=1;
        temp->left=temp->right=NULL;
        return temp;
    }

    int search(string s,int ind,node *curr){
        if(ind==s.size()){
            return (curr->ended==true);
        }
        if(curr->left!=NULL){
            if(curr->left->c==s[ind]){
                return search(s,ind+1,curr->left);
            }
        }
        if(curr->right!=NULL){
            if(curr->right->c==s[ind]){
                return search(s,ind+1,curr->right);
            }
        }
        return 0;
    }

    void insert_util(string s,int ind, node *curr){
        if(ind==s.size()){
            return;
        }
        bool y=false;
        if(ind==s.size()-1){
            y=true;
        }
        if(curr->left!=NULL && curr->left->c==s[ind]){
            ++curr->left->num;
            insert_util(s,ind+1,curr->left);
        }
        else if(curr->right!=NULL && curr->right->c==s[ind]){
            ++curr->right->num;
            insert_util(s,ind+1,curr->right);
        }
        else if(curr->left==NULL){
            curr->left=newNode(s[ind],y);
            insert_util(s,ind+1,curr->left);
        }
        else{
            curr->right=newNode(s[ind],y);
            insert_util(s,ind+1,curr->right);
        }
    }

    int insert_node(string s){
        if(search(s,0,root)==1){
            return 0;
        }
        ++root->num;
        insert_util(s,0,root);
        return 1;
    }

    void insert_pre(string s,int ind){
        ++root->num;
        insert_util(s,ind,root);
    }

    node *del_util(string s,int ind,node *curr){
        if(ind>=s.size()){
            return curr;
        }
        if(curr!=NULL){
            if(curr->c==s[ind]){
                --curr->num;
                curr->left=del_util(s,ind+1,curr->left);
                curr->right=del_util(s,ind+1,curr->right);
                if(curr->num==0){
                    if(curr->ended==true){
                        curr->ended=false;
                    }
                    return NULL;
                }
            }
        }
        return curr;
    }

    int delete_node(string s){
        if(search(s,1,root)==0){
            return 0;
        }
        root=del_util(s,0,root);
        return 1;
    }

    void preorder(node *curr){
        cout<<curr->c<<" ";
        if(curr->left!=NULL){
            preorder(curr->left);
        }
        if(curr->right!=NULL){
            preorder(curr->right);
        }
    }

    void delete_pre_node(string s,int ind){
        root=del_util(s,ind,root);
    }

    node *getroot(){
        return root;
    }

    int search1(string s,int ind,node *curr){
        if(curr==NULL){
            return 0;
        }
        if(ind==s.size()-1 && curr->c==s[ind]){
            //cout<<curr->num<<" n ";
            return curr->num;
        }
        if(curr->c==s[ind]){
            return search1(s,ind+1,curr->left)+search1(s,ind+1,curr->right);
        }
        return 0;
    }

    int max(int a,int b){
        if(a>b){
            return a;
        }
        return b;
    }

    int search2(string s,int ind,node* curr){
        if(curr==NULL || ind==s.size() || (s[ind]!=curr->c && s[ind]!='?')){
            return 0;
        }
        int u=curr->num;
        if(s[ind]=='$'){
            u=0;
        }
        return u+search2(s,ind+1,curr->left)+search2(s,ind+1,curr->right);
    }

};

/*
    Since our string can start with either 0 or 1, I add $ sign as a buffer to start the trie at a single root.
*/

int main(){
    freopen("t1.txt","r",stdin);
    int t;
    cin>>t;
    trie prefix,word;
    while(t--){
        int choice;
        string s;
        cin>>choice>>s;
        if(choice==1){
            if(word.insert_node(s)==1){
                for(int i=0;i<s.size();i++){
                    prefix.insert_pre(s,i);
                }
            }
        }
        else if(choice==2){
            s='$'+s;
            if(word.delete_node(s)==1){
                for(int i=1;i<s.size();i++){
                    s[i-1]='$';
                    prefix.delete_pre_node(s,i-1);
                }
            }
        }
        else if(choice==3){
            s='$'+s;
            cout<<prefix.search1(s,0,prefix.getroot())<<endl;
        }
        else if(choice==4){
            s='$'+s;
            cout<<word.search2(s,0,word.getroot())<<endl;
        }
    }
    //word.preorder(word.getroot());
    return 0;
}
