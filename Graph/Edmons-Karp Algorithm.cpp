struct MaximumFlow_EdmondsKarp {
	struct Edge {
		int to, cap;
		Edge *rev;
		Edge(int to, int cap) : to(to), cap(cap) {}
	};

	int n, source, sink;
	vector<vector<Edge*>> graph;

	MaximumFlow_EdmondsKarp(int n, int source, int sink) : n(n), source(source), sink(sink) {
		graph.resize(n);
	}

	void addEdge(int u, int v, int cap) {
		Edge *forward = new Edge(v, cap);
		Edge *reverse = new Edge(u, 0);
		forward->rev = reverse;
		reverse->rev = forward;
		graph[u].push_back(forward);
		graph[v].push_back(reverse);
	}
	
	int bfs() {
		vector<bool> check(n, false);
		vector<pair<int, int>> from(n, {-1, -1});

		queue<int> q;
		q.push(source);
		check[source] = true;
		while(!q.empty()) {
			int x = q.front();
			q.pop();
			for(int i = 0; i < graph[x].size(); i++) {
				Edge *e = graph[x][i];
				if(e->cap > 0 && !check[e->to]) {
					q.push(e->to);
					check[e->to] = true;
					from[e->to] = {x, i};
				}
			}
		}

		if(!check[sink])
			return 0;

		int x = sink;
		int c = graph[from[x].first][from[x].second]->cap;
		while(from[x].first != -1) {
			c = min(c, graph[from[x].first][from[x].second]->cap);
			x = from[x].first;
		}

		x = sink;
		while(from[x].first != -1) {
			Edge *e = graph[from[x].first][from[x].second];
			e->cap -= c;
			e->rev->cap += c;
			x = from[x].first;
		}
		return c;
	}

	int flow() {
		int ans = 0;
		while(true) {
			int f = bfs();
			if(f == 0) break;
			ans += f;
		}
		return ans;
	}
};
