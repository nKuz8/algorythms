#include "graph-b.h"
#include "graph-b.cpp"

int main() {
	vector<vector<int>> Temp = {{0, 1, 1, 0, 0, 0, 0},
                				{0, 0, 0, 1, 0, 0, 0},
                				{0, 0, 0, 1, 0, 1, 0},
                				{0, 0, 0, 0, 0, 0, 1},
                				{0, 0, 0, 0, 0, 1, 0},
                				{0, 0, 0, 0, 0, 0, 1},
                				{0, 0, 0, 0, 0, 0, 0}};
	Graph <int> graph1(Temp);
	stack<int> sort = graph1.Tarjan_algorythm(0);
	size_t size = sort.size();
	cout<<"Tarjan_algorythm"<<endl;
	for(int i = 0; i < size; i++) {
		cout<<sort.top()<<'\t';
		sort.pop();
	}
	cout<<endl;
	Temp = {{0, 1, 1, 1, 1, 0},
            {1, 0, 1, 1, 1, 0},
            {1, 1, 0, 1, 0, 1},
            {1, 1, 1, 0, 1, 0},
            {1, 1, 0, 1, 0, 1},
            {0, 0, 1, 0, 1, 0}};
	Graph <int> graph2(Temp);
	Graph <int> graph3(Temp);
	vector<Edge<int>> Result = graph3.Fleury_algorythm(0);
	cout<<"Fleury_algorythm"<<endl;
	for(int i = 0; i < Result.size(); i ++) cout<<Result[i].first<<Result[i].second<<'\t';
	cout<<endl;
	cout<<"Cycle algorythm"<<endl;	
	vector<int> result = graph3.FindEulerPath(0);
	for(int i = 0; i < result.size(); i ++) cout<<result[i]<<'\t';
	cout<<endl;	
	Temp = {{0, 0, 0, 1, 0, 0, 0, 0}, 
			{1, 0, 0, 0, 0, 0, 0, 0},
			{0, 1, 0, 0, 1, 0, 1, 0},
			{1, 0, 0, 0, 1, 0, 0, 0},
			{0, 1, 0, 0, 0, 0, 0, 0},
			{0, 0, 1, 0, 1, 0, 0, 0},
			{0, 1, 1, 0, 0, 1, 0, 0},
			{0, 0, 0, 0, 1, 0, 1, 0}};
	Graph <int> graph4(Temp);
	cout<<"Kosaraju_Algorythm"<<endl;						  		
	graph4.Kosaraju_Algorythm();					  
    return 0;             
}