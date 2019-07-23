struct BipartiteMatching {
	int n, m;
	vector<vector<int>> graph;
	vector<int> A, B;
	vector<bool> vis;
	BipartiteMatching(int n, int m) : n(n), m(m), graph(n), A(n, -1), B(m, -1), vis(n, false) {}

	void addEdge(int u, int v) {
		graph[u].push_back(v);
	}

	bool dfs(int a) {
		vis[a] = true;
		for(auto b : graph[a]) {
			if(B[b] == -1 || (!vis[B[b]] && dfs(B[b]))) {
				A[a] = b;
				B[b] = a;
				return true;
			}
		}
		return false;
	}

	int flow() {
		int f = 0;
		for(int i = 0; i < n; i++) {
			fill(vis.begin(), vis.end(), false);
			if(dfs(i)) f++;
		}
		return f;
	}
};
