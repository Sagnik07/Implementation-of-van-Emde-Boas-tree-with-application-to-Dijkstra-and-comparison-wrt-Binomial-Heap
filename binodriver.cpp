#include "utilities.h"
#include "binomialheap.h"
typedef pair<int, int> ipair;
int main(){ 
    int ch,key;    
    int n, e, i;
    //cout << "Please enter number of nodes " ;
    cin >> n;
    //cout << "Please enter the number of edges";
    cin >> e;
    vector < ipair > graph[n+1];
    vector < int > dist(n+1, INT_MAX);
    unordered_map< int, list<int> > umap; 
    //cout << "Please enter " << e << " edges s d w " << endl;
    for(i=0; i<e; i++){
        int x, y, z;
        cin >> x >> y >> z;
        graph[x].push_back(make_pair(y, z));
		graph[y].push_back(make_pair(x, z));
    }
    //cout << "Enter the source ";
    int source;
    cin >> source;
    dist[source] = 0;
    umap[0].push_back(source);
    BinomialHeap bh;
    list<node*> bheap; 
    const clock_t begin_time2 = clock();
    bh.bino_heap=bheap;
    int succ;
    bheap = bh.insert(bheap,source);     
    while(!bheap.empty()){  
        node *temp = bh.getmin(bheap); 
        succ = temp->data;      
        while(!umap[succ].empty()){
				int u = umap[succ].front();
				umap[succ].pop_front();
				for(i=0; i<graph[u].size(); i++){
					ipair p = graph[u][i];
					int v = p.first;
					int w = p.second;
					if(dist[v] > (dist[u] + w)){
						dist[v] = dist[u] + w;
                        bheap = bh.insert(bheap,dist[v]);						
						umap[dist[v]].push_back(v);
					}
				}
			}        
         bheap = bh.extractmin(bheap);
    }
    cout << (double( clock () - begin_time2 ) *1000/CLOCKS_PER_SEC ) <<endl;
    cout << "Result " << endl;
    for(i=0; i<n; i++){
        cout << i << " " << dist[i] << endl;
    }
    return 0; 
} 