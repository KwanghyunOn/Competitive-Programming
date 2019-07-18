const int MAXN = 10050;

vector<int> adj[2 * MAXN], rev[2 * MAXN];
int component[2 * MAXN], indeg[2 * MAXN], num[2 * MAXN];
vector<int> cmp[2 * MAXN], order, topo;
set<int> sEdge[2 * MAXN];
bool vis[2 * MAXN];
int n;

int node(int x) {
	if(x < 0)
		return 2 * (-x) - 1;
	else
		return 2 * x - 2;
}

void dfs(int node) {
	if(vis[node]) return;
	vis[node] = true;
	for(auto &cnode : adj[node])
		dfs(cnode);
	order.pb(node);
}

void rev_dfs(int node, int cnt) {
	if(vis[node]) return;
	vis[node] = true;
	cmp[cnt].pb(node);
	component[node] = cnt;
	for(auto &cnode : rev[node])
		rev_dfs(cnode, cnt);
}

void topSort(int node) {
	if(vis[node]) return;
	vis[node] = true;
	for(auto &cnode : sEdge[node])
		topSort(cnode);
	topo.pb(node);
}

int main() {
	int m;
	geti(n, m);
	while(m--) {
		int a, b;
		geti(a, b);
		adj[node(-a)].pb(node(b));
		rev[node(b)].pb(node(-a));
		adj[node(-b)].pb(node(a));
		rev[node(a)].pb(node(-b));
	}

  // Kosaju start
	rep(i, 2 * n) {
		if(!vis[i])
			dfs(i);
	}
	memset(vis, 0, sizeof vis);
	reverse(all(order));
	int cnt = 0;
	for(auto &node : order) {
		if(!vis[node]) {
			rev_dfs(node, cnt);
			cnt++;
		}
	}
	// Kosaju end

  // Check possibility
	rep(i, n) {
		if(component[2*i] == component[2*i + 1]) {
			cout << 0;
			return 0;
		}
	}
	
	// find SCC edges
	rep(start, 2*n) {
		for(auto &end : adj[start]) {
			if(component[start] != component[end]) {
				sEdge[component[start]].insert(component[end]);
				indeg[component[end]]++;
			}
		}
	}

  // Topological Sort
	memset(vis, 0, sizeof vis);
	rep(i, cnt) {
		if(indeg[i] == 0)
			topSort(i);
	}
	reverse(all(topo));
	rep(i, cnt) {
		num[topo[i]] = i;
	}
	
	cout << 1 << endl;
	rep(i, n) {
		int c1 = component[2 * i];
		int c2 = component[2 * i + 1];
		if(num[c1] < num[c2]) {
			cout << 0 << " ";
		} else {
			cout << 1 << " ";
		}
	}
}
