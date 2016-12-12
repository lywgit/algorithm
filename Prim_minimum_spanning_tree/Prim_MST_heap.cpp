#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<unordered_set>
#include"Heap.h"
using namespace std;

struct Edge{
    Edge(){};
    Edge(int n1, int n2, int c){node1=n1; node2=n2; cost=c;};
    int node1, node2, cost;
};


vector<Edge> PrimMST(unordered_set<int> nodes, vector<Edge> edges, map<int, vector<int> > node_edges){
    int big = 99999;
    vector<Edge> mst;
    // initialize heap with fake edges for convenience
    map<int, MinHeap> heap_node_cost; 
    for (unordered_set<int>::iterator iter = nodes.begin(); iter!= nodes.end(); iter++){
        MinHeap h; 
        h.insert(Node(-1, big)); 
        heap_node_cost[*iter] = h;
    }
    // start with seed_node
    int seed_node = 1;
    int current_node = seed_node;
    vector<int> affected_edges = node_edges[current_node];
    nodes.erase(current_node);
    for (int i=0; i<affected_edges.size(); i++){
        int iedge = affected_edges[i];
        Edge e = edges[iedge];
        int affected_node = e.node1 == current_node ? e.node2 : e.node1;
        if (nodes.count(affected_node)){
            heap_node_cost[affected_node].insert(Node(iedge, edges[iedge].cost));
        }
    }

    // main loop
    while (nodes.size()>0){
        // find min edge and node
        int min_cost = big;
        int min_cost_edge;
        int min_cost_node;
        for (unordered_set<int>::iterator iter = nodes.begin(); iter!=nodes.end(); iter++){
            int node_id = *iter;
            int cost = heap_node_cost[node_id].peek().key_;
            if (cost < min_cost) {
                int iedge = heap_node_cost[node_id].peek().id_;
                min_cost = cost;
                min_cost_edge = iedge;
                min_cost_node = node_id;
            }
        }
        mst.push_back(edges[min_cost_edge]);
        nodes.erase(min_cost_node);
        // update heaps
        current_node = min_cost_node;
        affected_edges = node_edges[current_node];
        nodes.erase(current_node);
        for (int i=0; i<affected_edges.size(); i++){
            int iedge = affected_edges[i];
            Edge e = edges[iedge];
            int affected_node = e.node1 == current_node ? e.node2 : e.node1;
            if (nodes.count(affected_node)){
                heap_node_cost[affected_node].insert(Node(iedge, edges[iedge].cost));
            }
        }
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
    file_stream >> num_nodes >> num_edges;
    cout<<"node:"<< num_nodes <<"  edges:" << num_edges <<endl;

    vector<Edge> edges;
    map<int, vector<int> > node_edges; 
    // map is in fact unnecessary here, can simply use index=node_id-1 to store in an array. I just want to make it more general
    unordered_set<int> nodes;
    for (int iedge=0; iedge<num_edges; iedge++){
        int node1, node2, cost;
        file_stream >> node1 >> node2 >> cost;
        Edge e(node1, node2, cost);
        edges.push_back(e);
        if (nodes.insert(node1).second) 
            node_edges.insert(pair<int, vector<int> >(node1, vector<int>(1,iedge)));
        else
            node_edges[node1].push_back(iedge);

        if (nodes.insert(node2).second) 
            node_edges.insert(pair<int, vector<int> >(node2, vector<int>(1,iedge)));
        else
            node_edges[node2].push_back(iedge);

    }     

    vector<Edge> mst = PrimMST(nodes, edges, node_edges);
    
    long total_cost(0); 
    for (int i=0; i<mst.size();i++){
        total_cost += mst[i].cost;
    }
    cout <<"Total cost of MST: "<< total_cost<<endl;    
    
    return 0;
}


