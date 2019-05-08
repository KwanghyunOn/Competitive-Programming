// Hopcroft-Karp
// in: n, m, graph
// out: match, matched
// vertex cover: (reached[0][left_node] == 0) || (reached[1][right_node] == 1)

struct BipartiteMatching {
	int n, m;
	vector<vector<int>> graph;
	vector<int> match, matched;
	vector<int> level;
	vector<int> edgeview;
	vector<int> reached[2];
	BipartiteMatching(int n, int m) : n(n), m(m), graph(n), match(n, -1), matched(m, -1) {}


	void addEdge(int u, int v) {
		graph[u].push_back(v);
	}


	bool assignLevel() {
		bool reachable = false;
		level.assign(n, -1);
		reached[0].assign(n, 0);
		reached[1].assign(m, 0);
		queue<int> q;

		for(int i = 0; i < n; i++) {
			if(match[i] == -1) {
				level[i] = 0;
				reached[0][i] = 1;
				q.push(i);
			}
		}

		while(!q.empty()) {
			int cur = q.front(); q.pop();
			for(auto adj : graph[cur]) {
				reached[1][adj] = 1;
				int next = matched[adj];
				if(next == -1) {
					reachable = true;
				} else if(level[next] == -1) {
					reached[0][next] = 1;
					level[next] = level[cur] + 1;
					q.push(next);
				}
			}
		}

		return reachable;
	}


	int findPath(int cur) {
		for(int &i = edgeview[cur]; i < graph[cur].size(); i++) {
			int adj = graph[cur][i];
			int next = matched[adj];
			if(next >= 0 && level[next] != level[cur] + 1) continue;
			if(next == -1 || findPath(next)) {
				match[cur] = adj;
				matched[adj] = cur;
				return 1;
			}
		}
		return 0;
	}


	int solve() {
		int ans = 0;
		while(assignLevel()) {
			edgeview.assign(n, 0);
			for(int i = 0; i < n; i++)
				if(match[i] == -1)
					ans += findPath(i);
		}
		return ans;
	}
};
