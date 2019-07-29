vector<int> adj[MAXN], rev[MAXN], order;
bool vis[MAXN];
int ci[MAXN];

void dfs(int v) {
	for(auto c : adj[v]) if(!vis[c]) {
		vis[c] = true;
		dfs(c);
	}
	order.push_back(v);
}

void rev_dfs(int v, int id) {
	ci[v] = id;
	for(auto c : rev[v]) if(!vis[c]) {
		vis[c] = true;
		rev_dfs(c, id);
	}
}

int SCC() {
	for(int v = 1; v <= n; v++)
		if(!vis[v]) vis[v] = true, dfs(v);
	reverse(order.begin(), order.end());
	for(int v = 1; v <= n; v++) vis[v] = false;
	int sz = 0;
	for(int v : order)
		if(!vis[v]) vis[v] = true, rev_dfs(v, ++sz);
	return sz;
}
