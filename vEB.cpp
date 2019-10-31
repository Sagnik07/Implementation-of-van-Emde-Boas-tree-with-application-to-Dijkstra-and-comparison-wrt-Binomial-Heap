#include <bits/stdc++.h>
using namespace std;
class vEBoas{
    public :
        int u;
        int sqrt_u;
        int minelement;
        int maxelement;
        int clustersize;
        vEBoas *summary;
        vEBoas **cluster;
    public:
        int poweroftwo(int val){
            if(val<0)return 0;
            --val;
            val |= val>>1;
            val |= val>>2;
            val |= val>>4;
            val |= val>>8;
            val |= val>>16;
            return (val + 1);
        }
        double lowersqrt(int value){
            return pow(2, floor(log2(value) / 2));
        }
        double highersqrt(int value){
            return pow(2, ceil(log2(value) / 2));
        }
        int high(int i){
            return (i / lowersqrt(u));
            //return (i / ceil(sqrt(u)));
        }
        int low(int j){
            return (j % (int)lowersqrt(u)) ;
           // return (j % (int)ceil(sqrt(u))) ;
        }
        int index(int i, int j){
            return (i * lowersqrt(u) + j);
        }
        vEBoas(int s){    
            if(s <= 0){
                cout << " The u value should be greater than zero"; 
            }        
            minelement = INT_MIN;
            maxelement = INT_MIN;  
            u=poweroftwo(s);   
            sqrt_u = sqrt(u);    
            int hsqrt = highersqrt(u);   
            int i;
            summary = NULL;                      
            if(u > 2){
                summary = new vEBoas(highersqrt(u));
                cluster = new vEBoas *[hsqrt];
                for(i=0; i<highersqrt(u); i++){                    
                    cluster[i] =  new vEBoas(lowersqrt(u));
                }
            }
            else{
                cluster = NULL;
            }  
        }    
};
int findmin(vEBoas * node){
    if(!node){return INT_MIN;}
    return node->minelement;    
}
int findmax(vEBoas * node){
    if(!node){return INT_MIN;}
    return node->maxelement;    
}
void insert(vEBoas *node, int key, int u){    
    if(!node){        
        node = new vEBoas(u);
    }    
    if(key < 0 || key >= node->u){
        cout << "\nKey out of range";
        return;
    }
    if(node->minelement == INT_MIN){
        node->minelement = key;
        node->maxelement = key;
        return;
    }
    if( key == node->minelement || key == node->maxelement){
        return ;
    }
    if(node->minelement > key){
        int t = key;
        key = node->minelement;
        node->minelement = t;
    }
    if(node->maxelement < key){
        node->maxelement = key;
    }
    if(node->u <=2){
        return;
    }
    int i = node->high(key);
    int j = node->low(key);
    if(node->cluster[i] == NULL){
        insert(node->summary, i, node->sqrt_u);
    }
    insert(node->cluster[i], j, node->sqrt_u);    
}
bool exists(vEBoas *node, int key){
    if(!node){return false;}        
    if(key < node->minelement || key > node->maxelement || key<0 || key >= node->u){
        //cout << "Key is not present" << endl;
        return false;
    }
    if(node->minelement == key){
        return true;
    }    
    if(!node->summary){
        return (node->maxelement == key);
    }
    if(exists(node->cluster[node->high(key)], node->low(key))){
        return true;
    }
    else {
        //cout << "Key is not present" << endl;
        return false;
    }
}
void vEB_print ( vEBoas * node){
  if ( !node ) return;
  cout << "Universe" << node->u << endl;
  cout << "Cluster size" << node->sqrt_u << endl;
  cout << "VEB " << node << std::endl;
  cout << "Minimum " << node->minelement << endl;
  cout << "Maximum " << node->maxelement << endl;
  cout << "Cluster size " << node->lowersqrt(node->u) << endl;
  cout << "Number of clusters " << node->highersqrt(node->u) << endl;
  cout << "Summary " << node->summary << std::endl;
  if ( node->u > 2 ){
    for ( int i = 0; i < node->highersqrt(node->u); ++i ){
      //cout << "cluster " << i << ": " << node->cluster[i] << std::endl;
    }
  }
  else{
    //cout << "cluster " << node->cluster << std::endl;
  }
}
int successor(vEBoas *root,int val) {
    int i,j;
    if(root==NULL || root->u==1)
        return -1;
    if(root->u==2)  {
        if(val==0 && root->maxelement==1)
            return 1;
        else
            return -1;
    }
    else if(root->minelement!=INT_MIN && val<root->minelement)  
        return root->minelement; 
    else    {
        i=root->high(val);
        if(root->summary==NULL) {
            if(val<root->maxelement)
                return root->maxelement;
            else
                return -1;
        }
        
        else    {
            if(root->low(val)<findmax(root->cluster[i]))    {
                j=successor(root->cluster[i],root->low(val));
                if(j==-1)
                    return -1;
            }
            else    {
                i=successor(root->summary,i);
                if(i==-1)   {
                    if(val<root->maxelement)
                        return root->maxelement;
                    else
                        return -1;
                }
                j=findmin(root->cluster[i]);
                if(j==-1)
                    return -1;
            }
            
        }
        
    }
    return root->index(i,j);     
    
}
int predecessor(vEBoas *root,int val) {
    int i,j;
    if(root==NULL || root->u==1)
        return -1;
    if(root->u==2)  {
        if(val==1 && root->minelement==0)
            return 0;
        else
            return -1;
    }
    else if (root->maxelement != -1 && val > root->maxelement) { 
        return root->maxelement; 
    } 
    else    {
        i=root->high(val);
        if(root->summary==NULL) {
            if(val>root->minelement)
                return root->minelement;
            else
                return -1;
        }
        
        else    {
            if(root->low(val)>findmin(root->cluster[i]))    {
                j=predecessor(root->cluster[i],root->low(val));
                if(j==-1)
                    return -1;
            }
            else    {
                i=predecessor(root->summary,i);
                if(i==-1 || i==INT_MIN)   {
                    if(val>root->minelement)
                        return root->minelement;
                    else
                        return -1;
                }
                j=findmax(root->cluster[i]);
                if(j==-1)
                    return -1;
            }
            
        }
        
    }
    return root->index(i,j);  
}
void delete1(vEBoas *root,int val) {
    int i,j;
    if(root==NULL || val<root->minelement || val>root->maxelement)  {        
        return;
    }
    else if(root->u==2)   {
        root->minelement=(val==0)?1:0;
        root->maxelement=root->minelement;
    }
    else    {
        if(val==root->minelement)   {
            i=findmin(root->summary);
            if(i==-1 || i==INT_MIN) {
                if(root->minelement==root->maxelement)  {
                    root->minelement=INT_MIN;
                    root->maxelement=INT_MIN;
                }
                else
                    root->minelement=root->maxelement;
                return;
            }
            root->minelement=root->index(i,root->cluster[i]->minelement);
            val=root->minelement;
        }
        delete1(root->cluster[root->high(val)],root->low(val));
        j= findmin(root->cluster[root->high(val)]);
        if(j==-1 || j==INT_MIN) 
            delete1(root->summary,root->high(val));

        if(root->maxelement==val) {
            j=findmax(root->summary);
            if(j==-1 || j==INT_MIN)
                root->maxelement=root->minelement; 
            else    {
                i=findmax(root->summary);
                root->maxelement=root->index(i,root->cluster[i]->maxelement);
            }
        }
    }
}
int main(){
    int u;
    cout << "Enter size ";
    cin >> u;
    vEBoas * veb = new vEBoas(u); 
    cout << veb->poweroftwo(u) << endl;
    // vEBoas * veb = new vEBoas(u);  
    // insert(veb, 2, u); 
    // insert(veb, 3, u); 
    // insert(veb, 5, u);
    // insert(veb, 10, u);
    // insert(veb, 4, u);
    // insert(veb, 6, u);
    // // cout << successor(veb, 3) << endl;
    // // cout << successor(veb, 3) << endl;
    // vEB_print(veb);  
    // while(1){
    //     int x;cin >>x;
    //     cout << "Predecessor ";
    //     cout << predecessor(veb, x) << endl;
    //     cout << "Present ";
    //     cout << exists(veb, x) <<endl; 
    //     if(x == 1){break;}
    // }    
    //cout << findmax(veb) << endl;
    
    // cout << "Successor ";
    // cout << successor(veb, x) << endl;
    while(1){
        int x,y;
        cout << "Enter Choice ";
        cin >> x;
        cout << endl;
        switch (x)
        {
        case 1://insert
            
            cout << "Enter number to insert ";
            cin>>y;
            insert(veb, y, u); 
            break;
        case 2://exist
            
            cout << "Enter number to search ";
            cin>>y;
            cout << exists(veb, y) << endl; 
            break;
        case 3://display
            vEB_print(veb);
            break;
        case 4://succ
            
            cout << "Enter number whose succ you want to find ";
            cin>>y;
            cout<< successor(veb, y) << endl;
            break;
        case 5://Prede
            
            cout << "Enter number whose prede you want to find ";
            cin>>y;
            cout << predecessor(veb, y) <<endl; 
            break;
        case 6://Delete
           
            cout << "Enter number to delete ";
            cin>>y;
            delete1(veb, y); 
            break;        
        default:
            break;
        }
    }
   
return 0;
}
