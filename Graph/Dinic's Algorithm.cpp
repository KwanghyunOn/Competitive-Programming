// https://github.com/kcm1700/algorithms/blob/master/graph/maxflow.cpp#L89

// MaxFlowDinic::init(n);
// MaxFlowDinic::addEdge(0, 1, 100, 100); // for bidirectional edge
// MaxFlowDinic::addEdge(1, 2, 100); // directional edge
// result = MaxFlowDinic::solve(0, 2); // source -> sink
// graph[i][edgeIndex].cap -> residual capacity
//
// in order to find out the minimum cut, use `l'.
// if l[i] == 0, i is unreachable.

struct MaxFlowDinic {
	typedef long long flow_t;

	struct Edge {
		int to, ri;
		flow_t cap;
	};

	int n;
	vector<vector<Edge>> graph;
	vector<int> l, start;

	void init(int sz) {
		n = sz;
		graph.resize(n);
		for(int i = 0; i < n; i++)
			graph[i].clear();
	}
	
	void addNodes(int cnt) {
		n += cnt;
		graph.resize(n);
	}

	void addEdge(int s, int e, flow_t cap, flow_t caprev = 0) {
		Edge forward = {e, (int)graph[e].size(), cap};
		Edge reverse = {s, (int)graph[s].size(), caprev};
		graph[s].push_back(forward);
		graph[e].push_back(reverse);
	}

	bool assignLevel(int source, int sink) {
		memset(&l[0], 0, sizeof(l[0]) * l.size());
		l[source] = 1;
		queue<int> que;
		que.push(source);
		while(!que.empty() && !l[sink]) {
			int v = que.front(); que.pop();
			for(auto c : graph[v]) {
				if(c.cap == 0 || l[c.to]) continue;
				l[c.to] = l[v] + 1;
				que.push(c.to);
			}
		}
		return l[sink] != 0;
	}

	flow_t blockFlow(int v, int sink, flow_t currentFlow) {
		if(v == sink) return currentFlow;
		for(int &i = start[v]; i < (int)graph[v].size(); i++) {
			Edge &c = graph[v][i];
			if(c.cap == 0 || l[c.to] != l[v] + 1) continue;
			if(flow_t f = blockFlow(c.to, sink, min(currentFlow, c.cap))) {
				graph[v][i].cap -= f;
				graph[c.to][c.ri].cap += f;
				return f;
			}
		}
		return 0;
	}

	flow_t solve(int source, int sink) {
		l.resize(n), start.resize(n);
		flow_t maxFlow = 0;
		while(assignLevel(source, sink)) {
			memset(&start[0], 0, sizeof(start[0]) * start.size());
			while(flow_t f = blockFlow(source, sink, numeric_limits<flow_t>::max()))
				maxFlow += f;
		}
		return maxFlow;
	}
};
