struct MCMF {
	typedef long long flow_t;

	struct Edge {
		int to, ri;
		flow_t cap, cost;
	};

	int n;
	vector<vector<Edge>> graph;
	vector<int> pv, pe;
	vector<flow_t> dist;
	vector<bool> inq;

	void init(int sz) {
		n = sz;
		graph.resize(n);
		pv.resize(n), pe.resize(n);
		dist.resize(n), inq.resize(n);
	}

	void addEdge(int s, int e, flow_t cap, flow_t cost) {
		Edge forward = {e, (int)graph[e].size(), cap, cost};
		Edge reverse = {s, (int)graph[s].size(), 0, -cost};
		graph[s].push_back(forward);
		graph[e].push_back(reverse);
	}

	bool spfa(int source, int sink, flow_t &totalFlow, flow_t &totalCost) {
		fill(dist.begin(), dist.end(), IINF);
		fill(inq.begin(), inq.end(), false);

		queue<int> que;
		que.push(source);
		dist[source] = 0, inq[source] = true;
		while(!que.empty()) {
			int v = que.front(); que.pop();
			inq[v] = false;
			for(int i = 0; i < (int)graph[v].size(); i++) {
				Edge &e = graph[v][i];
				if(e.cap > 0 && dist[e.to] > dist[v] + e.cost) {
					dist[e.to] = dist[v] + e.cost;
					pv[e.to] = v, pe[e.to] = i;
					if(!inq[e.to])
						que.push(e.to), inq[e.to] = true;
				}
			}
		}

		if(dist[sink] == IINF) return false;
		// add this limit when we don't require maxflow
		// if( dist[sink] > 0 ) return false;

		flow_t blockFlow = numeric_limits<flow_t>::max();
		for(int v = sink; v != source; v = pv[v])
			blockFlow = min(blockFlow, graph[pv[v]][pe[v]].cap);

		for(int v = sink; v != source; v = pv[v]) {
			int ri = graph[pv[v]][pe[v]].ri;
			graph[pv[v]][pe[v]].cap -= blockFlow;
			graph[v][ri].cap += blockFlow;
		}
		totalFlow += blockFlow;
		totalCost += blockFlow * dist[sink];
		return true;
	}

	pair<flow_t, flow_t> solve(int source, int sink) {
		flow_t totalFlow = 0, totalCost = 0;
		while(spfa(source, sink, totalFlow, totalCost));
		return make_pair(totalFlow, totalCost);
	}
};
