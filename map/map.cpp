#include <iostream>
#include <vector>
#include <ctime>
#include <vector>
#include <fstream>
#define red true
#define black false
using namespace std;

template <typename T, typename K> struct Node {
	Node<T, K>* left = nullptr;
	Node<T, K>* right = nullptr;
	Node<T, K>* parent = nullptr;
	bool color; 
	K key;
	T Data;
	void operator = (Node<T, K> temp)	{
		this->left = temp.left;
		this->right = temp.right;
		this->parent = temp.parent;
		this->color = temp.color;
		this->Data = temp.Data;
		this->key = temp.key;
	}
	Node () {
		left = nullptr;
		right = nullptr;
		parent = nullptr;
		color = red;
		key = 0;
		Data = 0;
	}
	Node(Node<T, K>* temp) {
            this->Data = temp->Data;
            this->key = temp->key;
            this->color = temp->color;

            if (temp->left != this->leaf) {
                this->left = new Node<T, K>(temp->left);
                this->left->parent = this;
            }
            if (temp->right != this->leaf) {
                this->right = new Node<T, K>(temp->right);
                this->right->parent = this;
            }
        }
};

template <typename T, typename K> class Map {
	private: 
		Node<T, K>* root;
		Node<T, K>* leaf = new Node<T, K>;
		size_t size;
		vector<int> cases; 

	public:
		Map() {
			root = this->leaf;
			size = 0;
			this->leaf->color = black;
			cases.resize(4);
		}

		Map(Map<T, K>* map)
    	{
       	 	root = new Node<T, K>;
       	 	root = map->root;
    	}
    	Map<T, K>* operator=(Map<T, K>* map)
   	 	{
        this = map;
        return *this;
    	}
		bool Is_empty() {
			if (root == this->leaf) return true;
			else return false;
		}


		void Add_elem(int Key, T item){
			Node<T, K>* temp = new Node<T, K>;
			temp->key = Key;
			temp->Data = item;
			temp->color = red;
			temp->left = this->leaf;
			temp->right = this->leaf;
			if(size == 0) {
				size ++;
				root = temp;
				root->color = black;
			}
			else {
				if(root->key >= Key) {
					if(root->left == this->leaf){
					root->left = temp;
					temp->parent = root;
					size++;
					}
					else Add_elem_Rec(temp, root->left);
				}
				else {
					if (root->right == this->leaf) {
						root->right = temp;
						temp->parent = root;
						size++;
						}
					else Add_elem_Rec(temp, root->right);	
					}
				balance_add(temp);	
				}
			}	
		void print_Tree()
		{
		if(root == this->leaf) cout<<"The tree is empty!"<<endl;
		else {	
			cout << root->key << root->color << endl;
			recursive_print(root);
			}
		}
		void recursive_print(Node<T, K>* temp)
		{
		if (temp->left != this->leaf){
		cout<<"left of "<<temp->key<<endl;	
		cout << temp->left->key << temp->left->color << endl;
		recursive_print(temp->left);
		cout << "end left of "<<temp->left->key<<endl;
		}
		if (temp->right != this->leaf){
		cout<<"right of "<<temp->key<<endl;	
		cout << temp->right->key << temp->right->color << endl;
		recursive_print(temp->right);
		cout << "end right of "<<temp->right->key<<endl;
			}
		}

		void Add_elem_Rec(Node<T, K>* elem, Node<T, K>* node) {
			if(node->key >= elem->key) {
				if(node->left == this->leaf){
					node->left = elem;
					elem->parent = node;
					size++;
				}
				else Add_elem_Rec(elem, node->left);
			}
			else {
				if(node->right == this->leaf) {
					node->right = elem;
					elem->parent = node;
					size++;
				}
				else Add_elem_Rec(elem, node->right);
			}
		}

		void balance_add(Node<T, K>* elem) {
			Node<T, K> * uncle;
			Node<T, K> * Par = elem->parent;
			if (elem == root) {
				elem->color = black;
				cases[0]++;
			}
			else if(Par->color == red) {
				Par->parent->left == Par ? uncle = Par->parent->right : uncle = Par->parent->left;
				if(uncle->color == red) {
					Par->color = black;
					uncle->color = black;
					Par->parent->color = red;
					cases[1]++;
					balance_add(Par->parent);
				}
				else {
					Node<T, K> * GrPar = elem->parent->parent;
					if(GrPar->left->right == elem) {
						Left_Rotate(elem, Par, GrPar);
						Right_Rotate(elem, elem->parent, elem->parent->parent);
						cases[2]++;
					}
					else if(GrPar->right->left == elem) {
						Right_Rotate(elem, Par, GrPar);
						Left_Rotate(elem, elem->parent, elem->parent->parent);
						cases[2]++;

					}
					else if(GrPar->right->right == elem) Left_Rotate(Par, GrPar, GrPar->parent);
					else if(GrPar->left->left == elem) Right_Rotate(Par, GrPar, GrPar->parent);
					cases[3]++;
					GrPar->color = red;
					GrPar->parent->color = black;

				}
			}
		}

		void Left_Rotate(Node<T, K>* elem, Node<T, K>* Par, Node<T, K>* GrPar) {
			if(Par == root) {
				root = elem;
				Par->right = elem->left;
				Par->right->parent = Par;
				Par->parent = elem;
				elem->left = Par;	
			}
			else {
				GrPar->left == Par ? GrPar->left = elem : GrPar->right = elem;
				elem->parent = GrPar;
				Par->right = elem->left;
				Par->right->parent = Par;
				elem->left = Par;
				Par->parent = elem;
			}
		}

		void Right_Rotate(Node<T, K>* elem, Node<T, K>* Par, Node<T, K>* GrPar){
			if(Par == root) {
				root = elem;
				Par->left = elem->right;
				Par->left->parent = Par;
				elem->right = Par;
				Par->parent = elem;
			}
			else {
				GrPar->left == Par ? GrPar->left = elem : GrPar->right = elem;
				elem->parent = GrPar;
				Par->left = elem->right;
				Par->left->parent = Par;
				elem->right = Par;
				Par->parent = elem;
			}
		}

		void Remove_elem(T elem) {
			Node<T, K>* temp = root;
			Node<T, K>* del = root;
			bool dir = false;

			while(elem != temp->key && temp != this->leaf) {
				if(elem < temp->key) {
					temp = temp->left;
					dir = true;
					}
				else {
					temp = temp->right;
					dir = false;
				}
			}
			if(temp == this->leaf) {
				cout<<"No such element found!"<<endl;
				return;
			}

			if(temp->left == this->leaf && temp->right == this->leaf) {

				if(temp->color == red) {
					dir ? temp->parent->left = this->leaf : temp->parent->right = this->leaf;
					temp = this->leaf;
					size--;
					return;
				}
				else {
					if(temp == root) {
						root = this->leaf;
						return;
					}
					else {
						balance_del(temp);
						temp->color = red;
						Remove_elem(temp->key);
					}
				}
			}
			else if(temp->left == this->leaf && temp->right != this->leaf) {
				if(temp == root) {
					temp->right->color = black;
					root = temp->right;
					temp = this->leaf;
					return;
				}
				temp->right->color = black;
				dir ? temp->parent->left = temp->right : temp->parent->right = temp->right;
				temp->right->parent = temp->parent;
				temp = this->leaf;
				return;
			}
			else if(temp->left != this->leaf && temp->right == this->leaf) {
				if(temp == root) {
					temp->left->color = black;
					root = temp->left;
					temp = this->leaf;
					return;
				}
				temp->left->color = black;
				dir ? temp->parent->left = temp->left : temp->parent->right = temp->left;
				temp->left->parent = temp->parent;
				temp = this->leaf;
				return;
			}
			else {
				Node<T, K>* del = new Node<T, K>;
				del = temp;
				temp = temp->right;
				if(temp->left == this->leaf) {
					if(temp->color == red) {
						temp->parent->Data = temp->Data;
						temp->parent->key = temp->key;
						temp->parent->right = this->leaf;
						delete &temp;
						return;
					}
					else {

						balance_del(temp);
						temp->parent->Data = temp->Data;
						temp->parent->key = temp->key;
						temp->parent->right == temp ? temp->parent->right = this->leaf : temp->parent->left = this->leaf;
						delete &temp;
						return;
					}
				}
				else {
					while (temp->left != this->leaf) temp = temp->left;
					if (temp->right == this->leaf) {
						if(temp->color == red) {
						temp->parent->left = this->leaf;
						del->Data = temp->Data;
						del->key = temp->key;
						delete &temp;
						return;
						}
						else {
							balance_del(temp);
							temp->parent->Data = temp->Data;
							temp->parent->key = temp->key;
							temp->parent->right == temp ? temp->parent->right = this->leaf : temp->parent->left = this->leaf;
							delete &temp;
							return;
						}
					}
					else {
						if(temp->color == red) {
							temp->parent->left = temp->right;
							temp->right->parent = temp->parent;
							del->Data = temp->Data;
							del->key = temp->key;
							temp = this->leaf;
							return;
						}
						else {
							int Key = temp->key;
							T Dat = temp->Data;
							Remove_elem(temp->key);
							del->Data = Dat;
							del->key = Key;
							return;
						}
					}
				}	
			}

		}

		void balance_del(Node<T, K>* elem) {
			if(elem == root) {


			}
			else {
				Node<T, K>* S_x;
				elem->parent->left == elem ? S_x = elem->parent->right : S_x = elem->parent->left;


				if(S_x->color == red) {

					S_x->color = black;
					elem->parent->color = black;
					elem->parent->left == elem ? Left_Rotate(S_x, S_x->parent, S_x->parent->parent) : Right_Rotate(S_x, S_x->parent, S_x->parent->parent);
				}
				else {			
					if(S_x->left->color == black && S_x->right->color == black && S_x->parent->color == black) {
						S_x->color = red;

						balance_del(S_x->parent);
						return;	
					}
					
	
				}
				if(S_x->left->color == black && S_x->right->color == black && S_x->parent->color == red) {
						S_x->color = red;
						S_x->parent->color = black;
					}
				else {

					if((S_x->parent->left->left->color == black && S_x->parent->left == S_x) || (S_x->parent->right->right->color == black && S_x->parent->right == S_x)) {

						S_x->parent->right == S_x ? Right_Rotate(S_x->left, S_x, S_x->parent) : Left_Rotate(S_x->right, S_x, S_x->parent);
						S_x->parent->color = black;
						S_x->color = red;
						S_x->parent->right == S_x ? Left_Rotate(S_x->parent, elem->parent, elem->parent->parent) : Right_Rotate(S_x->parent, elem->parent, elem->parent->parent);
						S_x->parent->color = elem->parent->color;
						elem->parent->color = black;
						S_x->color = black;
					}
					else {
						S_x->parent->right == S_x ? Left_Rotate(S_x, S_x->parent, S_x->parent->parent) : Right_Rotate(S_x, S_x->parent, S_x->parent->parent);
						S_x->color = elem->parent->color;
						elem->parent->color = black;
						S_x->left == elem->parent ? S_x->right->color = black : S_x->left->color = black;
					}

				}	
			}
		}

	void clearAll() {
        recursive_Clear(this->root);
        size = 0;
        for(int i = 0; i < 4; i++) cases[i] = 0;
        root = this->leaf;
    	}

    void recursive_Clear(Node<T, K>* elem) {
        if (elem->left != this->leaf) {
            recursive_Clear(elem->left);
        	}
        if (elem->right != this->leaf) {
            recursive_Clear(elem->right);
        }
        elem = this->leaf;

    }

    T search(K key) {
    	Node<T, K>* temp = root;
 		bool find = true;

    	while(key != temp->key) {
				if(key < temp->key) {
					if(temp->left == this->leaf) {
						find = false;
						break;
						}
					temp = temp->left;
					}
				else if (key > temp->key){
					if(temp->right == this->leaf) {
						find = false;
						break;
						}
					temp = temp->right;
				}

			}
		if(!find) {
			cout<<"No such element!"<<endl;
			return -1;
		}
		else return temp->Data;	
    }

    T operator [](K Key) {
    	return search(Key);
    }

    bool Is_Ok() {
        int BlackHeightGlobal = 0;
        Node<T, K>* elem = this->root;
        while (elem != this->leaf) {
            if (elem->color == black) BlackHeightGlobal++;
            else if (elem->left->color == red && elem->left != this->leaf || elem->right->color == red && elem->right != this->leaf){
             	return false;
             }
            elem = elem->left;
        }
        int BlackHeight = 0;
        return Is_Ok_Rec(root, BlackHeight, BlackHeightGlobal);
    }

   bool Is_Ok_Rec(Node<T, K>* elem, int height, int Global) {
        if (elem->color == black)
            height++;
        else if (elem->left->color == red && elem->left != this->leaf || elem->right->color == red && elem->right != this->leaf)
            return false;
        if (elem->left != this->leaf)
            return Is_Ok_Rec(elem->left, height, Global);
        else if (elem->right != this->leaf)
            return Is_Ok_Rec(elem->right, height, Global);
        else
            return height == Global;
    }

    vector<int> GetCases() {
    	return cases;
    }

};

