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
		int next;
		int inv;		// inverse edge index
		flow_t cap;		// residual capacity
	};

	int n;
	vector<vector<Edge>> graph;

	vector<int> l, start;

	void init(int _n) {
		n = _n;
		graph.resize(n);
		for(int i = 0; i < n; i++) graph[i].clear();
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
		queue<int> q;
		q.push(source);
		while(!q.empty() && !l[sink]) {
			int cur = q.front(); q.pop();
			for(int i = 0; i < graph[cur].size(); i++) {
				int next = graph[cur][i].next;
				if(l[next]) continue;
				if(graph[cur][i].cap > 0) {
					l[next] = l[cur] + 1;
					q.push(next);
				}
			}
		}
		return l[sink] != 0;
	}


	flow_t blockFlow(int cur, int sink, flow_t currentFlow) {
		if(cur == sink) return currentFlow;
		for(int &i = start[cur]; i < graph[cur].size(); i++) {
			int next = graph[cur][i].next;
			if(graph[cur][i].cap == 0 || l[next] != l[cur] + 1)
				continue;
			if(flow_t f = blockFlow(next, sink, min(graph[cur][i].cap, currentFlow))) {
				int inv = graph[cur][i].inv;
				graph[cur][i].cap -= f;
				graph[next][inv].cap += f;
				return f;
			}
		}
		return 0;
	}


	flow_t solve(int source, int sink) {
		l.resize(n);
		start.resize(n);
		flow_t ans = 0;
		while(assignLevel(source, sink)) {
			memset(&start[0], 0, sizeof(start[0]) * start.size());
			while(flow_t flow = blockFlow(source, sink, numeric_limits<flow_t>::max()))
				ans += flow;
		}
		return ans;
	}
};
