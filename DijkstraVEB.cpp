#include "utilities.h"
using namespace std;
typedef pair<int, int> ipair;
struct vEBoas{
    int u;
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
    root->u=s;    
    root->l=lowersqrt(s);
    root->h=highersqrt(s);    
    root->summary=NULL;
    if(root->u <= 2){
        root->cluster = NULL;
    }
    else{
        root->cluster = new vEBoas * [root->h];
        for(int j=0; j<root->h; j++){
            root->cluster[j]=NULL;            
        }
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
void insert(vEBoas *&root, int key, int u){    
    if(!root){        
        root = new vEBoas;
        root = createnode(root, u);
    }  
    if( key == root->minelement || key == root->maxelement){
        return ;
    }  
    if(key < 0 || key >= root->u){
        cout << "\nKey out of range";
        return;
    }    
    if(root->minelement == INT_MIN){
        emptyinsert(root, key);
        return;
    }    
    else if(root->minelement > key){
        swap(key, root->minelement);        
    }
    if(root->maxelement < key){
        root->maxelement = key;
    }
    if(root->u <=2){
        return;
    }
    if(root->cluster[high(root, key)] == NULL){
        insert(root->summary, high(root, key), root->h);
    }
    insert(root->cluster[high(root, key)], low(root, key), root->l);    
}
int successor(vEBoas *root,int val) {
    int i,j, ml, offset, sc;
    if(root==NULL)
        return -1;
    if(root->u==2){
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
    if(root==NULL)
        return -1;
    if(root->u==2){
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
int main(){
    int n, e, i;
    cout << "Please enter number of nodes " ;
    cin >> n;
    cout << "Please enter the number of edges";
    cin >> e;
    vector < ipair > graph[n+1];
    vector < int > dist(n+1, INT_MAX);
    unordered_map< int, list<int> > umap; 
    cout << "Please enter " << e << " edges s d w " << endl;
    for(i=0; i<e; i++){
        int x, y, z;
        cin >> x >> y >> z;
        graph[x].push_back(make_pair(y, z));
		graph[y].push_back(make_pair(x, z));
    }
    cout << "Enter the source ";
    int source;
    cin >> source;
    dist[source] = 0;
    umap[0].push_back(source);
    vEBoas *root = new vEBoas;
    root = createnode(root, 256);
    insert(root, 0, 16);
    int succ=0;
    do{
        while(true){
			if(!umap[succ].empty()){
				int u = umap[succ].front();
				umap[succ].pop_front();
				for(i=0; i<graph[u].size(); i++){
					ipair p = graph[u][i];
					int v = p.first;
					int w = p.second;
					if(dist[v] > (dist[u] + w)){
						dist[v] = dist[u] + w;
						insert(root, dist[v], 16);
						umap[dist[v]].push_back(v);
					}
				}
			}
			else{
				break;
			}
        }
        succ = successor(root, succ);
    }while(succ != -1);
    cout << "Result " << endl;
    for(i=0; i<n; i++){
        cout << i << " " << dist[i] << endl;
    }
    return 0;
}