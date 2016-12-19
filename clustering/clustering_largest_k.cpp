#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm> // for sort
#include<unordered_set>
#include<bitset>
#include<sstream>

using namespace std;

// currently 24 is hard-coded
const int NumBit = 24;

struct Node{
    bitset<NumBit> label;
    int id;
    bool operator==(const Node & other) const {
        return other.label==label;
    }
};

struct NodeHasher{
    size_t operator()(const Node & n) const{
        hash<bitset<NumBit> > hash_fn;
        return hash_fn(n.label);
    }
};

struct Edge{
    Edge(int n1, int n2){
        node1=n1; node2=n2; 
    };
    int node1;
    int node2;
};

int distance(Node e1, Node e2){
    return NumBit-(e1.label ^ ~e2.label).count();
}

Node FormNode(int id, string bits){
    Node n;
    n.id = id;
    stringstream ss(bits);
    for (int i=0; i<NumBit; i++){
        bool temp;
        ss >> temp;
        n.label[i] = temp;
    }
    return n;
}

vector<Node> D1Candidate(Node n){
    vector<Node> candidates(NumBit, n);
    for (int i = 0; i<NumBit; i++){
        candidates[i].label.flip(i);
    }
    return candidates;
}

vector<Node> D2Candidate(Node n){
    vector<Node> candidates((NumBit*(NumBit-1))/2, n);
    int i_case(0);
    for (int i = 0; i<NumBit; i++){
        for (int j = i+1; j <NumBit; j++){
            candidates[i_case].label.flip(i);
            candidates[i_case].label.flip(j);
            i_case++;
        }
    }
    return candidates;
    
}

void ComputeSmallEdges(vector<Edge> & edges, vector<Node> const & nodes, unordered_multiset<Node, NodeHasher> const & node_multiset){
    int num_node = nodes.size();
    typedef unordered_multiset<Node,NodeHasher>::iterator Iter; 
    vector<Edge> d0_edge;
    vector<Edge> d1_edge;
    vector<Edge> d2_edge;
    for (int i=0; i<num_node; i++){
        // distance 0
        pair<Iter, Iter> range = node_multiset.equal_range(nodes[i]);
        for (Iter iter = range.first; iter != range.second; iter++){
            if (iter->id > i)
                d0_edge.push_back(Edge(i, iter->id));
        }
        // distance 1
        vector<Node> d1 = D1Candidate(nodes[i]);
        for (vector<Node>::iterator iter_d1 = d1.begin(); iter_d1 != d1.end(); iter_d1++){
            pair<Iter, Iter> range = node_multiset.equal_range(*iter_d1);
            for (Iter iter = range.first; iter != range.second; iter++){
                if (iter->id > i)
                    d1_edge.push_back(Edge(i, iter->id));
            }
        }
        // distance 2
        vector<Node> d2 = D2Candidate(nodes[i]);
        for (vector<Node>::iterator iter_d2 = d2.begin(); iter_d2 != d2.end(); iter_d2++){
            pair<Iter, Iter> range = node_multiset.equal_range(*iter_d2);
            for (Iter iter = range.first; iter != range.second; iter++){
                if (iter->id > i)
                    d2_edge.push_back(Edge(i, iter->id));
            }
        }
    }
    edges.insert(edges.end(), d0_edge.begin(), d0_edge.end());
    edges.insert(edges.end(), d1_edge.begin(), d1_edge.end());
    edges.insert(edges.end(), d2_edge.begin(), d2_edge.end());
    cout <<"Number of edges with distance 0, 1, 2:  "<< d0_edge.size() <<", "<< d1_edge.size()<<", "<<d2_edge.size()<<endl;
}


void Clustering(vector<Node> nodes, vector<Edge> edges, int & k){
    cout <<"Clustering"<<endl;
    int num_nodes = nodes.size();
    vector<int> parents;
    unordered_set<int> cluster_leaders;
    
    for (int i=0; i<num_nodes;i++) {
        parents.push_back(i);
        cluster_leaders.insert(i);
    }
    
    vector<Edge>::iterator iter = edges.begin();
    while (iter != edges.end()){
        int s1 = parents[iter->node1];
        int s2 = parents[iter->node2];
        if (s1 != s2){
            for (int i=0; i<num_nodes;i++)
                if (parents[i] == s2) parents[i] = s1;
            cluster_leaders.erase(s2);
        }
        iter++;
    }
    k = cluster_leaders.size();
}


int main(int argc, char* argv []){

    if (argc<2){
        cerr <<"You should specify a file name."<<endl;
        return 1;
    }
    ifstream file_stream (argv[1]);
    if (!file_stream){
        cerr <<"Error: File not opened."<<endl;
        return 1;
    }
    int num_node;
    int num_bit;
    file_stream >> num_node >> num_bit;
    cout<< "number of node: "<<num_node<<endl;
    vector<Node> nodes;
    unordered_multiset<Node, NodeHasher> node_multiset;
    cout << "size of node set "<<node_multiset.size()<<endl;
    string bit_string;
    int id = 0;
    getline(file_stream, bit_string); // to discard the first line
    while (getline(file_stream, bit_string)){
        Node n = FormNode(id, bit_string);   
        nodes.push_back(n);
        node_multiset.insert(n);
        id++;
    }
    cout << "node.size() = "<<nodes.size()<<endl;
    cout << "node_multiset.size() = "<<node_multiset.size()<<endl;

    vector<Edge> edges;
    ComputeSmallEdges(edges, nodes, node_multiset);

    int k; 
    Clustering(nodes, edges, k);
    cout <<"Number of clusters (after mergeing all edges with distance <= 2) : "<< k <<endl;

    return 0;
}



