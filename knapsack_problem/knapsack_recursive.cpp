#include<iostream>
#include<fstream>
#include<vector>
#include<unordered_map>
using namespace std;

int max(int i, int j){
    return i>j ? i : j;
}

class Optimal{
    public:
        Optimal(int num_items, int weight_limit);  
        ~Optimal();  
        bool isKnown(int item_number_cap, int weight_cap) const;
        int getValue(int item_number_cap, int weight_cap);
        void setValue(int item_number_cap, int weight_cap, int value);

    private:
        int weight_limit_;
        int num_items_;
        int count_;
        unordered_map<int, int> * ValueArr_;

};

Optimal::Optimal(int num_items, int weight_limit) {
    num_items_ = num_items; 
    weight_limit_ = weight_limit; 
    count_ = 0; 
    if (num_items_ > 0)
        ValueArr_ = new unordered_map<int,int>[num_items_ + 1];
    else
        ValueArr_ = NULL;
};  

bool Optimal::isKnown(int item_number_cap, int weight_cap) const { 
    return ValueArr_[item_number_cap].count(weight_cap) > 0; 
};

int Optimal::getValue(int item_number_cap, int weight_cap){
    return ValueArr_[item_number_cap][weight_cap];
};


void Optimal::setValue(int item_number_cap, int weight_cap, int value){
    ValueArr_[item_number_cap][weight_cap] = value;
    count_++;
};

Optimal::~Optimal(){
    if (ValueArr_ != NULL) {
        delete [] ValueArr_;
    }
    cout <<"Number of call to setValue()  "<<count_<<endl;
}


int Knapsack(int item_number_cap, int weight_cap, Optimal & optimal, vector<int> & values, vector<int> & weights){

    if (item_number_cap < 1 || weight_cap < 1) {
        return 0;
    }
    int v_item = values[item_number_cap-1];
    int w_item = weights[item_number_cap-1];
    if (optimal.isKnown(item_number_cap, weight_cap) ) {
        return optimal.getValue(item_number_cap,weight_cap);      
    }
    int result;
    if (weight_cap < w_item) {
        result = Knapsack(item_number_cap-1, weight_cap, optimal, values, weights);
        optimal.setValue(item_number_cap, weight_cap, result);      
        return result;
    }

    int v_exclude = Knapsack(item_number_cap-1, weight_cap,        optimal, values, weights);
    int v_include = Knapsack(item_number_cap-1, weight_cap-w_item, optimal, values, weights) + v_item;
    result = max(v_exclude, v_include);
    optimal.setValue(item_number_cap, weight_cap, result);      
    return result;
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

    int num_items;
    int weight_limit;
    file_stream >> weight_limit >> num_items;
    cout<< "knapsack weight limit: " << weight_limit << endl
        << "number of items: " << num_items << endl;

    vector<int> values;
    vector<int> weights;
    int v, w;
    while (file_stream >> v >> w){
        values.push_back(v);
        weights.push_back(w);
    }
    cout<< "size of values and weighs: " <<values.size()<<", "<<weights.size()<<endl;

    Optimal optimal(num_items, weight_limit);

    Knapsack(num_items, weight_limit, optimal, values, weights);
    cout<< "optimal total item values: " << optimal.getValue(num_items, weight_limit) << endl;  

    return 0;
}
