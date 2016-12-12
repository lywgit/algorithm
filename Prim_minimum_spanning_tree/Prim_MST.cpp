#include<iostream>
#include<fstream>
#include<vector>
#include<unordered_set>
using namespace std;

struct Edge{
    Edge(int n1, int n2, int c){node1 = n1, node2 = n2; cost = c;};
    int node1, node2, cost;
};

vector<Edge> PrimMST(unordered_set<int> nodes, vector<Edge> edges){
    int big = 999999;
    int seed_node = 1;
    vector<Edge> mst;
    nodes.erase(seed_node);     
    while (nodes.size()>0){
        int min_cost = big;
        Edge e_min_cost(0,0,0);
        int new_node = -1;
        for (int i=0; i<edges.size(); i++){  
            int n1 = edges[i].node1, n2 = edges[i].node2, cost = edges[i].cost;
            if (!nodes.count(n1) && nodes.count(n2) && cost < min_cost){ 
                e_min_cost =  edges[i];
                new_node = n2;
                min_cost = cost;
            }
            if (!nodes.count(n2) && nodes.count(n1) && cost < min_cost){ 
                e_min_cost =  edges[i];
                new_node = n1;
                min_cost = cost;
            }
        }
        mst.push_back(e_min_cost);
        nodes.erase(new_node);
    }
    return mst;
}

int main(int argc, char* argv []){
    if (argc < 2){
        cerr << "You need to specify a file name." <<endl;
        return 1;
    }
    ifstream file_stream(argv[1]);
    if (!file_stream){
        cerr <<"File "<<argv[1]<<" not opened."<<endl;
        return 1;
    }
    int num_nodes, num_edges;
    vector<Edge> edges;
    unordered_set<int> nodes;
    file_stream >> num_nodes >> num_edges;
    cout<<"node:"<< num_nodes <<"  edges:" << num_edges <<endl;
    int i= 0;
    while (i < num_edges){
        int node1, node2, cost;
        file_stream >> node1 >> node2 >> cost;
        Edge e(node1, node2, cost);
        edges.push_back(e);
        nodes.insert(node1);
        nodes.insert(node2);
        i++;
    }    

    vector<Edge> MST = PrimMST(nodes, edges);
    long total_cost(0); 
    for (int i=0; i<MST.size();i++){
        total_cost += MST[i].cost;
    }
    cout <<"Total cost of MST: "<< total_cost<<endl;

    return 0;
}


