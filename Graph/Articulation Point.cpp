int num[MAXN], low[MAXN], cur;
bool cut[MAXN];
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
		}
	}
	if(p == -1 && child > 1) cut[v] = true;
}
