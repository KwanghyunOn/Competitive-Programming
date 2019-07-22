vector<int> adj[2*MAXN], rev[2*MAXN];
int n, m;
inline int f(int x) { return (x > 0) ? x : -x+n; }
void addEdge(int a, int b) {
	adj[f(-a)].push_back(f(b));
	rev[f(b)].push_back(f(-a));
	adj[f(-b)].push_back(f(a));
	rev[f(a)].push_back(f(-b));
}

void readInput() {
	scanf("%d%d", &n, &m);
	rep(i, m) {
		int a, b; scanf("%d%d", &a, &b);
		addEdge(a, b);
	}
}


bool vis[2*MAXN];
void dfs(int v, vector<int> &order) {
	for(auto c : adj[v]) if(!vis[c]) {
		vis[c] = true;
		dfs(c, order);
	}
	order.push_back(v);
}

int ci[2*MAXN];
void rev_dfs(int v, int id) {
	ci[v] = id;
	for(auto c : rev[v]) if(!vis[c]) {
		vis[c] = true;
		rev_dfs(c, id);
	}
}

int SCC() {
	vector<int> order;
	repp(v, 2*n) if(!vis[v]) vis[v] = true, dfs(v, order);
	repp(v, 2*n) vis[v] = false;
	reverse(order.begin(), order.end());
	int sz = 0;
	for(auto v : order) if(!vis[v]) vis[v] = true, rev_dfs(v, ++sz);
	return sz;
}

set<int> sadj[2*MAXN];
void findSCCEdge() {
	repp(v, 2*n) {
		for(auto c : adj[v])
			if(ci[v] != ci[c]) sadj[ci[v]].insert(ci[c]);
	}
}

void scc_dfs(int x, vector<int> &topsort) {
	for(auto y : sadj[x]) if(!vis[y]) {
		vis[y] = true;
		scc_dfs(y, topsort);
	}
	topsort.push_back(x);
}
