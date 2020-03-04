#include <vector>
#include <iostream>
#include <list>
#include <functional>
#include <random>

using namespace std;

template <typename V, typename K> struct HashNode {
	V value;
	K key;
};

template <typename V, typename K, typename F = hash<K>> class HashMap{
	private:
		vector<list<HashNode<V, K>>> mainTable;
		size_t Elem_number;
		size_t List_number;
		float a = 2.0;
		F hashFunc;

	public:
		HashMap() {
			Elem_number = 0;
			List_number = 10;
			mainTable.resize(List_number);
		}
		~HashMap() {
			Elem_number = 0;
			List_number = 0;
			mainTable.clear();
			mainTable.resize(List_number);
		}

		void Add_elem (V value, K key) {
			HashNode<V, K> elem;
			elem.value = value;
			elem.key = key;
			mainTable[hashFunc(key) % List_number].push_back(elem);
			Elem_number++;
			if(Elem_number / List_number >= a) reHash(2*List_number + 1);
		}

		V Search(K key) {
			for(auto i = mainTable[hashFunc(key) % List_number].begin(); i != mainTable[hashFunc(key) % List_number].end(); ++i) {
				if((*i).key == key) return (*i).value;
			}
			return -1;
		}

		void reHash(size_t size) {
			if(size > List_number) {
				vector<list<HashNode<V, K>>> copyTable(mainTable);
				mainTable.clear();
				List_number = size;
				mainTable.resize(List_number);
				for(int i = 0; i < copyTable.size(); i++) {
					for(auto j = copyTable[i].begin(); j != copyTable[i].end(); ++j) {
						mainTable[hashFunc((*j).key) % List_number].push_back((*j));
					}
				}
				copyTable.clear();
			}
		}

		void ClearAll() {
			Elem_number = 0;
			mainTable.clear();
		}

		void Remove(K key) {

			for(auto i = mainTable[hashFunc(key) % List_number].begin(); i != mainTable[hashFunc(key) % List_number].end(); ++i) {
				if((*i).key == key) {
					cout<<"Deleted!"<<endl;
					mainTable[hashFunc(key) % List_number].erase(i);
					Elem_number--;
					return;
				}
			}
			cout<<"No such element!"<<endl;
			return;
		}

		float GetLoad() {
			return (float)Elem_number/(float)List_number;
		}

		void SetLoad(float size) {
			a = size;
			reHash((size_t)Elem_number/a);
		}
		size_t GetList() {
			return List_number;
		}	

		size_t GetElem() {
			return Elem_number;
		}
};
 