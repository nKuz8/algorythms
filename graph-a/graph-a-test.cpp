#include "graph-a.h"
#include "graph-a.cpp"

using namespace std;

int main() {
	Graph <int> graph;

	vector<int> search = graph.Dijkstra_search(4);
	cout<<"The shortest ways from the 4-th node to all other nodes found by Dijkstra search:"<<endl;
	for(int i = 0; i < search.size(); i++) cout<<search[i]<<'\t';
	cout<<"\n";
	vector<vector<int>> Search = graph.Floyd_Warshall_search();
	cout<<"The shortest ways in  this graph: "<<endl;	
	for(int i = 0; i < Search.size(); i++){
		for(int j = 0; j < Search[i].size(); j++) cout<<Search[i][j]<<'\t';
		cout<<endl;	
	}
	search.clear();
	search = graph.Prim_tree(1);
	cout<<"Minimum spanning tree found by Prim algorythm: "<<endl;
	for(int i = 0; i < search.size(); i++) cout<<search[i]<<'\t';
	cout<<"\n";
	vector<Edge<int>> Tree = graph.Kruscal_tree();
	cout<<"Minimum spanning tree found by Kruscal algorythm: "<<endl;
	for(int i = 0; i < Tree.size(); i++) cout<<Tree[i].first<<Tree[i].second<<'\t';	
	return 0;
}