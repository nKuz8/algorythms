#include "map.cpp"
#include <random>

using namespace std;
int main() {
	random_device rd;
	mt19937_64 gen(rd());
	uniform_int_distribution<> dis(1, 100000);
	Map<int, int> tree;
	ofstream fout("statistic.txt");
	for(int j = 0; j < 50; j++) {
		for (int i = 0; i < 20000; i ++) {
			tree.Add_elem(dis(gen), 7);
			}
		cout<<tree.Is_Ok()<<endl;
		for (int i = 0; i < tree.GetCases().size(); i++) fout<<tree.GetCases()[i]<<'\t';
			
			if(j != 49) tree.clearAll();
		fout<<endl;	

	}
	fout.close();
	// tree.print_Tree();
	/*cout<<endl;
	tree.Remove_elem(0);
	tree.print_Tree();
	cout<<endl;
	tree.Remove_elem(1);
	tree.print_Tree();
	cout<<endl;
	tree.Remove_elem(2);
	tree.print_Tree();
	cout<<endl;
	tree.Remove_elem(3);
		tree.print_Tree();
	cout<<endl;*/
	for(int i = 0; i < 50; i++) {
		tree.Remove_elem(dis(gen));
	}
	cout<<tree.Is_Ok()<<endl;
	return 0;
}