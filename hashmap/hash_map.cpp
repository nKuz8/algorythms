#include "hash_map.h"

int main() {
	HashMap<int, int> Map;
	random_device rd;
	mt19937_64 gen(rd());
	uniform_int_distribution<> dis(1, 100000);
	cout<<Map.GetLoad()<<endl;
	for(int j = 0; j < 5; j++) {
		for (int i = 0; i < 50000; i ++) {
			Map.Add_elem(dis(gen), dis(gen));
			}
		}
	printf("%f\n%d\n", Map.GetLoad(), Map.GetElem());	
	Map.Remove(6);

}

