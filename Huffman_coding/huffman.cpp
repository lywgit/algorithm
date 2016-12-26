#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm> // for heap 
#include <string>
#include <unordered_map>
using namespace std;

typedef long Key;

struct Node {
    Node(int i, Key w){ id = i; weight = w; left=NULL; right=NULL;};
    int id;
    Key weight;
    Node *left;
    Node *right;
};

class Tree {
    public:
        Tree(){ root_ = NULL;};
        ~Tree(){ DestroyTree(); };
        void Insert();
        Node *MakeRoot(Node n);
        Node *get_root() {return root_;} ; 
        Node *Search(int id){ return Search(id, root_); };
        Node *GetAddress(int id){ return node_address.find(id)->second; };
        void InsertChildrenAt(Node * target, Node child1, Node Child2);
        void DestroyTree(){ DestroyTree(root_);};

    private:
        Node *root_;
        void DestroyTree(Node * leaf);
        void Insert(Node * leaf);
        Node *Search(int id , Node * n);
        unordered_map<int, Node*> node_address;
};

Node MergeNodes(Node node1, Node node2){
    static int id(-1);
    return Node(id--, node1.weight+node2.weight);
}

void Tree::DestroyTree(Node *leaf){
    if (leaf != NULL){
        DestroyTree(leaf->left);
        DestroyTree(leaf->right);
        delete leaf;
    }
}

Node * Tree::Search(int id,  Node* n){
    if (n != NULL){
        if (n->id == id) return n;
        Node * result = Search(id, n->left);
        if (result != NULL){
            return result;
        }else{
            return Search(id, n->right);
        }       
    }else{
        return NULL;    
    }

}

Node* Tree::MakeRoot(Node n){
    root_ = new Node(n.id, n.weight);
    return root_;
}
void Tree::InsertChildrenAt(Node * target, Node child1, Node child2){
    target->left  = new Node(child1.id, child1.weight);
    target->right = new Node(child2.id, child2.weight);
    node_address.insert(pair<int, Node*>(child1.id, target->left));
    node_address.insert(pair<int, Node*>(child2.id, target->right));
}

struct comparator{
    bool operator()(Node i, Node j){ return i.weight > j.weight; }
};

Node PopNode(vector<Node> & symbols){
    Node n = symbols.front();
    pop_heap(symbols.begin(), symbols.end(), comparator()); // The front node is placed at the back and is not deleted
    symbols.pop_back();
    return n;
}

void PushNode(vector<Node> & symbols, Node n){ 
    symbols.push_back(n);
    push_heap(symbols.begin(), symbols.end(), comparator());
}

void HuffmanCoding(vector<Node> & symbols, Tree & tree){
    if (symbols.size() == 2){
        Node A = PopNode(symbols);
        Node B = PopNode(symbols);
        Node AB = MergeNodes(A, B);
        //cout <<"Merging "<<A.id<<" "<<B.id<<" into "<<AB.id<<" weights: "<<A.weight<<"+"<<B.weight<<"="<<AB.weight<<endl;

        Node* root_ptr = tree.MakeRoot(AB);
        //cout <<"Making root with node id "<<AB.id<<endl;
        tree.InsertChildrenAt(root_ptr, A, B); 
        //cout <<"Two children: "<<A.id<<" "<<B.id<<endl;
        return;
    }
    Node A = PopNode(symbols);
    Node B = PopNode(symbols);
    Node AB = MergeNodes(A, B);
    //cout <<"Merging "<<A.id<<" "<<B.id<<" into "<<AB.id<<" weights: "<<A.weight<<"+"<<B.weight<<"="<<AB.weight<<endl;
    PushNode(symbols, AB);

    HuffmanCoding(symbols, tree);

    //Node * AB_ptr = tree.Search(AB.id); // with node_address keeping the mapping, don't need the search anymore
    Node * AB_ptr = tree.GetAddress(AB.id);
    tree.InsertChildrenAt(AB_ptr, A, B);
    //cout <<"Unpacking "<< AB_ptr->id<<" into " <<A.id <<" and "<< B.id<<endl;
    
    return;
}

void CheckLevel(Node * n, int depth, int & max, int & min){    
    if (n != NULL){
        int id = n->id;
        if (id >= 0){
            max = max > depth ? max : depth;
            min = min < depth ? min : depth;
        }
        CheckLevel(n->left,  depth+1, max, min);
        CheckLevel(n->right, depth+1, max, min);
    }
}

void FindMaxMinCodeWordLength(Tree & tree, int & max, int & min){
    cout <<"Finding Max/Min level of coding ..."; 
    Node * root = tree.get_root();
    CheckLevel(root, 0, max, min);
    cout << " done."<<endl;
}

int main(int argc, char* argv[]){

    if (argc<2){
        cerr <<"You should specify a file name."<<endl;
        return 1;
    }
    fstream file_stream (argv[1]);
    if (!file_stream){
        cerr <<"Error: File not opened."<<endl;
        return 1;
    }

    int num_symbols;
    file_stream >> num_symbols;
    cout << "number of symbols: "<<num_symbols << endl;
    
    vector<Node> symbols;
    int w;
    int id = 0;
    while (file_stream >> w){
        symbols.push_back(Node(id++, w));    
    }
    cout << "symbols.size: "<< symbols.size()<<endl;

    make_heap(symbols.begin(), symbols.end(), comparator()); 
    Tree tree;
    HuffmanCoding(symbols, tree);
    
    int max(0), min(num_symbols);
    FindMaxMinCodeWordLength(tree, max, min);
    cout<<"Maximum/Minumum codeword length: "<<max<<" "<<min<<endl; 
    

    return 0;
}
