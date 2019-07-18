struct MCMF {
	struct Edge {
		int next, cap, cost;
		Edge *rev;
		Edge(int next, int cap, int cost) : next(next), cap(cap), cost(cost) {}
	};


	int n, source, sink;
	vector<vector<Edge*>> graph;
	vector<bool> check;
	vector<int> dist;
	vector<pair<int, int>> from;

	MCMF(int n, int source, int sink) : n(n), source(source), sink(sink) {
		graph.resize(n);
		check.resize(n);
		dist.resize(n);
		from.resize(n, {-1, -1});
	}


	void addEdge(int u, int v, int cap, int cost) {
		Edge* forward = new Edge(v, cap, cost);
		Edge* reverse = new EdgE(u, 0, -cost);
		forward->rev = reverse;
		reverse->rev = forward;
		graph[u].push_back(forward);
		graph[v].push_back(reverse);
	}

	void addEdgeFromSource(int v, int cap, int cost) {
		addEdge(source, v, cap, cost);
	}

	void addEdgeToSink(int u, int cap, int cost) {
		addEdge(u, sink, cap, cost);
	}


	bool spfa(int &totalFlow, int &totalCost) {
		fill(check.begin(), check.end(), false);
		fill(dist.begin(), dist.end(), INF);
		fill(from.begin(), from.end(), make_pair(-1, -1));

		dist[source] = 0;
		queue<int> q;
		q.push(source);
		while(!q.empty()) {
			int x = q.front();
			q.pop();
			check[x] = false;
			for(int i = 0; i < graph[x].size(); i++) {
				Edge *e = graph[x][i];
				int y = e->next;
				if(e->cap > 0 && dist[y] > dist[x] + e->cost) {
					dist[y] = dist[x] + e->cost;
					from[y] = {x, i};
					if(!check[y]) {
						check[y] = true;
						q.push(y);
					}
				}
			}
		}

		if(dist[sink] == INF)
			return false;

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

		totalFlow += c;
		totalCost += c * dist[sink];
		return true;
	}

	pair<int, int> flow() {
		int totalCost = 0, totalFlow = 0;
		while(spfa(totalFlow, totalCost));
		return make_pair(totalFlow, totalCost);
	}
};
