vector<int> adj[MAXN], rev[MAXN];

vector<int> order;
bool vis[MAXN];
int component[MAXN];
vector<int> cp[MAXN];

void dfs(int node) {
	if(vis[node]) return;
	vis[node] = true;
	for(auto &cnode : adj[node])
		dfs(cnode);
	order.pb(node);
}

// initialize vis[] before calling this function
void rev_dfs(int node, int cpNum) {
	if(vis[node]) return;
	vis[node] = true;
	component[node] = cpNum;
	for(auto cnode : rev[node])
		rev_dfs(cnode, cpNum);
}

int main() {
	int n, E;
	geti(n, E);
	rep(i, E) {
		int u, v;
		geti(u, v);
		adj[u].pb(v);
		rev[v].pb(u);
	}

  // Step 1
	repp(i, n) {
		if(!vis[i])
			dfs(i);
	}
	reverse(all(order));
	fill(vis + 1, vis + n + 1, 0);
	
	// Step 3
	int cnt = 0;
	rep(i, n) {
		if(component[order[i]] == 0) {
			cnt++;
			rev_dfs(order[i], cnt);
		}
	}

	cout << cnt << endl;
	vector<vector<int>> ans(cnt);
	repp(i, n) {
		ans[component[i] - 1].pb(i);
	}
	sort(all(ans));
	for(auto v : ans) {
		for(auto e : v) {
			cout << e << " ";
		}
		cout << -1 << endl;
	}
}
