#include <bits/stdc++.h>
#include "utilities.h"
using namespace std;
struct vEBoas{
    int universesize;
    int l, h;
    int minelement;
    int maxelement;   
    vEBoas *summary;
    vEBoas **cluster;
}; 
int high(vEBoas *node, int i){
    return (i / node->l);    
}
int low(vEBoas *node, int j){
    return (j % node->l) ;    
}
int index(vEBoas *node, int i, int j){
    return (i * node->l + j);
}
int findmin(vEBoas * node){
    if(!node){return -1;}
    return node->minelement;    
}
int findmax(vEBoas * node){
    if(!node){return -1;}
    return node->maxelement;    
}
vEBoas * createnode(vEBoas *root, int size){
    int s=poweroftwo(size);
    root->universesize=s;    
    root->l=lowersqrt(s);
    root->h=highersqrt(s);    
    root->summary=NULL;        
    if(root->universesize  > 2){
        root->cluster = new vEBoas * [root->h];
        for(int j=0; j<root->h; j++){
            root->cluster[j]=NULL;            
        }
    }
    else if(root->universesize <= 2){
        root->cluster = NULL;
    }    
    root->minelement=INT_MIN;
    root->maxelement=INT_MIN;
    return root;    
}
void emptyinsert(vEBoas *root, int val){
    root->minelement=val;
    root->maxelement=val;
}
void swap(int &a, int &b){
    int temp=a;
    a=b;
    b=temp;
}
void insert(vEBoas *&node, int val, int u){    
    if(!node){        
        node = new vEBoas;
        node = createnode(node, u);
    }  
    if( val == node->minelement || val == node->maxelement){
        return ;
    }  
    if(val < 0 || val >= node->universesize){
        cout << "\nKey out of range";
        return;
    }    
    if(node && node->minelement == INT_MIN){
        emptyinsert(node, val);
        return;
    }    
    else if(node && node->minelement > val){
        swap(val, node->minelement);        
    }
    if(node && node->maxelement < val){
        node->maxelement = val;
    }
    if(node && node->universesize <=2){
        return;
    }
    if(node->cluster[high(node, val)]){
        insert(node->summary, high(node, val), node->h);
    }
    insert(node->cluster[high(node, val)], low(node, val), node->l);    
}
int successor(vEBoas *root,int val) {
    int i,j, ml, offset, sc;
    if(root==NULL)
        return -1;
    if(root->universesize==2){
        if(val==0 && root->maxelement==1)
            return 1;
        else
            return -1;
    }
    else if(root->minelement!=-1 && val<(root->minelement))  
        return root->minelement; 
    else{
        ml=findmax(root->cluster[high(root, val)]);
        if(ml!=-1 && low(root, val)< ml){
            offset = successor(root->cluster[high(root, val)], low(root, val));
            return index(root, high(root, val), offset);
        }
        else{
            sc=successor(root->summary, high(root, val));
            if(sc == -1){
                return -1;
            }
            else{
                offset = findmin(root->cluster[sc]);
                return index(root, sc, offset);
            }
        }             
    }
}
int predecessor(vEBoas *root,int val) {
    int i,j, ml, offset, pc;
    if(!root)
        return -1;
    if(root->universesize==2){
        if(val==1 && root->minelement==0)
            return 0;
        else
            return -1;
    }    
    else if(root->maxelement != -1 && val>root->maxelement){
        return root->maxelement;
    }
    else{
        ml=findmin(root->cluster[high(root, val)]);
        if(ml!=-1 && low(root, val)>ml){
            offset = predecessor(root->cluster[high(root, val)], low(root, val));
            return index(root, high(root, val), offset);
        }
        else{
            pc=predecessor(root->summary, high(root, val));
            if(pc == -1){
                if(root->minelement!=-1 && val>root->minelement){
                    return root->minelement;
                }
                else{
                    return -1;
                }
            }
            else{
                offset=findmax(root->cluster[pc]);
                return index(root, pc, offset);
            }
        }        
    }
}
void deletenode(vEBoas *& node, int val) {
    if(!node || val<0 || val>=node->universesize || val<node->minelement || val>node->maxelement){
        return;
    }
    if(node && val == node->minelement) {
        int i = findmin(node->summary);
        if(i == -1 || i == INT_MIN) {
            if(node && node->minelement != node->maxelement) {
                node->minelement = node->maxelement;
                return;
            }
            node->minelement = node->maxelement = INT_MIN;
            delete node;
            node = NULL;
            return;
        }
        val = node->minelement = index(node, i, node->cluster[i]->minelement);
    }
    if(node && node->universesize > 2) {        
        deletenode(node->cluster[high(node, val)], low(node, val));
        int temp = findmin(node->cluster[high(node, val)]);
        if(temp == -1 or temp == INT_MIN) {
            deletenode(node->summary, high(node, val));
        }
    }
    if(node && node->maxelement == val) {
        int temp = findmax(node->summary);
        if(temp == -1 or temp == INT_MIN) {
            node->maxelement = node->minelement;
        } else {
            int i = findmax(node->summary);
            node->maxelement = index(node, i, node->cluster[i]->maxelement);
        }
    }
}
bool exists(vEBoas *root,int val){
    if(!root || val <0 || val>=root->universesize){
        return false;
    }
    if(root && root->minelement == val || root->maxelement==val){
        return true;
    }
    else if(root && root->universesize == 2){
        return false;
    }
    else{
        return exists(root->cluster[high(root, val)], low(root, val));
    }
}
int main(){
    int u;
    cout << "Enter size ";
    cin >> u;     
    cout << poweroftwo(u) << endl;
    vEBoas * veb = new vEBoas;
    createnode(veb, u);
    //insert
    for(int j=0; j<16; j++){
        insert(veb, j, u); 
        cout << j << " Inserted" << endl;
    }
    //exists
    for(int j=0; j<16; j++){
        cout << j << " Exists " << exists(veb, j) << endl; 
    }
    //successor
    for(int j=0; j<16; j++){
        cout << "Successor of "<< j << " is " << successor(veb, j) << endl;
    }    
    //predecessor
    for(int j=0; j<16; j++){
        cout << "Predecessor of "<< j << " is " << predecessor(veb, j) << endl;
    }    
    //delete
    for(int j=0; j<16; j++){
        deletenode(veb, j);
        cout << "Deleted "<< j <<  endl;
    }
    //exists
    for(int j=0; j<16; j++){
        cout << j << " Exists " << exists(veb, j) << endl; 
    }  
return 0;
}
