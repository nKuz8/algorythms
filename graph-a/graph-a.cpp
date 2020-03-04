
using namespace std;


template <typename T> struct Edge{
	int first;
	int second;
	T wieght;
};

template <class T> class Edge_Comp{
	public:
	bool operator() (Edge<T> first, Edge<T> last){
            return first.wieght < last.wieght;
        }
    };

template <typename T> class Graph {
	private:
		vector<vector<T>> S_matrix = {{0, 2, 1, 3, 0, 6, 0},
                         			  {2, 0, 0, 1, 3, 0, 0},
                         			  {1, 0, 0, 2, 0, 4, 0},
                        			  {3, 1, 2, 0, 0, 0, 1},
                         			  {0, 3, 0, 0, 0, 0, 4},
                         			  {6, 0, 4, 0, 0, 0, 7},
                        			  {0, 0, 0, 1, 4, 7, 0}};
		vector<vector<pair<int, T>>> S_list;
		vector<Edge<T>> Edge_list;
	public:
		Graph() {
			convert_to_list();
			convert_to_edge();
		}

		vector<T>& operator [] (int i) {
			return S_matrix[i];
		}

		void convert_to_list() {
			vector<pair<int, T>> temp;
			pair<int, T> node;
			for(int i = 0; i < S_matrix.size(); i++) {
				for(int j = 0; j < S_matrix[i].size(); j++){
					if (S_matrix[i][j] != 0) {
						node.first = j;
						node.second = S_matrix[i][j];
						temp.push_back(node);
					}
				}
			S_list.push_back(temp);
			temp.clear();	
			}
		}
		void convert_to_edge(){
			Edge<T> temp;
			for(int i = 0; i < S_matrix.size(); i++) {
				for(int j = 0; j < S_matrix[0].size(); j++) {
					if(S_matrix[i][j] != 0) {
						temp.first = i;
						temp.second = j;
						temp.wieght = S_matrix[i][j];
						Edge_list.push_back(temp);
					}
				}
			}
		}

		vector<T> depth_fisrt_search(int node){
			vector<T> result;
			result.push_back(node);
			vector<bool> visit(S_matrix[0].size(), {false});
			visit[node] = true;
			for(int i = 0; i < S_list[node].size(); i ++) {
				if(visit[S_list[node][i].first] == false) dps_rec(S_list[node][i].first, visit, result);
				}
			return result;	
			}
		void dps_rec(int node, vector<bool>& visit, vector<T>& result){
			result.push_back(node);	
			visit[node] = true;
			for(int i = 0; i < S_list[node].size(); i ++) {
					if(visit[S_list[node][i].first] == false) dps_rec(S_list[node][i].first, visit, result);
					}
		}

		vector<T> breadth_first_search(int node) {
			queue<T> Queue;
			vector<bool> visit(S_matrix[0].size(), {false});
			vector<T> result;
			int x;
			Queue.push(node);
			visit[node] = true;
			while(!Queue.empty()) {
				x = Queue.front();
				Queue.pop();
				result.push_back(x);
				for(int i = 0; i < S_list[x].size(); i++) {
					if(visit[S_list[x][i].first] == false) {
						Queue.push(S_list[x][i].first);
						visit[S_list[x][i].first] = true;
					}
				}
			}
			return result;
		}

		vector<T> Dijkstra_search(int node) {
			vector<T> D(S_matrix[0].size(), {INT_MAX});
			vector<bool> visit(S_matrix[0].size(), {false});
			D[node] = 0;
			T min;
			for (int k = 0; k < D.size(); k++) {
				min = 0;
				for(int i = 0; i < D.size(); i++) {
					if(D[i] <= D[min] && visit[i] == false) {
						min = i;
					}
				}
				visit[min] = true;
				for(int i = 0; i < S_list[min].size(); i++) {
					if(D[S_list[min][i].first] > D[min] + S_list[min][i].second) D[S_list[min][i].first] = D[min] + S_list[min][i].second;
				}
			}
			return D;
		}

		vector<vector<T>> Floyd_Warshall_search() {
			vector<vector<T>> Result(S_matrix);
			for(int i = 0; i < Result.size(); i ++){
				for(int j = 0; j < Result.size(); j++) {
					if(Result[i][j] == 0 && i != j) Result[i][j] = 20000000;
				}
			}
			for(int k = 0; k < S_matrix[0].size(); k++) {
				for(int i = 0; i < S_matrix[0].size(); i++) {
					for(int j = 0; j < S_matrix[0].size(); j++) {
						Result[i][j] = Min(Result[i][j], Result[i][k]+Result[k][j]);
					}
				}
			}
			return Result;
		}

		T Min (T a, T b) {
			if(a <= b) return a;
			else return b;
		}

		vector<T> Prim_tree(int node) {
			vector<T> D(S_matrix[0].size(), {INT_MAX});
			vector<int> Parent(S_matrix[0].size(), {NULL});
			vector<bool> visit(S_matrix[0].size(), {false});
			D[node] = 0;
			T min;
			for(int k = 0; k < visit.size(); k++) {
				min = 0;
				for(int i = 0; i < D.size(); i++) {
					if(D[i] <= D[min] && visit[i] == false) {
						min = i;
					}
				}
				visit[min] = true;
				for(int i = 0; i < S_list[min].size(); i++) {
					if(S_list[min][i].second < D[S_list[min][i].first] && visit[S_list[min][i].first] == false) {
						D[S_list[min][i].first] = S_list[min][i].second;
						Parent[S_list[min][i].first] = min;
					}
				}
			}
			return Parent;
		}

		vector<Edge<T>> convert_to_edge_k(){
			Edge<T> temp;
			vector<Edge<T>> Result;
			for(int i = 0; i < S_matrix.size(); i++) {
				for(int j = 0; j < i; j++) {
					if(S_matrix[i][j] != 0) {
						temp.first = i;
						temp.second = j;
						temp.wieght = S_matrix[i][j];
						Result.push_back(temp);
					}
				}
			}
			return Result;
		}

		vector<Edge<T>> Kruscal_tree() {
			vector<int> D(S_matrix[0].size(), {0});
			vector<Edge<T>> Edge_list_1 = convert_to_edge_k();
			vector<Edge<int>> Result;
			int temp;
			sort(Edge_list_1.begin(), Edge_list_1.end(), Edge_Comp<T>());
			for(int i = 0; i < D.size(); i++) D[i] = i;
			for(int i = 0; i < Edge_list_1.size(); i++) {
				if(D[Edge_list_1[i].first] != D[Edge_list_1[i].second]) {
					Result.push_back(Edge_list_1[i]);
					temp = D[Edge_list_1[i].first];
					for(int j = 0; j < D.size(); j++) {
						if(D[j] == temp) D[j] = D[Edge_list_1[i].second];
					}
				}
			}
			return Result;	
		}
};

