#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

int max(int i, int j){
    return i>j ? i : j;
}

void Knapsack(vector<vector<int> > & optimal, vector<int> & values, vector<int> & weights){
    cout << "in knapsack"<<endl;
    int num_items = optimal.size()-1;
    int weight_limit = optimal[0].size()-1;
    for (int w_cap=0; w_cap<=weight_limit; w_cap++)
        optimal[0][w_cap] = 0;
    
    for (int i=1; i<=num_items; i++){
        int v_item = values[i-1];
        int w_item = weights[i-1];
        for (int w_cap=0; w_cap<=weight_limit; w_cap++){
            if (w_cap < w_item){
                optimal[i][w_cap] = optimal[i-1][w_cap];
            }
            else{
                int v_exclude = optimal[i-1][w_cap];
                int v_include = optimal[i-1][w_cap-w_item] + v_item;
                optimal[i][w_cap] = max(v_include, v_exclude);
            }
        }
    }      

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

    vector<vector<int> > optimal(num_items+1);
    for (int i=0;i<=num_items;i++)
        optimal[i].resize(weight_limit+1);

    Knapsack(optimal, values, weights);
    cout<< "optimal total item values: " << optimal[num_items][weight_limit] << endl;  

    return 0;
}
