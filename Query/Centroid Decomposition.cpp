struct Node {
	int to;
	ll weight;
};

const int MAXN = 2e5 + 50;
vector<Node> adj[MAXN];

bool vis[MAXN];
int sz[MAXN];
void dfsSize(int v, int p) {
	sz[v] = 1;
	for(auto c : adj[v]) if(!vis[c.to] && c.to != p) {
		dfsSize(c.to, v);
		sz[v] += sz[c.to];
	}
}

int dfsCentroid(int v, int p, int size) {
	for(auto c : adj[v])
		if(!vis[c.to] && c.to != p && sz[c.to] > size/2)
			return dfsCentroid(c.to, v, size);
	return v;
}


void solve(int ctr) {}

void decompose(int v) {
	dfsSize(v, -1);
	int ctr = dfsCentroid(v, -1, sz[v]);
	solve(ctr);
	vis[ctr] = true;
	for(auto c : adj[ctr])
		if(!vis[c.to]) decompose(c.to);
}
