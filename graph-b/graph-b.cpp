using namespace std;


template <typename T> struct Edge{
	int first;
	int second;
	T wieght;
};

template <typename T> class Graph {
	private:
		vector<vector<T>> S_matrix; 
		vector<vector<pair<int, T>>> S_list;
		vector<Edge<T>> Edge_list;
	public:
		Graph(vector<vector<T>> Matrix) {
			if(S_matrix.size() != 0) {
				for(int i = 0; i < S_matrix.size(); i ++) {
					S_matrix[i].clear();
					S_list[i].clear();
				}
				S_list.clear();
				S_matrix.clear();
				Edge_list.clear();	
			}
			vector<T> Temp;
			for(int i =0; i < Matrix.size(); i ++) {
				for(int j =0; j < Matrix[i].size(); j ++) Temp.push_back(Matrix[i][j]);
				S_matrix.push_back(Temp);
				Temp.clear();	
			}
			convert_to_list();
			convert_to_edge();
		}
		vector<T>& operator [] (int i) {
			return S_matrix[i];
		}

		void convert_to_list() {
			S_list.clear();
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
			Edge_list.clear();
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

		stack<int> Tarjan_algorythm(int node) {
			vector<bool> Visit(S_matrix[0].size(), false);
			stack <int> Time;
			for(int i = 0; i < Visit.size(); i ++) {
				if(Visit[i] == false) dfs_inv(Time, Visit, i);
			}
			return Time;
		}

		void dfs_inv(stack<int>& Time, vector<bool>& Visit, int node) {
			Visit[node] = true;
			for(int i = 0; i < S_list[node].size(); i++) {
				if(Visit[S_list[node][i].first] == false) {
					dfs_inv(Time, Visit, S_list[node][i].first);
				}
			}
			// cout<<node;
			Time.push(node);
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

		vector<Edge<T>> Fleury_algorythm(int node) {
			vector<Edge<T>> Edge_list_Save(Edge_list);
			vector<vector<T>> S_matrix_save(S_matrix); 
			vector<vector<pair<int, T>>> S_list_save(S_list);
			vector<Edge<T>> Result;
			Edge<T> res;
			int Temp = node;
			while(Edge_list.size() > 0) {
				for(int j = 0; j < S_list[Temp].size(); j ++) {
					if(!Is_bridge(Temp, S_list[Temp][j].first)) {
						res.first = Temp;
						res.second = S_list[Temp][j].first;
						T t1 = S_list[Temp][j].first;
						delete_edge(Temp, S_list[Temp][j].first);
						Temp = t1;
						Result.push_back(res);
						break;
					}
					else if(S_list[Temp].size() == 1) {
						res.first = Temp;
						res.second = S_list[Temp][j].first;
						Result.push_back(res);
						T t1 = S_list[Temp][j].first;
						delete_edge(Temp, S_list[Temp][j].first);
						Temp = t1;
						break;
					}
				}
			}
			Edge_list = Edge_list_Save;
			S_matrix = S_matrix_save;
			S_list = S_list_save;
			return Result;
		}
		

		bool Is_bridge(T v, T v1){
			vector<Edge<T>> temp_edge(Edge_list);
			vector<vector<T>> S_matrix_save(S_matrix); 
			vector<vector<pair<int, T>>> S_list_save(S_list);
			vector<T> first = breadth_first_search(v);	
			delete_edge(v, v1);
			vector<T> second = breadth_first_search(v);
			Edge_list = temp_edge;
			S_matrix = S_matrix_save;
			S_list = S_list_save;
			if(first.size() == second.size()) return false;
			else return true;
		}

		void delete_edge(T v, T v1){
			S_matrix[v][v1] = 0;
			S_matrix[v1][v] = 0;
			convert_to_edge();
			convert_to_list();
		}

		vector<int> FindEulerPath(int node) {
			vector<Edge<T>> Edge_list_Save(Edge_list);
			vector<vector<T>> S_matrix_save(S_matrix); 
			vector<vector<pair<int, T>>> S_list_save(S_list);
			vector<int> Result;
			FindEulerPathRec(node, Result);
			Edge_list = Edge_list_Save;
			S_matrix = S_matrix_save;
			S_list = S_list_save;
			return Result;
		}

		void FindEulerPathRec(int node, vector<int>& Result) {
			for(int i = 0; i < S_list[node].size(); i ++) {
				T t1 = S_list[node][i].first;
				delete_edge(node, S_list[node][i].first);
				FindEulerPathRec(t1, Result);
			}
			Result.push_back(node);
		}

		void depth_first_search(int node, vector<bool>& visit){
			vector<T> result;
			result.push_back(node);
			visit[node] = true;
			for(int i = 0; i < S_list[node].size(); i ++) {
				if(visit[S_list[node][i].first] == false) dfs_rec(S_list[node][i].first, visit, result);
				}
			for(int i = 0; i < result.size(); i ++) cout<<result[i];	
			// return result;	
			}


		void Kosaraju_Algorythm() {
			vector<bool> Visit(S_matrix[0].size(), false);
			stack<int> Stack;
			int temp;
			Matrix_transp();
			for(int i = 0; i < Visit.size(); i++) {
				if(Visit[i] == false) dfs_inv(Stack, Visit, i);
			}
			Matrix_transp();
			for(int i = 0; i < Visit.size(); i ++) Visit[i] = false;
			while(Stack.size() > 0) {
				temp = Stack.top();
				Stack.pop();
				if(Visit[temp] == false) {
					depth_first_search(temp, Visit);
					cout<<endl;	
					}
				}	

		}

		void Matrix_transp() {
			for(int i = 0; i < S_matrix.size();i ++) {
				for(int j = i; j < S_matrix[i].size(); j++) {
				swap(S_matrix[i][j], S_matrix[j][i]);
				}
			}
			convert_to_edge();
			convert_to_list();
		}


		void swap(T& a, T& b) {
			T temp;
			temp = a;
			a = b;
			b = temp;
		}

		void dfs_rec(int node, vector<bool>& visit, vector<T>& result){
			result.push_back(node);	
			visit[node] = true;
			for(int i = 0; i < S_list[node].size(); i ++) {
				if(visit[S_list[node][i].first] == false) dfs_rec(S_list[node][i].first, visit, result);
				}
		}


};		