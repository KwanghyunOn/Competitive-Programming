struct Edge {
	int to, weight, ri;
};
vector<Edge> adj[MAXN];


// Centroid Decomposition
int sz[MAXN];
void dfsSize(int v, int p) {
	sz[v] = 1;
	for(auto c : adj[v]) if(c.to != p) {
		dfsSize(c.to, v);
		sz[v] += sz[c.to];
	}
}

int dfsCentroid(int v, int p, int size) {
	for(auto c : adj[v]) {
		if(c.to != p && sz[c.to] > size/2)
			return dfsCentroid(c.to, v, size);
	}
	return v;
}

void decompose(int v, int &ans) {
	dfsSize(v, -1);
	int ctr = dfsCentroid(v, -1, sz[v]);
	solve(ctr);

	for(auto c : adj[ctr]) {
		// erase edge of ctr
		swap(adj[c.to][c.ri], adj[c.to].back());
		int v =	adj[c.to][c.ri].to;
		int id = adj[c.to][c.ri].ri;
		adj[v][id].ri = c.ri;
		adj[c.to].pop_back();

		decompose(c.to, ans);
	}
	adj[ctr].clear();
}
