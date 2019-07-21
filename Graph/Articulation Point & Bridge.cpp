int num[MAXN], low[MAXN], cur;
bool cut[MAXN];		// cut[v]: true if v is articulation point
vector<pii> bridge;	// list of bridges
void dfs(int v, int p) {
	int child = 0;
	low[v] = num[v] = ++cur;
	for(auto c : adj[v]) if(c != p) {
		if(num[c]) low[v] = min(low[v], num[c]);
		else {
			child++;
			dfs(c, v);
			low[v] = min(low[v], low[c]);
			if(p != -1 && low[c] >= num[v]) cut[v] = true;
			if(low[c] > num[v]) bridge.emplace_back(min(v, c), max(v, c));
		}
	}
	if(p == -1 && child > 1) cut[v] = true;
}
