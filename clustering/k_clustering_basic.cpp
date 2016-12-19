#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm> // for sort
#include<unordered_set>

using namespace std;


struct Edge{
    Edge(int n1, int n2, int c){ node1=n1; node2=n2; cost=c;};
    int node1;
    int node2;
    int cost;
};

bool isSmaller(Edge e1, Edge e2){ return e1.cost<e2.cost;}// for sorting


void KClustering(int k, vector<Edge> edges, int num_node, int & max_spacing){
    
    sort(edges.begin(), edges.end(), isSmaller);
    // node ids are 1~500
    vector<int> parent(num_node+1); 
    unordered_set<int> cluster_heads;
    for (int i=1; i<=num_node;i++){
        parent[i] = i;
        cluster_heads.insert(i); 
    }
    vector<Edge>::iterator iter = edges.begin(); 
    while (iter != edges.end()){
        // Find
        int s1 = parent[iter->node1]; 
        int s2 = parent[iter->node2]; 
        if (s1 != s2) {
            // Union
            for (int i=1; i<=num_node; i++)
                if (parent[i] == s2) parent[i]=s1; 
            cluster_heads.erase(s2);
            //cout<<"Union "<<s2<<" -> "<< s1<<endl;
        }       
        iter++;
        if (cluster_heads.size() == k) {
            cout<<"The K-cluster heads are: ";
            unordered_set<int>::iterator it=cluster_heads.begin();    
            while (it != cluster_heads.end()){ cout <<*it++<<" "; }
            cout<<endl;
            break;
        }
    }

    while (iter != edges.end()){
        if (parent[iter->node1] != parent[iter->node2]) {
            cout<< "Spacing: edge between "<<parent[iter->node1]<<" and "<<parent[iter->node2]<<", cost = "<<iter->cost << endl ;
            break;
        }
        iter++;
    }
    max_spacing = iter->cost;

}


int main(int argc, char* argv []){

    if (argc<2){
        cerr <<"You should specify a file name."<<endl;
        return 1;
    }
    fstream file_stream (argv[1]);
    if (!file_stream){
        cerr <<"Error: File not opened."<<endl;
        return 1;
    }
    int num_node;
    file_stream >> num_node;
    cout<< "number of node: "<<num_node<<endl;
    vector<Edge> edges;
    int n1, n2, cost;
    while (file_stream >> n1 >> n2 >> cost){
        // cout<<n1<<" "<<n2<<" "<<cost<<endl;
        edges.push_back(Edge(n1, n2, cost));
    } 
    int max_cluster_spacing;
    KClustering(4, edges, num_node, max_cluster_spacing);
    for (int i=0; i<10; i++){
        //cout << edges[i].node1 <<" "<<edges[i].node2<<" "<<edges[i].cost<<endl; 
    }
    cout<<"max cluster spacing: "<<max_cluster_spacing<<endl;

    return 0;
}



